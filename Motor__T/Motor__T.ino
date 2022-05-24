int encoder0PinA = 8;
int encoder0PinB = 9;

int encoder0Pos = 0;
int encoder0PinALast = LOW;

int n = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
    pinMode(28, OUTPUT); pinMode(29, OUTPUT);
  Serial1.begin (9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  n = digitalRead(encoder0PinA);
    analogWrite(4, 50); digitalWrite(28, LOW); digitalWrite(29, HIGH);

  if((encoder0PinALast == LOW) && (n == HIGH)) {
    if(digitalRead(encoder0PinB) == LOW) {
      encoder0Pos--;
    }
    else {
      encoder0Pos++;
    }
    Serial1.println(encoder0Pos);
  }
  encoder0PinALast = n;
}
