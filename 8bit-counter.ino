/*     ----------------------------------------------
 *     |  Arduino 8bit counter                      |
 *     |  Potentometer .: 8 LED's :. Pushbutton     |
 *     ----------------------------------------------
 */

#define potPin A0                                                                       //Declaring A0 as potentiometer pin
#define pushBtn 2                                                                       //Declaring D2 as push button (intrrupt)

void reset();                                                                           //Declaring functions for intrrupt and counter
void binaryNum(int counter);
  
int ptr,speed;                                                                          //Declaring pointer (ptr) and speed (speed) variables to point and store the speed after converting analog value.
int counter=0;                                                                          //Declaring and initializing counter starting from 0
int ledPins[] = {3,4,5,6,7,8,9,10};

void setup()
{ 
    //Setting up each pin connected to an LED to output mode (pulling high (on) or low (off)
    
    for(ptr=0;ptr<8;ptr++)                                                              //loop will repeat eight times
      pinMode(ledPins[ptr],OUTPUT);                                                     //set each LED pin to output
  
    pinMode(2,INPUT_PULLUP);                                                            //initializing digital pin 2 as an input with the internal pull-up resistor enabled
                                                                                        //Reference: https://www.arduino.cc/en/Tutorial/DigitalPins
    attachInterrupt(digitalPinToInterrupt(pushBtn),reset,RISING);                       //Specifing pin 2 for external interrupt, and reset function is called when there is RISING (LOW to HIGH) at D2 pin 
                                                                                        //Reference: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
}


void loop()                                                                             //run code continuously
{   
  speed=map(analogRead(potPin),0,1023,0,600);                                           //Reading analog value from potentiometer and converting values from 0-1023 to 0-600 using map function and storing it in speed
  delay(speed);                                                                         //Setting the speed of counter as per potentiometer input
    
    binaryNum(counter);                                                                 //Calling binaryNum function (binary to decimal converter)
  
    if(counter<256)                                                                     //Checking if counter is not exceeding 255
      counter++;                                                                        //Incrementing counter by 1
    else
      counter=0;                                                                        //If counter exceeds 255 setting it to 0 to start from initial state
}

void binaryNum(int counter)                                                             //Finction defination for binaryNum
{
    //This function converts decimal to binary and powers up the leds according to the binary number
  
    for(ptr=0;ptr<8;ptr++)                                                              //Loop runs for 8 times as it is 8bit counter 
    {
        //This part of code digit by digit to binary and powers up 
      if (counter%2)                         
        digitalWrite(ledPins[ptr],1);
      else
        digitalWrite(ledPins[ptr],0);
      counter=counter/2;
    }
}


void reset()                                                                            //Intrrupt function defination
{
    //This function gives an indication when reset button is pressed and resets counter to 0 
    
    //This part of code is to indicate usage of reset button  
    //Blinks all LED's twice to indicate the start of counting
    for(ptr=0;ptr<8;ptr++)
      digitalWrite(ledPins[ptr],1);
    delay(300);
  
    for(ptr=0;ptr<8;ptr++)
      digitalWrite(ledPins[ptr],0);
    delay(300);
  
    for(ptr=0;ptr<8;ptr++)
      digitalWrite(ledPins[ptr],1);
    delay(300);
  
    for(ptr=0;ptr<8;ptr++)
      digitalWrite(ledPins[ptr],0);
    delay(300);
  
    counter=0;                                                                          //Counter being reset to 0
}
