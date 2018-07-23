// Uses tower light: https://www.adafruit.com/product/2993
// Wire as such: https://learn.adafruit.com/rgb-led-strips/usage
// Add a start button to pin 13

// NOTE: These are all set to PWM pins.  Not a requirement
//const int BUZZER = 11;
const int GREEN = 9;
const int YELLOW = 6;
const int RED = 3;
//const int START_BTN = 13;

int start_race = false;
int countdown_done = true;
int btn_state = 0;

// mic
const int sampleWindow = 500; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

float green = 0.3;
float yellow = 0.9;
float red = 1.5;

void setup() {
  Serial.begin(9600);
  
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  
  startup();
}

void startup(){
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  delay(1000);
  digitalWrite(RED, HIGH);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, HIGH);
  delay(1000);
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  delay(1000);
  digitalWrite(RED, HIGH);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, HIGH);
  delay(1000);
  
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  delay(100);
  digitalWrite(RED, HIGH);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, HIGH);
  delay(100);
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  delay(100);
  digitalWrite(RED, HIGH);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, HIGH);
}


void loop() {
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 5.0) / 1024;  // convert to volts

   Serial.println(volts);
   
   if(volts < green){
     digitalWrite(GREEN, HIGH);
     digitalWrite(YELLOW, HIGH);
     digitalWrite(RED, HIGH);
   }else if(volts < yellow){
     digitalWrite(GREEN, LOW);
     digitalWrite(YELLOW, HIGH);
     digitalWrite(RED, HIGH);
   }else if(volts < red){
     digitalWrite(GREEN, HIGH);
     digitalWrite(YELLOW, LOW);
     digitalWrite(RED, HIGH);
    }else{
     digitalWrite(GREEN, HIGH);
     digitalWrite(YELLOW, HIGH);
     digitalWrite(RED, LOW);
   }
}
