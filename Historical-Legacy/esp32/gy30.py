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
