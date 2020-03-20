#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H

#include "Arduino.h"

class PressureSensor
{
  private:
    const float UPPER_VOLTS =  4.5; //UPPER READING (VOLTS)
    const float LOWER_VOLTS =  0.5; //LOWER READING (VOLTS)

    const float UPPER_PSI =  150;   //UPPER READING (PSI)
    const float LOWER_PSI =  0;     //LOWER READING (PSI)


    int m_pin;

    float scale(float input) {
      return map(input, LOWER_VOLTS, UPPER_VOLTS, LOWER_PSI, UPPER_PSI);
    }
    
  public:
    PressureSensor(int pin) {
      m_pin = pin;
    }

    float getPSI() {
      return scale( analogRead(m_pin) );
    }


};

#endif
