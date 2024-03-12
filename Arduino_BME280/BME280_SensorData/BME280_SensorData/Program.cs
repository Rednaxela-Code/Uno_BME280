using BME280_SensorData.Models;
using BME280_SensorData.Settings;
using Newtonsoft.Json;
using System.IO.Ports;

SerialPortSettings serialPortSettings = new();

var serialPort = new SerialPort(
    serialPortSettings.PortName,
    serialPortSettings.BaudRate,
    serialPortSettings.Parity,
    serialPortSettings.DataBits,
    serialPortSettings.StopBits);

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