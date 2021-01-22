#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__

// 设置输入引脚 24bit
const byte BIT[] = {54, 55, 56, 57, 58, 59, 60, 61,
                    62, 63, 64, 65, 66, 67, 68, 69,
                    22, 24, 26, 28, 30, 32, 34, 36
                   };

// 按位取数据表
const byte byte_bit_table[] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};

#define CLK 35    // 595 = 11，时钟
#define LOCK 37   // 595 = 12，锁存
#define IN 39     // 595 = 14，串行数据输入

// 初始化函数
void init_bootloader()
{
  for (byte i = 0; i < 24; i++) pinMode(BIT[i], INPUT);

  // 让三个595引脚都是输出状态
  pinMode(LOCK, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(IN, OUTPUT);
}

// 向595中灌入数，一次灌入15组
void input_595(byte * buffer_595)
{
  digitalWrite(LOCK, LOW); // 将LOCK口上面加低电平让芯片准备好接收数据

  for (byte i = 0; i < 15; i++)
  {
    shiftOut(IN, CLK, MSBFIRST, buffer_595[i]);
  }

  // 串行数据输入引脚为IN，时钟引脚为CLK，执行MSB有限发送，发送数据table[i]
  digitalWrite(LOCK, HIGH); // 将LOCK这个针脚恢复到高电平（显示）
}

// 读取bootloader拨码开关中的内容，一次一个字节
char read_byte(byte num)
{
  byte temp;
  
  switch (num)
  {
    case 1:
      for (byte i = 0; i < 8; i++)
      {
        // 第一次不移动（移动0为空操作）
        temp <<= 1;
        // 反过来，高位移动7次，低位一次都不移动（所以把左移放在最前头）
        temp |= digitalRead(BIT[7 - i]);
      }
      break;
    case 2:
      for (byte i = 8; i < 16; i++)
      {
        // 第一次不移动（移动0为空操作）
        temp <<= 1;
        // 反过来，高位移动7次，低位一次都不移动（所以把左移放在最前头）
        temp |= digitalRead(BIT[7 - i]);
      }
      break;
    case 3:
      for (byte i = 16; i < 24; i++)
      {
        // 第一次不移动（移动0为空操作）
        temp <<= 1;
        // 反过来，高位移动7次，低位一次都不移动（所以把左移放在最前头）
        temp |= digitalRead(BIT[7 - i]);
      }
      break;
    default:
      Serial.println(F("-> Fatal error：read_byte"));
      Serial.print(F("-> num can only be equal to 1 or 2 or 3 where num = "));
      Serial.print(num);
      break;
  }
  return temp;
}

// 读取bootloader中的所有数据
void read_data()
{
  //74HC595
  byte buffer_595[15] = {0};

  for (byte i = 0; i < 15; i++)
  {
    for (byte j = 0; j < 8; j++)
    {
      // 改变其中的一位
      buffer_595[i] = byte_bit_table[j];
      // 送数
      input_595(buffer_595);
      // 等一下，开始读数
      delay(100);

      Serial.print(read_byte(1));
      Serial.print(read_byte(2));
      Serial.print(read_byte(3));

      Serial1.print(read_byte(1));
      Serial1.print(read_byte(2));
      Serial1.print(read_byte(3));
    }
  }
}

#endif
