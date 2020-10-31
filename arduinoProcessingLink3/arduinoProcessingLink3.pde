//this working code recieves positions from processingArduinoLink2 but doesnt have delimiter

import processing.serial.*;

int xpos=90;
int ypos=90;

Serial myPort;
String val;
int a;

void setup()
{
  //size(360,360);
  fullScreen();
  frameRate(100);
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0],19200);
  update(mouseX,mouseY);
  delay(60);
  
}

void draw()
{
  background(127);
  fill(255,0,0);
  rect(width/2,height/2-5,mouseX-width/2,10);
  fill(0,255,0);
  rect(width/2-5,height/2,10,mouseY-height/2);
  //delay(60);
  if ( myPort.available() > 0) 
  
  {  // If data is available,
  val = myPort.readStringUntil('1');         // read it and store it in val
  //val = myPort.readString();
  } 
  //a = Integer.parseInt(val);
  
  val = trim(val);
  
  println(val);
  //if (Integer.parseInt(val) != 1){
  //  //return;
  //  println("Woo!");
  //}
  update(mouseX,mouseY);
}

void update(int x, int y)
{
  xpos = x;
  ypos = y;
  
  myPort.write(xpos+"x");
  myPort.write(ypos+"y");
}
