#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for Native USB only
  }


  

  // set the data rate for the SoftwareSerial port
//  mySerial.begin(38400);
  mySerial.begin(115200);
  mySerial.println("Hello, world?");
}

void loop() // run over and over
{ 
  if (mySerial.available())
    mySerial.write(mySerial.read());
//  if (Serial.available())
//    mySerial.write(Serial.read());
//    if (mySerial.available())
//      mySerial.write(mySerial.read());


//  mySerial.println("Good moon!");
//  delay(500);

}
