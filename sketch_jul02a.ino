// Uses tower light: https://www.adafruit.com/product/2993
// Wire as such: https://learn.adafruit.com/rgb-led-strips/usage
// Add a start button to pin 13

// NOTE: These are all set to PWM pins.  Not a requirement
//const int BUZZER = 11;
const int GREEN = 9;
const int YELLOW = 5;
const int RED = 3;
//const int START_BTN = 13;

int start_race = false;
int countdown_done = true;
int btn_state = 0;

// mic
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup() {
  Serial.begin(9600);
  
  // pinMode(BUZZER, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  // pinMode(START_BTN, INPUT);
  
  testrun();
  //digitalWrite(RED, HIGH);
}

// 1 sec test of each light and buzzer
void testrun() {
  Serial.println("test run");
  digitalWrite(RED, HIGH);
  delay(1000);
  digitalWrite(RED, LOW);
  //digitalWrite(YELLOW, HIGH);
  //delay(1000);
  //digitalWrite(YELLOW, LOW);
  //digitalWrite(GREEN, HIGH);
  //delay(1000);
  //digitalWrite(GREEN, LOW);
  //digitalWrite(GREEN, HIGH);
  
  Serial.println("test run done");
  
  // digitalWrite(BUZZER, HIGH);
  // delay(1000);
  // digitalWrite(BUZZER, LOW);
}

// Does the countdown
void go() {
  if (!countdown_done) {
    return;
  }
  countdown_done = false;
  start_race = true;
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  // digitalWrite(BUZZER, LOW);
  delay(300);
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, HIGH);
  delay(1000);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, HIGH);
  // digitalWrite(BUZZER, HIGH);
  // delay(1000);
  // digitalWrite(BUZZER, LOW);
  countdown_done = true;  
}

// Race waiting (red light only)
void stop_race() {
  start_race = false;
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  //digitalWrite(BUZZER, LOW);
  digitalWrite(RED, HIGH);
  delay(2000); // 2 second delay (for debounce)
}

void loop() {
  // btn_state = digitalRead(START_BTN);
  // if(btn_state == HIGH) {  // Protoshield pulled high by default
  /*
   if (start_race) {
    stop_race();
   } else {
    go(); 
   } */
  // }
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
  
}
