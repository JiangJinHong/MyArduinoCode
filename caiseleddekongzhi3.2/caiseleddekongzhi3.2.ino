void setup()
{
  pinMode(11, OUTPUT);  //发红色光
  pinMode(10, OUTPUT);  //发绿色光
  pinMode(9, OUTPUT);   //发蓝色光
}
 
void loop()
{
  digitalWrite(11,HIGH); digitalWrite(10,LOW); digitalWrite(9,LOW);
  delay(1000);                    
  digitalWrite(11,LOW); digitalWrite(10,HIGH); digitalWrite(9,LOW);
  delay(1000);                    
  digitalWrite(11,LOW); digitalWrite(10,LOW); digitalWrite(9,HIGH);
  delay(1000);                    
}

