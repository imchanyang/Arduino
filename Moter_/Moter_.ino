void setup() {
  // put your setup code here, to run once:
  pinMode(8, INPUT); pinMode(9, INPUT); pinMode(10, INPUT); pinMode(11, INPUT);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial1.print(digitalRead(8)); Serial1.print(' ');
  Serial1.print(digitalRead(9)); Serial1.print(' ');
  Serial1.print(digitalRead(10)); Serial1.print(' ');
  Serial1.print(digitalRead(11)); Serial1.print(' ');
  Serial1.print('\n');
  delay(100);
  

}
