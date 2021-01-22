#ifndef __TEST_H__
#define __TEST_H__

#include "pins_define.h"  // 第一层：硬件定义层（串口、引脚）
#include "bios.h"         // 第二层：基本输入输出数据层
#include "relay_op.h"     // 第三层：基本继电器运算

// 采用延时模式
#define TEST_DELAY 300



void test_A() // 遍历测试A是否正常工作
{
  for (long i = 0; i < 65536; i++)
  {
    Serial.print(F("set_A = ")); // 打印当前设定值
    Serial.println(i);
    set_A(i);
    delay(TEST_DELAY);
  }
}

void test_B() // 遍历测试B是否正常工作
{
  for (long i = 0; i < 65536; i++)
  {
    Serial.print(F("set_B = ")); // 打印当前设定值
    Serial.println(i);
    set_B(i);
    delay(TEST_DELAY);
  }
}



void test_carry() // 测试carry进位设置与取消是否正常工作
{
  set_carry();
  delay(TEST_DELAY);
  unset_carry();
  delay(TEST_DELAY);
}

void test_add_sub() // 测试加减法设置是否正常工作
{
  set_add();
  delay(TEST_DELAY);
  set_sub();
  delay(TEST_DELAY);
}

void test_left_right() // 测试 左移/右移 是否正常工作
{
  set_left_enable();
  delay(TEST_DELAY);
  set_right_enable();
  delay(TEST_DELAY);
}



void test_single_adder_allstep() // 测试一个加法器是否能正常工作，遍历测试
{
  // 测试单个加法器
  for (byte a = 0; a < 4; a++) // 测试A
  {
    for (byte b = 0; b < 4; b++) // 测试B
    {
      for (byte c = 0; c < 2; c++) // 测试carry（取值范围是bool，但是不能用bool，因为bool无法等于2）
      {
        add_and_check(a, b, c);
      }
    }
  }
}



// 测试加法api
void test_all_adder_allstep()
{
  for (long a = 0; a < 65536; a++) // 测试A
  {
    for (long b = 0; b < 65536; b++) // 测试B
    {
      for (byte c = 0; c < 2; c++) // 测试carry（取值范围是bool，但是不能用bool，因为bool无法等于2）
      {
        add_and_check(a, b, c);
      }
    }
  }
}

// 测试减法api
void test_all_sub_allstep()
{
  for (long a = 0; a < 65536; a++) // 测试A
  {
    for (long b = 0; b < 65536; b++) // 测试B
    {
      sub_and_check(a, b, 1); // 取反加一，所以carry一直等于1
    }
  }
}

#endif
