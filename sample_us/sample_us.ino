int delayus = 0;
int range = 0;

void setup() {
  pinMode(13, OUTPUT);  //SOUT
  pinMode(11, INPUT);   //SIN
  Serial.begin(9600);
}

void loop() {
  digitalWrite(13, LOW);
  delayMicroseconds(2);
  digitalWrite(13, HIGH);
  delayMicroseconds(10);
  digitalWrite(13, LOW);
  delayus = pulseIn(11, HIGH, 30000);
  
  range = delayus;
  range /= 59;
  Serial.println(range);
}
