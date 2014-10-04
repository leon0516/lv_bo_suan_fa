/*
A、名称：一阶滞后滤波法
B、方法：
    取a=0-1，本次滤波结果=(1-a)*本次采样值+a*上次滤波结果。
C、优点：
    对周期性干扰具有良好的抑制作用；
    适用于波动频率较高的场合。
D、缺点：
    相位滞后，灵敏度低；
    滞后程度取决于a值大小；
    不能消除滤波频率高于采样频率1/2的干扰信号。
E、整理：shenhaiyu 2013-11-01
*/
 
int Filter_Value;
int Value;
 
void setup() {
  Serial.begin(9600);       // 初始化串口通信
  randomSeed(analogRead(0)); // 产生随机种子
  Value = 300;
}
 
void loop() {
  Filter_Value = Filter();       // 获得滤波器输出值
  Serial.println(Filter_Value); // 串口输出
  delay(50);
}
 
// 用于随机产生一个300左右的当前值
int Get_AD() {
  return random(295, 305);
}
 
// 一阶滞后滤波法
#define FILTER_A 0.01
int Filter() {
  int NewValue;
  NewValue = Get_AD();
  Value = (int)((float)NewValue * FILTER_A + (1.0 - FILTER_A) * (float)Value);
  return Value;
}
