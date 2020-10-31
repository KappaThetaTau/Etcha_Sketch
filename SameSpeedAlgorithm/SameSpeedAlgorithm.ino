const int stepPin = 3; //Initialize Arduino pin that sends steps to motor driver
const int dirPin = 4; //Initialize Arduino pin that controls direction that motor spins
int choice; //Initialize variable named choice for user inputs

float len;
float recordLen;

float positions[] = {0,100,2,4,6,8,10,12,14,0};

float matSize;
float maxJump = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  matSize = sizeof(positions)/sizeof(positions[0]);
  Serial.println(matSize);

  for(int i = 0; i < matSize-1; i++){
    if (abs(positions[i+1] - positions[i]) > maxJump){
      maxJump = abs(positions[i+1] - positions[i]);
    }
  }
  Serial.print(maxJump);
}

void loop() {
  // put your main code here, to run repeatedly:
  float speedFrac = 0;
  float currentStep = 0;
  float prevStep = 0;
  for(int i = 0; i < matSize; i++){
    if (positions[i] > positions[i+1]){
      digitalWrite(dirPin, LOW);
    } else {
      digitalWrite(dirPin, HIGH);
    }
//    Serial.print(positions[i]);
//    Serial.print("    ");
//    Serial.println(positions[i+1]);

    for(int steps = 1; steps < maxJump; steps++){
      speedFrac = abs((positions[i]-positions[i+1])/maxJump);
      //Serial.println(speedFrac);
      currentStep = int(speedFrac*steps);
      prevStep = int(speedFrac*(steps-1));
      if (prevStep != currentStep){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(500);
      } else {
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
      } 
    }
  }
}
