/*
  - 좌회전, 우회전 신호를 생략한 사거리 신호등
    보행자 버튼은 현재 초록불인 신호등을 빨간불로
    현재 빨간불인 신호들을 초록불로
*/

#define U_RED 20
#define U_YEL 3
#define U_GRE 4         // 위쪽 신호등
#define R_RED 5
#define R_YEL 6
#define R_GRE 7         // 오른쪽 신호등
#define L_RED 26
#define L_YEL 24
#define L_GRE 22        // 왼쪽 신호등
#define D_RED 27
#define D_YEL 25
#define D_GRE 23        // 아래쪽 신호등
#define BUTTON 2        // 보행자 버튼
#define UD_BlinkT 1000  // 위,아래 노란불 점멸시간(1초)
#define LR_BlinkT 1000  // 오른쪽, 왼쪽 노란불 점멸시간(1초)
#define interval 5000   // 시간 간격 기본값(5초)

unsigned long prevT = 0;

void setup() {
  pinMode(U_RED, OUTPUT);
  pinMode(U_YEL, OUTPUT);
  pinMode(U_GRE, OUTPUT);
  pinMode(R_RED, OUTPUT);
  pinMode(R_YEL, OUTPUT);
  pinMode(R_GRE, OUTPUT);
  pinMode(L_RED, OUTPUT);
  pinMode(L_YEL, OUTPUT);
  pinMode(L_GRE, OUTPUT);
  pinMode(D_RED, OUTPUT);
  pinMode(D_YEL, OUTPUT);
  pinMode(D_GRE, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP ); // 풀업저항
}

void loop() {
  int button = digitalRead(2);    // 버튼 핀번호(2) 정의 
  
  UD_GreOn();                     // 위쪽, 아래쪽 신호 변경
  
  if(button == 0){                // 버튼이 눌렸을 때
    delay(3000);                  // 딜레이 3초
    UD_Blink();                   // 위쪽, 아래쪽 노란불 점멸
    LR_GreOn();                   // 왼쪽, 오른쪽 신호 변경
    delay(15000);                 // 초록불 점등 시간(15초)
  }
  
  if(millis() - prevT >= 3*interval) {    // ( 현재 시간 - 이전 시간 ) >= 초록불 점등 시간(15초)
    UD_Blink();                   // 위쪽, 아래쪽 노란불 점멸
    LR_GreOn();                   // 왼쪽, 오른쪽 신호 변경
    delay(15000);                 // 초록불 점등 시간(15초)
    LR_Blink();                   // 왼쪽, 오른쪽 노란불 점멸
    prevT = millis();             // 현재 시간을 이전 시간 변수에 저장
  }
}

void UD_GreOn(){
  digitalWrite(U_GRE, HIGH); digitalWrite(D_GRE, HIGH); // 위쪽, 아래쪽 초록불 on
  digitalWrite(R_RED, HIGH); digitalWrite(L_RED, HIGH); // 왼쪽, 오른쪽 빨간불 on
  digitalWrite(R_GRE, LOW); digitalWrite(L_GRE, LOW);   // 왼쪽, 오른쪽 초록불 off
}

void LR_GreOn() {
  digitalWrite(U_RED, HIGH); digitalWrite(D_RED, HIGH); // 위쪽, 아래쪽 빨간불 on
  digitalWrite(R_GRE, HIGH); digitalWrite(L_GRE, HIGH); // 왼쪽, 오른쪽 초록불 on
  digitalWrite(R_RED, LOW); digitalWrite(L_RED, LOW);   // 왼쪽, 오른쪽 빨간불 off
}

void UD_Blink() {
  digitalWrite(U_GRE, LOW); digitalWrite(D_GRE, LOW);   // 위쪽, 아래쪽 초록불 off
  for(int i = 0; i < 5; i++){                           // 위쪽, 아래쪽 노란불 점멸
    digitalWrite(U_YEL, HIGH); digitalWrite(D_YEL, HIGH);
    delay(UD_BlinkT);                                   // 점멸 간격(1초)
    digitalWrite(U_YEL, LOW); digitalWrite(D_YEL, LOW);
    delay(UD_BlinkT);
    }
}

void LR_Blink() {
  digitalWrite(R_GRE, LOW); digitalWrite(L_GRE, LOW);   // 왼쪽, 오른쪽 초록불 off
  for(int i = 0; i < 5; i++){                           // 왼쪽, 오른쪽 노란불 점멸(5회)
    digitalWrite(R_YEL, HIGH); digitalWrite(L_YEL, HIGH);
    delay(LR_BlinkT);                                   // 점멸 간격(1초)
    digitalWrite(R_YEL, LOW); digitalWrite(L_YEL, LOW);
    delay(LR_BlinkT);
    }
}
