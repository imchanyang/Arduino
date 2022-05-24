void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT); pinMode(5, OUTPUT);

  pinMode(28, OUTPUT); pinMode(29, OUTPUT);
  pinMode(30, OUTPUT); pinMode(31, OUTPUT);

  pinMode(17, OUTPUT); tone(17, 3000); delay(100); noTone(17);
  Serial1.begin(9600);
}
char Rx_data = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available()) {
    Rx_data = Serial1.read(); Serial1.print(Rx_data);
  }

  analogWrite(4, 50); digitalWrite(28, LOW); digitalWrite(29, HIGH);
  
}
