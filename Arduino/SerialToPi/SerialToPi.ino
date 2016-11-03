#include <ArduinoJson.h>

void serialInit()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  //시리얼 포트가 연결이 되지 않을 경우, LED를 켠다.
  while(!Serial) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  digitalWrite(LED_BUILTIN, LOW);

  //접속 상태 점검
  Serial.print('C');
  while(1) {
    if (Serial.available() > 0) {
      char Byte = Serial.read();
      if( Byte == 'R' )
      {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.print('R');
        break;
      }
    }
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
  serialInit();

  DynamicJsonBuffer jsonBuffer;
  JsonObject& object = jsonBuffer.createObject();

  object["name"] = "test";
  object["test"] = "it's test";
  object["value"] = 10;

  object.printTo(Serial);
  Serial.print('\n');
}

void loop() {

}
