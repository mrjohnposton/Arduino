
//******************************************************************************************************************
/* by John Poston 8/8/2016

General Public License rev. 3

  Easy to use 2x16 lcd menu with multiple functions
  Remote,Motor controls, and OOP (Object Oriented Program) Experiments

  -CONTENTS
  --  readSwitches  ***Function to read switches attached to A on 11 and B on 10
  --  mainMenu  *******Main Menu function for selecting different sketches
  --  menuOne  ********IR remote control key is displayed on the LCD and the Serial Monitor
  --  menuTwo  ********IR remote Control of Motors  http://www.instructables.com/id/ARDUINO-based-IR-remote-control-robot/step4/Project-step2-upload-IR-robot-code-and-play/
  --  menuThree *******IR remote HEX value to LCD
  --  menuFour ********Blink without delay on/off time control (???PWM for DC Motors???)
  --  menuFive ********Blink by Classes from:  https://learn.adafruit.com/multi-tasking-the-arduino-part-1/a-classy-solution
  --  menuSix *********DRTV Remote Control Decodes
  --  menuSeven *******
  --  menuEight *******
  --  menuNine ********
  --  menuTen *********
  --  menuEleven ******
  --  CONNECTIONS *****Enter "CONECTIONS" into the Edit/Find dialog box
  --  Index
  --  Glossary
*/
//**********************************************LIBRARIES***********************************************************
//#include <Wire.h>//These libraries can be downloaded from:  https://www.arduino.cc/en/Reference/Libraries
#include <LiquidCrystal_I2C.h>
#include <IRremote.h> //  https://brainy-bits.com/tutorials/ir-remote-arduino/

//*********************************************LIQUID CRYSTAL*******************************************************
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address (0x3F) or (0x27)
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address (0x3F) or (0x27)
//****************************************************LEDS**********************************************************
int ledPin = 13;
int ledPins[] = {
  2, 3, 4, 5, 6, 7
};       // an array of pin numbers to which LEDs are attached
int pinCount = 6;           // the number of pins (i.e. the length of the array)

//*************************************************STRINGS**********************************************************
String blanks = "                "; //Puts 16 Blank Spaces on LCD
String fileName = "A_1_IR_Remote_16x2_LCD_Menus_08_18_2016";  // Prints file name to LCD and Serial Monitor
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
  //Switch PinModes
  pinMode(swA, INPUT_PULLUP);
  pinMode(swB, INPUT_PULLUP);
  //Declare LCD Object and size
  lcd.begin(16, 2);  // initialize the lcd for 16 chars 2 lines, turn on backlight
  


  //Led array as outputs
  for (int thisPin = 0; thisPin < pinCount; thisPin++)  {
    pinMode(ledPins[thisPin], OUTPUT);
  }//for end bracket
lcd.home();
lcd.print(fileName);
Serial.print(fileName);
delay (1000);
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
      lcd.print("#1 IRremote Test");//menuXxx function also displays the address on the serial monitor
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
      lcd.print("#2  IR Motor Out");//menuXxx function also displays the address on the serial monitor
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
      lcd.print("#3 IR HEX Value ");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuThree();                //function chosen for this case selected by the variable resistor
      }                            // end of if bracket.  Runs function until swB is pressed inside of function
      break;
    //==================================================================================================================
    //================================================menuFour==========================================================

    case 4:
      lcd.home();                   //Bring cursor back to the beginning
      //       --1234567890123456-- //Lcd numbers for place holders
      lcd.print("#4 Blink Times-o");//menuXxx function also displays the address on the serial monitor
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
      lcd.print("#5 Blink Classes");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuFive();                 //function chosen for this case selected by the variable resistor
      }                          // end of if bracket.  Runs function until swB is pressed inside of function
      break;
    //==================================================================================================================
    //================================================menuSix===========================================================

    case 6:
      lcd.home();                  //Bring cursor back to the beginning
      //       --1234567890123456-- //Lcd numbers for place holders
      lcd.print("#6  DRTV Remote ");//menuXxx function also displays the address on the serial monitor
      lcd.setCursor(0, 1);          //Put cursor at the begining of the second line
      lcd.print("Press A:ON B:OFF");//Line two for the choices to start or stop a function
      delay (tic);                  //Delay long enough for the lcd to refresh and display
      readSwitches();               //Goes to the readSwitches function
      if (swAval == 0)              //If swA is pressed, activate the function
      { //if bracket
        menuSix();                  //function chosen for this case selected by the variable resistor
      }                            // end of if bracket.  Runs function until swB is pressed inside of function
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
      }                            // end of if bracket.  Runs function until swB is pressed inside of function
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
    //================================================menuEleven===========================================================

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

  int receiver = 8; // Signal Pin of IR receiver to Arduino Digital Pin 8

  IRrecv irrecv(receiver);     // create instance of 'irrecv'
  decode_results results;      // create instance of 'decode_results'
  irrecv.enableIRIn(); // Start the receiver
  lcd.clear();

  lcd.setCursor(0, 0);
  //         --1234567890123456-- //Lcd numbers for place holders
  lcd.print("IR Remote Value");

  //****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

    //*******************************************Put function executions Below******************************************

    lcd.print(blanks);
    lcd.home();

    //Put function executions here
    for (int thisPin = 2; thisPin < 8; thisPin++) {
      digitalWrite(thisPin, LOW);
    }
    lcd.setCursor(0, 1);


    if (irrecv.decode(&results)) // have we received an IR signal?
    {
      switch (results.value)
      {
        case 0xFF629D: Serial.println("  --Forward--   "); lcd.print("  --Forward--   "); break;
        case 0xFF22DD: Serial.println(" LEFT"); lcd.print("-LEFT-");   break;
        case 0xFF02FD: Serial.println(" -OK-"); lcd.print("-OK- ");   break;
        case 0xFFC23D: Serial.println(" RIGHT"); lcd.print("-RIGHT-");  break;
        case 0xFFA857: Serial.println("  --Reverse--   "); lcd.print("  --Reverse--   "); break;
        case 0xFF6897: Serial.println(" 1"); digitalWrite (2, HIGH); lcd.print("-1-"); break;
        case 0xFF9867: Serial.println(" 2"); digitalWrite (3, HIGH); lcd.print("-2-"); break;
        case 0xFFB04F: Serial.println(" 3");  digitalWrite (4, HIGH); lcd.print("-3-"); break;
        case 0xFF30CF: Serial.println(" 4"); digitalWrite (5, HIGH); lcd.print("-4-"); break;
        case 0xFF18E7: Serial.println(" 5");  digitalWrite (6, HIGH); lcd.print("-5-"); break;
        case 0xFF7A85: Serial.println(" 6");  digitalWrite (7, HIGH); lcd.print("-6-"); break;
        case 0xFF10EF: Serial.println(" 7"); lcd.print("-7-"); break;
        case 0xFF38C7: Serial.println(" 8"); lcd.print("-8-");  break;
        case 0xFF5AA5: Serial.println(" 9");  lcd.print("-9-"); break;
        case 0xFF4AB5: Serial.println(" 0");  lcd.print("-0- "); break;
        case 0xFF42BD: Serial.println(" *");         lcd.print("-*-");             break;
        case 0xFF52AD: Serial.println(" #");          lcd.print("-#-");            break;
        case 0xFFFFFFFF: Serial.println(" REPEAT");    lcd.print("-REPEAT-");           break;
        //COLOR BUTTONS ON THE DIRECT TV REMOTE
        case 0xC332FABB: Serial.println(" RED ");         lcd.print("-RED-");             break;
        case 0x8C0B38A3: Serial.println(" GREEN ");         lcd.print("-GREEN-");             break;
        case 0x2591C110: Serial.println(" YELLOW ");         lcd.print("-YELLOW-");             break;
        case 0x506AE98B: Serial.println(" BLUE ");         lcd.print("-BLUE-");             break;

        default:
          Serial.println(" other button   "); lcd.print("     WHOOPS !!! ");

      }// End Case
      delay(500); // Do not get immediate repeat
      //END translateIR
      irrecv.resume(); // receive the next value
    }

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
  //       --1234567890123456-- //Lcd numbers for place holders
  lcd.print("-Motor Control-");


  lcd.setCursor(0, 1);
  lcd.print(blanks);
  lcd.home();
  //      --1234567890123456-- //Lcd numbers for place holders


  int RECV_PIN = 8;

  byte pinTwo = 2;   // + Left Motor
  byte pinThree = 3; // - Left Motor
  byte pinFour = 4;  // + Right Motor
  byte pinFive = 5;  // - Right Motor
  byte pinSix = 6;
  byte pinSeven = 7;

  IRrecv irrecv(RECV_PIN);
  decode_results results;

  int statusled = 13;
  Serial.begin(9600); //Begin serial connection 9600 baud rate
  Serial.println("Hello");
  irrecv.enableIRIn();

  pinMode(statusled, OUTPUT);
  pinMode(pinTwo, OUTPUT);
  pinMode(pinThree, OUTPUT);
  pinMode(pinFour, OUTPUT);
  pinMode(pinFive, OUTPUT);
  digitalWrite(statusled, LOW);


  //****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

    //*******************************************Put function executions Below******************************************
    if (irrecv.decode(&results)) {

      digitalWrite(statusled, HIGH);

      irrecv.resume();

      if (results.value == 0xFF629D) { // type your remote forward robot control button hex value in underlined area.
        Serial.println("Forward");
        digitalWrite(pinTwo, HIGH);
        digitalWrite(pinThree, LOW);
        digitalWrite(pinFour, HIGH);
        digitalWrite(pinFive, LOW);


        lcd.setCursor(0, 1);
        // lcd.print(blanks);
        // lcd.home();
        //      --1234567890123456-- //Lcd numbers for place holders
        lcd.print("  --Forward--  ");

      } else if (results.value == 0xFF22DD) { // type your remote left robot control button hex value in underlined area.

        digitalWrite(pinTwo, HIGH);
        digitalWrite(pinThree, LOW);
        digitalWrite(pinFour, LOW);
        digitalWrite(pinFive, LOW);

        lcd.setCursor(0, 1);
        //  lcd.print(blanks);
        //lcd.home();
        //      --1234567890123456-- //Lcd numbers for place holders
        lcd.print("    --Left--   ");



      }

      else if (results.value == 0xFFC23D) { // type your remote right robot control button hex value in underlined area.

        digitalWrite(pinTwo, LOW);
        digitalWrite(pinThree, LOW);
        digitalWrite(pinFour, HIGH);
        digitalWrite(pinFive, LOW);

        lcd.setCursor(0, 1);
        //lcd.print(blanks);
        // lcd.home();
        //      --1234567890123456-- //Lcd numbers for place holders
        lcd.print("   --Right--   ");

      } else if (results.value == 0xFFA857) { // type your remote backward robot control button hex value in underlined area.

        digitalWrite(pinTwo, LOW);
        digitalWrite(pinThree, HIGH);
        digitalWrite(pinFour, LOW);
        digitalWrite(pinFive, HIGH);

        lcd.setCursor(0, 1);
        //lcd.print(blanks);
        //lcd.home();
        //      --1234567890123456-- //Lcd numbers for place holders
        lcd.print("  --Reverse--   ");

      } else if (results.value == 0xFF02FD) { // -ok- type your remote stop robot control button hex value in underlined area.

        digitalWrite(pinTwo, LOW);
        digitalWrite(pinThree, LOW);
        digitalWrite(pinFour, LOW);
        digitalWrite(pinFive, LOW);

        lcd.setCursor(0, 1);
        // lcd.print(blanks);
        //lcd.home();
        //      --1234567890123456-- //Lcd numbers for place holders
        lcd.print("    --Stop--   ");

      }
    }


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
  //       --1234567890123456-- //Lcd numbers for place holders
  lcd.print("  Remote Control");
  //Put variables and "setup" information here to run only once.
  int RECV_PIN = 8;
  IRrecv irrecv(RECV_PIN);
  decode_results results;
  irrecv.enableIRIn(); // Start the receiver




  //****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

    //*******************************************Put function executions Below******************************************


    if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      irrecv.resume(); // Receive the next value
      long outPut = results.value;
      lcd.setCursor(0, 1);
      lcd.print("HEX:0x");
      lcd.print(outPut, HEX);
      lcd.print("     ");
    }


    delay(100);
    //lcd.setCursor(13, 0);//Comment out when sketch is added
    // lcd.print("Run");    //Comment out when sketch is added
    // delay(tic);          //Comment out when sketch is added or it will be glitchy

    readSwitches();                    //Read the switch values in the readSwitches function
    if (swBval == 0) {                 //Look to see if swB is pressed
      lcd.clear();

      //*************************************************End of menu chosen sketch****************************************

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

  int ledState = LOW;             // ledState used to set the LED
  pinMode(ledPin, OUTPUT);   // set the digital pin as output:
  unsigned long previousMillis = 0;        // will store last time LED was updated
  long OnTime;           // milliseconds of on-time
  long OffTime;          // milliseconds of off-time

  lcd.clear();
  lcd.setCursor(0, 0);
  //      --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Blink millis() ");


  //****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

    //*******************************************Put function executions Below******************************************

    //Read the potentiometer for the off time
    int sensorReading = analogRead(A0);
    OffTime = map(sensorReading, 0, 1023, 1, 1000);
OnTime = OffTime;  //can get rid of this and add another pot for OnTime
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();

    if ((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, ledState);    // Update the actual LED
    }
    lcd.setCursor(0, 1);
    //      --1234567890123456-- //Lcd numbers for place holders
    lcd.print("On:");
    lcd.print(OnTime);
    lcd.print(" Off:");
    lcd.print(OffTime);
    lcd.print("   ");


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
  
//Good Info on Object Oriented Programming  --OOP--
//http://www.mactech.com/articles/mactech/Vol.09/09.10/CPPBasics/index.html
//http://www.instructables.com/id/Arduino-Button-Tutorial/step5/Adding-Buttons-and-Going-OO/

  //********************** This would be equivalent to the setup area in a regular sketch *************************

  lcd.clear();
  lcd.setCursor(0, 0);
  //       --1234567890123456-- //Lcd numbers for place holders
  lcd.print("Flash by Classes");
  lcd.setCursor(0, 1);
  //      --1234567890123456-- //Lcd numbers for place holders
  class Flasher
  {
      // Class Member Variables
      // These are initialized at startup
      int ledPin;      // the number of the LED pin
      long OnTime;     // milliseconds of on-time
      long OffTime;    // milliseconds of off-time

      // These maintain the current state
      int ledState;                 // ledState used to set the LED
      unsigned long previousMillis;   // will store last time LED was updated

      // Constructor - creates a Flasher
      // and initializes the member variables and state
    public:
      Flasher(int pin, long on, long off)
      {
        ledPin = pin;
        pinMode(ledPin, OUTPUT);

        OnTime = on;
        OffTime = off;

        ledState = LOW;
        previousMillis = 0;
      }

      void Update()
      {
        // check to see if it's time to change the state of the LED
        unsigned long currentMillis = millis();

        if ((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
        {
          ledState = LOW;  // Turn it off
          previousMillis = currentMillis;  // Remember the time
          digitalWrite(ledPin, ledState);  // Update the actual LED
        }
        else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
        {
          ledState = HIGH;  // turn it on
          previousMillis = currentMillis;   // Remember the time
          digitalWrite(ledPin, ledState);   // Update the actual LED
        }
      }
  };
  //     Led Pin, On ,OFF
  Flasher led1(2, 10, 199);
  Flasher led2(3, 11, 200);
  Flasher led3(4, 10, 198);
  Flasher led4(5, 11, 201);
  Flasher led5(6, 10, 197);
  Flasher led6(7, 11, 202);


  //****************************************This would be the end of the setup area***********************************

  while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

    //*******************************************Put function executions Below******************************************

    led1.Update();
    led2.Update();
    led3.Update();
    led4.Update();
    led5.Update();
    led6.Update();

    //*************************************************End of menu chosen sketch****************************************



    readSwitches();                      //Read the switch values in the readSwitches function
    if (swBval == 0) {                 //Look to see if swB is pressed
      lcd.clear();                     //if so, clear the lcd

      //**************************************Do stuff here before going back to Main Menu**************************
      for (int thisPin = 0; thisPin < pinCount; thisPin++)  {//Sets all the Leds off when function is stopped
        digitalWrite(ledPins[thisPin], LOW);
      }//for end bracket

      return;

    }//if swB is pressed Return
  }//While bracket
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuSix Function Block ---
void menuSix() { //function bracket
 
    //********************** This would be equivalent to the setup area in a regular sketch *************************
//Old Direct TV Remote Control
   int receiver = 8; // Signal Pin of IR receiver to Arduino Digital Pin 8

  IRrecv irrecv(receiver);     // create instance of 'irrecv'
  decode_results results;      // create instance of 'decode_results'
  irrecv.enableIRIn(); // Start the receiver
  lcd.clear();

  lcd.setCursor(0, 0);
  //       --1234567890123456-- //Lcd numbers for place holders
  lcd.print(" DRTV IR Value  ");

    //****************************************This would be the end of the setup area***********************************

    while (swBval == 1) { //While the B button is not pushed, do this until B is pushed

    //*******************************************Put function executions Below******************************************
 lcd.print(blanks);
    lcd.home();

    //Put function executions here
    for (int thisPin = 2; thisPin < 8; thisPin++) {
      digitalWrite(thisPin, LOW);
    }
    lcd.setCursor(0, 1);


    if (irrecv.decode(&results)) // have we received an IR signal?
    {
      switch (results.value)
      {
        case 0xF24119FE: Serial.println("  --Forward--   "); lcd.print("  --Forward--   "); break;
        case 0xC53794B4: Serial.println(" LEFT"); lcd.print("-LEFT-");   break;
        case 0x75A956A7: Serial.println(" -SELECT-"); lcd.print("-SELECT- ");   break;
        case 0xBC9DF06: Serial.println(" RIGHT"); lcd.print("-RIGHT-");  break;
        case 0xB489062B: Serial.println("  --Reverse--   "); lcd.print("  --Reverse--   "); break;
        case 0xC9767F76: Serial.println(" 1"); digitalWrite (2, HIGH); lcd.print("-1-"); break;
        case 0xC8155AB1: Serial.println(" 2"); digitalWrite (3, HIGH); lcd.print("-2-"); break;
        case 0xB6996DAE: Serial.println(" 3");  digitalWrite (4, HIGH); lcd.print("-3-"); break;
        case 0x969AE844: Serial.println(" 4"); digitalWrite (5, HIGH); lcd.print("-4-"); break;
        case 0x4AAFAC67: Serial.println(" 5");  digitalWrite (6, HIGH); lcd.print("-5-"); break;
        case 0x9C2A936C: Serial.println(" 6");  digitalWrite (7, HIGH); lcd.print("-6-"); break;
        case 0x833ED333: Serial.println(" 7"); lcd.print("-7-"); break;
        case 0x55F2B93: Serial.println(" 8"); lcd.print("-8-");  break;
        case 0xDE78B0D0: Serial.println(" 9");  lcd.print("-9-"); break;
        case 0xF32F72D7: Serial.println(" 0");  lcd.print("-0- "); break;
        case 0xBDE97C12: Serial.println("DASH");         lcd.print("-DASH-");             break;
        case 0x3F23F43: Serial.println("-ENTER-");          lcd.print("-ENTER-");            break;
        case 0xFFFFFFFF: Serial.println(" REPEAT");    lcd.print("-REPEAT-");           break;
        //COLOR BUTTONS ON THE DIRECT TV REMOTE
        case 0xC332FABB: Serial.println(" RED ");         lcd.print("-RED-");             break;
        case 0x8C0B38A3: Serial.println(" GREEN ");         lcd.print("-GREEN-");             break;
        case 0x2591C110: Serial.println(" YELLOW ");         lcd.print("-YELLOW-");             break;
        case 0x506AE98B: Serial.println(" BLUE ");         lcd.print("-BLUE-");             break;

        default:
          Serial.println(" other button   "); lcd.print("     WHOOPS !!! ");

      }// End Case
      delay(500); // Do not get immediate repeat
      //END translateIR
      irrecv.resume(); // receive the next value
    }



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
  /*
    //********************** This would be equivalent to the setup area in a regular sketch *************************

    lcd.clear();
    lcd.setCursor(0, 0);
    //      --1234567890123456-- //Lcd numbers for place holders

    lcd.setCursor(0, 1);
    //      --1234567890123456-- //Lcd numbers for place holders


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
    }//While bracket  */
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuEight Function Block ---
void menuEight() { //function bracket
  /*
    //********************** This would be equivalent to the setup area in a regular sketch *************************

    lcd.clear();
    lcd.setCursor(0, 0);
    //      --1234567890123456-- //Lcd numbers for place holders

    lcd.setCursor(0, 1);
    //      --1234567890123456-- //Lcd numbers for place holders


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
    }//While bracket  */
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuNine Function Block ---
void menuNine() { //function bracket
  /*
    //********************** This would be equivalent to the setup area in a regular sketch *************************

    lcd.clear();
    lcd.setCursor(0, 0);
    //      --1234567890123456-- //Lcd numbers for place holders

    lcd.setCursor(0, 1);
    //      --1234567890123456-- //Lcd numbers for place holders


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
    }//While bracket  */
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuTen Function Block ---
void menuTen() { //function bracket
  /*
    //********************** This would be equivalent to the setup area in a regular sketch *************************

    lcd.clear();
    lcd.setCursor(0, 0);
    //      --1234567890123456-- //Lcd numbers for place holders

    lcd.setCursor(0, 1);
    //      --1234567890123456-- //Lcd numbers for place holders


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
    }//While bracket  */
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     --- menuEleven Function Block ---
void menuEleven() { //function bracket
  /*
    //********************** This would be equivalent to the setup area in a regular sketch *************************

    lcd.clear();
    lcd.setCursor(0, 0);
    //      --1234567890123456-- //Lcd numbers for place holders
    lcd.print("Program Name...");
    lcd.setCursor(0, 1);
    //      --1234567890123456-- //Lcd numbers for place holders


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
    }//While bracket  */
}//last function bracket
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//https://programmingelectronics.com/tutorial-24-multi-dimensional-arrays-aka-matrix-old-version/

//https://learn.adafruit.com/multi-tasking-the-arduino-part-1/a-clean-sweep

//https://learn.adafruit.com/multi-tasking-the-arduino-part-2/what-is-an-interrupt

//http://paulmurraycbr.github.io/ArduinoTheOOWay.html

//http://playground.arduino.cc/Code/Library

//https://www.arduino.cc/en/Hacking/LibraryTutorial   ... Good starter OOP!!!

//
