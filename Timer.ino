class Timer {
  private:
    unsigned long initStamp;
    unsigned long duration;

  public:
    Timer(int durationMS) {
      duration = durationMS;
      initStamp = millis();
    }

    void reset() {
      initStamp = millis();
    }

    void setDuration(newDuration) {
      duration = newDuration;
    }

    bool isActive() {
      if (millis() - initStamp >= duration) {
        return false;
      }
      return true;
    }
};