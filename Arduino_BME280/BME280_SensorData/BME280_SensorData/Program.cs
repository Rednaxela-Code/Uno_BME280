using BME280_SensorData.Models;
using Newtonsoft.Json;
using System.IO.Ports;

string portName = "COM3";
int baudRate = 9600;
var parity = Parity.None;
int dataBits = 8;
var stopBits = StopBits.One;

var serialPort = new SerialPort(portName, baudRate, parity, dataBits, stopBits);

try
{
    serialPort.Open();

    while (serialPort.IsOpen == true)
    {
        var jsonData = serialPort.ReadLine();

        WeatherData weatherData = JsonConvert.DeserializeObject<WeatherData>(jsonData);

        Console.WriteLine($"Temperature: {weatherData.Temperature}");
        Console.WriteLine($"Humidity: {weatherData.Humidity}");
        Console.WriteLine($"Pressure: {weatherData.Pressure}");
        Console.WriteLine($"Altitude: {weatherData.Altitude}");
        Console.WriteLine();

    }
}
catch (Exception ex)
{
    Console.WriteLine("Error: " + ex.Message);
}
finally
{
    serialPort.Close();
}