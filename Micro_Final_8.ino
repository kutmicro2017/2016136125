#include <Adafruit_NeoPixel.h>
#include <DHT11.h>
#define PIN 5                  //data out이 연결된 핀 번호
#define NUM_LEDS 16            // 네오픽셀 LED 갯수
#define Neo_Sw 7               // 네오픽셀 on / off 스위치
#define Hum_Sw 6               // 가습기 on / off 스위치
#define Humidifier1 15
#define Humidifier2 16
#define DHTPIN  14             // DHT핀을 16번으로 정의한다(DATA핀)
#define DHTTYPE DHT11          // DHT타입을 DHT11로 정의한다

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int potentiometer = A0;         // 가변저항을 A0핀으로 설정

int Sw_count = 0;               // 스위치 눌린 횟수 카운트
int switchState = 0;            // 현재 스위치 상태
int lastSwitchState = 0;        // 지난 스위치 상태

int Hum_count = 0;
int switchState_Hum = 0;
int lastHumSwitchState = 0; 

float temp, humi;

DHT11 dht(DHTPIN);        // DHT설정 - dht (디지털14, dht11)

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  
  pixels.begin();         //네오픽셀 사용설정
  pixels.setPixelColor(0, pixels.Color(0,0,0));//네오픽셀 초기설정
  pixels.show();          //네오픽셀 설정 적용
  
  pinMode(Neo_Sw, INPUT_PULLUP);  // 풀업저항 스위치 
  pinMode(Hum_Sw, INPUT_PULLUP);  // 풀업저항 스위치
  pinMode(Humidifier1, OUTPUT);    // 가습기
  pinMode(Humidifier2, OUTPUT);
}

int red = 234, green = 156, blue = 26; // 네오픽셀 초기값
int count20 = 0; // 습도 설정이 여러번 눌려서 실행이 여러번 되는 것을 방지
int count30 = 0; 
int count50 = 0;  
bool state20 = false;   // 습도예약을 위한 상태
bool state30 = false;   // 습도예약을 위한 상태
bool state50 = false;   // 습도예약을 위한 상태

void loop() {
 int pmValue = analogRead(potentiometer);  // pmValue는 가변저항값 변수
 pmValue = map(pmValue, 0, 1023, 0, 255);  // 가변저항값 변경
 
 checkNeoSwitch(); checkHumSwitch();
 Serial.print("Neo : ");
 Serial.println(Sw_count);
 Serial.print("HUm : ");
 Serial.println(Hum_count);
  int err;
  //float humi;
  if((err=dht.read(humi, temp))==0)         //온도, 습도 읽어와서 표시
  {
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
  }
  delay(1);                     

 if(Serial1.available() > 0){
    for(int i = 0; i < 3; i++){
        char c = Serial1.read();  // 블루투스로 받은 문자  
        Serial.println(c);
        if(c == 'N') {  Sw_count++;  }  // 네오픽셀 카운트+
        if(c == 'H') {  Hum_count++; }  // 가습기 카운트+           
        if(c == 'r') { red = Serial1.parseInt(); }  // r색상 저장
        if(c == 'g') { green = Serial1.parseInt(); }// g색상 저장
        if(c == 'b') { blue = Serial1.parseInt(); } // b색상 저장
        
        if(c == 'z') {  // 저장된 색상 불러오기
          for(int i = 0; i < 3; i++){
            char d = Serial1.read();
            Serial.println(d);
            if(d == 'r') { red = Serial1.parseInt(); }
            if(d == 'g') { green = Serial1.parseInt(); }
            if(d == 'b') { blue = Serial1.parseInt(); }
          }
         }
          
        if(c == 'A') { 
          if(humi < 20) {   // 습도20% 예약
            state20 = true; 
            count20++;
            
          }  
        } 
        if(c == 'B') {
          if(humi < 30) {   // 습도30% 예약
            state30 = true;
            count30++;
          }  
        } 
        if(c == 'C') { 
          if(humi < 50) {   // 습도50% 예약
            state50 = true; 
            count50++;
          }  
        } 
    }
  } 
    // 네오픽셀
    if(Sw_count % 2 == 1 && Sw_count >= 1){    // 스위치 눌린 횟수가 1이상의 홀수
        colorWipe(pixels.Color(red, green, blue), 1); 
        pixels.setBrightness(pmValue);         // 가변저항값에 따라 밝기 조절
    }
    else{  colorWipe(pixels.Color(0, 0, 0), 1);  }
    Serial.print("Sw_count : ");
    Serial.println(Sw_count);
    
    // 가습기 
    if(Hum_count % 2 == 1 && Hum_count >= 1){  digitalWrite(Humidifier1, LOW); digitalWrite(Humidifier2, LOW);   }
    else{  digitalWrite(Humidifier1, HIGH); digitalWrite(Humidifier2, HIGH);  }  
    Serial.print("hum_count : ");
    Serial.println(Hum_count);
    
 if(count20 % 2 == 0) state20 = false;
 if(count30 % 2 == 0) state30 = false;
 if(count50 % 2 == 0) state50 = false;

  // 가습기 예약 상태 체크, 실행
 if(state20 == true){
    if(Hum_count % 2 == 1){
      if(humi >= 20){ state20 = false; Hum_count = 0; } }
      else if( Hum_count % 2 == 0 ) { Hum_count++; }
  }
  if(state30 == true){
    if(Hum_count % 2 == 1){
      if(humi >= 30){ state30 = false; Hum_count = 0; } }
      else if( Hum_count % 2 == 0 ) { Hum_count++;}
  }

  if(state50 == true){
    if(Hum_count % 2 == 1){ 
    if(humi >= 50){ state50 = false; Hum_count = 0; } }
    else if( Hum_count % 2 == 0 ) { Hum_count++; }
  }

 

}

void colorWipe(uint32_t c, uint8_t wait) {  // led를 차례대로 켜는 함수
  for(uint16_t i=0; i<16; i++) {
      pixels.setPixelColor(i, c);
      pixels.show();
      delay(1);                             // 딜레이가 매우적으므로 한번에 켜지는 것 처럼 보임
  }
}
void checkNeoSwitch(){                          // 스위치가 눌린 횟수를 체크하는 함수
  switchState = digitalRead(Neo_Sw);            // 현재 스위치 상태에 버튼 상태 저장
  if(switchState != lastSwitchState) {          // 현재 스위치 상태와 이전 상태가 다르면
     if(switchState == LOW)                     // 현재 스위치가 눌렸으면
        Sw_count++;                             // 스위치 카운트를 늘려줌
  }
  lastSwitchState = switchState;                // 현재 스위치 상태를 이전 스위치 상태에 저장
 }
 
 void checkHumSwitch(){                         // 스위치가 눌린 횟수를 체크하는 함수
  switchState_Hum = digitalRead(Hum_Sw);        // 현재 스위치 상태에 버튼 상태 저장
  if(switchState_Hum != lastHumSwitchState) {   // 현재 스위치 상태와 이전 상태가 다르면
     if(switchState_Hum == LOW)                 // 현재 스위치가 눌렸으면
        Hum_count++;                            // 스위치 카운트를 늘려줌
  }
  lastHumSwitchState = switchState_Hum;         // 현재 스위치 상태를 이전 스위치 상태에 저장
 }
