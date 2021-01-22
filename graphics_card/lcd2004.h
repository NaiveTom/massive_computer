#ifndef __LCD2004_H__
#define __LCD2004_H__

#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8, 9, 10, 11);

void init_lcd()
{
  // 开始2004运转
  lcd.begin(20, 4);
}

void display_2004(byte pipeline_stage, unsigned long inst_num, unsigned long op_num)
{
  lcd.setCursor(0, 0);
  lcd.print(F("PIPELINE STAGE: "));
  lcd.print(millis());

  lcd.setCursor(0, 1);
  lcd.print(F("RUN TIME: "));
  lcd.print(millis()/1000);
  lcd.print(F(" s"));

  lcd.setCursor(0, 2);
  lcd.print(F("INST NUM: "));
  lcd.print(inst_num);

  lcd.setCursor(0, 3);
  lcd.print(F("OP NUM: "));
  lcd.print(op_num);
}

#endif
