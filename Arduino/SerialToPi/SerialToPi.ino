#include <DHT.h>
#include <ArduinoJson.h>

#define DHTPIN 2
#define DHTTYPE DHT22

int DelayInterval = 10000;
DHT dht(DHTPIN, DHTTYPE);

//시리얼 초기화 및 서버 연결 상태 점검 
void initSerial()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  //시리얼 포트가 연결이 되지 않을 경우, LED를 켠다.
  while(!Serial) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  digitalWrite(LED_BUILTIN, LOW);

  //접속 상태 확인
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

// 센서 값을 Json으로 변경
JsonObject &toJson(float temp, float humid, int light) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject &jsonObj = jsonBuffer.createObject();
 
  jsonObj["Temp"] = temp;
  jsonObj["Humid"] = humid;
  jsonObj["Light"] = light;

  return jsonObj;
}

// 시리얼 수신 시 발생
void serialEvent() {
  if (Serial.available() > 0) {
    String readBuffer = Serial.readString();
    DynamicJsonBuffer jsonBuffer;
    JsonObject &jsonObj = jsonBuffer.parseObject(readBuffer);
    
    String Command = jsonObj["Comm"];
    //딜레이 간격 조절
    if (Command == "setInterval") {
      DelayInterval = jsonObj["Interval"];
      Serial.print('R');
    }
  }
}

void setup() {
  initSerial();
  dht.begin();
}

void loop() {
  float tmp = dht.readTemperature();
  float hum = dht.readHumidity();
  
  toJson(tmp, hum, 1000).printTo(Serial);
  Serial.println("");
  delay(DelayInterval);
}
