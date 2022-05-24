void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
//  pinMode(43, OUTPUT); pinMode(40, OUTPUT);
//  digitalWrite(43, LOW); digitalWrite(40, LOW);

}

char RX_Date = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) {
    //BT->USB
    Serial1.write(Serial.read());
  }
  if(Serial1.available()) {
    //USB->BT
    Serial.write(Serial1.read());
  }
}

//RX_Data = Serial.read();
//Serial1.print(RX_Data);
//if(RX_Data == '7') { digitalWrite(43, HIGH);}
//else if(RX_Data == '8') {digitalWrite(40, HIGH);}
//else if(RX_Data == '9') {
//digitalWrite(43, LOW); digitalWrite(40, LOW);}

//Serial.write(Serial1.read());
