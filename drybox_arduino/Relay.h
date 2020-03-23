#ifndef RELAY_H
#define RELAY_H

namespace RelayState
{
enum state {
  ON,
  OFF
};
}

class Relay
{
  private:
    int m_pin;
    bool m_isRunning;

    int m_cycleCount;

  public:
    Relay(int pin) {
      m_pin = pin;
      m_isRunning = true;

      m_cycleCount = 0;
    };

    void init() {
      pinMode(m_pin, OUTPUT);
      set(false);
    };

    bool getState() {
      return m_isRunning;
    };

    String getStateStr() {
      if (m_isRunning) {
        return "ON";
      } else {
        return "OFF";
      }
    }

    void toggle() {
      set(!m_isRunning);
    }

    void set(RelayState::state s) {
      if (s == RelayState::ON) {
        set(true);
      } else {
        set(false);
      }
    }

    void set(boolean state) {
      if (state != m_isRunning) {
        m_isRunning = state;
        m_isRunning ? setOn() : setOff();
      }
    }

    void setOn() {
      digitalWrite(m_pin, HIGH);
      m_cycleCount++;
    }

    void setOff() {
      digitalWrite(m_pin, LOW);
    }

    int getCycleCount() {
      return m_cycleCount;
    }

    void resetCycleCount() {
      m_cycleCount = 0;
    }

};

#endif
