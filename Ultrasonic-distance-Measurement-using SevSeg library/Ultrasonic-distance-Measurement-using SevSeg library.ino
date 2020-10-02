#include "SevSeg.h" // library for 7 segment display

SevSeg sevseg; // initate 7 segment display

//ultrasonic sensor pins globar variables
int trigger = A1;
int echo = A0;

int dist; // variable to be read by display
int usec; //value from the trig and echo pins

void setup()
{

  Serial.begin(9600); // serial monotor comm rate

  pinMode(trigger, OUTPUT); // set to output
  pinMode(echo, INPUT);     // set to input

  // set up SevSeg library parmeters
  byte numDigits = 4;                            // number of digits on the display
  byte displaypins[] = {13, 12, 11, 10};         // pin numbers for each digit
  byte segmentPins[] = {9, 8, 7, 6, 5, 4, 3, 2}; // pins for each part of the 7 segment display

  bool resistorsOnSegments = true;    // true if resistors are being used
  bool updateWithDelaysIn = true;     // delays used
  byte hardwareConfig = COMMON_ANODE; // display type
  sevseg.begin(hardwareConfig, numDigits, displaypins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(100); // brightness level of the display
}

void loop()
{

  digitalWrite(trigger, LOW); // send short signal on the trigpin

  delayMicroseconds(5);

  digitalWrite(trigger, HIGH); // send signal for 10ms

  delayMicroseconds(10);

  digitalWrite(trigger, LOW); // turn off signal after 10ms

  usec = pulseIn(echo, HIGH); // read signal from trigpin

  // determine distance by using the time from the trig and echo pins // divide interval by 2 then divide again by 29
  dist = (usec / 2) / 28;

  // print to serial monitor

  Serial.print(dist);

  Serial.print("cm");
  Serial.print("\n");
  Serial.println();

  //print to 7 segment display
  sevseg.setNumber(dist); // print the value of cm to the display
  delay(10);
  sevseg.refreshDisplay();
}
