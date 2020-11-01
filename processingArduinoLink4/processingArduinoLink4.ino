//this working code recieves positions from arduinoProcessingLink2 but doesnt have delimiter

int ypos = 0;
int xpos = 0;

const int stepPinx = 3; //Initialize Arduino pin that sends steps to motor driver
const int dirPinx = 4; //Initialize Arduino pin that controls direction that motor spins
const int stepPiny = 5;
const int dirPiny = 6;

float positions[] = {0, 0};
float matSize = 2;
float maxJump = 0;

int differencex;
int differencey;

void setup() {
  pinMode(stepPinx, OUTPUT);
  pinMode(dirPinx, OUTPUT);
  pinMode(stepPiny, OUTPUT);
  pinMode(dirPiny, OUTPUT);

  Serial.begin(19200); // 19200 is the rate of communication
  Serial.println("Rolling"); // some output for debug purposes.
  Serial.print("A");
  pinMode(13, OUTPUT);
}

void loop() {
  static int v = 0; // value to be sent to the motor (0-180)
  if ( Serial.available()) {
    char ch = Serial.read(); // 124x75y
    switch (ch) { // switch based on the value of ch
      case '0'...'9': // if it's numeric
        v = v * 10 + ch - '0';
        /*
           ch = 124x
           v = 1
           v = 12
           v = 124

        */
        break;
      case 'x': // if it's x

        //Serial.print("Old Position: ");
        //Serial.print(xpos);

        //Serial.println(xpos);

        //        Serial.print(xpos);
        //        Serial.println("x");

        differencex = v - xpos;
        xpos = v;
        //Serial.print("   New Position: ");
        //Serial.println(xpos);
        if (differencex < 0) {
          digitalWrite(dirPinx, LOW);
        } else {
          digitalWrite(dirPinx, HIGH);
        }
        differencex = abs(map(differencex, 0, 360, 0, 200)); //maps the choice variable from degrees to positive number of steps
        //This for loop steps the motor forwards until the user input "choice" is reached
        //The timing in micro seconds is specific to the type of stepper motor used
        digitalWrite(13, LOW);

        v = 0;
        //Serial.print("X difference: ");
        //Serial.println(differencex); //Prints "choice" to serial monitor in number of steps

        Serial.println(1);


        break;
      case 'y':

        differencey = v - ypos;
        ypos = v;

        if (differencey < 0) {
          digitalWrite(dirPiny, LOW);
        } else {
          digitalWrite(dirPiny, HIGH);
        }
        differencey = abs(map(differencey, 0, 360, 0, 200)); //maps the choice variable from degrees to positive number of steps
        //This for loop steps the motor forwards until the user input "choice" is reached
        //The timing in micro seconds is specific to the type of stepper motor used
        digitalWrite(13, LOW);

        v = 0;
        //        Serial.print(ypos);
        //        Serial.println("y");
        break;
    }
    positions[0] = xpos;
    positions[1] = ypos;

    if (differencex > differencey) {
      maxJump = differencex;

      float speedFrac = abs(differencey / maxJump);
      float currentStep = 0;
      float prevStep = 0;
      for (int i = 0; i < matSize; i++) {
        if (differencex < 0) {
          digitalWrite(dirPinx, LOW);
        } else {
          digitalWrite(dirPinx, HIGH);
        }
        if (differencey < 0) {
          digitalWrite(dirPiny, LOW);
        } else {
          digitalWrite(dirPiny, HIGH);
        }


        for (int steps = 1; steps < maxJump; steps++) {
          currentStep = int(speedFrac * steps);
          prevStep = int(speedFrac * (steps - 1));

          digitalWrite(stepPinx, HIGH);
          delayMicroseconds(500);
          digitalWrite(stepPinx, LOW);
          delayMicroseconds(500);
          if (prevStep != currentStep) {
            digitalWrite(stepPiny, HIGH);
            delayMicroseconds(500);
            digitalWrite(stepPiny, LOW);
            delayMicroseconds(500);
          } else {
            digitalWrite(stepPiny, LOW);
            delayMicroseconds(1000);
          }
        }
      }
    } else {
      maxJump = differencey;

      float speedFrac = abs(differencex / maxJump);
      float currentStep = 0;
      float prevStep = 0;
      for (int i = 0; i < matSize; i++) {
        if (differencey < 0) {
          digitalWrite(dirPiny, LOW);
        } else {
          digitalWrite(dirPiny, HIGH);
        }
        if (differencex < 0) {
          digitalWrite(dirPinx, LOW);
        } else {
          digitalWrite(dirPinx, HIGH);
        }


        for (int steps = 1; steps < maxJump; steps++) {
          currentStep = int(speedFrac * steps);
          prevStep = int(speedFrac * (steps - 1));

          digitalWrite(stepPiny, HIGH);
          delayMicroseconds(500);
          digitalWrite(stepPiny, LOW);
          delayMicroseconds(500);
          if (prevStep != currentStep) {
            digitalWrite(stepPinx, HIGH);
            delayMicroseconds(500);
            digitalWrite(stepPinx, LOW);
            delayMicroseconds(500);
          } else {
            digitalWrite(stepPinx, LOW);
            delayMicroseconds(1000);
          }
        }
      }
    }



    //Enter main code in here
  }
  Serial.print("We Have Reached Our Position");

}
