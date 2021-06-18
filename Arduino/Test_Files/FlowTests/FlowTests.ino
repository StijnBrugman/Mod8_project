#define flowsensor 2 // Sensor Input

volatile float flow_frequency; // Measures flow sensor pulsesunsigned 

float l_second; // Calculated litres/hour
unsigned long currentTime;
unsigned long cloopTime;

unsigned long volume = 0;

void flow () // Interrupt function

{
   flow_frequency++;
}

   void setup()
 {
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   Serial.begin(9600);
   attachInterrupt(0, flow, RISING); // Setup Interrupt
   sei(); // Enable interrupts
   currentTime = millis();
   cloopTime = currentTime;
}

   void loop ()
{
   currentTime = millis();
   // Every second, calculate and print millilitres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      unsigned long dt = currentTime - cloopTime;
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_second = 1000.0*(flow_frequency / 4380.0); // (Pulse frequency x 60 min) / 7.5Q = flowrate in mL/second
      volume += 1.34 * dt * l_second / 1000.0; //ml
      flow_frequency = 0; // Reset Counter
//      Serial.print(l_second); // Print millilitres/second
//      Serial.println(" mL/second");
      Serial.println(volume);
   }
}
