#ifndef __RELAY_OP_H__
#define __RELAY_OP_H__

// 采用延时模式
#define RELAY_DELAY 300



// 进行加法和检查
long add_and_check(long A, long B, byte carry)
{
  mux_add_sub(); // mux设置为加法器
  set_add(); // 设置为加法

  set_A( A );
  set_B( B );

  if (carry == 0) unset_carry(); // 取消最低进位
  else if (carry == 1) set_carry(); // 设置最低进位
  else // 如果carry输入不是bool范围，那么直接报错！
  {
    Serial.println(F("-> Fatal error: add_and_check"));
    Serial.print(F("-> carry(bool) cannot be "));
    Serial.println(carry);
  }

  delay(RELAY_DELAY);

  long ans_should = A + B + carry;
  long ans_relay = get_D() + long(get_carry()) * 65536;

  if (ans_should != ans_relay) // 发生运算错误，报错
  {
    Serial.print(F("-> Fatal error: add_and_check"));
    Serial.print(F("-> "));
    Serial.print( A ); Serial.print(F(" + ")); Serial.print( B );
    Serial.print(F(" ans_should = "));
    Serial.print(ans_should);
    Serial.print(F(" ans_relay = "));
  }

  Serial.println(ans_should);
}



// 进行减法和检查
// 使用说明：如果是最低的一个byte，那么carry设置成1（取反加一）
// 如果不是最低位，那么只需要把之前的carry溢出弄成最低进位即可
int sub_and_check(long A, long B, byte carry)
{
  mux_add_sub(); // mux设置为加法器
  set_sub(); // 设置为减法

  set_A( A );
  set_B( B );

  if (carry == 0) unset_carry(); // 取消最低进位
  else if (carry == 1) set_carry(); // 设置最低进位
  else // 如果carry输入不是bool范围，那么直接报错！
  {
    Serial.println(F("-> Fatal error: sub_and_check"));
    Serial.print(F("-> carry(bool) cannot be "));
    Serial.println(carry);
  }

  delay(RELAY_DELAY);

  long ans_should = A + (65535 - B) + carry; // 取反码
  long ans_relay = get_D() + long(get_carry()) * 65536;

  if (ans_should != ans_relay) // 发生运算错误，报错
  {
    Serial.println(F("-> Fatal error: sub_and_check"));
    Serial.print(F("-> carry = ")); Serial.print(carry); Serial.print(F(" ")); // 输出carry的值
    Serial.print( A ); Serial.print(F(" - ")); Serial.print( B );
    Serial.print(F(" ans_should = "));
    Serial.print(ans_should);
    Serial.print(F(" ans_relay = "));
  }

  Serial.println(ans_relay); // 输出结果
}

#endif
