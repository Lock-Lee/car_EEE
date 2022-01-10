void forward() {
  digitalWrite(Motor1, HIGH);
  digitalWrite(Motor2, LOW);
  digitalWrite(Motor3, HIGH);
  digitalWrite(Motor4, LOW);
}
void reward() {
  digitalWrite(Motor1, LOW);
  digitalWrite(Motor2, HIGH);
  digitalWrite(Motor3, LOW);
  digitalWrite(Motor4, HIGH);
}
void left() {
  digitalWrite(Motor1, HIGH);
  digitalWrite(Motor2, LOW);
  digitalWrite(Motor3, LOW);
  digitalWrite(Motor4, LOW);

}
void right() {
  digitalWrite(Motor1, LOW);
  digitalWrite(Motor2, LOW);
  digitalWrite(Motor3, HIGH);
  digitalWrite(Motor4, LOW);

}
void stop() {
  digitalWrite(Motor1, LOW);
  digitalWrite(Motor2, LOW);
  digitalWrite(Motor3, LOW);
  digitalWrite(Motor4, LOW);

}
