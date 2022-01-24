

float sensorvolt(){
float temp;

val11=analogRead(A0);

temp=val11/4.092;

val11=(int)temp;

val2=((val11%100)/10.0);

return val2;

delay(1000);
}

float DHThum() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
 if (isnan(h) || isnan(t)) {
   
    
  }else{
    return h;
  }

}
int Ultrasonic() {
  long duration, cm;

  pinMode(pingPin, OUTPUT);


  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);

  cm = microsecondsToCentimeters(duration);
 
  float sum = map(cm, 0, 32, 16, 0);
  if( sum < 0 ) sum = 0;
 
  Serial.print(sum);
  
  Serial.println();
  return sum;
  delay(100);

}

long microsecondsToCentimeters(long microseconds)
{

  return microseconds / 29 / 2;
}
