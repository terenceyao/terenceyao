// 作者：温水里的青蛙（QQ:253693763）
// 先导入Brain-master.zip库
#include <Brain.h>

Brain brain(Serial); // 不能使用软串口，波特率太高数据丢失严重；Arduino Uno只有一个串口，因此在写入程序时要将蓝牙主机断电，避免影响程序写入。
const int signalLedPin = 13; // 用作信号指示灯
// 状态LED
const int ledPin1 = 2;
const int ledPin2 = 3;
const int ledPin3 = 4;
const int ledPin4 = 5;

void setup() {
  pinMode(signalLedPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  Serial.begin(57600); // 务必修改为57600，Brain-master库中的实例都是针对Mind Flex所以实例中均设置为9600。
}
// 判断是否有信号
boolean hasSignal(int signal) {
  if (signal == 29 || signal == 54 || signal == 55 || signal == 56 || signal == 80 || signal == 81 || signal == 82 || signal == 107 || signal == 200)
    return false;
  else
    return true;
}

void loop() {
  if (brain.update()) { // loop中不断调用update方法解析字节流，当解析到一个完整的包则返回为ture。
    if (hasSignal(brain.readSignalQuality())) { // 有信号时
      digitalWrite(signalLedPin, HIGH); // 信号灯点亮
      int value = brain.readAttention(); // 读取注意力或者冥想度
      if (value > 80) {
        digitalWrite(ledPin4, HIGH);
      } else {
        digitalWrite(ledPin4, LOW);
      }
      if (value > 60) {
        digitalWrite(ledPin3, HIGH);
      } else {
        digitalWrite(ledPin3, LOW);
      }
      if (value > 40) {
        digitalWrite(ledPin2, HIGH);
      } else {
        digitalWrite(ledPin2, LOW);
      }
      if (value > 20) {
        digitalWrite(ledPin1, HIGH);
      } else {
        digitalWrite(ledPin1, LOW);
      }
    } else {
      digitalWrite(signalLedPin, LOW);
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);
    }
  }
}
