/*
A、名称：加权递推平均滤波法
B、方法：
    是对递推平均滤波法的改进，即不同时刻的数据加以不同的权；
    通常是，越接近现时刻的数据，权取得越大。
    给予新采样值的权系数越大，则灵敏度越高，但信号平滑度越低。
C、优点：
    适用于有较大纯滞后时间常数的对象，和采样周期较短的系统。
D、缺点：
    对于纯滞后时间常数较小、采样周期较长、变化缓慢的信号；
    不能迅速反应系统当前所受干扰的严重程度，滤波效果差。
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
 
// 加权递推平均滤波法
#define FILTER_N 12
int coe[FILTER_N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};    // 加权系数表
int sum_coe = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 11 + 12; // 加权系数和
int filter_buf[FILTER_N + 1];
int Filter() {
  int i;
  int filter_sum = 0;
  filter_buf[FILTER_N] = Get_AD();
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = filter_buf[i + 1]; // 所有数据左移，低位仍掉
    filter_sum += filter_buf[i] * coe[i];
  }
  filter_sum /= sum_coe;
  return filter_sum;
}
