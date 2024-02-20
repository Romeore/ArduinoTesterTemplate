using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Text;
using System.Threading;

namespace ArduinoTesterTemplate
{
    public enum ArduinoCommand : byte
    {
        EXAMPLECOMMAND,
        EXAMPLEPINREAD,
        EXAMPLEWITHPARAMS
    }

    public class ArduinoHandler 
    {

        private const char COMMAND_TERMINATOR = '$';
        private Dictionary<ArduinoCommand, string> _arduinoCommands;

        public SerialPort SerialPort { get; private set; }

        public ArduinoHandler(string portName)
        {
            InitSerialPort(portName);
            InitCommandDictionary();
        }

        private void InitSerialPort(string portName)
        {
            SerialPort = new SerialPort(portName, 9600, Parity.None, 8, StopBits.One);
            SerialPort.WriteTimeout = 2000;
            SerialPort.ReadTimeout = 2000;
        }

        public void Open()
        {
            if (SerialPort.IsOpen) return;

            SerialPort.Open();
        }

        public void Close()
        {
            if (!SerialPort.IsOpen) return;

            SerialPort.Close();
        }

        private void InitCommandDictionary()
        {
            _arduinoCommands = new Dictionary<ArduinoCommand, string>();
            _arduinoCommands.Add(ArduinoCommand.EXAMPLECOMMAND, "EXAMPLECOMMAND");
            _arduinoCommands.Add(ArduinoCommand.EXAMPLEPINREAD, "EXAMPLEPINREAD");
            _arduinoCommands.Add(ArduinoCommand.EXAMPLEWITHPARAMS, "EXAMPLEWITHPARAMS");
        }

        public void SendCommand(ArduinoCommand command, params string[] parameters)
        {
            if (!SerialPort.IsOpen) return;

            StringBuilder commandBuilder = new StringBuilder();

            commandBuilder.Append(_arduinoCommands[command]);

            foreach(var parameter in parameters)
            {
                commandBuilder.Append(",");
                commandBuilder.Append(parameter);
            }

            commandBuilder.Append(COMMAND_TERMINATOR);

            SerialPort.Write(commandBuilder.ToString());
        }

        public string ReadMessage()
        {
            string response = "";

            try
            {
                response = SerialPort.ReadExisting();
            }
            catch (Exception)
            {
                // Handle it as you wish
            }

            return response;
        }

        public string Query(ArduinoCommand command, params string[] parameters)
        {
            SendCommand(command, parameters);
            Thread.Sleep(1000);
            return ReadMessage();
        }
    }
}
