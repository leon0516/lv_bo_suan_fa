/*
A、名称：算术平均滤波法
B、方法：
    连续取N个采样值进行算术平均运算：
    N值较大时：信号平滑度较高，但灵敏度较低；
    N值较小时：信号平滑度较低，但灵敏度较高；
    N值的选取：一般流量，N=12；压力：N=4。
C、优点：
    适用于对一般具有随机干扰的信号进行滤波；
    这种信号的特点是有一个平均值，信号在某一数值范围附近上下波动。
D、缺点：
    对于测量速度较慢或要求数据计算速度较快的实时控制不适用；
    比较浪费RAM。
E、整理：shenhaiyu 2013-11-01
*/
 
int Filter_Value;
 
void setup() {
  Serial.begin(9600);       // 初始化串口通信
  randomSeed(analogRead(0)); // 产生随机种子
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
 
// 算术平均滤波法
#define FILTER_N 12
int Filter() {
  int i;
  int filter_sum = 0;
  for(i = 0; i < FILTER_N; i++) {
    filter_sum += Get_AD();
    delay(1);
  }
  return (int)(filter_sum / FILTER_N);
}
