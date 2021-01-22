#ifndef __PINS_H__
#define __PINS_H__

#include <arduino.h>
// 注意，不可以使用PROGMEM，使用了会出错

/*
   基本输入输出
*/

// 第一个操作数，A0-A15，用模拟口
const byte A[] = {54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69}; // A0-A15模拟口

// 第二个操作数，B0-B15
const byte B[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};

// 运行结果D，D0-D15
const byte D[] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53};

/*
   加法器
*/

// 加法器进位最低位输入C_0与最高位输出C_2
#define C_0 2
#define C_2 3

/*
   减法器：异或反码单元
*/

// 符号位，高电平时减法，低电平时加法（注意把C_0也置为1，因为是取反加一）
#define SIGN 4

/*
   8-bit 移位器
*/

// 左移溢出位
#define LEFT_SPILL 5
// 右移溢出位
#define RIGHT_SPILL 6
// 左移使能，使能后（高电平）将进行左移操作
#define LEFT_EN 7

/*
   3-8译码器 MUX
*/

// 定义引脚
#define MUX_1 8
#define MUX_2 9
#define MUX_3 10

/*
   初始化部分
*/

// 串口初始化函数，并输出使用提示
void init_serial()
{
  Serial.begin(115200); // 打开串口，波特率115200
  delay(100);
  Serial.println(F("-> Serial begins successfully @ 115200\n"));
  Serial.println(F("-> Welcome to use relay computer\n"));

  // 启动和内存板卡的通信
  Serial1.begin(115200);
}

// 初始化引脚
void init_pins()
{

  /*
    基本输入输出
  */

  // 第一个操作数，A0-A15，输出
  for (byte i = 0; i < 16; i++) pinMode(A[i], OUTPUT);
  // 第二个操作数，B0-B15，输出
  for (byte i = 0; i < 16; i++) pinMode(B[i], OUTPUT);
  // 计算结果，D0-D7，输入
  for (byte i = 0; i < 16; i++) pinMode(D[i], INPUT);

  /*
     加法器
  */

  // 加法器进位输入与输出，C0输出、C2输入
  pinMode(C_0, OUTPUT);
  pinMode(C_2, INPUT);

  /*
    异或单元
  */

  // 加减符号位，输出
  pinMode(SIGN, OUTPUT);

  /*
    8-bit 移位器
  */

  // 左移溢出，输入
  pinMode(LEFT_SPILL, INPUT);
  // 右移溢出，输入
  pinMode(RIGHT_SPILL, INPUT);
  // 左移使能，输出
  pinMode(LEFT_EN, OUTPUT);

  /*
    3-8译码器 MUX
  */

  pinMode(MUX_1, OUTPUT);
  pinMode(MUX_2, OUTPUT);
  pinMode(MUX_3, OUTPUT);
}

#endif
