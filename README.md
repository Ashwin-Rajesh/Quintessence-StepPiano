# Step-Piano
  Arduino project that playes notes when a user steps on a step in a staircase. The motion is detected using an LDR and laser. When the laser beam is  cut, the LDR's resistance increases. The LDR in a potential divider configuration is connected to the inout of a comparator that outputs to the arduino.
  
  It also plays a pre-programmed sequence of notes when no motion has been detected for a pre-programmed amount of time.
