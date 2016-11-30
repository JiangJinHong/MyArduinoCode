void  setup( ) {
  Serial.begin(115200);
}

void loop( ) {
 float vi=analogRead(A2)/1023.0*5;
 float vo=analogRead(A3)/1023.0*5;

 Serial.print("Input voltage is  "); 
 Serial.print(vi); Serial.println("V");

 Serial.print("Output voltage is "); 
 Serial.print(vo); Serial.println("V");
 delay(1000);
}
