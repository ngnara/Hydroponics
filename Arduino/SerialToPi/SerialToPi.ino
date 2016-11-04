#include <ArduinoJson.h>

void initSerial()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  //시리얼 포트가 연결이 되지 않을 경우, LED를 켠다.
  while(!Serial) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  digitalWrite(LED_BUILTIN, LOW);

  //접속 상태 대기
  while(1) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print('C');
    delay(1000);
    if (Serial.available() > 0) {
      char Byte = Serial.read();
      if( Byte == 'R' ) {
        Serial.print('R');
        break;
      }
    }
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void serialEvent() {
  if (Serial.available() > 0) {
    String readedBuffer = "";
    digitalWrite(LED_BUILTIN, HIGH);
    readedBuffer = Serial.readString();
    Serial.println(readedBuffer);
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
  initSerial();
}

void loop() {

}
