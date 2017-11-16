/*
  - 좌회전, 우회전 신호를 생략한 사거리 신호등
    보행자 버튼은 현재 초록불인 신호등을 빨간불로
    현재 빨간불인 신호들을 초록불로
*/
// 위쪽, 아래쪽 신호등
#define UD_RED 10
#define UD_YEL 9
#define UD_GRE 8
// 오른쪽, 왼쪽 신호등       
#define RL_RED 13
#define RL_YEL 12
#define RL_GRE 11       
// 보행자 버튼
#define BUTTON 2

int spareTimeNum[10][8][8] = {
  {
    // 0
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  {
    // 1
    { 0, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 1, 1, 1 }
  },
  {
    // 2
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 1, 1, 0 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 1 }
  },
  {
    // 3
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  {
    // 4
    { 1, 0, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 }
  },
  {
    // 5
    { 1, 1, 1, 1 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 0 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  {
    // 6
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  {
    // 7
    { 1, 1, 1, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 }
  },
  {
    // 8
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  {
    // 9
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  }  
};

int pedLightSign[2][8][8] = {
  {
    // 정지
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 1, 1, 0, 1, 0 },
    { 0, 1, 0, 1, 1, 0, 1, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 }  
  },
  {
    // 보행
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 1 },
    { 0, 1, 0, 1, 1, 0, 1, 0 },
    { 0, 1, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 1, 0 },
    { 0, 0, 1, 0, 0, 0, 1, 0 }
  }
};

int spareTimeCol[] = { 21, 20, 19, 18, 17, 16, 15, 14 };
int spareTimeRow[] = { 29, 28, 27, 26, 25, 24, 23, 22 };  

int pedLightCol[]  = { 39, 38, 37, 36, 35, 34, 33, 32 };
int pedLightRow[]  = { 49, 48, 47, 46, 45, 44, 43, 42 };

#define interval 10000   // 시간 간격 기본값(10초)

unsigned long prevT = 0;
volatile bool button = true;
void butState() {   button = false;    }

void setup() {
  // 상하 신호등 출력 핀모드 설정
  pinMode(UD_RED, OUTPUT);
  pinMode(UD_YEL, OUTPUT);
  pinMode(UD_GRE, OUTPUT);
  // 좌우 신호등 출력 핀모드 설정
  pinMode(RL_RED, OUTPUT);
  pinMode(RL_YEL, OUTPUT);
  pinMode(RL_GRE, OUTPUT);
  // 보행자 Dot-Matrix 신호등 출력 핀모드 설정
  for(int i = 0; i < 8; i++ )
  {
    pinMode(spareTimeCol[i], OUTPUT);
    pinMode(spareTimeRow[i], OUTPUT);
    pinMode(pedLightCol[i], OUTPUT);
    pinMode(pedLightRow[i], OUTPUT);
  }
  // 보행자 버튼 핀모드 설정(풀업저항)
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(0, butState, FALLING);
}

void loop() {
  
  UD_GreOn();                    // 위쪽, 아래쪽 신호 변경
  
  unsigned long startTime, endTime;
  startTime = endTime = millis();
  while (endTime - startTime < interval) { // 10초 동안
    SpareTimeNumM(interval / 1000);        // 10
    PedLightSignM(0);           // 보행자 신호 빨간불
    if (button == false) {      //스위치가 눌렸으면
      button = true;        
      unsigned int pedSignStart, pedSignEnd;
      for (int num = 3; num >= 0; num--) {  // 3초 대기
        pedSignStart = pedSignEnd = millis();
        while (pedSignEnd - pedSignStart < 1000 ) { //
          SpareTimeNumM(interval / 1000);
          PedLightSignM(0);
          pedSignEnd = millis();  
        }
      }
      UD_Blink();
      LR_GreOn();
      for (int num = (interval / 1000); num >= 0; num--) {
        pedSignStart = pedSignEnd = millis();
        while (pedSignEnd - pedSignStart < 1000) {
          if(button == false){  // 버튼이 또 눌리면
            button = true; 
            num = (interval / 1000);
          }
          SpareTimeNumM(num);
          PedLightSignM(1);
          pedSignEnd = millis();
        }
      }
      LR_Blink();
      UD_GreOn();
      startTime = millis(); //차량 신호의 길이를 0초부터 다시 시작
   }
    endTime = millis();
  }
  UD_Blink();
  LR_GreOn();  

  for (int num = (interval / 1000); num >= 0; num--) {
    unsigned long startTime, endTime;
    startTime = endTime = millis();
    while (endTime - startTime < 1000) {
      SpareTimeNumM(num);
      PedLightSignM(1);
      if(button == false){
        button = true;
        num = (interval / 1000);
      }
      endTime = millis();
    }
  }
  LR_Blink();
}
// --------------------------------------------------------함수

void ClearSpareT(){ // 숫자 도트매트릭스 끄기
    for(int i = 0; i < 8; i++){
        digitalWrite( spareTimeCol[i], HIGH);
        digitalWrite( spareTimeRow[i], LOW);
      }
  }
  
void ClearPedL(){ // 보행자 그림 도트매트릭스 끄기
  for(int i = 0; i < 8; i++){
        digitalWrite( pedLightCol[i], HIGH);
        digitalWrite( pedLightRow[i], LOW);
      }
 }

void PedLightSignM(int on1){
    for(int r = 0; r < 8; r++){
        ClearPedL();
        digitalWrite(pedLightRow[r], HIGH);
        for(int c = 0; c < 8; ++c){
            if(pedLightSign[on1][r][c]) 
              digitalWrite(pedLightCol[c], LOW);
          }
          delay(1);
          ClearPedL();
      }
  }
void SpareTimeNumM(int num){
     for(int r = 0; r < 8; r++){
         ClearSpareT();
         digitalWrite(spareTimeRow[r], HIGH);
         for(int c = 0; c < 4; c++){
             if(spareTimeNum[num / 10][r][c])
               digitalWrite(spareTimeCol[c], LOW);
          }
         for (int c = 0; c < 4; ++c){ 
             if (spareTimeNum[num % 10][r][c]) 
               digitalWrite(spareTimeCol[c + 4], LOW);
          }  
          delay(1);
          ClearSpareT();
       }
 }
  
void UD_GreOn(){
  digitalWrite(UD_GRE, HIGH); digitalWrite(UD_RED, LOW);   // 위쪽, 아래쪽 초록불 on, 빨간불 off
  digitalWrite(RL_RED, HIGH); digitalWrite(RL_GRE, LOW);   // 왼쪽, 오른쪽 빨간불 on, 초록불 off
}

void LR_GreOn() {
  digitalWrite(RL_GRE, HIGH); digitalWrite(RL_RED, LOW);   // 왼쪽, 오른쪽 초록불 on, 빨간불 off
  digitalWrite(UD_RED, HIGH); digitalWrite(UD_GRE, LOW);   // 위쪽, 아래쪽 빨간불 on, 초록불 off  
}

void UD_Blink() {
  digitalWrite(UD_GRE, LOW);                            // 위쪽, 아래쪽 초록불 off
 
  unsigned long UD_startTime, UD_endTime;
  UD_startTime = UD_endTime = millis();
  while (UD_endTime - UD_startTime <= interval) {
    SpareTimeNumM(interval / 1000);
    PedLightSignM(0);
 
    unsigned long UD_blinkStart, UD_blinkEnd;
    UD_blinkStart = UD_blinkEnd = millis();
    while (UD_blinkEnd - UD_blinkStart < 500) {
      SpareTimeNumM(interval / 1000);
      PedLightSignM(0);
      digitalWrite(UD_YEL, HIGH);
      UD_blinkEnd = millis();
    }
    UD_blinkStart = UD_blinkEnd = millis();
    while (UD_blinkEnd - UD_blinkStart < 500) {
      SpareTimeNumM(interval / 1000);
      PedLightSignM(0);
      digitalWrite(UD_YEL, LOW);
      UD_blinkEnd = millis();
    }
   UD_endTime = millis();
  }
}


void LR_Blink() {
  digitalWrite(RL_GRE, LOW);                             // 왼쪽, 오른쪽 초록불 off
 
  unsigned long LR_startTime, LR_endTime;
  LR_startTime = LR_endTime = millis();
  while (LR_endTime - LR_startTime <= interval) {
    SpareTimeNumM(interval / 1000);
    PedLightSignM(0);
 
    unsigned long LR_blinkStart, LR_blinkEnd;
    LR_blinkStart = LR_blinkEnd = millis();
    while (LR_blinkEnd - LR_blinkStart < 500) {
       SpareTimeNumM(interval / 1000);
       PedLightSignM(0);
      digitalWrite(RL_YEL, HIGH);
      LR_blinkEnd = millis();
    }
    LR_blinkStart = LR_blinkEnd = millis();
    while (LR_blinkEnd - LR_blinkStart < 500) {
      SpareTimeNumM(interval / 1000);
      PedLightSignM(0);
      digitalWrite(RL_YEL, LOW);
      LR_blinkEnd = millis();
    }
    LR_endTime = millis();
  }
}
