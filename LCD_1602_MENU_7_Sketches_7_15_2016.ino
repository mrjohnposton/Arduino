
//******************************************************************************************************************
/* by John Poston 7/15/2016 
 
 This version has only one Function pasted into this program: menuOne led scan
 
 A video of this in operation on youtube at:  https://youtu.be/GRrijVuDGwc
 - Purpose and General Operation
 The purpose of this file is to have many sketches run on one program.  This was achieved by using a potentiometer to 
 select the different menu choices. A previous version of this had 7 different sketches in it. Once a menu item is
 selected with the potentiometer(on pin A0), press the button connected to pin 11; this is the 'A' button. To stop the 
 sketch and go back to the menu selector, press 'B' button connected to pin 10.
 An example of a menu driven function is in menuOne.  This function example strobes leds (on pins 2-7)back and forth
 on 6 leds using the millis(); delay format.  The rate of strobing is adjustable with the same potentiometer to select 
 the menu.  Once the 'B' button is pressed, the potentiometer will once again be used to select a menu item.  The 'B'
 button may have to be held down for 3 seconds for the example to complete a cycle.
 
 -I2C Address
 At powerup or reset, this program will immediately send the LCD's I2C address to the serial monitor along with the
 file name.  If the file name is changed, go down to the String revLev and change the text.  The file name will
 also appear on the LCD for 2 seconds at startup.
 
 -I license this under the General Public License rev. 3.  
 
 -INDEXING/FINDING     Highlight content (of the area to review ex. menuOne)
                        Ctrl + c (to copy)
                        Ctrl + f (to pull up "Find")
                        Ctrl + v (to paste into the "Find" entry box)
                        Enter    (Press Enter as many times as needed to go to the selectors or the function areas)
 
 -CONTENTS
 --  readSwitches  ***Function to read switches attached to A on 11 and B on 10
 --  blinker  ********Function that blinks the lcd backlight on power up
 --  mainMenu  *******Main Menu function for selecting different sketches
 --  I2Cscan  ********Scans the I2C hardward for the address and sends it to the serial monitor
 --  menuOne  ********Example (led scan) of "HOW TO" import a sketch into the the function menuOne() {...}
 --  menuTwo  ********LCD Cylon/Knight Rider Scan back and forth
 --  menuThree *******Led graph and tone follower
 --  menuFour ********LCD Bar Graph 1 to 16 Blocks Use Pot to move up and down
 --  menuFive ********ASCII glyphs by decimal number
 --  menuSix *********Counter Using millis() adjustable count rate in mS
 --  menuSeven *******Block Selector using the potentiometer with a tone and led13 activated when block 1 or 16 is selected
 --  menuEight
 --  menuNine
 --  menuTen
 --  CONNECTIONS  ***Enter "CONECTIONS" into the Edit/Find dialog box
 
 */

//**********************************************LIBRARIES***********************************************************
#include <Wire.h>//These libraries can be downloaded from:  https://www.arduino.cc/en/Reference/Libraries
#include <LiquidCrystal_I2C.h>
//*********************************************LIQUID CRYSTAL*******************************************************
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address (0x3F) or (0x27)
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address (0x3F) or (0x27)
//****************************************************LEDS**********************************************************
int ledPins[] = { 
  2, 3, 4, 5, 6, 7 };       // an array of pin numbers to which LEDs are attached
int pinCount = 6;           // the number of pins (i.e. the length of the array)
//***********************************************FILE NAME**********************************************************
//file name string to be put into serial out or lcd
String revLev = "LCD_1602_MENU_";
String revLevB = "7_Sketches_7_15_2016";
//*************************************************STRINGS**********************************************************
String menu="Menu = ";
String blanks="                ";//Puts 16 Blank Spaces on LCD
//**********************************************VARIABLES***********************************************************
//Switch Variables
byte swA = 11; 
byte swAval;
byte swB = 10; 
byte swBval;
int tic = 71; //Brief pauses to be used in delays
//*************************************************SET UP***********************************************************
void setup(){//setup code put here to run once  
  Serial.begin(9600); //Begin serial connection 9600 baud rate
  Serial.println("File Name:   ");
  Serial.print(revLev);
  Serial.println(revLevB);
  Serial.println("");

  //Switch PinModes
  pinMode(swA,INPUT_PULLUP);
  pinMode(swB,INPUT_PULLUP);
  //Declare LCD Object and size
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.print(revLev);
  lcd.setCursor(0,1);
 lcd.print(revLevB);
  delay(2000);

  //Led array as outputs
  for (int thisPin = 0; thisPin < pinCount; thisPin++)  {
    pinMode(ledPins[thisPin], OUTPUT);
  }//for end bracket 

  I2Cscan();//run the I2C scanner to determine the address for the lcd setup  
  blinker();//run the backlight on and off at startup
}//Setup end bracket
//*************************************************LOOP*************************************************************
void loop(){  //loop code to run repeatedly

  mainMenu();   //Runs the menu selector for the number function to run

}
//**********************************************readSwitcher*******************************************************
void readSwitches(){  //Evaluates the States of the four Switches
  swAval = digitalRead(swA); 
  swBval = digitalRead(swB);    
  //delay(300);
}
//**********************************************blinker*************************************************************
void blinker(){  //Blinks lcd backlight on and off at startup
  for(int i = 0; i< 5; i++)  
  {
    lcd.noBacklight();
    delay(20);
    lcd.backlight();
    delay(20);
  } 
}
//************************************************mainMenu*************************************************************
void mainMenu(){
  int sensorReading = 0;
  sensorReading = analogRead(A0);
  int rangeMenu = map(sensorReading, 0, 1023, 1, 11); 
  int(inByte) = rangeMenu;
  switch (inByte){ 
    //******************************************************************************************************************
    //==================================================================================================================
    //================================================menuOne===========================================================

  case 1:

    lcd.home();                   //Bring cursor back to the beginning
    //       --1234567890123456-- //Lcd numbers for place holders
    lcd.print("#1 LED SCANNER  ");//menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuOne();                  //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;

    //==================================================================================================================
    //================================================menuTwo===========================================================

  case 2:
    lcd.home();                   //Bring cursor back to the beginning
    //       --1234567890123456-- //Lcd numbers for place holders
    lcd.print("#2 ---CYLONS--- ");//menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuTwo();                  //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;
    //==================================================================================================================
    //================================================menuThree=========================================================

  case 3:
    lcd.home();                   //Bring cursor back to the beginning
    //       --1234567890123456-- //Lcd numbers for place holders
    lcd.print("#3 Graph + Tone ");//menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuThree();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;
    //==================================================================================================================
    //================================================menuFour==========================================================

  case 4:
    lcd.home();                   //Bring cursor back to the beginning
    //       --1234567890123456-- //Lcd numbers for place holders
    lcd.print("#4 --LCD Graph--");//menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuFour();                 //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;
    //==================================================================================================================
    //================================================menuFive==========================================================

  case 5:
    lcd.home();                   //Bring cursor back to the beginning
    //       --1234567890123456-- //Lcd numbers for place holders
    lcd.print("#5 ASCII GLYPHS ");//menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuFive();                 //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;
    //==================================================================================================================
    //================================================menuSix===========================================================

  case 6:
    lcd.home();                  //Bring cursor back to the beginning
    //       --1234567890123456-- //Lcd numbers for place holders
    lcd.print("#6  mS Timer    ");//menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuSix();                  //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;
    //==================================================================================================================
    //================================================menuSeven=========================================================

  case 7:
    lcd.home();                   //Bring cursor back to the beginning
    //       --1234567890123456-- //Lcd numbers for place holders
    lcd.print("#7 Block Select ");//menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuSeven();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;
    //==================================================================================================================
    //================================================menuEight=========================================================

  case 8:
    lcd.home();                  //Bring cursor back to the beginning
    //       --1234567890123456-- //Lcd numbers for place holders
    lcd.print("#8  Empty       ");//menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuEight();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;
    //==================================================================================================================
    //================================================menuNine==========================================================

  case 9:
    lcd.home();                  //Bring cursor back to the beginning
    //       --1234567890123456-- //Lcd numbers for place holders
    lcd.print("#9    Empty     ");//menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuNine();                 //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;
    //==================================================================================================================
    //================================================menuTen===========================================================

  case 10:
    lcd.home();                  //Bring cursor back to the beginning
    //       --1234567890123456-- //Lcd numbers for place holders
    lcd.print("#10     Empty   ");//menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuTen();                  //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;


    //These brackets are only used at the end of the last case
  }//End of Switch Bracket
}//End of mainMenu function Bracket
//==================================================================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuOne Function Block ---
//menuOne is used as AN -E-X-A-M-P-L-E- for inserting other sketches into Function Blocks

void menuOne(){//function bracket

  //******** This would be equivalent to the setup area in a regular sketch *********
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("--- Example ---");
  lcd.setCursor(0,1);
  lcd.print(" -- Led Scan -- ");
  //*************This would be the end of the setup area*****************************

  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //*********Put function executions Below********

    unsigned long previousMillis = 0;    
    int sensorReading = analogRead(A0);
    int interval = map(sensorReading, 0, 1023,200,20);    
    unsigned long currentMillis = millis();  
    // loop from the lowest pin to the highest:
    for (int thisPin = 2; thisPin < 8; thisPin++) {
      // turn the pin on:
      while (currentMillis - previousMillis <= interval)
        currentMillis = millis();
      digitalWrite(thisPin, HIGH);   
      currentMillis = millis();
      previousMillis = currentMillis;
      digitalWrite(thisPin-1, LOW);  
    }
    // loop from the highest pin to the lowest:
    for (int thisPin = 7; thisPin > 1; thisPin--) {
      while (currentMillis - previousMillis <= interval)
        currentMillis = millis();
      digitalWrite(thisPin, LOW);
      previousMillis = currentMillis; 
      digitalWrite(thisPin-1, HIGH);
    }      
    //********************************End of menu chosen sketch****************************   

    //lcd.setCursor(13,0);
    //lcd.print("Run");
    //delay(tic); //Comment out when sketch is added or it will be glitchy

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuTwo Function Block ---
void menuTwo(){//function bracket
  char block = 255; //ASCII glyph for a block

  // Print a message to the LCD. BLOCKS
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(block);
  lcd.setCursor(0,1);
  lcd.print(block);

  delay(100);
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here
    unsigned long previousMillis = 0;
    int sensorReading = analogRead(A0);

    int interval = map(sensorReading, 0, 1023,200,50); 
    //int interval = 50;           // sequence interval in milliseconds

    for (int positionCounter = 1; positionCounter < 1; positionCounter++) {
      // scroll one position left:
      lcd.scrollDisplayLeft();
      // wait a bit:
      readSwitches();

      delay(interval);
    }

    // (0 to 15) to the right
    // to move it offscreen right:
    for (int positionCounter = 0; positionCounter < 15; positionCounter++) {
      // scroll one position right:
      lcd.scrollDisplayRight();
      // wait a bit:
      readSwitches();

      delay(interval);
    }

    // scroll 16 positions (display length + string length) to the left
    // to move it back to center:
    for (int positionCounter = 1; positionCounter < 16; positionCounter++) {
      // scroll one position left:
      lcd.scrollDisplayLeft();

      delay(interval);
    }


    //lcd.setCursor(13,0);
    //lcd.print("Run");
    //delay(tic); //Comment out when sketch is added or it will be glitchy

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuThree Function Block ---
void menuThree(){//function bracket

  //******** This would be equivalent to the setup area in a regular sketch *********
  lcd.clear();
  lcd.setCursor(0,0);
  //       --1234567890123456-- //Lcd numbers for place holders
  lcd.print("           Led #");

  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here

    int sensorReading = analogRead(A0);
    int thisPitch = map(sensorReading, 0, 1023,1000,10000);
    // play the pitch:
    tone(9, thisPitch, 250);
    lcd.setCursor(0,1);
    lcd.print("Freq = ");
    lcd.setCursor(7,1);
    lcd.print(thisPitch);
    lcd.setCursor(11,1);
    lcd.print("   ");
    // delay in between reads for stability

    int sensorReadingB = sensorReading;
    // map the result to a range from 0 to the number of LEDs:
    int ledNum = map(sensorReadingB, 0, 1023, 1, 7);
    lcd.setCursor(14,1);
    lcd.print(ledNum);
    lcd.print(blanks);
    // delay(75);     
    // loop over the LED array:
    for (int thisPin = 0; thisPin< pinCount; thisPin++) {
      // if the array element's index is less than ledLevel,
      // turn the pin for this element on:
      if (thisPin < ledNum) {
        digitalWrite(ledPins[thisPin], HIGH);
      } 
      // turn off all pins higher than the ledLevel:
      else {
        digitalWrite(ledPins[thisPin], LOW); 
      }
    } 

    lcd.setCursor(8,0);

    //lcd.setCursor(13,0);
    //lcd.print("Run");
    //delay(tic); //Comment out when sketch is added or it will be glitchy

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuFour Function Block ---
void menuFour(){//function bracket

  int analogPin = 0; // The main input
  float d = 0;
  float oldit = 0;
  lcd.setCursor(0,0);
  lcd.print(blanks);

  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here


    int num = analogRead(analogPin); // get our input
    int it = map(num, 0., 1023., 0, 17);  // take our input and break it down to 16

    lcd.setCursor(0,0); 
    lcd.print(num);   // print the actual number we're using.
    lcd.print("   "); //print blank spaces to clear register so numbers don't hang around

    if (it > oldit) { // check if the number changes to a higher number
      for (d = 0; it >= d; d++) { // count up from 0 to 15
        lcd.setCursor(d, 1); // start at the bottom left and work forward
        lcd.write(1023); // show a block
      }
    }

    if (it <= oldit) { // check if the number changed to a smaller number
      for (d = 15; it <= d; d--) { //count down from 15 to 0
        lcd.setCursor(d, 1); // start at the bottom right and work back
        lcd.write(1022); // show blank
      }
    }

    oldit = it;  

    lcd.setCursor(13,0);
    lcd.print("Run");
    delay(tic); //Comment out when sketch is added or it will be glitchy

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuFive Function Block ---
void menuFive(){//function bracket

  lcd.clear();
  lcd.setCursor(0,0);

  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here

    int sensorReading = analogRead(A0);
    // map the result to a range from 0 to the number of LEDs:
    int rangeMenu = map(sensorReading, 0, 1023, 33,257); //set ASCII range from 33 to 255
    delay(tic*3);
    lcd.setCursor(0,1);
    char thisChar = rangeMenu;  //qualify rangeMenu from a number to the ASCII glyph value
    //lcd.print(blanks);
    // lcd.setCursor(13,0);
    // lcd.print("    ");
    lcd.setCursor(0,0);
    //       --1234567890123456-- //Lcd numbers for place holders
    lcd.print("DEC: ");
    lcd.setCursor(5,0);
    lcd.print(rangeMenu,DEC);
    lcd.print("    ");
    lcd.setCursor(0,1);
    //       --1234567890123456-- //Lcd numbers for place holders
    lcd.print("ASCII: ");

    lcd.print(thisChar);
    lcd.print(thisChar);
    lcd.print(thisChar);
    lcd.print(thisChar);
    lcd.print(thisChar);
    lcd.print(thisChar);
    lcd.print(thisChar);
    lcd.print(thisChar);
    lcd.print(thisChar);

    // lcd.setCursor(13,0);
    //lcd.print("Run");
    // delay(tic); //Comment out when sketch is added or it will be glitchy

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuSix Function Block ---
void menuSix(){//function bracket
lcd.clear();
int goUpOne=0;
   unsigned long previousMillis = 0;    



  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here


  // digitalWrite(blinker,HIGH);

  
  unsigned long currentMillis = millis();  
 lcd.setCursor(6,1);

    lcd.print("    ");
    lcd.setCursor(6,1);
    lcd.print(goUpOne/10.,1);
        goUpOne ++;
int sensorReading = analogRead(A0);
  int interval = map(sensorReading, 0, 1023,50,200);
  lcd.setCursor(0,0);
  lcd.print("milliSecs:  ");
  lcd.setCursor(11,0);
  lcd.print(interval);
  lcd.print("    ");  
     while (currentMillis - previousMillis <= interval){
      currentMillis = millis();
   //digitalWrite(blinker,LOW);
 }
    currentMillis = millis();
    previousMillis = currentMillis;

  

    //lcd.setCursor(13,0);
   // lcd.print("Run");
   // delay(tic); //Comment out when sketch is added or it will be glitchy

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuSeven Function Block ---
void menuSeven(){//function bracket
byte led = 13;
  pinMode (led,OUTPUT);
lcd.clear();
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here
int sensorReading = analogRead(A0);
  int interval = map(sensorReading, 0, 1023,0,15); 
  lcd.setCursor(0,0);
  lcd.print("Block No.: ");
  lcd.print(interval+1);
  lcd.print("   ");
  lcd.setCursor(0,1);
  char block = 255;
  if(interval <= 0); 
  lcd.setCursor(0,1);
  lcd.setCursor(interval-1,1);
  lcd.print("   ");
  lcd.setCursor(interval,1);
  lcd.print(block);
  lcd.setCursor(interval+1,1);
  lcd.print("   ");
  if((interval <= 0) || (interval >=15)){
    digitalWrite (led,HIGH);
    tone(9,5000,100);
  }//end of if bracket
  else{
    digitalWrite (led,LOW);
    tone (9,30,100);
  }//end of else bracket

    //lcd.setCursor(13,0);
   // lcd.print("Run");
    //delay(tic); //Comment out when sketch is added or it will be glitchy

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuEight Function Block ---
void menuEight(){//function bracket
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here


    lcd.setCursor(13,0);
    lcd.print("Run");
    delay(tic); //Comment out when sketch is added or it will be glitchy

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuNine Function Block ---
void menuNine(){//function bracket
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here


    lcd.setCursor(13,0);
    lcd.print("Run");
    delay(tic); //Comment out when sketch is added or it will be glitchy

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuTen Function Block ---
void menuTen(){//function bracket
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here


    lcd.setCursor(13,0);
    lcd.print("Run");
    delay(tic); //Comment out when sketch is added or it will be glitchy

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                            --I2C Address Scanner Function
void I2Cscan () {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknow error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(100);
  byte oerror, oaddress;
  int onDevices;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Scanning...");
  //lcd.print (onDevices = 0);
  for(oaddress = 1; oaddress < 127; oaddress++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(oaddress);
    oerror = Wire.endTransmission();

    if (oerror == 0)
    {
      lcd.setCursor(0,1); 
      lcd.print("I2C 0x");
      if (oaddress<16)
        lcd.print("0");
      lcd.print(oaddress,HEX);
      lcd.print(" ");
      onDevices++;
    }
    else if (oerror==4)
    {
      lcd.print("error address 0x");
      if (oaddress<16)
        lcd.print("0");
      lcd.print(oaddress,HEX);
    }    
  }
  if (onDevices == 0)
    lcd.print("No I2C devices found\n");
  else
    lcd.print("done");

  delay(100);
  lcd.setCursor(0,0); 
  lcd.print(blanks);
  if (swBval==0){
    lcd.clear();
    return;
  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/* ***************************************----- CONNECTIONS ----****************************************************
 
 Parts:
 Led Shield copy and paste to ebay search:    Arduino Display kit 6 bit Blue LED Module Board for UNO MEGA2560 AVR ARM FPGA 
 Sensor Shield Expansion board copy and paste to ebay search:    Sensor Shield Expansion Board Shield For Arduino UNO R3 V5.0 Electric Module 
 4 Button Keypad ebay search:    Arduino keypad 4 Button Key Module Switch Keyboard for UNO MEGA2560 Breadboard 
 16 x 2 1602 LCD with I2C interface ebay search:   1602 LCD 16x2  with IIC I2C Serial Interface Adapter Module
 
 Wiring:
 20 K ohm potentiometer wiper to A0 one side to ground and the other to 5volts
 Led shield ground leg bent out to connect to a ground on the sensor shield and the others are plugged into 2,3,4,5,6, and 7
2 Button Keypad shield inserted into the sensor shield in pins 10,11, and the common of the led shield goes to ground.
 LCD I2C connected to the IIC on the sensor shield... SCL to SCL, SDA to SDA, + to +, and - to -
 I hope to have some good pictures for the set up for this.
 
 Note:  I am still somewhat of a beginner with arduino.  I needed to come up with a different approach to programming
 because I was so slow at getting things to work.  This ability to look at alot of sketches to find different control 
 structure types helped me to find examples really fast to build on things I had already tried without having to 
 open up alot of other sketches.  I initially had no plans to come up with something that I wanted to publish on the
 internet.  After searching through hundreds of sketches, I noticed there were a few genuises out there I should give
 credit to.  I also wanted to be helpful to others and publish this to speed up the learning curve to programming effectively on the arduino.
 */







