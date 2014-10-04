/*
A、名称：限幅滤波法（又称程序判断滤波法）
B、方法：
    根据经验判断，确定两次采样允许的最大偏差值（设为A），
    每次检测到新值时判断：
    如果本次值与上次值之差<=A，则本次值有效，
    如果本次值与上次值之差>A，则本次值无效，放弃本次值，用上次值代替本次值。
C、优点：
    能有效克服因偶然因素引起的脉冲干扰。
D、缺点：
    无法抑制那种周期性的干扰。
    平滑度差。
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
  Value = Filter_Value;          // 最近一次有效采样的值，该变量为全局变量
  Serial.println(Filter_Value); // 串口输出
  delay(50);
}
 
// 用于随机产生一个300左右的当前值
int Get_AD() {
  return random(295, 305);
}
 
// 限幅滤波法（又称程序判断滤波法）
#define FILTER_A 1
int Filter() {
  int NewValue;
  NewValue = Get_AD();
  if(((NewValue - Value) > FILTER_A) || ((Value - NewValue) > FILTER_A))
    return Value;
  else
    return NewValue;
}
