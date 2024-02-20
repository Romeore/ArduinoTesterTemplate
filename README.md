
# Arduino Tester Template by Alon Vaisgur

## Introduction

The primary purpose of this Arduino project is to guide other developers on how to use Arduino for testers by manipulating the state of specific pins on the Arduino board that are connected to the hardware component. This README also includes instructions for setting up and using the `ArduinoHandler` C# class on the PC side to communicate with the Arduino.

## Requirements

- Arduino IDE (version 1.8.15)
- CommandHandler library
- Hardware component
- USB-B cable

### Optional

- .NET Framework or .NET Core
- C# development environment (e.g., Visual Studio)

## Installation

### Arduino IDE

1. Download and install the Arduino IDE version 1.8.15.
2. Open the Arduino IDE after installation.

### CommandHandler Library

1. Go to `Sketch` > `Include Library` > `Add ZIP Library...` in the Arduino IDE.
2. Search for and select the `CommandHandler` library.
3. Access it again via `Sketch` > `Include Library` and click on it.

## Software Setup

1. Connect your Arduino board to your computer using a USB cable.
2. Open the Arduino IDE.
3. Select your Arduino board type and port under `Tools` > `Board` and `Tools` > `Port`.
4. Open your project sketch file (.ino) in the Arduino IDE.
5. Compile the sketch by clicking on the `Verify` button (checkmark icon).
6. Once compiled successfully, upload the sketch to your Arduino board by clicking on the `Upload` button (right arrow icon).

## Command Protocol and Communication

### Command Structure

Commands sent to the Arduino have arguments separated by commas (`,`) and end with a dollar sign (`$`). This structure is essential for the Arduino to parse and execute the commands correctly.

### Adding New Commands

To add new commands, use the `addCommand` function of the `CommandHandler` library. This function takes the command name and a pointer to the function that executes the command.

Syntax:

```cpp
cmdHdl.addCommand("<CommandName>", <pointerToFunction>);
```

### Read arguments

To read command's arguments, Use the following example:

```cpp
void exampleWithParams() {
  double exampleNumber;
  exampleNumber = cmdHdl.readDoubleArg(); // You need to do it for every argument

  if(cmdHdl.argOk) {
    // Do stuff with it..
  }
  else {
    // No remaining parameters (In this specific example, it also means parmeterless command)
  }
}
```

### Notifying the PC of Success or Failure

After executing a command, use `sendSuccess()` to indicate success and `sendFail()` to indicate failure. These functions communicate the operation status back to the PC.

Example:

```cpp
void myCustomCommand() {
    // Command implementation
    // On success
    sendSuccess();
    // On failure
    sendFail();
}

void setup() {
    // Adding the custom command
    cmdHdl.addCommand("MyCommand", myCustomCommand);
    // ...other setup code...
}

void loop() {
    cmdHdl.processSerial(Serial);
}
```

## PC Side Setup and Communication with Arduino

### Setting Up the ArduinoHandler

1. **Include the Class**: Ensure the `ArduinoHandler.cs` file is part of your C# project.
2. **Instantiate ArduinoHandler**: Replace `"COM3"` with the COM port your Arduino is connected to.

  ```csharp
  ArduinoHandler arduino = new ArduinoHandler("COM3");
  ```

3. **Open Serial Connection**:

  ```csharp
  arduino.Open();
  ```

### Sending Commands to Arduino

- **Without Parameters**:

```csharp
arduino.SendCommand(ArduinoCommand.EXAMPLECOMMAND);
```

- **With Parameters**:

```csharp
arduino.SendCommand(ArduinoCommand.EXAMPLEWITHPARAMS, "parameter1", "parameter2");
```

### Reading Messages from Arduino

```csharp
string message = arduino.ReadMessage();
Console.WriteLine(message);
```

### Querying Arduino and Waiting for Response

```csharp
string response = arduino.Query(ArduinoCommand.EXAMPLEPINREAD, "parameter1");
Console.WriteLine(response);
```

### Closing the Serial Connection

```csharp
arduino.Close();
```

## Examples

### Toggle an LED

```csharp
arduino.Open();
arduino.SendCommand(ArduinoCommand.TOGGLELED);
arduino.Close();
```

### Read Sensor Value

```csharp
arduino.Open();
string sensorValue = arduino.Query(ArduinoCommand.READSENSORVALUE);
Console.WriteLine($"Sensor Value: {sensorValue}");
arduino.Close();
```

## Conclusion

The integration of the `ArduinoHandler` class into your C# projects to communicate with the Arduino creates abstraction using simple software commands.
