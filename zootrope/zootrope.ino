const int controlPin_1 = 2;
const int controlPin_2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchStatePin = 5;
const int potPin = A0;
int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;
int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;

void setup()
{
    pinMode(directionSwitchPin, INPUT);
    pinMode(onOffSwitchStatePin, INPUT);
    pinMode(controlPin_1, OUTPUT);
    pinMode(controlPin_2, OUTPUT);
    digitalWrite(enablePin, LOW);
}
void readOnOffSwitchState()
{
    onOffSwitchState = digitalRead(onOffSwitchStatePin);
}
void readDirectionSwitchState()
{
    directionSwitchState = digitalRead(directionSwitchPin);
}
void readMotorSpeed()
{
    motorSpeed = analogRead(potPin) / 4;
}

/// Motor on of functionallity/////////
void toggleMotorEnabledState()
{
    motorEnabled = !motorEnabled;
}

bool onOffSwitchStateHasChanged()
{
    return previousOnOffSwitchState != onOffSwitchState;
}
bool isMotorEnabled()
{
    return onOffSwitchState == HIGH;
}
void turnOnMotor()
{
    analogWrite(enablePin, motorSpeed);
}
void turnOffMotor()
{
    analogWrite(enablePin, 0);
}

void writeMotorOnOffState()
{
    if (motorEnabled == 1)
    {
        turnOnMotor();
    }
    else
    {
        turnOffMotor();
    }
}

void storePreveousOnOffState()
{
    previousOnOffSwitchState = onOffSwitchState;
}

void setMotorOnOffState()
{
    if (onOffSwitchStateHasChanged())
    {
        if (isMotorEnabled())
        {
            toggleMotorEnabledState();
        }
    }
}

/// motor direction code starts here ///////////
void writeMotorDirectionForward()
{
    digitalWrite(controlPin_1, HIGH);
    digitalWrite(controlPin_2, LOW);
}

void writeMotorDirectionBackward()
{
    digitalWrite(controlPin_2, HIGH);
    digitalWrite(controlPin_1, LOW);
}

void writeMotorDirection()
{
    if (motorDirection == 1)
    {
        writeMotorDirectionForward();
    }
    else
    {
        writeMotorDirectionBackward();
    }
}

void setMotorSpinDirection()
{
    if (previousDirectionSwitchState != directionSwitchState)
    {
        if (directionSwitchState == HIGH)
        {
            motorDirection = !motorDirection;
        }
    }
}

void storePreviousDirectionState()
{
    previousDirectionSwitchState = directionSwitchState;
}

void loop()
{
    readOnOffSwitchState();
    delay(1);
    readDirectionSwitchState();
    readMotorSpeed();

    setMotorOnOffState();

    setMotorSpinDirection();
    writeMotorDirection();

    writeMotorOnOffState();

    storePreveousOnOffState();
    storePreviousDirectionState();
}