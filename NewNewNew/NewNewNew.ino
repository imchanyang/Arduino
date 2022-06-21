#include <SimpleTimer.h>
SimpleTimer timer;

const int trigPin = 38;
const int echoPin = 37;
int duration;
float distance;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  //타이머
  timer.setInterval(200, Uart1);
  // 모터 
  pinMode(4, OUTPUT); pinMode(5, OUTPUT);
  pinMode(28, OUTPUT); pinMode(29, OUTPUT);
  pinMode(30, OUTPUT); pinMode(31, OUTPUT);
  // 초음파
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
}

unsigned char Uart0ProtocolPointer = 0;
unsigned char Uart0ReciveCheckEnd = 0;
unsigned char Data[12] = {0,};
unsigned int X_center = 0;
unsigned int Y_center = 0;
unsigned int signature = 0;
bool findBallFlag = false;

unsigned int width_1, width_2, height;
int same = 0;
int count = 0;

void UartRxProtocol() {
  unsigned char Uart0_Data;
  if(Serial.available()){
    Uart0_Data = Serial.read();

    switch(Uart0ProtocolPointer) {
      case 0: if(0xaa == Uart0_Data){Uart0ProtocolPointer = 1;}
              else {Uart0ProtocolPointer = 0;}
      break;
      case 1: if(0x55 == Uart0_Data) {Uart0ProtocolPointer = 10;}
              else {Uart0ProtocolPointer = 0;}
      break;
      case 10: Data[0] = Uart0_Data; Uart0ProtocolPointer = 11; break;
      case 11: Data[1] = Uart0_Data; Uart0ProtocolPointer = 12; break;
      case 12: Data[2] = Uart0_Data; Uart0ProtocolPointer = 13; break;
      case 13: Data[3] = Uart0_Data; Uart0ProtocolPointer = 14; break;
      case 14: Data[4] = Uart0_Data; Uart0ProtocolPointer = 15; break;
      case 15: Data[5] = Uart0_Data; Uart0ProtocolPointer = 16; break;
      case 16: Data[6] = Uart0_Data; Uart0ProtocolPointer = 17; break;
      case 17: Data[7] = Uart0_Data; Uart0ProtocolPointer = 18; break;
      case 18: Data[8] = Uart0_Data; Uart0ProtocolPointer = 19; break;
      case 19: Data[9] = Uart0_Data; Uart0ProtocolPointer = 20; break;
      case 20: Data[10] = Uart0_Data; Uart0ProtocolPointer = 21; break;
      case 21: Data[11] = Uart0_Data; Uart0ProtocolPointer = 100; break;

      case 100: if(0x00 == Uart0_Data) {Uart0ProtocolPointer = 101;}
                else {Uart0ProtocolPointer = 0;}
      break;
      case 101: if(0x00 == Uart0_Data) {Uart0ProtocolPointer = 102;}
                else {Uart0ProtocolPointer = 0;}
      break;
      case 102:if(0x00 == Uart0_Data) {Uart0ProtocolPointer = 103;}
                else {Uart0ProtocolPointer = 0;}
      break;
      case 103: if(0x55 == Uart0_Data) {
                Uart0ProtocolPointer = 0; Uart0ReciveCheckEnd = 1;
      }
               else {Uart0ProtocolPointer = 0;}
      break;
      default : Uart0ProtocolPointer = 0;
      break;
    }
  }
}

void Serial_Main0(void) {
  if(Uart0ReciveCheckEnd == 1) {
    Uart0ReciveCheckEnd = 0;
    if(Data[6] == 1) {
      X_center = 256 + Data[5];
    }
    else {
      X_center = Data[5];
    }
       Y_center = Data[7];
       width_1 = Data[9];
       width_2 = Data[10];
       height = Data[11];
       signature = Data[3];
  }
}

//------------------------------------------------------------------------------------------
void turnRight(int speed){
  analogWrite(4, speed+20); digitalWrite(28, LOW); digitalWrite(29, HIGH);
  analogWrite(5, speed); digitalWrite(30, HIGH); digitalWrite(31, HIGH);
}
void turnLeft(int speed){
  analogWrite(4, speed); digitalWrite(28, LOW); digitalWrite(29, HIGH); 
  analogWrite(5, speed+20); digitalWrite(30, HIGH); digitalWrite(31, HIGH);
}

void goStraight(int speed){
  analogWrite(4, speed); digitalWrite(28, LOW); digitalWrite(29, HIGH); 
  analogWrite(5, speed); digitalWrite(30, HIGH); digitalWrite(31, HIGH);
}
void directionStop(int speed){
  analogWrite(4, speed); digitalWrite(28, HIGH); digitalWrite(29, LOW); 
  analogWrite(5, speed); digitalWrite(30, HIGH); digitalWrite(31, LOW);
}
void stop(int speed){
  analogWrite(4, speed); digitalWrite(28, LOW); digitalWrite(29, LOW);
  analogWrite(5, speed); digitalWrite(30, HIGH); digitalWrite(31, LOW);
}
void binglebangle(){
  analogWrite(4, 35); digitalWrite(28, HIGH); digitalWrite(29, HIGH); 
  analogWrite(5, 35); digitalWrite(30, HIGH); digitalWrite(31, HIGH);
}


void ballTracking() {
  // 방향
  // 중앙에 있는 경우
  binglebangle();
  if(130 <= X_center && X_center < 200 && signature == 1) {
     goStraight(70);
  }
  // 좌측에 있는 경우
  else if(0 <= X_center && X_center < 130 && signature == 1) {
      turnRight(50);
  }
  // 우측에 있는 경우
  else if(200 <= X_center && X_center < 317 && signature == 1) {
      turnLeft(50);
  }
  // 못찾았을 경우
  if(count >= 20 ) {
    binglebangle();
  }
}

void ballTrackingBlue() {
  // 방향
  // 중앙에 있는 경우
  binglebangle();
  if(125 <= X_center && X_center < 195 && signature == 4) {
     goStraight(70);
  }
  // 좌측에 있는 경우
  else if(0 <= X_center && X_center < 135 && signature == 4) {
      turnRight(50);
  }
  // 우측에 있는 경우
  else if(195 <= X_center && X_center < 317 && signature == 4) {
      turnLeft(50);
  }
  // 못찾았을 경우
  if(count >= 20) {
    binglebangle();
  }
}

void goalTrackingRed() {
    binglebangle();
    if(135 <= X_center && X_center < 195 && signature == 3) {
     goStraight(80);
  }
  // 좌측에 있는 경우
  else if(0 <= X_center && X_center < 135 && signature == 3) {
      turnRight(45);
  }
  // 우측에 있는 경우
  else if(195 <= X_center && X_center < 317 && signature == 3) {
      turnLeft(45);
  }
  // 못찾았을 경우
  if(count >= 20 ) {
      binglebangle();
    }
}

void goalTrackingGreen() {

    if(135 <= X_center && X_center < 195 && signature == 2) {
     goStraight(80);
  }
  // 좌측에 있는 경우
  else if(0 <= X_center && X_center < 135 && signature == 2) {
      turnRight(45);
  }
  // 우측에 있는 경우
  else if(195 <= X_center && X_center < 317 && signature == 2) {
      turnLeft(45);
  }
  // 못찾았을 경우
  if(count >= 20 ) {
      binglebangle();
    }
}

void sbcg() {
    binglebangle();

  if(135 <= X_center && X_center < 195 && signature == 1) {
     if(distance < 13) {
        stop(1);
        goStraight(100);
     }
     else {
        goStraight(60);
     } 
  }
  // 좌측에 있는 경우
  else if(0 <= X_center && X_center < 135 && signature == 1) {
    analogWrite(4, 45); digitalWrite(28, LOW); digitalWrite(29, HIGH);
    analogWrite(5, 45); digitalWrite(30, HIGH); digitalWrite(31, LOW);
  }
  // 우측에 있는 경우
  else if(195 <= X_center && X_center < 317 && signature == 1) {
     analogWrite(4, 45); digitalWrite(28, LOW); digitalWrite(29, LOW); 
     analogWrite(5, 45); digitalWrite(30, HIGH); digitalWrite(31, HIGH);
  }
  // 못찾았을 경우
  if(count >= 20 ) {
    binglebangle();
  }
}

void defence() {
  binglebangle();
  // ballTracking();
}

//---------------------------------------------------------------------------------------------------------------------
void Uart1() {
  if(same == X_center) {
    count++;
  }
  else {
    count = 0;
  }
  same = X_center;
//------------------------------------------------------
  Serial1.print("count : ");
  Serial1.println(count);
  Serial1.print(X_center);
  Serial1.print(' ');
  Serial1.println(Y_center);

  Serial1.print(width_1);
  Serial1.print(' ');
  Serial1.print(width_2);
  Serial1.print(' ');
  Serial1.println(height);

  Serial1.print("sig");
  Serial1.print(':');
  Serial1.println(signature);

// ------------------------------------------------
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 /2;
  

// 수비모드
 if(distance > 35 ) { 
    goalTrackingGreen();
  
 }
 else if(distance < 35){
    timer.setInterval(200, Uart2);
  
 }
}

void Uart2() {
  binglebangle();
}


void loop() {
  timer.run();
  UartRxProtocol();
  Serial_Main0();
}
