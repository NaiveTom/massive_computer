#include "pins_define.h"  // 第一层：硬件定义层（串口、引脚）
#include "bios.h"         // 第二层：基本输入输出数据层
#include "relay_op.h"     // 第三层：基本继电器运算

#include "test.h" // 测试库



void setup()
{
  init_serial();
  init_pins();
}



void loop()
{
  // test_carry();
}
