

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Using a 5 pin rotary encoder made by Keyes from the 37 in 1 Sensor Kit

const int encoderPinA = 7;     // right (labeled DT on our decoder)
const int encoderPinB = 8;     // left (labeled CLK on our decoder)
const int encoderSwitchPin = 9;

volatile unsigned int encoderPos = 0;     // a counter for the dial
int buttonState = 0;

const int maxVal = 360;

// interrupt service routine vars
boolean A_set = false;
boolean B_set = false;

void doEncoderA(){
    // Test transition, did things really change?
    if( digitalRead(encoderPinA) != A_set )
    {
        A_set = !A_set;
        // adjust counter + if A leads B
        if ( A_set && !B_set )
        {
            // Increment or roll over
            if (encoderPos == maxVal)
            {
                encoderPos = 0;
            }
            else
            {
                encoderPos += 1;
            }
            
        }
    }
}

void doEncoderB(){
    if( digitalRead(encoderPinB) != B_set )
    {
        B_set = !B_set;
        //    adjust counter - 1 if B leads A
        if( B_set && !A_set )
        {
            // Decrement or roll over
            if (encoderPos == 0)
            {
              encoderPos=maxVal;
            }
            else
            {
                encoderPos -= 1;
            }
            
        }
    }
} 



void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Encoder value");
  
  pinMode(encoderPinA, INPUT_PULLUP);
pinMode(encoderPinB, INPUT_PULLUP);
pinMode(encoderSwitchPin, INPUT);

// encoder pin on interrupt 0 (pin 7)
attachInterrupt(0, doEncoderA, CHANGE);

// encoder pin on interrupt 1 (pin 8)
attachInterrupt(1, doEncoderB, CHANGE); 

}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  //lcd.print("        ");
  buttonState = digitalRead(encoderSwitchPin);
  if(buttonState == LOW){
    encoderPos = 0;
  }
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(encoderPos);  
  //lcd.print(buttonState); 
  lcd.print("        "); //clear following cells if neccessary
}
