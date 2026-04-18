int const Y_PIN = 13;
int const G_PIN = 10;
int const R_PIN = 8;
int const RSET_BTN = 7;

const int ARM_PIN = 5; // manual jumper input for A
const int TARGET_PIN = 4; // manual jumper input for T
const int ALIGN_PIN = 3; // manual jumper input for L
const int FAULT_PIN = 2; // manual jumper input for F

enum State {
IDLE,
SEARCHING,
READY,
LOCKOUT
};

State currentState = IDLE;

void setup() {
pinMode(Y_PIN, OUTPUT);
pinMode(G_PIN, OUTPUT);
pinMode(R_PIN, OUTPUT);

// INPUT_PULLUP means:
// open wire = HIGH
// grounded wire/button = LOW
pinMode(RSET_BTN, INPUT_PULLUP);
pinMode(ARM_PIN, INPUT_PULLUP);
pinMode(TARGET_PIN, INPUT_PULLUP);
pinMode(ALIGN_PIN, INPUT_PULLUP);
pinMode(FAULT_PIN, INPUT_PULLUP);

Serial.begin(9600);
}

void loop() {
// Convert physical pin readings into FSM-style signals
// Grounded = signal is ON / true
bool A = (digitalRead(ARM_PIN) == LOW); // Arm
bool T = (digitalRead(TARGET_PIN) == LOW); // Target detected
bool L = (digitalRead(ALIGN_PIN) == LOW); // Aligned
bool F = (digitalRead(FAULT_PIN) == LOW); // Fault
bool R = (digitalRead(RSET_BTN) == LOW); // Reset

// FSM NEXT-STATE LOGIC
switch (currentState) {

case IDLE:
// if (F) next_state = LOCKOUT;
// else if (A) next_state = SEARCHING;
// else next_state = IDLE;
if (F) {
currentState = LOCKOUT;
} else if (A) {
currentState = SEARCHING;
}
break;

case SEARCHING:
// if (F) next_state = LOCKOUT;
// else if (!A) next_state = IDLE;
// else if (T && L) next_state = READY;
// else next_state = SEARCHING;
if (F) {
currentState = LOCKOUT;
} else if (!A) {
currentState = IDLE;
} else if (T && L) {
currentState = READY;
}
break;

case READY:
// Verilog equivalent:
// if (F) next_state = LOCKOUT;
// else if (!A) next_state = IDLE;
// else if (!T || !L) next_state = SEARCHING;
// else next_state = READY;
if (F) {
currentState = LOCKOUT;
} else if (!A) {
currentState = IDLE;
} else if (!T || !L) {
currentState = SEARCHING;
}
break;

case LOCKOUT:
// Verilog equivalent:
// if (R && !F) next_state = IDLE;
// else next_state = LOCKOUT;
if (R && !F) {
currentState = IDLE;
}
break;
}

// outputs depend only on current state
switch (currentState) {
case IDLE:
// IDLE -> all LEDs off
digitalWrite(Y_PIN, LOW);
digitalWrite(G_PIN, LOW);
digitalWrite(R_PIN, LOW);
break;

case SEARCHING:
// SEARCHING -> yellow on
digitalWrite(Y_PIN, HIGH);
digitalWrite(G_PIN, LOW);
digitalWrite(R_PIN, LOW);
break;

case READY:
// READY -> green on
digitalWrite(Y_PIN, LOW);
digitalWrite(G_PIN, HIGH);
digitalWrite(R_PIN, LOW);
break;

case LOCKOUT:
// LOCKOUT -> red on
digitalWrite(Y_PIN, LOW);
digitalWrite(G_PIN, LOW);
digitalWrite(R_PIN, HIGH);
break;
}

// Optional Serial Monitor debugging
Serial.print("A=");
Serial.print(A);
Serial.print(" T=");
Serial.print(T);
Serial.print(" L=");
Serial.print(L);
Serial.print(" F=");
Serial.print(F);
Serial.print(" R=");
Serial.print(R);
Serial.print(" | State=");

switch (currentState) {
case IDLE:
Serial.println("IDLE");
break;
case SEARCHING:
Serial.println("SEARCHING");
break;
case READY:
Serial.println("READY");
break;
case LOCKOUT:
Serial.println("LOCKOUT");
break;
}

delay(100);
}
