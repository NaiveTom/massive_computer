#ifndef __ENCODER_H__
#define __ENCODER_H__


// stage检测接口，一共40状态
const byte input[] = {54, 55, 56, 57, 58, 59, 60, 61,
                      62, 63, 64, 65, 66, 67, 68, 69,
                      22, 24, 26, 28, 30, 32, 34, 36,
                      38, 40, 42, 44, 46, 48, 50, 52,
                      23, 25, 27, 29, 31, 33, 35, 37
                     };


// 编码器输出接口
const byte output[] = {39, 41, 43, 45, 47, 49};


// 位与数据转换表
const byte byte_bit_table[] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20};


void init_encoder()
{
  for (byte i = 0; i < 40; i++)
    pinMode(input[i], INPUT);

  for (byte i = 0; i < 6; i++)
    pinMode(output[i], OUTPUT);
}


byte read_stage() // 优先编码器，只读取最低位
{
  for (byte i = 0; i < 40; i++)
    if (digitalRead(input[i]))
      return i + 1; // 正常输出 1-40 的值

  return 0; // 证明目前状态都空了，可以打开继电器让信号振荡了
}


void write_stage(byte data)
{
  for (byte i = 0; i < 6; i++)
    digitalWrite(output[i], data & byte_bit_table[i]);
}


#endif
