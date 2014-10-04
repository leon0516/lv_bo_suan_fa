/*
A、名称：中位值平均滤波法（又称防脉冲干扰平均滤波法）
B、方法：
    采一组队列去掉最大值和最小值后取平均值，
    相当于“中位值滤波法”+“算术平均滤波法”。
    连续采样N个数据，去掉一个最大值和一个最小值，
    然后计算N-2个数据的算术平均值。
    N值的选取：3-14。
C、优点：
    融合了“中位值滤波法”+“算术平均滤波法”两种滤波法的优点。
    对于偶然出现的脉冲性干扰，可消除由其所引起的采样值偏差。
    对周期干扰有良好的抑制作用。
    平滑度高，适于高频振荡的系统。
D、缺点：
    计算速度较慢，和算术平均滤波法一样。
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
 
// 中位值平均滤波法（又称防脉冲干扰平均滤波法）（算法1）
#define FILTER_N 100
int Filter() {
  int i, j;
  int filter_temp, filter_sum = 0;
  int filter_buf[FILTER_N];
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
  // 去除最大最小极值后求平均
  for(i = 1; i < FILTER_N - 1; i++) filter_sum += filter_buf[i];
  return filter_sum / (FILTER_N - 2);
}
 
 
//  中位值平均滤波法（又称防脉冲干扰平均滤波法）（算法2）
/*
#define FILTER_N 100
int Filter() {
  int i;
  int filter_sum = 0;
  int filter_max, filter_min;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = Get_AD();
    delay(1);
  }
  filter_max = filter_buf[0];
  filter_min = filter_buf[0];
  filter_sum = filter_buf[0];
  for(i = FILTER_N - 1; i > 0; i--) {
    if(filter_buf[i] > filter_max)
      filter_max=filter_buf[i];
    else if(filter_buf[i] < filter_min)
      filter_min=filter_buf[i];
    filter_sum = filter_sum + filter_buf[i];
    filter_buf[i] = filter_buf[i - 1];
  }
  i = FILTER_N - 2;
  filter_sum = filter_sum - filter_max - filter_min + i / 2; // +i/2 的目的是为了四舍五入
  filter_sum = filter_sum / i;
  return filter_sum;
}*/
