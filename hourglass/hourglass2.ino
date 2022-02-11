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

void setLed(int ledPin, uint8_t state)
{
    digitalWrite(ledPin, state);
}

void setAllLeds()
{
    for (int ledPin = 2; ledPin < 8; ++ledPin)
    {
        setLed(ledPin, blinkState);
    }
}
void turnOnLed(int ledPin)
{
    setLed(ledPin, HIGH);
}

void turnOffLed(int ledPin)
{
    setLed(ledPin, LOW);
}

void turnOffAll()
{
    for (int ledPin = 2; ledPin < 8; ++ledPin)
    {
        turnOffLed(ledPin);
    }
}
void turnOnAll()
{
    for (int ledPin = 2; ledPin < 8; ++ledPin)
    {
        turnOnLed(ledPin);
    }
}

void invertBlinkState()
{
    blinkState = !blinkState;
}

void blinkAllLeds()
{
    setPreviousTime();
    invertBlinkState();
    setAllLeds();
}

bool millisHasPassedSincePreviousStoredTime(long int ms)
{
    return millis() - previousTime > ms;
}

bool timeIsUp()
{
    return led > 7;
}
// states hmm make state machine maybe instead
bool switchHasTriggered()
{
    return digitalRead(switchPin) != previousSwitchState;
}

void resetLedIterator()
{
    led = 2;
}

void setPreviousSwitchState()
{
    previousSwitchState = digitalRead(switchPin);
}

void setPreviousTime()
{
    previousTime = millis();
}

void updateHourglass()
{
    if (millisHasPassedSincePreviousStoredTime(intervall))
    {
        turnOnLed(led);
        ++led;
        setPreviousTime();
    }
}

void signalTimeIsUp()
{
    if (millisHasPassedSincePreviousStoredTime(1000))
    {
        blinkAllLeds();
    }
}

void restartHourGlass()
{
    turnOffAll();
    resetLedIterator();
    setPreviousSwitchState();
}

void loop()
{
    updateHourglass();

    if (timeIsUp())
    {
        signalTimeIsUp();
    }

    if (switchHasTriggered())
    {
        restartHourGlass();
    }
}