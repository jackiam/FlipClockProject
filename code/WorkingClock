#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

int steps = 16;        //Set steps for 16-16-18.
int* stepptr = &steps; //pointer to reassign steps.
int count = 0;         //Set count at zero, should count forever.

// Set HIGH/LOW based on the step sequence. This will vary based on your motor. 
// You can check your coils with either a multimeter or a piece of wire. Use continuity on multimeter or
// a piece of wire. Connect 2 motor pins with a single piece of wire. If they are part of the same coil, the motor
// should be more difficult to rotate by hand.

const int stepSequence[4][4] = {
  {HIGH, LOW, HIGH, LOW},  // Step 1
  {LOW, HIGH, HIGH, LOW},  // Step 2
  {LOW, HIGH, LOW, HIGH},  // Step 3
  {HIGH, LOW, LOW, HIGH}   // Step 4
};

int stepIndex = 0;  // Step position tracker

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Start with motor off
  disableMotor();
}

void loop() {
  // Step the motor stepptr times smoothly.
  for (int i = 0; i < *stepptr; i++) {  //edited after
    stepMotor();
    delayMicroseconds(2000);  // Smooth movement with precise delay
  }

  // Turning off motor to prevent overheating. This dramatically reduced motor and motor controller temps.
  // They are now about room temperature.
  disableMotor();

  // This code makes up for uneven step numbers. For a true minute I need 16.666... steps.
  // This is not achievable with 200 steps per motor revolution (steps per rev may vary with motor type). 
  // So I make up for with 16-16-18.  
  //add 1 to count
  count++;

  int mod3 = count % 3;
  int mod9 = count % 9;

  if (mod9 == 0){ //probably not needed due to mod3 being below, but this code has near 100% accuracy, so I'm keeping it.
    *stepptr = 18;
  }
  if (mod3 == 0){ //Every third step adds 2 steps to make up for 0.666... steps needed.
    *stepptr = 18;
  }
  else{
    *stepptr = 16;
  }
  // Wait 59.875 seconds. Not 60 seconds because motor takes approximately 0.125 seconds to move (steps).
  delay(59875);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void stepMotor() {

  digitalWrite(IN1, stepSequence[stepIndex][0]);
  digitalWrite(IN2, stepSequence[stepIndex][1]);
  digitalWrite(IN3, stepSequence[stepIndex][2]);
  digitalWrite(IN4, stepSequence[stepIndex][3]);

  // Move to the next step
  stepIndex = (stepIndex + 1) % 4;
}

// Function to disable motor and prevent overheating
// Turning off motor to prevent overheating. This dramatically reduced motor and motor controller temps.
// They are now about room temperature.
void disableMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
