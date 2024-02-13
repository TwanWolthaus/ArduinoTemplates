# ArduinoTemplates
C++ templates for a timer and a rotary encoder to use in the Arduino IDE. The class of the encoder is called RotaryButton and implements a RotaryEncoder and a Button. AttachInterupt() functions are used to update the state of RotaryButton and can be read with getPosition() and isPressed(). More info is available in the comments.

The Button is not very reliable, the RotaryEncoder is super reliable.

Having trouble understanding update() of RotaryEncoder? This table shows what states it goes through during a rotation (view in raw mode):

rotating cw:
         start              end
stateSum   |  2  1  0  1  2  |  
direction  |  0  1  0 -1  0  |  

rotating ccw:
         start              end
stateSum   |  2  1  0  1  2  |
direction  |  0 -1  0  1  0  |
