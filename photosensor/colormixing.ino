const int greenLEDPin = 9;
const int blueLEDPin = 10;
const int redLEDPin = 11;

const int redSensorPin = A0;
const int greenSensorPin = A1;
const int blueSensorPin = A2;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

void initLEDS()
{
    pinMode(greenLEDPin, OUTPUT);
    pinMode(redLEDPin, OUTPUT);
    pinMode(blueLEDPin, OUTPUT);
}
void initSerialPort()
{
    Serial.begin(9600);
}
void setup()
{
    initSerialPort();
    initLEDS();
}

void loop()
{
    //  Serial.print("raw sensor values");
    //  Serial.print("red:");
    //  Serial.print(redSensorValue);
    //  Serial.print("\t green");
    //  Serial.print(greenSensorValue);
    //  Serial.print("\t blue: ");
    //  Serial.println(blueSensorValue);
    //  Serial.println("-------------------");

    redValue = analogRead(redSensorPin) / 4;
    delay(5);
    greenValue = analogRead(greenSensorPin) / 4;
    delay(5);
    blueValue = analogRead(blueSensorPin) / 4;

    analogWrite(redLEDPin, redValue);
    analogWrite(greenLEDPin, greenValue);
    analogWrite(blueLEDPin, blueValue);
}