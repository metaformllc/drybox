/*
   drybox_arduino.ino

   Moisure control regulation software

   Paul Sites
   Metaform LLC © 2020

*/

#include "PressureSensor.h"
#include "HTSensor.h"
#include "Relay.h"

#include "Enums.h"


#define PRESSURE_PIN  A1
#define SHT35_PIN     A5
#define STORAGE_PIN  2
#define COMPRESSOR_PIN  3
#define DRYER_PIN  4

/* ********** COMPRESSOR LIMITS ********** */
#define MIN_PRESSURE 50
#define MAX_PRESSURE 70

/* ********** DRYER CYCLE LIMITS ********** */
#define START_DRY_PRESSURE 60
#define STOP_DRY_PRESSURE  30

/* ********** HUMIDITY LIMITS ********** */
#define STOP_HUMIDITY  1
#define START_HUMIDITY 2

/* ********** DRYER CYCLE LIMITS ********** */
#define CYCLE_SWITCH_LIMIT 2


HTSensor htSensor(SHT35_PIN);
PressureSensor pressure(PRESSURE_PIN);

Relay compressor(COMPRESSOR_PIN);
Relay storageValve(STORAGE_PIN);
Relay dryerValve(DRYER_PIN);


State::state currentState;
Compressor::state compState;

void setup()
{
  Serial.begin(1000000);
  Serial.println("********** METAFORM DRYBOX: INIT **********");
  currentState = State::STEADY;

  htSensor.init();
  compressor.init();
  storageValve.init();
  dryerValve.init();

  Serial.println("********** METAFORM DRYBOX: INIT COMPLETE **********");
  Serial.println();
  Serial.println();

  Serial.println("Humidity (%), Temperature (C), PSI, Compressor, Storage, Dryer, State, Duration");
}


void loop()
{
  htSensor.update();
  float currentPSI = pressure.getPSI();

  /*
     Compressor Control
      Make sure we keep the tanks charged.
  */
  if (currentPSI < MIN_PRESSURE) {
    compressor.set(RelayState::ON);
  } else if (currentPSI >= MAX_PRESSURE) {
    compressor.set(RelayState::OFF);
  }

  /*
     Dryer Control
      Switch which dryer tube we use.
  */
  if (storageValve.getCycleCount() >= CYCLE_SWITCH_LIMIT ) {
    dryerValve.toggle();
    storageValve.resetCycleCount();
  }

  /*
     Moisture Control
      Start drying cycles as needed.
  */
  switch (currentState) {
    case State::STEADY:
      if (htSensor.getH() > START_HUMIDITY) {
        currentState = State::DRYING;
      } else if (!compressor.getState()) {
        //delay(5000);
      }
      break;
    case State::DRYING:
      if (currentPSI >= START_DRY_PRESSURE) {
        storageValve.set(RelayState::ON);
      } else if (currentPSI <= STOP_DRY_PRESSURE) {
        storageValve.set(RelayState::OFF);
      }

      if (htSensor.getH() < STOP_HUMIDITY) {
        currentState = State::STEADY;
      }
      break;
    default:
      break;
  }

  int duration_s = millis() / 1000;
  Serial.println(String(htSensor.getH()) + ", " + String(htSensor.getT()) + ", " + currentPSI + ", " + compressor.getStateStr() + ", " + storageValve.getStateStr() + ", " + dryerValve.getStateStr() + ", " + State::toString(currentState) + ", " + pressure.getRaw() + ", " + String(duration_s) );

  delay(250);
}
