#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

const int Y_LED = 13;
const int G_LED = 10;
const int R_LED = 8;
const int RESET_BTN = 5;
const int IR_PIN = 7;

enum State {
IDLE,
SEARCHING,
READY,
LOCKOUT
};

State currentState = IDLE;

void setup() {
pinMode(Y_LED, OUTPUT);
pinMode(G_LED, OUTPUT);
pinMode(R_LED, OUTPUT);
}

void loop() {
// IDLE
currentState = IDLE;
updateOutputs();
delay(1500);

// SEARCHING
currentState = SEARCHING;
updateOutputs();
delay(1500);

// READY
currentState = READY;
updateOutputs();
delay(1500);

// LOCKOUT
currentState = LOCKOUT;
updateOutputs();
delay(1500);
}

void updateOutputs() {
switch (currentState) {
case IDLE:
digitalWrite(Y_LED, LOW);
digitalWrite(G_LED, LOW);
digitalWrite(R_LED, LOW);
break;

case SEARCHING:
digitalWrite(Y_LED, HIGH);
digitalWrite(G_LED, LOW);
digitalWrite(R_LED, LOW);
break;

case READY:
digitalWrite(Y_LED, LOW);
digitalWrite(G_LED, HIGH);
digitalWrite(R_LED, LOW);
break;

case LOCKOUT:
digitalWrite(Y_LED, LOW);
digitalWrite(G_LED, LOW);
digitalWrite(R_LED, HIGH);
break;
}
}
