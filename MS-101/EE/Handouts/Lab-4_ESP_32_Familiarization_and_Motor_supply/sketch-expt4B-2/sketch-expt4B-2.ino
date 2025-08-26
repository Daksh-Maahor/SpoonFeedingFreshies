// Arduino pins for PWM outputs connected to Motor Enables.
#define MOTOR_PWM 6
// Arduino digital pins for motor direction
#define MOTOR_PLUS 10
#define MOTOR_MINUS 11
void setup() {
  int i;
  // Set Motor control pins in output mode
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_PLUS, OUTPUT);
  pinMode(MOTOR_MINUS, OUTPUT);
  //At power on, the motor should be OFF
  idle();
  //For potential debugging
  //Serial.begin(9600);
}
void idle(void) {
  /* Turns the motor OFF */
  digitalWrite(MOTOR_PLUS, LOW);
  digitalWrite(MOTOR_MINUS, LOW);
  digitalWrite(MOTOR_PWM, LOW);
}
void run_motor(int pwmValue) {
  int direction, m_plus, m_minus, m_pwm;
  /*negative values of pwmValue imply that absolute value of pwmValue
   *should be applied in reverse direction.*/
  if (pwmValue < 0) {
    direction = -1;
    pwmValue = -pwmValue;
  } else direction = 1;
  if (pwmValue > 255) pwmValue = 255;

     m_plus = MOTOR_PLUS;
     m_minus = MOTOR_MINUS;
     m_pwm = MOTOR_PWM;
  if (direction == 1) {
    digitalWrite(m_plus, HIGH);
    digitalWrite(m_minus, LOW);
  } else {
    digitalWrite(m_plus, LOW);
    digitalWrite(m_minus, HIGH);
  }
  //write values to debug code
  //Serial.print(" m_plus: ");
  //Serial.print(m_plus);
  //Serial.print(" m_minus: ");
  //Serial.print(m_minus);
  //Serial.print(" pwmValue: ");
  //Serial.println(pwmValue);
  //Set rotation direction
  //And set the pwm value
  analogWrite(m_pwm, pwmValue);
  //Done!
}

void loop(void) {
int pwmValue;
  //In Expt. 4B-2, we accelerate, decelerate, stop
  //Then accelerate decelerate in the opposite direction. 
  //Accelerate from 0 to max
  for (pwmValue = 0; pwmValue < 255; pwmValue += 16) {
    run_motor(pwmValue);
    delay(200);
  }
  //Decelerate to 0 then accelerate in the reverse direction to max
  for (pwmValue = 240; pwmValue > -255; pwmValue -= 16) {
    run_motor(pwmValue);
    delay(200);
  }
  //Decelerate from max pwmValue in reverse direction to static
  for (pwmValue = -240; pwmValue < 0; pwmValue += 16) {
    run_motor(pwmValue);
    delay(200);
  }
  //Take a breath ... and repeat the loop
  delay(500);
}
