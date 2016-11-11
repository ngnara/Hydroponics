#include <DHT.h>
#include <ArduinoJson.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11
#define LIGHT_PIN A0
#define PH_METER_PIN A1
#define PH_ARRAY_LENGTH 40

int pHArray[PH_ARRAY_LENGTH];
int pHArrayIndex = 0;
int DelayInterval = 10000;
DHT dht(DHT_PIN, DHT_TYPE);

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
JsonObject &toJson(float temp, float humid, int light, float ph) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject &jsonObj = jsonBuffer.createObject();

  jsonObj["Temp"] = temp;
  jsonObj["Humid"] = humid;
  jsonObj["Light"] = light;
  jsonObj["pH"] = ph;

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

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}

float readpH () {
      float pHValue, voltage;
      pHArray[pHArrayIndex++] = analogRead(PH_METER_PIN);
      if(pHArrayIndex == PH_ARRAY_LENGTH )
        pHArrayIndex=0;
      voltage = avergearray(pHArray, PH_ARRAY_LENGTH) * 5.0 / 1024;
      pHValue = 3.5 * voltage + 0.0;

      return pHValue;
}

void setup() {
  initSerial();
  dht.begin();
}

void loop() {
  float tmp = dht.readTemperature();
  float hum = dht.readHumidity();
  int light = analogRead(LIGHT_PIN);
  float ph = readpH();

  //toJson(tmp, hum, light, ph).printTo(Serial);
  toJson(tmp, hum, 1000, 7.0).printTo(Serial);
  Serial.println("");
  delay(DelayInterval);
}
