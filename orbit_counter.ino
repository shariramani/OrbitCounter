int val=0; 
int prevValue=0;
int orbCounter=2017;


//Pin connected to ST_CP on the board
#define latchPin  D2
//Pin connected to SH_CP on the board
#define clockPin  D3
////Pin connected to DS on the board
#define dataPin D4


// digits 0-9
byte numbers[] = {B00111111,  //0
                  B00110000,  //1
                  B01011011,  //2
                  B01001111,  //3
                  B01100110,  //4
                  B01101101,  //5
                  B01111101,  //6
                  B00000111,  //7
                  B01111111,  //8
                  B01101111};   //9

// used as an output buffer
// display from left to right: digit3 digit2 digit1 digit0
byte digits[4];

byte animidx, animspeed, whichExample;
byte powers[5] = { B00001110, B00001101,B00001011,B00000111, B11111111};
word counter;
word cdelay;






void setup() {
pinMode(D8,OUTPUT);
pinMode(A0,INPUT);
Serial.begin(115200); 
digitalWrite(D8,HIGH); 

//4x7seg code
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  digits[0] = 2;
  digits[1] = 0;
  digits[2] = 1;
  digits[3] = 7;  




}

void loop() {
  // put your main code here, to run repeatedly:
prevValue=val;
val=analogRead(A0);

if ((prevValue <900) && (val >900)){ ++orbCounter ;}



simple1234();

/*
prevValue=val;
if(val<900){
  val=analogRead(A0);
  if(val>900){
    counter++;
    Serial.println(counter);
  }}

  */
delay(500);
    Serial.println(orbCounter);

}



void simple1234()
{
  int digit;
 digits[0] = 2;
  digits[1] = 0;
  digits[2] = 1;
  digits[3] = 7;  

  // write out each digit in turn to the display, only one digit at a time is actually being
  // shown, but because of the speed they're being updated it looks as though they are all
  // on together.

  for (byte t = 0; t<4; t++)
  {
    // tell the 595s we're about to add some new data!
    digitalWrite(latchPin, LOW);
    
    // shift out the bits
    // because we're using a common anode display, a high signal will turn an LED OFF
    // and a low signal will turn an LED ON. The opposite of a common cathode! 
    // If you're patterns look odd, check you have turned the LEDs on and off correctly!
    
    // the first 8 bits determine which of the 4 7-segment displays is active
    // (notice bit 0, doesn't do anything!)
    // B11111101 show display 4
    // B11111011 show display 3
    // B11110111 show display 2
    // B11101111 show display 1    
    // B11011111  how all display, but they'll have the same data!
    
    // the second 8 bits determine which LED to light up
    // B01111111 decimal point
    // B10111111 segment G of the 7-segment display
    // B11011111 segment F of the 7-segment display
    // B11101111 segment E of the 7-segment display
    // B11110111 segment D of the 7-segment display
    // B11111011 segment C of the 7-segment display
    // B11111101 segment B of the 7-segment display
    // B11111110 segment A of the 7-segment display 

   // shiftOut(dataPin, clockPin, MSBFIRST, 32+powers[t+1]);
    shiftOut(dataPin, clockPin, MSBFIRST, numbers[digits[t]]);    
    shiftOut(dataPin, clockPin, MSBFIRST, powers[t]);

    //tell the 595s to ouput our data
    digitalWrite(latchPin, HIGH);
  }
}

