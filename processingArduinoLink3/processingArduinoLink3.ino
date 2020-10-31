//this working code recieves positions from arduinoProcessingLink2 but doesnt have delimiter

int ypos = 0;
int xpos = 0;

const int stepPinx = 3; //Initialize Arduino pin that sends steps to motor driver
const int dirPinx = 4; //Initialize Arduino pin that controls direction that motor spins
int choicex; //Initialize variable named choice for user inputs
int differencex;

void setup() {
  pinMode(stepPinx, OUTPUT);
  pinMode(dirPinx, OUTPUT);

  Serial.begin(19200); // 19200 is the rate of communication
  Serial.println("Rolling"); // some output for debug purposes.
  Serial.print("A");
  pinMode(13,OUTPUT);
} 

void loop() {
  static int v = 0; // value to be sent to the motor (0-180)
  if ( Serial.available()) {
    char ch = Serial.read(); // 124x75y
    switch (ch) { // switch based on the value of ch
      case '0'...'9': // if it's numeric
        v = v * 10 + ch - '0';
        /*
         * ch = 124x
         * v = 1
         * v = 12
         * v = 124
         * 
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
        digitalWrite(13,LOW);
        for (int x = 0; x < differencex; x++) {
          digitalWrite(stepPinx, HIGH);
          delayMicroseconds(500);
          digitalWrite(stepPinx, LOW);
          delayMicroseconds(500);
          digitalWrite(13,HIGH);
        }
        digitalWrite(13,LOW);
        v = 0;
        //Serial.print("X difference: ");
        //Serial.println(differencex); //Prints "choice" to serial monitor in number of steps
        
        Serial.println(1);


        break;
      case 'y':

        ypos = v;
        v = 0;
        //        Serial.print(ypos);
        //        Serial.println("y");
        break;
    }
    //Enter main code in here
  }

}
