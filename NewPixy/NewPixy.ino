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
    X_center = Data[5];
    Y_center = Data[7];
    
  }

}

void Uart1() {
  Serial1.print(X_center);
  Serial1.print(' ');
  Serial1.println(Y_center);
    // 중앙에 있는 경우 : 직
  if(150 < X_center && X_center < 190) {
    analogWrite(4, 50); digitalWrite(28, HIGH); digitalWrite(29, HIGH);  
    analogWrite(5, 50); digitalWrite(30, LOW); digitalWrite(31, HIGH);
  }
  // 좌측에 있는 경우 : 
  else if(0 < X_center && X_center < 150) {
    analogWrite(4, 50); digitalWrite(28, HIGH); digitalWrite(29, HIGH);  
    analogWrite(5, 50); digitalWrite(30, LOW); digitalWrite(31, HIGH);
  }
  // 우측에 있는 경우 :
  else if(190 < X_center && X_center < 255) {
    analogWrite(5, 50); digitalWrite(30, LOW); digitalWrite(31, HIGH );
    analogWrite(4, 50); digitalWrite(28, HIGH); digitalWrite(29, HIGH);  
  }
}

void loop() {
  timer.run();
  UartRxProtocol();
  Serial_Main0();


}
