using System.IO.Ports;

namespace BME280_SensorData.Models
{
    public class SerialPortSettings
    {
        private readonly string _portName = "COM3";
        private readonly int _baudRate = 9600;
        private readonly Parity _parity = Parity.None;
        private readonly int _dataBits = 8;
        private readonly StopBits _stopBits = StopBits.One;

        public SerialPort InitSettings()
        {
            var serialPort = new SerialPort(_portName, _baudRate, _parity, _dataBits, _stopBits);
            return serialPort;
        }
    }
}
