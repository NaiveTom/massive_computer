#include <arduino.h>
#include "bootloader.h"
#include "lcd2004.h"
#include "pipeline.h"
#include "buzzer.h"

void setup()
{
  // 打开两个串口
  Serial.begin(115200);
  Serial1.begin(115200);

  init_bootloader();
  init_lcd();
  init_pipeline();
  init_beeper();

  read_data();
}

void loop()
{
  display_2004(decode_data(), 100, 500);
  beep(1);
}
