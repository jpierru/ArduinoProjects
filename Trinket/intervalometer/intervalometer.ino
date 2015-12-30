// This sketch will send out a Nikon D50 trigger signal (probably works with most Nikons)
// See the full tutorial at http://www.ladyada.net/learn/sensors/ir.html
// this code is public domain, please enjoy!
 
#define IRLEDPIN 1          // LED connected to digital pin 1
#define POTENTIOMETERPIN 3  // Potentiometer connected to analog pin 3
// The setup() method runs once, when the sketch starts
 
void setup()   {                
  // initialize the IR digital pin as an output:
  pinMode(IRLEDPIN, OUTPUT);      
}
 
void loop()                     
{
  int delaySeconds = getDelay();
 
  SendNikonCodeD3000();
 
  delay(delaySeconds*1000);  // wait one minute (60 seconds * 1000 milliseconds)
}

int getDelay() {
  // if POT_PIN is defined, we have a potentiometer on GPIO #3 on a Trinket 
//  int delaySetting = 60;   
#ifdef POTENTIOMETERPIN            
   int delaySetting = analogRead(POTENTIOMETERPIN);  // Read pin (0-255) (adjust potentiometer 
                                  //   to give 0 to Vcc volts
#endif

  // get the delay from the potentiometer setting
  int delaySeconds = int(30.0/1024*delaySetting);
//  if (delaySetting < 25) delaySeconds = 1;
//  else if (delaySetting < 50 ) delaySeconds = 2;
//  else if (delaySetting < 75 ) delaySeconds = 5;
//  else if (delaySetting < 100 ) delaySeconds = 10;
//  else if (delaySetting < 125 ) delaySeconds = 30;
//  else if (delaySetting < 150 ) delaySeconds = 60;
//  else if (delaySetting < 175 ) delaySeconds = 120;
//  else if (delaySetting < 200 ) delaySeconds = 300;
//  else if (delaySetting < 225 ) delaySeconds = 600;
//  else if (delaySetting < 255 ) delaySeconds = 1800;
  
//  if (delaySetting < 200) delaySeconds = 1;
//  else if (delaySetting < 400 ) delaySeconds = 2;
//  else if (delaySetting < 600 ) delaySeconds = 5;
//  else if (delaySetting < 800 ) delaySeconds = 10;
//  else if (delaySetting <= 1023 ) delaySeconds = 30;
//  else delaySeconds = 5;
  
  return delaySeconds;
}
 
// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
  int pause = (1000/38/2)-4;
  unsigned long start = micros();
  //cli();  // this turns off any background interrupts
 
  while (micros()-start<=microsecs) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRLEDPIN, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(pause);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRLEDPIN, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(pause);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   //microsecs -= 24;
  }
 
  sei();  // this turns them back on
}
 
void SendNikonCodeD50() {
  // This is the code for my particular Nikon, for others use the tutorial
  // to 'grab' the proper code from the remote
 
  pulseIR(2080);
  delay(27);
  pulseIR(440);
  delayMicroseconds(1500);
  pulseIR(460);
  delayMicroseconds(3440);
  pulseIR(480);
 
 
  delay(65); // wait 65 milliseconds before sending it again
 
  pulseIR(2000);
  delay(27);
  pulseIR(440);
  delayMicroseconds(1500);
  pulseIR(460);
  delayMicroseconds(3440);
  pulseIR(480);
}

void SendNikonCodeD3000() {
  // This is the code for my particular Nikon, for others use the tutorial
  // to 'grab' the proper code from the remote
 
  pulseIR(2000);
  delayMicroseconds(27830);
  pulseIR(390);
  delayMicroseconds(1580);
  pulseIR(410);
  delayMicroseconds(3580);
  pulseIR(400);
 
 
  delay(65); // wait 65 milliseconds before sending it again
 
  pulseIR(2000);
  delayMicroseconds(27830);
  pulseIR(390);
  delayMicroseconds(1580);
  pulseIR(410);
  delayMicroseconds(3580);
  pulseIR(400);
}
