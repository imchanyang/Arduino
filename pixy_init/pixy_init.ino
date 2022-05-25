void setup() { 
  Serial.begin(19200); 
  Serial1.begin(115200); 
} 
void loop(){ 
  if(Serial.available()){ 
    Serial1.println(Serial.read());
  }
}
