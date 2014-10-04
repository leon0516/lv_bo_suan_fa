/*
A、名称：中位值滤波法
B、方法：
    连续采样N次（N取奇数），把N次采样值按大小排列，
    取中间值为本次有效值。
C、优点：
    能有效克服因偶然因素引起的波动干扰；
    对温度、液位的变化缓慢的被测参数有良好的滤波效果。
D、缺点：
    对流量、速度等快速变化的参数不宜。
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
 
// 中位值滤波法
#define FILTER_N 101
int Filter() {
  int filter_buf[FILTER_N];
  int i, j;
  int filter_temp;
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = Get_AD();
    delay(1);
  }
  // 采样值从小到大排列（冒泡法）
  for(j = 0; j < FILTER_N - 1; j++) {
    for(i = 0; i < FILTER_N - 1 - j; i++) {
      if(filter_buf[i] > filter_buf[i + 1]) {
        filter_temp = filter_buf[i];
        filter_buf[i] = filter_buf[i + 1];
        filter_buf[i + 1] = filter_temp;
      }
    }
  }
  return filter_buf[(FILTER_N - 1) / 2];
}
