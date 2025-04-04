# 最终烧录进去，自动运行的代码文件
from machine import Pin,I2C,PWM,Timer
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

class GY30:
    def __init__(self, i2c, addr=0x23):
        self.i2c = i2c
        self.addr = addr
        self.init()
        
    def init(self):
        self.i2c.writeto(self.addr,chr(0x01)) # 通电运行 
        self.i2c.writeto(self.addr,chr(0x07)) # 复位
        self.i2c.writeto(self.addr,chr(0x10)) # 横向分辨率连续读取 1 Lx 120ms
    
    def get_val(self):
        gy = self.i2c.readfrom(self.addr,2) #0-65535 1 8bit 2  int 16 char 8
        gy30 = float(gy[0] << 8 | gy[1])/1.2 #左移动，可以理解为乘法 gy[0]*0xff 
        return gy30

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

i2c = I2C(0,scl = Pin(19),sda = Pin(21),freq = 1_000_000)
i2c1 = I2C(1,scl = Pin(22),sda = Pin(23),freq = 1_000_000)
ble = ESP32_BLE("LIGHT-BLE")

gy30=GY30(i2c,gy30_addr)
    
        
def send_ble_data():
    if ble.is_connected:
        ble.send(json.dumps(device))
    

def send_espnow_data():
    e.send(peer,json.dumps(device))
        
 
def main():
    while True:
        #oled_control()
        send_ble_data()
        send_espnow_data()
        time.sleep(1)
        
        
if __name__ == "__main__":
    main()


