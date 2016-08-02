
//******************************************************************************************************************
/* by John Poston 8/2/2016

  Easy to use 2x16 lcd menu with multiple functions

  --Parts: 2x16 lcd with i2c piggyback
         Potentiometer 20K ohms
         2 Switches
         6 leds with voltage drop resistors
         Piezo earphone or speaker
         IR remote reciever and remote control

  A video of this in operation on youtube at:  https://youtu.be/GRrijVuDGwc
  
  -- Purpose and General Operation
  The purpose of this file is to have many sketches run on one program.  This was achieved by using a potentiometer to
  select the different menu choices. Once a menu item is selected with the potentiometer(on pin A0), press the button
  connected to pin 11; this is the 'A' button. To stop the sketch and go back to the menu selector, press 'B' button 
  connected to pin 10.
 
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
  --  menuOne  ********
  --  menuTwo  ********
  --  menuThree *******
  --  menuFour ********
  --  menuFive ********
  --  menuSix *********
  --  menuSeven *******
  --  menuEight *******
  --  menuNine ********
  --  menuTen *********
  --  menuEleven ******
  --  CONNECTIONS *****Enter "CONECTIONS" into the Edit/Find dialog box
  --  Index
  --  Glossary
  --  Error Message Solved - Conflict with tone and the IR library using the same timer in the Libraries
*/
//**********************************************LIBRARIES***********************************************************
#include <Wire.h>//These libraries can be downloaded from:  https://www.arduino.cc/en/Reference/Libraries
#include <LiquidCrystal_I2C.h>
#include "IRremote.h" //  https://brainy-bits.com/tutorials/ir-remote-arduino/

//*********************************************LIQUID CRYSTAL*******************************************************
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address (0x3F) or (0x27)
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address (0x3F) or (0x27)
//Open the Serial Monitor to view the I2C address
//****************************************************LEDS**********************************************************
int ledPins[] = {
  2, 3, 4, 5, 6, 7
};       // an array of pin numbers to which LEDs are attached
int pinCount = 6;           // the number of pins (i.e. the length of the array)
//***********************************************FILE NAME**********************************************************
//file name string to be put into serial out or lcd
String revLev = "LCD_1602_MENU_";
String revLevB = "--08/02/2016--";
//*************************************************STRINGS**********************************************************
String menu = "Menu = ";
String blanks = "                "; //Puts 16 Blank Spaces on LCD
//**********************************************VARIABLES***********************************************************
//Switch Variables
byte swA = 11;
byte swAval;
byte swB = 10;
byte swBval;
int tic = 71; //Brief pauses to be used in delays
//*************************************************SET UP***********************************************************
void setup() { //setup code put here to run once
  Serial.begin(9600); //Begin serial connection 9600 baud rate
  Serial.println("File Name:   ");
  Serial.print(revLev);
  Serial.println(revLevB);
  Serial.println("");

  //Switch PinModes
  pinMode(swA, INPUT_PULLUP);
  pinMode(swB, INPUT_PULLUP);
  //Declare LCD Object and size
  lcd.begin(16, 2);  // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.print(revLev);
  lcd.setCursor(0, 1);
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
void loop() { //loop code to run repeatedly

  mainMenu();   //Runs the menu selector for the number function to run

}
//**********************************************readSwitcher*******************************************************
void readSwitches() { //Evaluates the States of the four Switches
  swAval = digitalRead(swA);
  swBval = digitalRead(swB);
  //delay(300);
}
//**********************************************blinker*************************************************************
void blinker() { //Blinks lcd backlight on and off at startup
  int bone = 3000;//tone frequency

  for (int i = 0; i < 20; i++)
  {
    lcd.noBacklight();
    tone(9, bone, 30);
    delay(35);
    lcd.backlight();
    delay(10);
    bone = bone + 250;
  }
}
//************************************************mainMenu*************************************************************
void mainMenu() {
  int sensorReading = 0;
  sensorReading = analogRead(A0);
  int rangeMenu = map(sensorReading, 0, 1023, 1, 11);
  int(inByte) = rangeMenu;
  switch (inByte) {
    //******************************************************************************************************************
    //==================================================================================================================
    //================================================menuOne===========================================================

    case 1:

      lcd.home();                   //Bring cursor back to the beginning
      //       --1234567890123456-- //Lcd numbers for place holders
      lcd.print("#1              ");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuOne();                  //function chosen for this case selected by the variable resistor
      }                             // end of if bracket.  Runs function until swB is pressed inside of function
      break;

    //==================================================================================================================
    //================================================menuTwo===========================================================

    case 2:
      lcd.home();                   //Bring cursor back to the beginning
      //       --1234567890123456-- //Lcd numbers for place holders
      lcd.print("#2              ");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuTwo();                  //function chosen for this case selected by the variable resistor
      }                             // end of if bracket.  Runs function until swB is pressed inside of function
      break;
    //==================================================================================================================
    //================================================menuThree=========================================================

    case 3:
      lcd.home();                   //Bring cursor back to the beginning
      //       --1234567890123456-- //Lcd numbers for place holders
      lcd.print("#3              ");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuThree();                //function chosen for this case selected by the variable resistor
      }                             // end of if bracket.  Runs function until swB is pressed inside of function
      break;
    //==================================================================================================================
    //================================================menuFour==========================================================

    case 4:
      lcd.home();                   //Bring cursor back to the beginning
      //       --1234567890123456-- //Lcd numbers for place holders
      lcd.print("#4              ");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuFour();                 //function chosen for this case selected by the variable resistor
      }                             // end of if bracket.  Runs function until swB is pressed inside of function
      break;
    //==================================================================================================================
    //================================================menuFive==========================================================

    case 5:
      lcd.home();                   //Bring cursor back to the beginning
      //       --1234567890123456-- //Lcd numbers for place holders
      lcd.print("#5              ");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuFive();                 //function chosen for this case selected by the variable resistor
      }                             // end of if bracket.  Runs function until swB is pressed inside of function
      break;
    //==================================================================================================================
    //================================================menuSix===========================================================

    case 6:
      lcd.home();                  //Bring cursor back to the beginning
      //       --1234567890123456-- //Lcd numbers for place holders
      lcd.print("#6              ");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuSix();                  //function chosen for this case selected by the variable resistor
      }                             // end of if bracket.  Runs function until swB is pressed inside of function
      break;
    //==================================================================================================================
    //================================================menuSeven=========================================================

    case 7:
      lcd.home();                   //Bring cursor back to the beginning
      //       --1234567890123456-- //Lcd numbers for place holders
      lcd.print("#7              ");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuSeven();                //function chosen for this case selected by the variable resistor
      }                             // end of if bracket.  Runs function until swB is pressed inside of function
      break;
    //==================================================================================================================
    //================================================menuEight=========================================================

    case 8:
      // Multiple "Blink Without Delays" using the millis()

      lcd.home();                  //Bring cursor back to the beginning
      //       --1234567890123456-- //Lcd numbers for place holders
      lcd.print("#8              ");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuEight();                //function chosen for this case selected by the variable resistor
      }                             // end of if bracket.  Runs function until swB is pressed inside of function
      break;
    //==================================================================================================================
    //================================================menuNine==========================================================

    case 9:
      lcd.home();                  //Bring cursor back to the beginning
      //       --1234567890123456-- //Lcd numbers for place holders
      lcd.print("#9              ");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuNine();                 //function chosen for this case selected by the variable resistor
      }                             // end of if bracket.  Runs function until swB is pressed inside of function
      break;
    //==================================================================================================================
    //================================================menuTen===========================================================

    case 10:
      lcd.home();                  //Bring cursor back to the beginning
      //       --1234567890123456-- //Lcd numbers for place holders
      lcd.print("#10             ");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuTen();                  //function chosen for this case selected by the variable resistor
      }                             // end of if bracket.  Runs function until swB is pressed inside of function
      break;


    //These brackets are only used at the end of the last case
    //}//End of Switch Bracket
    //}//End of mainMenu function Bracket
    //==================================================================================================================
    //================================================menuTen===========================================================

    case 11:
      lcd.home();                  //Bring cursor back to the beginning
      //       --1234567890123456-- //Lcd numbers for place holders
      lcd.print("#11             ");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuEleven();               //function chosen for this case selected by the variable resistor
      }                             // end of if bracket.  Runs function until swB is pressed inside of function
      break;


      //These brackets are only used at the end of the last case
  }//End of Switch Bracket
}//End of mainMenu function Bracket
//==================================================================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuOne Function Block ---
void menuOne() { //function bracket

  //********************** This would be equivalent to the setup area in a regular sketch *************************

  lcd.clear();
  lcd.setCursor(0, 0);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Name...");
  lcd.setCursor(0, 1);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Run... ");

//****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

//*******************************************Put function executions Below******************************************

    
    
//*************************************************End of menu chosen sketch****************************************

    

    readSwitches();                      //Read the switch values in the readSwitches function
    if (swBval == 0) {                 //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //**************************************Do stuff here before going back to Main Menu**************************


      return;

    }//if swB is pressed Return
  }//While bracket
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuTwo    Function Block ---
void menuTwo   () { //function bracket

  //********************** This would be equivalent to the setup area in a regular sketch *************************

  lcd.clear();
  lcd.setCursor(0, 0);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Name...");
  lcd.setCursor(0, 1);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Run... ");

//****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

//*******************************************Put function executions Below******************************************

    
    
//*************************************************End of menu chosen sketch****************************************

    

    readSwitches();                      //Read the switch values in the readSwitches function
    if (swBval == 0) {                 //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //**************************************Do stuff here before going back to Main Menu**************************


      return;

    }//if swB is pressed Return
  }//While bracket
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuThree Function Block ---
void menuThree() { //function bracket

  //********************** This would be equivalent to the setup area in a regular sketch *************************

  lcd.clear();
  lcd.setCursor(0, 0);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Name...");
  lcd.setCursor(0, 1);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Run... ");

//****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

//*******************************************Put function executions Below******************************************

    
    
//*************************************************End of menu chosen sketch****************************************

    

    readSwitches();                      //Read the switch values in the readSwitches function
    if (swBval == 0) {                 //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //**************************************Do stuff here before going back to Main Menu**************************


      return;

    }//if swB is pressed Return
  }//While bracket
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuFour Function Block ---
void menuFour() { //function bracket

  //********************** This would be equivalent to the setup area in a regular sketch *************************

  lcd.clear();
  lcd.setCursor(0, 0);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Name...");
  lcd.setCursor(0, 1);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Run... ");

//****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

//*******************************************Put function executions Below******************************************

    
    
//*************************************************End of menu chosen sketch****************************************

    

    readSwitches();                      //Read the switch values in the readSwitches function
    if (swBval == 0) {                 //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //**************************************Do stuff here before going back to Main Menu**************************


      return;

    }//if swB is pressed Return
  }//While bracket
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuFive Function Block ---
void menuFive() { //function bracket

  //********************** This would be equivalent to the setup area in a regular sketch *************************

  lcd.clear();
  lcd.setCursor(0, 0);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Name...");
  lcd.setCursor(0, 1);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Run... ");

//****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

//*******************************************Put function executions Below******************************************

    
    
//*************************************************End of menu chosen sketch****************************************

    

    readSwitches();                      //Read the switch values in the readSwitches function
    if (swBval == 0) {                 //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //**************************************Do stuff here before going back to Main Menu**************************


      return;

    }//if swB is pressed Return
  }//While bracket
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuSix Function Block ---
void menuSix() { //function bracket

  //********************** This would be equivalent to the setup area in a regular sketch *************************

  lcd.clear();
  lcd.setCursor(0, 0);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Name...");
  lcd.setCursor(0, 1);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Run... ");

//****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

//*******************************************Put function executions Below******************************************

    
    
//*************************************************End of menu chosen sketch****************************************

    

    readSwitches();                      //Read the switch values in the readSwitches function
    if (swBval == 0) {                 //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //**************************************Do stuff here before going back to Main Menu**************************


      return;

    }//if swB is pressed Return
  }//While bracket
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuSeven Function Block ---
void menuSeven() { //function bracket

  //********************** This would be equivalent to the setup area in a regular sketch *************************

  lcd.clear();
  lcd.setCursor(0, 0);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Name...");
  lcd.setCursor(0, 1);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Run... ");

//****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

//*******************************************Put function executions Below******************************************

    
    
//*************************************************End of menu chosen sketch****************************************

    

    readSwitches();                      //Read the switch values in the readSwitches function
    if (swBval == 0) {                 //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //**************************************Do stuff here before going back to Main Menu**************************


      return;

    }//if swB is pressed Return
  }//While bracket
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuEight Function Block ---
void menuEight() { //function bracket

  //********************** This would be equivalent to the setup area in a regular sketch *************************

  lcd.clear();
  lcd.setCursor(0, 0);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Name...");
  lcd.setCursor(0, 1);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Run... ");

//****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

//*******************************************Put function executions Below******************************************

    
    
//*************************************************End of menu chosen sketch****************************************

    

    readSwitches();                      //Read the switch values in the readSwitches function
    if (swBval == 0) {                 //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //**************************************Do stuff here before going back to Main Menu**************************


      return;

    }//if swB is pressed Return
  }//While bracket
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuNine Function Block ---
void menuNine() { //function bracket

  //********************** This would be equivalent to the setup area in a regular sketch *************************

  lcd.clear();
  lcd.setCursor(0, 0);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Name...");
  lcd.setCursor(0, 1);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Run... ");

//****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

//*******************************************Put function executions Below******************************************

    
    
//*************************************************End of menu chosen sketch****************************************

    

    readSwitches();                      //Read the switch values in the readSwitches function
    if (swBval == 0) {                 //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //**************************************Do stuff here before going back to Main Menu**************************


      return;

    }//if swB is pressed Return
  }//While bracket
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuTen Function Block ---
void menuTen() { //function bracket

  //********************** This would be equivalent to the setup area in a regular sketch *************************

  lcd.clear();
  lcd.setCursor(0, 0);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Name...");
  lcd.setCursor(0, 1);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Run... ");

//****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

//*******************************************Put function executions Below******************************************

    
    
//*************************************************End of menu chosen sketch****************************************

    

    readSwitches();                      //Read the switch values in the readSwitches function
    if (swBval == 0) {                 //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //**************************************Do stuff here before going back to Main Menu**************************


      return;

    }//if swB is pressed Return
  }//While bracket
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuEleven Function Block ---
void menuEleven() { //function bracket

  //********************** This would be equivalent to the setup area in a regular sketch *************************

  lcd.clear();
  lcd.setCursor(0, 0);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Name...");
  lcd.setCursor(0, 1);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Program Run... ");

//****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

//*******************************************Put function executions Below******************************************

    
    
//*************************************************End of menu chosen sketch****************************************

    

    readSwitches();                      //Read the switch values in the readSwitches function
    if (swBval == 0) {                 //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //**************************************Do stuff here before going back to Main Menu**************************


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
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
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
  lcd.setCursor(0, 0);
  lcd.print(" Scanning...");
  //lcd.print (onDevices = 0);
  for (oaddress = 1; oaddress < 127; oaddress++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(oaddress);
    oerror = Wire.endTransmission();

    if (oerror == 0)
    {
      lcd.setCursor(0, 1);
      lcd.print("I2C 0x");
      if (oaddress < 16)
        lcd.print("0");
      lcd.print(oaddress, HEX);
      lcd.print(" ");
      onDevices++;
    }
    else if (oerror == 4)
    {
      lcd.print("error address 0x");
      if (oaddress < 16)
        lcd.print("0");
      lcd.print(oaddress, HEX);
    }
  }
  if (onDevices == 0)
    lcd.print("No I2C devices found\n");
  else
    lcd.print("done");

  delay(100);
  lcd.setCursor(0, 0);
  lcd.print(blanks);
  if (swBval == 0) {
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

  
*/

/*
  ---------------------------------------------------GLOSSARY----------------------------------------------------
  --Aqua blue words--

  byte
  char
  const int
  float
  HEX
  HIGH
  INPUT_PULLUP
  int
  long
  LOW
  OUTPUT
  unsigned long
  void

  --Orange Words--

  analogRead
  analogWrite
  digitalRead
  digitalWrite
  lcd.begin
  lcd.clear
  lcd.home
  lcd.print
  lcd.setcursor
  lcd.write
  LiquidCrystal
  map
  millis ();
  pinMode
  Serial.begin
  Serial.print
  Serial.println
  tone
  Wire.beginTransmission
  Wire.endTransmission
  Wire.h

  --Green Words--

  break
  case
  elseif
  for
  if
  if/esle
  include
  loop
  return
  setup
  switch
  while




*/
/*
  ----------------------------------------------------LCD and Wire Key Words------------------------------------------------------
  --LCD Key Words--
  begin
  clear
  home
  print
  setCursor
  cursor
  noCursor
  blink
  noBlink
  display
  noDisplay
  autoscroll
  noAutoscroll
  leftToRight
  rightToLeft
  scrollDisplayLeft
  scrollDisplayRight
  createChar

  --Wire Key Words--
  begin
  beginTransmission
  endTransmission
  requestFrom
  send
  receive
  onReceive
  onRequest

*/


/*
  ----------------------------------------------------INDEX------------------------------------------------------
  A
  activate
  address
  analogpin
  analogRead
  analogWrite
  array
  ASCII

  B
  backlight
  bar
  baud rate
  begin
  blank
  blink
  block
  bracket
  button
  byte


  C


  D


  E


  F


  G


  H


  I


  J


  K


  L


  M


  N


  O


  P


  Q


  R


  S


  T


  U


  V



  W


  X


  Y


  Z




*/
/*

   ERROR MESSAGE when "tone" function and IR library used in the same sketch

   I can comment "tone" out and there isn't any error message

   #include "IRremote.h"

    tone(9, 1000, 250);


  Error Message Dialog Box:


  Arduino: 1.6.9 (Linux), Board: "Arduino/Genuino Uno"

  core/core.a(Tone.cpp.o): In function `__vector_7':
  /opt/arduino-1.6.9/hardware/arduino/avr/cores/arduino/Tone.cpp:539: multiple definition of `__vector_7'
  libraries/IRremote/IRremote.cpp.o:/home/banana/Arduino/libraries/IRremote/IRremote.cpp:339: first defined here
  collect2: error: ld returned 1 exit status
  exit status 1
  Error compiling for board Arduino/Genuino Uno.

  This report would have more information with
  "Show verbose output during compilation"
  option enabled in File -> Preferences.

  Solution: Go to the Library IRremoteInt.h

  find and make sure this part of the code is commented as follows:

  Arduino Duemilanove, Diecimila, LilyPad, Mini, Fio, etc
  #else
  #define IR_USE_TIMER1   // tx = pin 9
  // #define IR_USE_TIMER2     // tx = pin 3
  #endif

*/



