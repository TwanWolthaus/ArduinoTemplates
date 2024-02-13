# RotaryButton
C++ template for a rotary encoder to use in the Arduino IDE. The class is called RotaryButton and implements a RotaryEncoder and a Button. AttachInterupt() functions are used to update the state of RotaryButton and can be read with getPosition() and isPressed(). More info is available in the comments.

The Button is not very reliable, the RotaryEncoder is super reliable.

Having trouble understanding update() of RotaryEncoder? This table shows what states it goes through during a rotation:

rotating cw:
         start              end
stateSum   |  2  1  0  1  2  |  
direction  |  0  1  0 -1  0  |  

rotating ccw:
         start              end
stateSum   |  2  1  0  1  2  |
direction  |  0 -1  0  1  0  |
