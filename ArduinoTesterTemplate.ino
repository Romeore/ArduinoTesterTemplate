// Copyright (c) 2024 Alon Vaisgur
//
// Arduino Tester Template

#include <CommandHandler.h>

#define NUMBER 3 // This is an example number
#define PIN_EXAMPLE NUMBER

CommandHandler cmdHdl(",", '$');

void sendSuccess() {
  Serial.println("true");
}

void sendFail() {
  Serial.println("false");
}

void initPins() {
  /******** Output **************/
  pinMode(PIN_EXAMPLE , OUTPUT); // Output example
  digitalWrite(PIN_EXAMPLE, LOW); // SETS THE OUTPUT to 0

  /******** Input **************/
  pinMode(PIN_EXAMPLE , INPUT ); // INPUT_PULLUP is also an option, sets the pin to output.
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // setting up the serial port to 9600 baud

  // Setup callbacks for SerialCommand commands

  // You have two options, You can either request params, or just go for the basics. (When you ask for params, You can also get it parameterless)
  cmdHdl.addCommand("EXAMPLECOMMAND", example); // Executes when someone sends me "EXAMPLECOMMAND$"
  cmdHdl.addCommand("EXAMPLEPINREAD", examplePinRead); // Executes when someone sends me "EXAMPLEPINREAD, params$" (params <1 or 0>)
  cmdHdl.addCommand("EXAMPLEWITHPARAMS", exampleWithParams); // Executes when someone sends me "EXAMPLEPINREAD, params$"

  cmdHdl.setDefaultHandler(unrecognized); // Handler for command that isn't matched (sends fail)

  initPins();
}

// Usecase: Toggle a PIN
void toggleCommand() {
  digitalWrite(PIN_EXAMPLE, LOW);
  delay(2000);
  digitalWrite(PIN_EXAMPLE, HIGH);
  sendSuccess();
}

void loop() {
  cmdHdl.processSerial(Serial);
}

void example() {
  digitalWrite(PIN_EXAMPLE, LOW);
  sendSuccess();
}

// Usecase: Read a PIN value
void examplePinRead() {
  checkPin(PIN_EXAMPLE);
}

void exampleWithParams() {
  double exampleNumber;
  exampleNumber = cmdHdl.readDoubleArg(); // You need to do it for every argument

  // STRING EXAMPLE
  // char* exampleString
  // exampleString = cmdHdl.readStringArg();

  if(cmdHdl.argOk) {
    // DO STUFF WITH IT
  }
  else {
    // NO PARAMS LEFT (In this specific example, it also means parmeterless command
  }
}

void checkPin(int pin) {
  int expectedResult;

  expectedResult = cmdHdl.readIntArg();

  if (expectedResult == digitalRead(pin)) {
    sendSuccess();
  }
  else {
    sendFail();
  }
}


// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  sendFail();
}
