class Button {
  private:
    int buttonPIN;
    bool pressed = false;
    bool flag = false;

    unsigned long updateStamp = 0;

    bool hasPressure() {
      return !digitalRead(buttonPIN);
    }

  public:
    Button(int PINnumber) {
      buttonPIN = PINnumber;
      pinMode(buttonPIN, INPUT_PULLUP);
    }
    
    void setFlag(bool newFlag) {
      flag = newFlag;}

    bool getFlag() {
      return flag;}

    bool isPressed() {
      return pressed;}

    void update() {
      if ((millis() - updateStamp) > 20) {
        
        updateStamp = millis();

        if (hasPressure() != pressed) {
          pressed = !pressed;}
      }
    }
};

class RotaryEncoder  {
  private:
    int position = 0;
    int trendStart = 0;
    int trendEnd = 0;
    bool stable = true;

    byte CLK_PIN;
    byte DT_PIN;
    
  public:
    RotaryEncoder(byte CLK, byte DT) {
      CLK_PIN = CLK;
      DT_PIN = DT;

      pinMode(CLK_PIN, INPUT_PULLUP);
      pinMode(DT_PIN, INPUT_PULLUP);
    }

    int getPosition() {
      return position;}

    void reset() {
      position = 0;}

    void update() {

      bool CLK = digitalRead(CLK_PIN);
      bool DT = digitalRead(DT_PIN);

      int direction = CLK ^ DT ? (CLK ? 1 : -1) : 0;
      int stateSum = CLK + DT;

      if (stateSum == 2) {
        stable = true;
        if (trendStart != trendEnd) {
          position += trendStart * pow(trendEnd, 2);
        }
        trendStart = trendEnd = 0;
      }
      else if (stateSum == 1 && stable) {
        trendStart = direction;
        stable = false;
      }
      else if (stateSum == 1 && !stable) {
        trendEnd = direction;
      }
    }
};

class RotaryButton: public Button, public RotaryEncoder {
  public:
    RotaryButton(byte CLK, byte DT, byte SW): Button(SW), RotaryEncoder(CLK, DT) {}

    void update() {
      RotaryEncoder::update();
      Button::update();
    }
};

// void callUpdates() {
//   rotor.update();
// }

// void setup() {
//   attachInterrupt(digitalPinToInterrupt(PIN_CLK), callUpdates, CHANGE);
//   attachInterrupt(digitalPinToInterrupt(PIN_DT), callUpdates, CHANGE);
//   attachInterrupt(digitalPinToInterrupt(PIN_SW), callUpdates, CHANGE);
// }