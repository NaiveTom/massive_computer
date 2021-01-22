#ifndef __BIOS_H__
#define __BIOS_H__

#include "pins_define.h"

/*
   偏置表
*/

// 偏置表改成了16位，所以使用unsigned int存储（arduino的int最大32767）
const long byte_bit_table[] = {0x1, 0x2, 0x4, 0x8,
                               0x10, 0x20, 0x40, 0x80,
                               0x100, 0x200, 0x400, 0x800,
                               0x1000, 0x2000, 0x4000, 0x8000
                              };

/*
   加法器 & 异或单元
*/

void set_A(long num) // 设置加法器数A的输出为num
{
  // 第一次使用本函数调试检查用
  // Serial.println(num); Serial.println();
  for (byte i = 0; i < 16; i++)
  {
    digitalWrite(A[i], num & byte_bit_table[i]);
    // 第一次使用本函数调试检查用
    // Serial.print(i);
    // Serial.print(F("\t"));
    // Serial.println(num & byte_bit_table[i]);
  }
}

void set_B(long num) // 设置加法器数B的输出为num
{
  for (byte i = 0; i < 16; i++) digitalWrite(B[i], num & byte_bit_table[i]);
}



void set_add() // 设置加法
{
  digitalWrite(SIGN, LOW);
}

void set_sub() // 设置减法（异或门启动）
{
  digitalWrite(SIGN, HIGH);
}



long get_D() // 读取加法器结果数D
{
  long temp = 0;

  for (byte i = 0; i < 16; i++)
  {
    // 第一次不移动（移动0为空操作）
    temp <<= 1;
    // 反过来，高位移动15次，低位一次都不移动（所以把左移放在最前头）
    temp |= digitalRead(D[15 - i]);
  }

  return temp;
}



void set_carry() // 设置最低进位（用于减法和上一个数据相加结果）
{
  digitalWrite(C_0, HIGH);
}

void unset_carry() // 取消最低进位
{
  digitalWrite(C_0, LOW);
}

byte get_carry() // 读取最高进位，改了bool，一切ok
{
  return digitalRead(C_2);
}

/*
   移位器
*/

void set_IN(byte num) // 设置移位器输入
{
  for (byte i = 0; i < 8; i++) digitalWrite(A[i], num & byte_bit_table[i]);
}

byte get_OUT() // 读取移位器输出
{
  byte temp = 0;

  for (byte i = 0; i < 8; i++)
  {
    temp |= digitalRead(D[i]);
    temp <<= 1;
  }

  return temp;
}



void set_left_enable() // 设置左移使能
{
  digitalWrite(LEFT_EN, HIGH);
}

void set_right_enable() // 设置右移使能
{
  digitalWrite(LEFT_EN, LOW);
}



byte get_left_overflow() // 读取左移溢出，改了bool，一切ok
{
  return digitalRead(LEFT_SPILL);
}

byte get_right_overflow() // 读取右移溢出，改了bool，一切ok
{
  return digitalRead(RIGHT_SPILL);
}

/*
   节能模式 / 停机模式
*/

void energy_saving_mode() // 节能模式，关闭所有继电器
{
  set_A(0); // 把0送入a，关闭所有继电器
  set_B(0); // 把0送入b，关闭所有继电器

  set_add(); // 设置为加法，关闭所有继电器驱动和异或动作继电器
  unset_carry(); // 取消最低进位，关闭C_0继电器



  set_IN(0); // 把0送入shifter的in，关闭所有继电器

  set_right_enable(); // 关闭使能继电器，包括驱动继电器和动作继电器
}

/*
   mux单元
*/

void mux_add_sub()
{
  digitalWrite(MUX_3, LOW);
  digitalWrite(MUX_2, LOW);
  digitalWrite(MUX_1, LOW);
}

void mux_mul()
{
  digitalWrite(MUX_3, LOW);
  digitalWrite(MUX_2, LOW);
  digitalWrite(MUX_1, HIGH);
}

void mux_shift()
{
  digitalWrite(MUX_3, LOW);
  digitalWrite(MUX_2, HIGH);
  digitalWrite(MUX_1, LOW);
}

void mux_and()
{
  digitalWrite(MUX_3, LOW);
  digitalWrite(MUX_2, HIGH);
  digitalWrite(MUX_1, HIGH);
}

void mux_or()
{
  digitalWrite(MUX_3, HIGH);
  digitalWrite(MUX_2, LOW);
  digitalWrite(MUX_1, LOW);
}

void mux_not()
{
  digitalWrite(MUX_3, HIGH);
  digitalWrite(MUX_2, LOW);
  digitalWrite(MUX_1, HIGH);
}

void mux_xor()
{
  digitalWrite(MUX_3, HIGH);
  digitalWrite(MUX_2, HIGH);
  digitalWrite(MUX_1, LOW);
}

void mux_xnor()
{
  digitalWrite(MUX_3, HIGH);
  digitalWrite(MUX_2, HIGH);
  digitalWrite(MUX_1, HIGH);
}

#endif
