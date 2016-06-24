/*
MENU DRIVEN FUNCTIONS

by John Poston 25 June 2016

 DESCRIPTION:
   I wanted to have a multipurpose program that would allow me to cut and paste new sketches directly into an menu driven
 program, be able to view other sketches for references, simple enough to follow in blocks so if the code got 
 extremely long, it would be easy to navigate to any area using the Find feature in Edit.
   This program uses the switch/case information and uses function blocks to retrieve number sketches in the program 
via the menu.
  Please comment to my youtube channel https://www.youtube.com/channel/UCV59vYJuP6lOxj_wjEC2Fxg
 Code on GitHub  https://github.com/mrjohnposton/Arduino
   LCD address is sent to the serial monitor so that it can be changed if needed.
The address set for this program is 0x27. If yours reads different at power up on the serial monitor
you can change it in the lcd set up "LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
below.
  If you change the name of this sketch, do yourself a favor and change the string variable "revLev" to reflect
 your changes. This will also be broadcasted to the serial monitor at startup or reset of the sketch.
   Please feel free to use or change any part of this sketch as long as the credits below are listed if
 this is republished... Thanks!!!
 
 CREDITS:
 --I2C Scanner by Nick Gammon
 --Most others were made by Tom Igoe from the "Examples" in the Arduino IDE
 --Jeremy Blum's YT tutorial 13 "LCD Progress Bar"
 --u/n pjessop arduino forum #  16907.0 Analog LCD Bar Graph
 --Roberto Baldassar smooth analog lcd meter "NiceMeterHor..."
 --Simon Monk's "Programming Arduino Next Steps Going Further with Sketches"... enhanced my programming techniques
 --John Poston's LCD_MENU_FUNCTIONS 25 JUNE 2015
 
 -- FINDING --- Copy (cntrl+c) then paste into Find (cntrl+f) to go to a section
                Example; highlight the word "Connections" below, press cntrl  and c at the same time to copy the word, then
                press cntrl and f at the same to pull up the "Find" box, press
                cntrl and v at the same time to enter the word "Connections" into the Find box
                then press enter.  ... This is really fast after a couple of times!!!
 
 CONTENSTS:
 -  Connections - Go here to see the wiring connection descriptions. Also Parts used are listed here for searching on Ebay
 -  I2Cscan ----- I2C address scanner at startup and send the address to the serial monitor (good for troubleshooting)
 -  readSwitches  Reads the buttons for activating and deactivating functions listed in the menu
 -  potReadMenu - Main Menu Function
 -  menuOne ----- LCD Bar Graph 1 to 16 Blocks Use Pot to move up and down B button to Exit
 -  menuTwo ----- LCD Cylon / Knight Rider  Use Pot to control the scan rate and press B button to Exit  
 -  menuThree --- LED Scan using the millis() delay function
 -  menuFour ---- LCD Bar Graph different with scale numbers 
 -  menuFive ---- Tones by Potiometer and led graph     
 -  menuSix ----- ASCII glyphs by decimal number     
 -  menuSeven --- Put Your Sketch here!!!  
 -  menuEight --- Put Your Sketch here!!!    
 -  menuNine ---- Put Your Sketch here!!! 
 -  menuTen ----- Put Your Sketch here!!! 
 -  menuEleven -- Put Your Sketch here!!! 
 -  menuTwelve -- Put Your Sketch here!!! 
 
 
 */

//-------------------LIBRARIES-----------------------

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//---------------------------------------------------

// ------------------UPDATE FILENAME FOR LCD TO DISPLAY AT STARTUP----------------------
String revLev = "LCD_MENU_FUNCTIONS.ino";  //Always update

//--------------------Liquid Crystal Setup----------------------------------------------
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
int tic = 100;
int sensorMax;
int sensorMin;
int sensorReading;
int rangeMenu;
//---------------------------------------------------------------------------------------

//-----------------------Strings----------------------
String menu="Menu = ";
String blanks="                ";//Puts 16 Blank Spaces on LCD
//----------------------------------------------------
//-----------------------VARIABLES--------------------
//Blink for menuOne
byte led = 13;
//Switch Variables
byte swA = 11; 
byte swAval;
byte swB = 10; 
byte swBval;
byte swC = 9;  
byte swCval;
byte swD = 8;  
byte swDval;
byte ground = 12;//Fake ground to avoid using a ground wire for the four switches
//Scanner Leds for menuThree ---> Using Array
int timer = 100;           // The higher the number, the slower the timing.
int ledPins[] = { 
  2, 3, 4, 5, 6, 7 };       // an array of pin numbers to which LEDs are attached
int pinCount = 6;           // the number of pins (i.e. the length of the array)
//menuEight -- Analog bargraph on Character LCD
int analogPin = 0; // The main input

float d = 0;
float oldit = 0;
//-------------------------------------------------------


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^--- SETUP ---^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void setup(){
  Serial.begin(9600);  //Setup to use serial monitor
 
  pinMode(led,OUTPUT);
  //Switch PinModes
  pinMode(swA,INPUT_PULLUP);
  pinMode(swB,INPUT_PULLUP);
  pinMode(swC,INPUT_PULLUP);
  pinMode(swD,INPUT_PULLUP);
  pinMode(ground,OUTPUT);
  digitalWrite(ground,LOW);
  //   *** menuThree Led Scannner pinModes ***

  for (int thisPin = 0; thisPin < pinCount; thisPin++)  {
    pinMode(ledPins[thisPin], OUTPUT);      
  }

  //Declare LCD Object and size
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
 I2Cscan();
  introMenu();       //Displays File name at start up.
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
  //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$--- Main Loop  ---$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

void loop(){
  potReadMenu(); 

}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

//************************************Read Switches Function***********************************
void readSwitches(){  //Evaluates the States of the four Switches
  swAval = digitalRead(swA);
  swBval = digitalRead(swB);
  swCval = digitalRead(swC);
  swDval = digitalRead(swD);
}
//*********************************************************************************************

void introMenu(){//Displays information at startup
 Serial.println("File Name:  ");
  Serial.println(revLev);

  //Blinks the lcd backlight to indicate program is running
  for(int i = 0; i< 5; i++)  
  {
    lcd.noBacklight();
    delay(20);
    lcd.backlight();
    delay(20);
  }
  //-------- Write characters on the display ------------------
  // NOTE: Cursor Position: (CHAR, LINE) start at 0  
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("--- Arduino ---");
  lcd.setCursor(0,1);
  lcd.print("Menu Functions");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Program Name ");
  lcd.setCursor(0,1);
  lcd.print(revLev);//Print out the file name listed in the strings variables
  delay(500);
  lcd.clear();  
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MAIN MENU~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void potReadMenu(){
  sensorReading = 0;
  sensorReading = analogRead(A0);
  rangeMenu = map(sensorReading, 0, 1023, 1, 13); 
  int(inByte) = rangeMenu;
  switch (inByte){

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--- CASE AND FUNCTION SELECT BLOCK ---@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  case 1: 
    lcd.clear();                  //Clear the LCD
    lcd.setCursor(0,0);           //Start Cursor at column 0 and row 0
    lcd.print("Menu 1");         //menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("LCD Bar Graph");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuOne();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;                        //Break when another case is chosen using the variable resistor
    //####### Both of these are only used at the last case ########
    //} //End of Switch/Case Bracket
    //  } //End of Function Bracket

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--- CASE AND FUNCTION SELECT BLOCK ---@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  case 2: 
    lcd.clear();                  //Clear the LCD
    lcd.setCursor(0,0);           //Start Cursor at column 0 and row 0
    lcd.print("Menu 2");         //menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("LCD Cylon");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuTwo();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;                        //Break when another case is chosen using the variable resistor
    //####### Both of these are only used at the last case ########
    //} //End of Switch/Case Bracket
    //}  //End of Function Bracket
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--- CASE AND FUNCTION SELECT BLOCK ---@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  case 3: 
    lcd.clear();                  //Clear the LCD
    lcd.setCursor(0,0);           //Start Cursor at column 0 and row 0
    lcd.print("Menu 3");         //menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Leds-millis()");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuThree();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;                        //Break when another case is chosen using the variable resistor
    //####### Both of these are only used at the last case ########
    //} //End of Switch/Case Bracket
    //}  //End of Function Bracket
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--- CASE AND FUNCTION SELECT BLOCK ---@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  case 4: 
    lcd.clear();                  //Clear the LCD
    lcd.setCursor(0,0);           //Start Cursor at column 0 and row 0
    lcd.print("Menu 4 Lcd");         //menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Graph Scale");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuFour();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;                        //Break when another case is chosen using the variable resistor
    //####### Both of these are only used at the last case ########
    //} //End of Switch/Case Bracket
    //}  //End of Function Bracket
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--- CASE AND FUNCTION SELECT BLOCK ---@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  case 5: 
    lcd.clear();                  //Clear the LCD
    lcd.setCursor(0,0);           //Start Cursor at column 0 and row 0
    lcd.print("Menu 5 Tones");         //menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("by Pot leds too");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuFive();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;                        //Break when another case is chosen using the variable resistor
    //####### Both of these are only used at the last case ########
    //} //End of Switch/Case Bracket
    //}  //End of Function Bracket
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--- CASE AND FUNCTION SELECT BLOCK ---@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  case 6: 
    lcd.clear();                  //Clear the LCD
    lcd.setCursor(0,0);           //Start Cursor at column 0 and row 0
    lcd.print("Menu 6");         //menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("ASCII Glyphs");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuSix();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;                        //Break when another case is chosen using the variable resistor
    //####### Both of these are only used at the last case ########
    //} //End of Switch/Case Bracket
    //}  //End of Function Bracket
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--- CASE AND FUNCTION SELECT BLOCK ---@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  case 7: 
    lcd.clear();                  //Clear the LCD
    lcd.setCursor(0,0);           //Start Cursor at column 0 and row 0
    lcd.print("Menu 7");         //menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuSeven();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;                        //Break when another case is chosen using the variable resistor
    //####### Both of these are only used at the last case ########
    //} //End of Switch/Case Bracket
    //}  //End of Function Bracket
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--- CASE AND FUNCTION SELECT BLOCK ---@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  case 8: 
    lcd.clear();                  //Clear the LCD
    lcd.setCursor(0,0);           //Start Cursor at column 0 and row 0
    lcd.print("Menu 8");         //menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuEight();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;                        //Break when another case is chosen using the variable resistor
    //####### Both of these are only used at the last case ########
    //} //End of Switch/Case Bracket
    //}  //End of Function Bracket
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--- CASE AND FUNCTION SELECT BLOCK ---@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  case 9: 
    lcd.clear();                  //Clear the LCD
    lcd.setCursor(0,0);           //Start Cursor at column 0 and row 0
    lcd.print("Menu 9");         //menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuNine();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;                        //Break when another case is chosen using the variable resistor
    //####### Both of these are only used at the last case ########
    //} //End of Switch/Case Bracket
    //}  //End of Function Bracket
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--- CASE AND FUNCTION SELECT BLOCK ---@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  case 10: 
    lcd.clear();                  //Clear the LCD
    lcd.setCursor(0,0);           //Start Cursor at column 0 and row 0
    lcd.print("Menu 10");         //menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuTen();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;                        //Break when another case is chosen using the variable resistor
    //####### Both of these are only used at the last case ########
    //} //End of Switch/Case Bracket
    //}  //End of Function Bracket
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--- CASE AND FUNCTION SELECT BLOCK ---@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  case 11: 
    lcd.clear();                  //Clear the LCD
    lcd.setCursor(0,0);           //Start Cursor at column 0 and row 0
    lcd.print("Menu 11");         //menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuEleven();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;                        //Break when another case is chosen using the variable resistor
    //####### Both of these are only used at the last case ########
    //} //End of Switch/Case Bracket
    //}  //End of Function Bracket
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--- CASE AND FUNCTION SELECT BLOCK ---@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  case 12: 
    lcd.clear();                  //Clear the LCD
    lcd.setCursor(0,0);           //Start Cursor at column 0 and row 0
    lcd.print("Menu 12");         //menuXxx function also displays the address on the serial monitor
    lcd.setCursor(0,1);           //Put cursor at the begining of the second line
    lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
    delay (tic);                  //Delay long enough for the lcd to refresh and display
    readSwitches();               //Goes to the readSwitches function
    if (swAval==0)                //If swA is pressed, activate the function
    {                             //if bracket
      menuTwelve();                //function chosen for this case selected by the variable resistor
    }                             // end of if bracket.  Runs function until swB is pressed inside of function
    break;                        //Break when another case is chosen using the variable resistor
    //####### Both of these are only used at the last case ########
  } //End of Switch/Case Bracket
}  //End of Function Bracket
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//******************************************************************************************************

//                                     --- menuOne Function Block ---
void menuOne(){//function bracket
  lcd.setCursor(0,0);
  lcd.print(blanks);
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here

    int num = analogRead(analogPin); // get our input
    int it = map(num, 0., 1023., 0, 16);  // take our input and break it down to 16

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


    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd
      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//********************************************************************************************************

//******************************************************************************************************

//                                     --- menuTwo Function Block ---
void menuTwo(){//function bracket
  char block = 255; //ASCII glyph for a block

  // Print a message to the LCD.
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(block);
  lcd.setCursor(0,1);
  lcd.print(block);
  //lcd.print(block);
  delay(100);
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here
    // scroll 1 positions (string length) to the left
  // to move it offscreen left:
  
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
   lcd.noBacklight();
   delay(20);
    lcd.backlight();
     delay(interval);
  }

  // scroll 16 positions (display length + string length) to the left
  // to move it back to center:
  for (int positionCounter = 1; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    lcd.noBacklight();
   delay(20);
    lcd.backlight();
    readSwitches();
    // wait a bit:
    delay(interval);
  }
 

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd
      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//********************************************************************************************************

//******************************************************************************************************

//                                     --- menuThree Function Block ---
void menuThree(){//function bracket
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here
unsigned long previousMillis = 0;
  int sensorReading = analogRead(A0);
  // map the result to a range from 0 to the number of LEDs:
  int interval = map(sensorReading, 0, 1023, 20,150); 
 //int interval = 50;           // sequence interval in milliseconds
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
    
    
    lcd.setCursor(8,0);
    lcd.print("Three");
    delay(tic);

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd
      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//********************************************************************************************************

//******************************************************************************************************

//                                     --- menuFour Function Block ---
void menuFour(){//function bracket

    //Put function executions here
    
    lcd.setCursor(0,0);
lcd.print(blanks);
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 
 
 //Put function executions here
  float num = analogRead(analogPin); // get our input
 float it = map(num, 0, 1023, 0, 16);  // take our input and break it down to 16
 lcd.setCursor(0, 0); // print the actual number we're using.
 lcd.print(num);

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
 
    
    lcd.setCursor(8,0);
    lcd.print("Four");
    delay(tic);

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd
      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  
  }//While bracket 
}//last function bracket
//********************************************************************************************************

//******************************************************************************************************

//                                     --- menuFive Function Block ---
void menuFive(){//function bracket
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here
    
  int sensorReading = analogRead(A0);
 int thisPitch = map(sensorReading, 0, 1023,1000,6003);
  // play the pitch:
  tone(2, thisPitch, 250);
 lcd.setCursor(0,1);
 lcd.print("Freq = ");
 lcd.setCursor(7,1);
 lcd.print(thisPitch);
 lcd.setCursor(11,1);
 lcd.print("   ");
    // delay in between reads for stability
 
  int sensorReadingB = sensorReading;
  // map the result to a range from 0 to the number of LEDs:
  int ledNum = map(sensorReadingB, 0, 1023, 1, 6);
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
    //lcd.print("Five");
    delay(tic);

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd
      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//********************************************************************************************************

//******************************************************************************************************

//                                     --- menuSix Function Block ---
void menuSix(){//function bracket
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here
    int sensorReading = analogRead(A0);
  // map the result to a range from 0 to the number of LEDs:
  int rangeMenu = map(sensorReading, 0, 1023, 33,255); //set ASCII range from 33 to 255
delay(tic*3);
lcd.setCursor(0,1);
char thisChar = rangeMenu;  //qualify rangeMenu from a number to the ASCII glyph value
lcd.print(blanks);
  lcd.setCursor(13,0);
 lcd.print("    ");
 lcd.setCursor(7,0);
 lcd.print("DEC:");
 lcd.setCursor(13,0);
 lcd.print(rangeMenu,DEC);
 lcd.setCursor(0,1);
 lcd.print("   ASCII:");
 lcd.print(thisChar);
 lcd.print(thisChar);
 lcd.print(thisChar);
 lcd.print(thisChar);
 lcd.print(thisChar);
 lcd.print(thisChar);
 
    
    lcd.setCursor(8,0);
    //lcd.print("Six");
    delay(tic);

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd
      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//********************************************************************************************************

//******************************************************************************************************

//                                     --- menuSeven Function Block ---
void menuSeven(){//function bracket
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here
    
    
    lcd.setCursor(8,0);
    lcd.print("Seven");
    delay(tic);

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd
      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//********************************************************************************************************

//******************************************************************************************************

//                                     --- menuEight Function Block ---
void menuEight(){//function bracket
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here
    
    
    lcd.setCursor(8,0);
    lcd.print("Eight");
    delay(tic);

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd
      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//********************************************************************************************************

//******************************************************************************************************

//                                     --- menuNine Function Block ---
void menuNine(){//function bracket
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here
    
    
    lcd.setCursor(8,0);
    lcd.print("Nine");
    delay(tic);

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd
      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//********************************************************************************************************

//******************************************************************************************************

//                                     --- menuTen Function Block ---
void menuTen(){//function bracket
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here
    
    
    lcd.setCursor(8,0);
    lcd.print("Ten");
    delay(tic);

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd
      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//********************************************************************************************************

//******************************************************************************************************

//                                     --- menuEleven Function Block ---
void menuEleven(){//function bracket
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here
    
    
    lcd.setCursor(8,0);
    lcd.print("Eleven");
    delay(tic);

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd
      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//********************************************************************************************************

//******************************************************************************************************

//                                     --- menuTwelve Function Block ---
void menuTwelve(){//function bracket
  while (swBval == 1){//While the B button is not pushed, do this until B is pushed 

    //Put function executions here
    
    
    lcd.setCursor(8,0);
    lcd.print("Twelve");
    delay(tic);

    readSwitches();                      //Read the switch values in the readSwitches function          
    if (swBval==0){                    //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd
      //Do stuff here before going back to Main Menu

      return;  

    }//if swB is pressed Return
  }//While bracket 
}//last function bracket
//********************************************************************************************************

 //*******************************************************************************************
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
  }}

/* **************************************************----- CONNECTIONS ----****************************************************

Parts:
Led Shield copy and paste to ebay search:    Arduino Display kit 6 bit Blue LED Module Board for UNO MEGA2560 AVR ARM FPGA 
Sensor Shield Expansion board copy and paste to ebay search:    Sensor Shield Expansion Board Shield For Arduino UNO R3 V5.0 Electric Module 
4 Button Keypad ebay search:    Arduino keypad 4 Button Key Module Switch Keyboard for UNO MEGA2560 Breadboard 
16 x 2 1602 LCD with I2C interface ebay search:   1602 LCD 16x2  with IIC I2C Serial Interface Adapter Module

Wiring:
20 K ohm Potiometer wiper to A0 one side to ground and the other to 5volts
Led shield ground leg bent out to connect to a ground on the sensor shield and the others are plugged into 2,3,4,5,6, and 7
4 Button Keypad shield inserted into the sensor shield in pins 9,10,11, and the ground plugged into 12.  I set pin 12 low so it would act as a fake ground.
LCD I2C connected to the IIC on the sensor shield... SCL to SCL, SDA to SDA, + to +, and - to -
I hope to have some good pictures for the set up for this.

Note:  I am still somewhat of a beginner with arduino.  I needed to come up with a different approach to programming
because I was so slow at getting things to work.  This ability to look at alot of sketches to find different control 
structure types helped me to find examples really fast to build on things I had already tried without having to 
open up alot of other sketches.  I initially had no plans to come up with something that I wanted to publish on the
internet.  After searching through hundreds of sketches, I noticed there were a few genuises out there I should give
credit to.  I also wanted to be helpful to others and publish this to speed up the learning curve to programming effectively on the arduino.
*/



