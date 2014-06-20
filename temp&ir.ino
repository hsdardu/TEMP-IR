
//数字端口必须接在3上
//红外发射实验测试程序
#include <IRremote.h>
#include <SPI.h>
#include <Ethernet.h>
#include <LeweiTcpClient.h>
#include <EEPROM.h>

#define LW_USERKEY "b568ec55d7e648b59b9ec94eec08be5e"
#define LW_GATEWAY "01"
#define LED_PIN 3

IRsend irsend;
LeweiTcpClient *client;

void setup()
{
  Serial.begin(9600);
  
  client = new LeweiTcpClient(LW_USERKEY, LW_GATEWAY);

  UserFunction uf1 (boxOn1,"boxOn");
  client->addUserFunction(uf1);
  UserFunction uf2 (boxOff,"boxOff");
  client->addUserFunction(uf2);
  
  pinMode(LED_PIN,OUTPUT);
}

void loop() 
{
   client->keepOnline();
}

void boxOn1() {
  client->setRevCtrlMsg("true","on");
  irsend.sendNEC(0x23448B7,  32); // 发送数字电视机顶盒遥控器上的数字0
  Serial.println('0x23448B7');
}
void boxOff() {
  client->setRevCtrlMsg("true","off");
  irsend.sendNEC(0x234E817,  32); // 发送数字电视机顶盒遥控器上的数字0
  Serial.println('0x234E817');
}


