/*
A、名称：消抖滤波法
B、方法：
    设置一个滤波计数器，将每次采样值与当前有效值比较：
    如果采样值=当前有效值，则计数器清零；
    如果采样值<>当前有效值，则计数器+1，并判断计数器是否>=上限N（溢出）；
    如果计数器溢出，则将本次值替换当前有效值，并清计数器。
C、优点：
    对于变化缓慢的被测参数有较好的滤波效果；
    可避免在临界值附近控制器的反复开/关跳动或显示器上数值抖动。
D、缺点：
    对于快速变化的参数不宜；
    如果在计数器溢出的那一次采样到的值恰好是干扰值,则会将干扰值当作有效值导入系统。
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
 
// 消抖滤波法
#define FILTER_N 12
int i = 0;
int Filter() {
  int new_value;
  new_value = Get_AD();
  if(Value != new_value) {
    i++;
    if(i > FILTER_N) {
      i = 0;
      Value = new_value;
    }
  }
  else
    i = 0;
  return Value;
}
