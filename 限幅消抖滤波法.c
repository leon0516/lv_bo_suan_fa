/*
A、名称：限幅消抖滤波法
B、方法：
    相当于“限幅滤波法”+“消抖滤波法”；
    先限幅，后消抖。
C、优点：
    继承了“限幅”和“消抖”的优点；
    改进了“消抖滤波法”中的某些缺陷，避免将干扰值导入系统。
D、缺点：
    对于快速变化的参数不宜。
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
 
// 限幅消抖滤波法
#define FILTER_A 1
#define FILTER_N 5
int i = 0;
int Filter() {
  int NewValue;
  int new_value;
  NewValue = Get_AD();
  if(((NewValue - Value) > FILTER_A) || ((Value - NewValue) > FILTER_A))
    new_value = Value;
  else
    new_value = NewValue;
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
