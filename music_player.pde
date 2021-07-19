import processing.serial.*;
import ddf.minim.*;
 
Serial myPort;
Minim minim;
AudioPlayer player;
byte startcode = 97;
byte stopcode = 23;
  
void setup()
{
  // In the next line, you'll need to change this based on your USB port name
  // For windows this port name is usually COM3
  myPort = new Serial(this, "COM3", 9600);
  minim = new Minim(this);
  
  // Put in the name of your sound file below, and make sure it is in the same directory
  player = minim.loadFile("C:\\Users\\UserName\\Downloads\\processing-3.5.4-windows64\\processing-3.5.4\\BRAHMS.mp3"); //Play this song //For my case the mp3 file was in downloads folder
}
 
void draw() {
  while (myPort.available() > 0) {
    int inByte = myPort.read();
    if (inByte == startcode) {
      player.rewind();
      player.play();
    }
    if(inByte == stopcode){
      player.pause();
    }
  }
}
