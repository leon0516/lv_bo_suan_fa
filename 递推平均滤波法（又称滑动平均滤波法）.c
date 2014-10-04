/*
A、名称：递推平均滤波法（又称滑动平均滤波法）
B、方法：
    把连续取得的N个采样值看成一个队列，队列的长度固定为N，
    每次采样到一个新数据放入队尾，并扔掉原来队首的一次数据（先进先出原则），
    把队列中的N个数据进行算术平均运算，获得新的滤波结果。
    N值的选取：流量，N=12；压力，N=4；液面，N=4-12；温度，N=1-4。
C、优点：
    对周期性干扰有良好的抑制作用，平滑度高；
    适用于高频振荡的系统。
D、缺点：
    灵敏度低，对偶然出现的脉冲性干扰的抑制作用较差；
    不易消除由于脉冲干扰所引起的采样值偏差；
    不适用于脉冲干扰比较严重的场合；
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
 
// 递推平均滤波法（又称滑动平均滤波法）
#define FILTER_N 12
int filter_buf[FILTER_N + 1];
int Filter() {
  int i;
  int filter_sum = 0;
  filter_buf[FILTER_N] = Get_AD();
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = filter_buf[i + 1]; // 所有数据左移，低位仍掉
    filter_sum += filter_buf[i];
  }
  return (int)(filter_sum / FILTER_N);
}
