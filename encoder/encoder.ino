#include <arduino.h>
#include "encoder.h"

#define RELAY 51

void setup()
{
  Serial.begin(115200); // 打开串口

  pinMode(RELAY, OUTPUT); // 弄个继电器来中继信号
  digitalWrite(RELAY, LOW); // 继电器断开，消除竞争冒险带来的错误多触发

  init_encoder(); // 初始化所有引脚

  while (read_stage()); // 等待多个信号自然消失
  Serial.println(F("Initialization completed ..."));

  digitalWrite(RELAY, HIGH); // 继电器合闸，之后信号可以正常传递
  Serial.println(F("The relay is connected and the clock signal starts to run ..."));
}

// 只有状态变化的时候才去更新编码器
byte stage = 0, last_stage = 0;
long last_time = 0;

void loop()
{
  stage = read_stage(); // 读取当前状态

  if (stage != last_stage)
  {
    write_stage(stage); // 编码器工作并把数据送到另一个单片机
    last_stage = stage; // 保存当前stage
    
    Serial.print(stage); // 打印当前stage
    Serial.print('\t');
    
    Serial.println(millis() - last_time); // 打印时间间隔
    last_time = millis(); // 保存当前时间
  }
}
