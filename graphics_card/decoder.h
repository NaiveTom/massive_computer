#ifndef __DECODER_H__
#define __DECODER_H__

// 设置stage检测，一共20状态
const byte pipeline[] = {23, 25, 27, 29, 31, 33};

void init_pipeline()
{
  for (byte i = 0; i < 6; i++)
    pinMode(pipeline[i], INPUT);
}

byte decode_data()
{
  byte temp = 0;

  for (byte i = 0; i < 6; i++)
  {
    // 第一次不移动（移动0为空操作）
    temp <<= 1;
    // 反过来，高位移动15次，低位一次都不移动（所以把左移放在最前头）
    temp |= digitalRead(pipeline[5 - i]);
  }

  return temp;
}

#endif
