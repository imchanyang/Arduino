#include <SimpleTimer.h>

SimpleTimer timer;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  timer.setInterval(200, Uart1);


  pinMode(4, OUTPUT); pinMode(5, OUTPUT);

  pinMode(28, OUTPUT); pinMode(29, OUTPUT);
  pinMode(30, OUTPUT); pinMode(31, OUTPUT);

 
}
// 현재 x축 값이 255까지 밖에 안된
unsigned char Uart0ProtocolPointer = 0;
unsigned char Uart0ReciveCheckEnd = 0;
unsigned char Data[12] = {0,};
unsigned int X_center = 0;
unsigned int Y_center = 0;

unsigned int X_center_1 =0, X_center_2 =0; 
unsigned int Y_center_1 =0, Y_center_2 = 0; 

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
  }


}

void Uart1() {

  if(same == X_center) {
    count++;
  }
  else {
    count = 0;
  }
  Serial1.print("count : ");
  Serial1.println(count);
  Serial1.print(X_center);
  Serial1.print(' ');
  Serial1.println(Y_center);

  same = X_center;

  Serial1.print(width_1);
  Serial1.print(' ');
  Serial1.print(width_2);
  Serial1.print(' ');
  Serial1.println(height);


  // 방향
  // 중앙에 있는 경우
  if(120 <= X_center && X_center < 210) {
     analogWrite(4, 30); digitalWrite(28, HIGH); digitalWrite(29, LOW); 
     analogWrite(5, 30); digitalWrite(30, HIGH); digitalWrite(31, LOW);
  // 거리
  if(50 >= width_1) {
      analogWrite(4, 25); digitalWrite(28, HIGH); digitalWrite(29, HIGH);
      analogWrite(5, 25); digitalWrite(30, LOW); digitalWrite(31, HIGH);
  }
//  else if(65 <= width_1) { 
//      analogWrite(4, 25); digitalWrite(28, LOW); digitalWrite(29, HIGH);
//      analogWrite(5, 25); digitalWrite(30, HIGH); digitalWrite(31, HIGH);
//  }
  else {
      analogWrite(4, 25); digitalWrite(28, LOW); digitalWrite(29, LOW);
      analogWrite(5, 25); digitalWrite(30, HIGH); digitalWrite(31, LOW);
  }
  }
  // 좌측에 있는 경우
  else if(0 <= X_center && X_center < 120) {
      analogWrite(4, 25); digitalWrite(28, HIGH); digitalWrite(29, HIGH); 
      analogWrite(5, 25); digitalWrite(30, HIGH); digitalWrite(31, HIGH);
     
  }
  // 우측에 있는 경우
  else if(210 <= X_center && X_center < 317) {
      analogWrite(4, 25); digitalWrite(28, LOW); digitalWrite(29, HIGH);
      analogWrite(5, 25); digitalWrite(30, LOW); digitalWrite(31, HIGH);
  }

  // 못찾았을 경우
  else if(count == 20) {
    analogWrite(4, 25); digitalWrite(28, HIGH); digitalWrite(29, HIGH); 
     analogWrite(5, 25); digitalWrite(30, HIGH); digitalWrite(31, HIGH);
  }


  
}

void loop() {
  timer.run();
  UartRxProtocol();
  Serial_Main0();
}
