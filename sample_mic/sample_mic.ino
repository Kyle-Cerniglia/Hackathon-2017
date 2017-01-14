int greatest = 0;
int greatest2 = 0;
int temp = 0;
int temp2 = 0;
int count = 0;
void setup() {
  Serial.begin(9600);

}

void loop() {
  temp = analogRead(21) * 4;
  //temp2 = analogRead(21) * 4;
  if(temp > greatest){
    greatest = temp;
  }
  //if(temp2 > greatest2){
    //greatest2 = temp2;
  //}
  Serial.print(temp);
  Serial.print(":");
  Serial.println(greatest);
  //Serial.print(temp2);
  //Serial.print(":");
  //Serial.println(greatest2);
  //Serial.println();
  
  if(count > 5000){
    count = 0;
    greatest = 0;
    greatest2 = 0;
  }
  count++;
}
