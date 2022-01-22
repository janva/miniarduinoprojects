const int switchPin = 8;
unsigned long previousTime = 0;
int switchState = 0;
int previousSwitchState = 0;
int led = 2;
long intervall = 2000;
uint8_t blinkState = HIGH;

void setup()
{
    for (int x = 2; x < 8; x++)
    {
        pinMode(x, OUTPUT);
    }
    pinMode(switchPin, INPUT);
}

bool timeIsUp()
{
    return led > 7;
}

void signalTimeIsUp()
{
    long currentTime = millis();
    if (currentTime - previousTime > 1000)
    {
        previousTime = currentTime;
        blinkState = !blinkState;
        for (int x = 2; x < 8; ++x)
        {

            digitalWrite(x, blinkState);
        }
    }
}

bool switchHasTriggered()
{
    return digitalRead(switchPin) != previousSwitchState;
}

void restartHourGlass()
{
    for (int x = 2; x < 8; ++x)
    {
        digitalWrite(x, LOW);
    }
    led = 2;
    previousSwitchState = digitalRead(switchPin);
}

void loop()
{
    long currentTime = millis();
    if (currentTime - previousTime > intervall)
    {
        digitalWrite(led, HIGH);
        ++led;
        previousTime = currentTime;
    }

    if (timeIsUp())
    {
        signalTimeIsUp();
    }

    if (switchHasTriggered())
    {
        restartHourGlass();
    }
}