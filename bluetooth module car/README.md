# Bluetooth Module Car

A simple sketch to control a robot car using an HC‑05 Bluetooth module. Send single-character commands from a phone or computer to move the car.

## Wiring
- HC‑05 RX → Arduino pin 9 (BT_TX)
- HC‑05 TX → Arduino pin 8 (BT_RX)
- Motor driver inputs IN1–IN4 → pins 2–5

## Commands
- `F` – forward
- `B` – backward
- `L` – turn left
- `R` – turn right
- `S` – stop
