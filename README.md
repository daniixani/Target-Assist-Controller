# Target-Assist-Controller
The system is intended to monitor the operating condition of the device and transition between different control states based on user commands and system conditions. Its purpose is to indicate whether the device is idle, searching for a target alignment, ready for use, or placed in a lockout due to a fault. 
#Project Overview
This project explores how a controller can manage target-alignment behavior and fault-safe system states for a handheld air-vortex demonstrator. The goal is to move beyond simple detection and create a controller that interprets inputs, determines system state, and gives user feedback through LEDs and later a buzzer and hardware controls.

The project was first implemented and verified in **Verilog** through simulation, then translated into an **Arduino-based hardware prototype** for manual input testing on a breadboard.

## Current Features

- Four-state controller:
- **Idle**
- **Searching**
- **Ready**
- **Lockout**
- Verilog FSM implementation
- Behavioral simulation and waveform validation in Vivado
- Arduino prototype for manual state testing
- LED state indication:
- **Yellow** = Searching
- **Green** = Ready
- **Red** = Lockout / Fault
- Reset behavior for clearing lockout after fault removal
- Early industrial design / controller attachment concept sketches

## State Logic

### Idle
System is unarmed and inactive.

### Searching
System is armed and actively searching for valid target/alignment conditions.

### Ready
System is armed, target is detected, and alignment condition is met.

### Lockout
System has detected a fault and remains inhibited until fault is cleared and reset is applied.

## Inputs

- **Arm (A)** – enables active operation
- **Target (T)** – indicates target detected
- **Align (L)** – indicates valid alignment / in-frame condition
- **Fault (F)** – forces lockout
- **Reset (R)** – clears lockout once fault is removed

## Outputs

- **Yellow LED** – Searching
- **Green LED** – Ready
- **Red LED** – Lockout / Fault
- **Future output:** buzzer for fault indication
- **Future output:** fire-enable / gated actuation signal

## Tools Used

- **Verilog**
- **Vivado**
- **Arduino**
- **Breadboard prototyping**
- **FSM design**
- **Manual hardware validation**
- **Concept sketching / enclosure ideation**

## Repository Structure

```text
verilog/
vort_fsm.v
vortex_fsm_tb.v

arduino/
v1_led_state_test.ino
v2_manual_input_fsm.ino

images/
waveform
searching_state
ready_state
lockout_state
controller_concept


