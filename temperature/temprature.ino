const int sensorPin = A0;
const float baselineTemperature = 23.0;

void initDigitalOutputs()
{
    for (int pinNr = 2; pinNr <= 4; pinNr++)
    {
        pinMode(pinNr, OUTPUT);
        digitalWrite(pinNr, LOW);
    }
}

void initSerialPort()
{
    Serial.begin(9600);
}

void lightLEDS(boolean first, boolean second, boolean third)
{
    digitalWrite(2, first);
    digitalWrite(3, second);
    digitalWrite(4, third);
}

//TODO WIP still in though-process
boolean temperatureIsDegreesBelowBaseline(float temperature, int degrees)
{
    return temperature < baselineTemperature + degrees;
}

int readHeatSensorIntValue()
{
    return analogRead(sensorPin);
}

float convertSensorValueToVoltage(int sensorValue)
{
    return (sensorValue / 1024.0) * 5.0;
}

float convertVoltageToTemperature(float voltage)
{
    return (voltage - .5) * 100;
}

float readHeatSensorAsVoltage()
{
    return convertSensorValueToVoltage(readHeatSensorIntValue());
}

float readHeatSensorAsCelsius()
{
    return convertVoltageToTemperature(readHeatSensorAsVoltage());
}

void writeTemperatureLevel(float temperature)
{
    //TODO WIP continue here whenever i get time
    if (temperatureIsDegreesBelowBaseline(temperature, 2))
    {
        lightLEDS(LOW, LOW, LOW);
    }
    else if (temperature >= baselineTemperature + 2 && temperature < baselineTemperature + 4)
    {
        lightLEDS(HIGH, LOW, LOW);
    }
    else if (temperature >= baselineTemperature + 4 && temperature < baselineTemperature + 6)
    {
        lightLEDS(HIGH, HIGH, LOW);
    }
    else if (temperature >= baselineTemperature + 6)
    {
        lightLEDS(HIGH, HIGH, HIGH);
    }
}

void setup()
{
    initDigitalOutputs();
    //Use serial port to communicate data from analog port to
    // screen using monitor in IDE.
    initSerialPort();
}

void loop()
{
    // Serial.println(temperature);
    writeTemperatureLevel(readHeatSensorAsCelsius());
    delay(1);
}
