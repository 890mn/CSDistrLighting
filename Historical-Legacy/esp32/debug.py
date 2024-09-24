from machine import Pin,I2C,PWM,Timer
from ssd1306 import SSD1306_I2C
from gy30 import GY30
import bluetooth
import time
import json
import network
import espnow


device={
    "on":False,
    "light":0,
    "power":50,
    "auto":False,
    "kelvin":4000,
    "luminance":400,
}

sta = network.WLAN(network.STA_IF)  # Or network.AP_IF
sta.active(True)

e = espnow.ESPNow()
e.active(True)
peer = b'\xcc\x50\xe3\x74\xf5\x1a'
e.add_peer(peer)
e.send(peer,json.dumps(device))

class ESP32_BLE():
    def __init__(self, name):
        self.led = Pin(2, Pin.OUT)
        self.timer1 = Timer(0)
        self.name = name
        self.ble = bluetooth.BLE()
        self.ble.active(True)
        self.ble.config(gap_name=name)
        self.ble.config(mtu=185)
        self.disconnected()
        self.ble.irq(self.ble_irq)
        self.register()
        self.ble.gatts_set_buffer(self.cx,185)
        self.advertiser()
        self.is_connected=False

    def connected(self):
        self.led.value(1)
        self.timer1.deinit()
        self.is_connected=True

    def disconnected(self):
        self.is_connected=False
        self.timer1.init(period=100, mode=Timer.PERIODIC, callback=lambda t: self.led.value(not self.led.value()))

    def ble_irq(self, event, data):
        global device
        if event == 1: #_IRQ_CENTRAL_CONNECT 手机链接了此设备
            self.connected()
        elif event == 2: #_IRQ_CENTRAL_DISCONNECT 手机断开此设备
            self.advertiser()
            self.disconnected()
        elif event == 3: #_IRQ_GATTS_WRITE 手机发送了数据 
            buffer = self.ble.gatts_read(self.cx)
            ble_msg = buffer.decode('UTF-8').strip()
            print(ble_msg)
            if ble_msg == "0":
                self.send(f'[{json.dumps(device)}]')
            else:
                value=json.loads(ble_msg)
                device['on']=value['on']
                device['auto']=value['auto']
                device['power']=value['power']
                device['kelvin']=value['kelvin']
                device['luminance']=value['luminance']
            
            
    def register(self):        
        service_uuid = '6E400000-B5A3-F393-E0A9-E50E24DCCA9E'
        characteristic_uuid = '6E400001-B5A3-F393-E0A9-E50E24DCCA9E'

        services = (
            (
                bluetooth.UUID(service_uuid), 
                (
                    (bluetooth.UUID(characteristic_uuid), bluetooth.FLAG_NOTIFY | bluetooth.FLAG_WRITE_NO_RESPONSE), 
                )
            ), 
        )
        ((self.cx,), ) = self.ble.gatts_register_services(services)
        

    def send(self, data):
        print(data)
        self.ble.gatts_notify(0, self.cx, data)

    def advertiser(self):
        name = bytes(self.name, 'UTF-8')
        adv_data = bytearray(b'\x02\x01\x02') + bytearray((len(name) + 1, 0x09)) + name
        self.ble.gap_advertise(100, adv_data)
        print(adv_data)
        print("\r\n")


gy30_addr = 0x23  # 光线传感器I2C地址
oled_addr = 0x3c  # oled屏幕I2C地址

i2c = I2C(0,scl = Pin(19),sda = Pin(21),freq = 1_000_000)
i2c1 = I2C(1,scl = Pin(22),sda = Pin(23),freq = 1_000_000)
ble = ESP32_BLE("LIGHT-BLE")
oled = SSD1306_I2C(128,64,i2c1,oled_addr)  # 0.96寸分辨率128*64
oled.contrast(255) #0-255

gy30=GY30(i2c,gy30_addr)
def oled_control():
    device['light']=int(gy30.get_val())
    oled.fill(0)
    if device['on']:
        oled.text("Light On",0,0)  # 第一行显示gy-30 lighting
    else:
        oled.text("Light Off",0,0)  # 第一行显示gy-30 lighting
        
    if device['auto']:
        oled.text("Auto Mode",0,30)  # 第一行显示gy-30 lighting
    else:
        oled.text("Manuel Mode",0,30)  # 第一行显示gy-30 lighting
        
    oled.text(f"Light: {device['light']} Lx",0,10)  # 第二行显示* 259.33 Lx *
    oled.text(f"Power: {device['power']} %",0,20)  # 第二行显示* 259.33 Lx *
    oled.show()
    
        
def send_ble_data():
    if ble.is_connected:
        ble.send(json.dumps(device))
    

def send_espnow_data():
    e.send(peer,json.dumps(device))
        
 
def main():
    while True:
        oled_control()
        send_ble_data()
        send_espnow_data()
        time.sleep(1)
                
        
if __name__ == "__main__":
    main()

