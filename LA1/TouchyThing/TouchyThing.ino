const int CAPACITIVE_TOUCH_INPUT_PIN = T9; // GPIO pin 32

const int Yellow_LED_OUTPUT_PIN = 21;
const int Red_LED_OUTPUT_PIN = 17;
const int Green_LED_OUTPUT_PIN = 16;

const int RED_TOUCH_THRESHOLD = 20; // turn on Red light if touchRead value < this threshold
const int YELLOW_TOUCH_THRESHOLD = 35; // turn on Yellow light if touchRead value < this threshold

void setup() {
  // initialise the serial line
  Serial.begin(115200); 
  
  // set up GPIO pin for external LEDs
  pinMode(Yellow_LED_OUTPUT_PIN, OUTPUT);
  pinMode(Red_LED_OUTPUT_PIN, OUTPUT);
  pinMode(Green_LED_OUTPUT_PIN, OUTPUT);
}

void loop() {
  // set up touch pin valve
  int touchVal = touchRead(CAPACITIVE_TOUCH_INPUT_PIN);

  // set up all the leds
  boolean Yellow_ledOn = false;
  boolean Red_ledOn = false;
  boolean Green_ledOn = false;

  if(touchVal < RED_TOUCH_THRESHOLD) { // if touch valve is lower than red touch capacitance, turn on the red light 
    Red_ledOn = true;
  }
  else if(touchVal < YELLOW_TOUCH_THRESHOLD) { // if touch valve is lower than yellow touch capacitance, turn on the yellow light 
    Yellow_ledOn = true;
  }
  else {
    Green_ledOn = true; // By default the green light is on
  }
  digitalWrite(Red_LED_OUTPUT_PIN, Red_ledOn);
  digitalWrite(Yellow_LED_OUTPUT_PIN, Yellow_ledOn);
  digitalWrite(Green_LED_OUTPUT_PIN, Green_ledOn);
  delay(200);
  
  // Touch pin T9 output serial plotter
  Serial.printf("%d\n", touchRead(CAPACITIVE_TOUCH_INPUT_PIN));
}
