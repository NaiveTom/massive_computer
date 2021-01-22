#ifndef __BUZZER_H__
#define __BUZZER_H__

#define BEEPER 13

void init_beeper()
{
  pinMode(BEEPER, OUTPUT);
}

unsigned long beep_time = 0;
// 响铃时长
#define BEEP_LEN 500

// 如果on是1，那么就响，如果on是0，那么就delay之后不响
void beep(bool on)
{
  if (on)
  {
    beep_time = 0; // 重新计时
    digitalWrite(BEEPER, HIGH); // 响
  }

  if (beep_time == 0) beep_time = millis(); // 开始计时
  else
  {
    if (beep_time + BEEP_LEN < millis())
    {
      beep_time = 0;
      digitalWrite(BEEPER, LOW); // 不响
    }
  }
}

#endif
