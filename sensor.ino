

float sensorAmp () {
  double c = getCA();
  Serial.println(c);
  return c;
  delay(1000);
}
double getCA() {
  int count = 200;
  double sum = 0;
  for (int i = 0; i < count; i++) {
    sum += getC();
  }
  double val = sum / count;
  return val;
}
// อ่านค่ากระแส
double getC() {
  int a = analogRead(A0);
  double v = (a / 1024.0) * 5000;
  double c = (v - offset) / sensitive;
  return c;
}

void wild_speed() {

 
 pulses++;
  if (millis() - timeold >= 1000) {
    //Don't process interrupts during calculations
    detachInterrupt(0);
    rpm = (60 * 1000 / pulsesperturn ) / (millis() - timeold) * pulses;
    timeold = millis();
    pulses = 0;
  }  
   Serial.print("Analog Value =");
  Serial.println(rpm);
 
  
  
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
  if( sum > 16 ) sum = 16;
  Serial.print(sum);
  
  Serial.println();
  return sum;
  delay(100);

}

long microsecondsToCentimeters(long microseconds)
{

  return microseconds / 29 / 2;
}
