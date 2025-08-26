// Arduino pins
#define MOTOR_PWM_PIN 18
#define MOTOR_PLUS 19
#define MOTOR_MINUS 23
void setup() {
  //set Motor control pins in output mode
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(MOTOR_PLUS, OUTPUT);
  pinMode(MOTOR_MINUS, OUTPUT);
  //At power on, all motors should be OFF
  idle();
  //For potential debugging
  //Serial.begin(9600);
}

void idle(void) {
  //Set motor control pins to 0 and PWM pin to LOW. Turns the motor OFF.
  digitalWrite(MOTOR_PLUS, LOW);
  digitalWrite(MOTOR_MINUS, LOW);
  digitalWrite(MOTOR_PWM_PIN, LOW);
}

void run_motor(int driveValue) {
  int direction, m_plus, m_minus, m_pwm;
  /*Negative driveValue values imply that the given driveValue
    should be applied in opposite direction.*/
  //separate driveValue magnitude and direction
  if (driveValue < 0) {
    direction = -1;
    driveValue = -driveValue;
  } else direction = 1;
  if (driveValue > 255) driveValue = 255;
     m_plus = MOTOR_PLUS;
     m_minus = MOTOR_MINUS;
     m_pwm = MOTOR_PWM_PIN;
  //write values to debug code
  //Serial.print(" m_plus: ");
  //Serial.print(m_plus);
  //Serial.print(" m_minus: ");
  //Serial.print(m_minus);
  //Serial.print(" driveValue: ");
  //Serial.println(driveValue);

  //Set rotation direction
  if (direction == 1) {
    digitalWrite(m_plus, HIGH);
    digitalWrite(m_minus, LOW);
  } else {
    digitalWrite(m_plus, LOW);
    digitalWrite(m_minus, HIGH);
  }
  //And set the pwm value
  analogWrite(m_pwm, driveValue);
  //Done!
}

void loop(void) {
int driveValue;
  //In Expt. 4B-1, we run the motor at constant driveValue.
  driveValue = 128; //edit this value for different driveValues.
//Run the motor at this PWM value, measure RPM on scope
//And  Repeat for other PWM values from 32 to 224 in steps of 32.
    run_motor(driveValue);
}
