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
    
    void setFlag(bool newFlag) { // Use setFlag() to determine if you have read the button already.
      flag = newFlag;}

    bool getFlag() {
      return flag;}

    bool isPressed() {
      return pressed;}

    void update() {
      if ((millis() - updateStamp) > 20) { // Check for debounce time.
        
        updateStamp = millis();

        if (hasPressure() != pressed) {
          pressed = !pressed;}
      }
    }
};

class RotaryEncoder  {
  private:
    int position = 0;
    int trendStart = 0; // Records the direction where the rotor starts moving to.
    int trendEnd = 0;   // Records the direction where the rotor last moved to.
    bool stable = true; // Indicates if the rotor is in a stable position.

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

    void update() { // This function is complicated, but is very reliable and doesn't need to check debounce time.

      bool CLK = digitalRead(CLK_PIN);
      bool DT = digitalRead(DT_PIN);

      int direction = CLK ^ DT ? (CLK ? 1 : -1) : 0; // The difference between CLK and DT. 1 is cw, -1 is ccw.
      int stateSum = CLK + DT;                       // The sum of CLK and DT.

      if (stateSum == 2) {                           // If CLK == DT == 1, the rotor is at a stable point.
        stable = true;
        if (trendStart != trendEnd) {                // If the directions are different, the rotor has succesfully turned.
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

class RotaryButton: public Button, public RotaryEncoder { // Implements a RotaryEncoder and a Button.
  public:
    RotaryButton(byte CLK, byte DT, byte SW): Button(SW), RotaryEncoder(CLK, DT) {}

    void update() {
      RotaryEncoder::update();
      Button::update();
    }
};

  //////////////////////////////////////////////////////////////////
 // Below here is a template to implement the interupt functions //
//////////////////////////////////////////////////////////////////

void callUpdates() {
  ROTARY_BUTTON_INSTANCE.update(); // This extra function is needed because attachInterrupt() cannot directly call methods.
}

void setup() {
  attachInterrupt(digitalPinToInterrupt(PIN_CLK), callUpdates, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_DT), callUpdates, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SW), callUpdates, CHANGE);
}
