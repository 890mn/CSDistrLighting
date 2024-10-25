#include <ESP8266WiFi.h>
#include <espnow.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <PID_v1.h>
#define NUMPIXELS 24  //灯珠数量
#define PIN 4    //灯珠连接的IO
#define DEADBAND 5     // 死区范围

uint8_t R = 0;
uint8_t G = 0;
uint8_t B = 0;
bool modeSwitch=false;
uint16_t light=0;
uint8_t power=50;
bool powerStatus=false;
uint16_t kelvin=4000;
uint16_t luminance=400;
bool previousState = false; // 假设这是一个全局变量

// 定义 PID 参数
double Input, Output, Setpoint;
double Kp = 0.02, Ki = 0.05, Kd = 0.01;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

double smoothOutput = 0; // 初始平滑输出值
double alpha = 0.2; // 平滑系数

StaticJsonDocument<185> doc;

// RGB灯带函数
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void kelvinToRGB(uint16_t K) 
{
  if(K<2700 || K > 6500){
    return;
  }
  float temp = K / 100.0;
  float red, green, blue;

  if (temp <= 66) {
    red = 255;
    green = temp;
    green = 99.4708025861 * log(green) - 161.1195681661;

    if (temp <= 19) {
      blue = 0;
    } else {
      blue = temp - 10;
      blue = 138.5177312231 * log(blue) - 305.0447927307;
    }
  } else {
    red = temp - 60;
    red = 329.698727446 * pow(red, -0.1332047592);
    green = temp - 60;
    green = 288.1221695283 * pow(green, -0.0755148492);
    blue = 255;
  }

  // 根据Arduino的要求，确保RGB值位于0到255之间
  R = constrain(red, 0, 255);
  G = constrain(green, 0, 255);
  B = constrain(blue, 0, 255);
}


void setPower(uint8_t P)
{
  strip.setBrightness(P);
}

void setRGB(uint8_t red,uint8_t green,uint8_t blue)
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    strip.setPixelColor(i, R, G, B);
  }
}

//开灯函数
void On()
{
  setPower(100);
  setRGB(R,G,B);
  strip.show();
}
//关灯函数
void Off()
{
  setPower(0);
  setRGB(0,0,0);
  strip.show();
}


//接收信息时的回调函数，每次接收信息会自动调用该函数
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  // 打印接收到的数据
  Serial.print("Received: ");
  for(int i = 0; i < len; ++i) {
    Serial.printf("%c", *(incomingData + i));  
  }
  Serial.println(); // 使用println来结束行，而不是打印一个空格
  
  // 尝试反序列化JSON
  DeserializationError error = deserializeJson(doc, incomingData, len);
  
  if (!error) {
    modeSwitch = doc["on"];
    light = doc["light"];
    power = doc["power"];
    powerStatus = doc["auto"];
    kelvin = doc["kelvin"];
    luminance = doc["luminance"];
    Input=light;
    Setpoint=luminance;
    if(modeSwitch != previousState) { // 检查状态是否改变
        if(modeSwitch) {
            On(); // 如果isOn变为true，打开设备
        } else {
            Off(); // 如果isOn变为false，关闭设备
        }
        previousState = modeSwitch; // 更新状态记录
    }
    // 打印解析得到的数据
     Serial.print("PreviousState: ");
     Serial.println(previousState);
     Serial.print("On: ");
     Serial.println(modeSwitch);
     Serial.print("Light: ");
     Serial.println(light);
     Serial.print("Power: ");
     Serial.println(power);
     Serial.print("Auto: ");
     Serial.println(powerStatus);
     Serial.print("Kelvin: ");
     Serial.println(kelvin);
     Serial.print("Luminance: ");
     Serial.println(luminance);
  } else {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
  }
}

void setup()
{
  Serial.begin(115200);

   // 初始化 PID 控制器
  myPID.SetMode(AUTOMATIC);
  // 设置采样周期（毫秒）
  myPID.SetSampleTime(1000); // 1秒采样一次
  


  kelvinToRGB(kelvin);
  WiFi.mode(WIFI_STA);//设置WIFI模式为STA
  WiFi.disconnect();//断开WIFI连接
  
  // Init ESP-NOW
  if (esp_now_init() != 0)//初始化espnow
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  Serial.println("esp_now init success");
  
  //执行完这个函数，每次接收数据就会自动调用回调函数了
  esp_now_register_recv_cb(OnDataRecv);

  strip.begin();
}

void loop()
{
  delay(1000);
  if(modeSwitch){ 
    if(powerStatus){
        // if ( < DEADBAND && output > -DEADBAND) {
        //   output = 0;
        // }
        myPID.Compute();
        setPower(Output);
        Serial.print("Input: ");
        Serial.println(Input);
        Serial.print("Output: ");
        Serial.println(Output);
        Serial.print("Setpoint: ");
        Serial.println(Setpoint);
    }else{
      setPower(map(power, 0, 100, 0, 255));
    }
    kelvinToRGB(kelvin);
    setRGB(R,G,B);
    strip.show();
  }
}
