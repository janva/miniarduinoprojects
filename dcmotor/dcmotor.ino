const int switch_pin = 2;
const int motor_pin = 9;
int switch_state = 0;

void setup (){
    pinMode(motor_pin, OUTPUT);
    pinMode(switch_pin, INPUT);
}

void loop(){
    switch_state = digitalRead(switch_pin);
    if (switch_state == HIGH){
        digitalWrite(motor_pin, HIGH);
    }else{
        digitalWrite(motor_pin, LOW);
        
    }
}