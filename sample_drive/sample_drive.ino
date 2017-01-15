//Drives forwards and backwards then turns left then right

int pin_motor_a_dir = 4;
int pin_motor_a_spd = 5;
int pin_motor_b_dir = 7;
int pin_motor_b_spd = 6;

void setup() {
  pinMode(pin_motor_a_dir, OUTPUT);
  pinMode(pin_motor_a_spd, OUTPUT);
  pinMode(pin_motor_b_dir, OUTPUT);
  pinMode(pin_motor_b_spd, OUTPUT);
}

void loop() {

  //Forwards
  digitalWrite(pin_motor_a_dir, 0);
  analogWrite(pin_motor_a_spd, 100);
  digitalWrite(pin_motor_b_dir, 0);
  analogWrite(pin_motor_b_spd, 100);
  delay(1000);
  
  //Backwards
  digitalWrite(pin_motor_a_dir, 1);
  analogWrite(pin_motor_a_spd, 100);
  digitalWrite(pin_motor_b_dir, 1);
  analogWrite(pin_motor_b_spd, 100);
  delay(1000);

  //Left
  digitalWrite(pin_motor_a_dir, 1);
  analogWrite(pin_motor_a_spd, 100);
  digitalWrite(pin_motor_b_dir, 0);
  analogWrite(pin_motor_b_spd, 100);
  delay(1000);

  //Right
  digitalWrite(pin_motor_a_dir, 0);
  analogWrite(pin_motor_a_spd, 100);
  digitalWrite(pin_motor_b_dir, 1);
  analogWrite(pin_motor_b_spd, 100);
  delay(1000);
}
