#ifndef HTSENSOR_H
#define HTSENSOR_H

#include "Arduino.h"
#include "Seeed_SHT35.h"


class HTSensor
{

  private:
    SHT35 *sensor;

    int m_pin;
    float m_temp, m_hum;

  public:
    HTSensor(int pin) {
      m_pin = pin;

      sensor = new SHT35(m_pin);
    }

    float getH() {
      return m_hum;
    }

    float getT() {
      return m_temp;
    }

    void update() {
      if (NO_ERROR != sensor->read_meas_data_single_shot(HIGH_REP_WITH_STRCH, &m_temp, &m_hum))
      {
        Serial.println("HT SENSOR READ FAILED!");
      }
    }




};

#endif
