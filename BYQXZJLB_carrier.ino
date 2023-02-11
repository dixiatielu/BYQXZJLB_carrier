/*
  *
  * 四川大学 2023机器人方案设计大赛 白蚁庆喜终见陆冰队 Arduino搬运小车代码
  * 2023年5月前仅限本小组使用，他人不得抄袭、复制、复用本工程的任何部分！
  * 
  * copyright 2023 dixiatielu@BYQXZJLB
  * 
  * An open source software
  * with NO WANNARY
  * COMMERCIAL USAGE PROHIBITED | 禁止商用
*/


/*宏定义*/
// 接线时请严格按照下方定义的引脚编号接线
#define tracePort1 2	// 循迹引脚4个
#define tracePort2 4
#define tracePort3 12
#define tracePort4 13
#define leftMotor1 5 // 马达引脚4个
#define leftMotor2 6
#define rightMotor1 9
#define rightMotor2 10
#define steerPort 3// 舵机（机械臂）引脚
//剩下11和8，A0-A5(D14-19)

// TODO: RGB（两个）端口、超声波端口

/*函数定义*/
// 初始化串口
void initTracePorts(); // 初始化循迹模块串口
void initColorSensorPorts(); // 初始化RGB颜色传感器串口
void initMotorPorts(); // 初始化马达模块串口
void initSteerEngine(); // 初始化舵机串口
void initUltrasonicSensorPorts();// 初始化超声波传感器串口

// 行驶部分
void readTraceSensors(); // 读取循迹传感器数据
void setMotorSpeed(int, int, int, int); // 设置马达转速
void straightForward(); // 直行
void minorLeftFix(); // 向左微调
void minorRightFix();
void sharpLeftFix(); // 向左大调
void sharpRightFix();
void trace(); // 循迹

/*变量定义*/

bool traceSensor[4] = {0, 0, 0, 0}; //4路循迹传感器的值
int crossCNT = 0;//已经经过的十字路口数目

// Arduino自带初始化函数
void setup() {
  initMotorPorts();
  initSteerEngine();
  initTracePorts();
  initColorSensorPorts();

}

// Arduino自带“主函数”，自动循环执行
void loop() {
  trace();//循迹
}

//初始化各种串口
void initTracePorts()
{
  pinMode(tracePort1, INPUT);
  pinMode(tracePort2, INPUT);
  pinMode(tracePort3, INPUT);
  pinMode(tracePort4, INPUT);
  return;
}
void initMotorPorts()
{
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  return;
}
void initSteerEngine()
{
  pinMode(steerPort, INPUT);
  return;
}
void initColorSensorPorts()
{
  //TODO
  return;
}
void initUltrasonicSensorPorts()
{
  //TODO
  return;
}

//读取循迹传感器数据
void readTraceSensors()
{
  traceSensor[0] = digitalRead(tracePort1); 
  traceSensor[1] = digitalRead(tracePort2);
  traceSensor[2] = digitalRead(tracePort3);
  traceSensor[3] = digitalRead(tracePort4);
  return;
}
//设置各个马达速度
void setMotorSpeed(int left1Speed, int left2Speed, int right1Speed, int right2Speed)
{
  analogWrite(leftMotor1, left1Speed);
  analogWrite(leftMotor2, left2Speed);
  analogWrite(rightMotor1, right1Speed);
  analogWrite(rightMotor2, right2Speed);
  return;
}

//小车行驶行为
void straightForward()
{
  setMotorSpeed(100, 100, 100, 100); //后期实验中根据需要调速
  return;
}
void minorLeftFix()
{
  setMotorSpeed();
  return;
}
void minorRightFix()
{
  return;
}
void sharpLeftFix()
{
  return;
}
void sharpRightFix()
{
  return;
}

// 循迹
void trace()
{
  //直行，循迹传感器0000或1111
  if((traceSensor[0] & traceSensor[1] & traceSensor[2] & traceSensor[3]) || !(traceSensor[0] | traceSensor[1] | traceSensor[2] | traceSensor[3]))
  {
    straightForward();
    return;
  }
  //向左微调，传感器0100
  if(!traceSensor[0] && traceSensor[1] && !traceSensor[2] && !traceSensor[3])
  {
    minorLeftFix();
    return;
  }
  //向右微调，传感器0010
  if(!traceSensor[0] && !traceSensor[1] && traceSensor[2] && !traceSensor[3])
  {
    minorRightFix();
    return;
  }
  //向左大调，传感器1000
  if(traceSensor[0] && !traceSensor[1] && !traceSensor[2] && !traceSensor[3])
  {
    sharpLeftFix();
    return;
  }
  //向右大调，传感器0001
  if(!traceSensor[0] && !traceSensor[1] && !traceSensor[2] && traceSensor[3])
  {
    sharpRightFix();
    return;
  }
  //向左转弯，传感器1100，十字路口+1
  if(traceSensor[0] && traceSensor[1] && !traceSensor[2] && !traceSensor[3])
  {
    turnLeft();
    crossCNT++;
    return;
  }
  //向右转弯，传感器0011，十字路口+1
  if(!traceSensor[0] && !traceSensor[1] && traceSensor[2] && traceSensor[3])
  {
    turnRight();
    crossCNT++;
    return;
  }
}