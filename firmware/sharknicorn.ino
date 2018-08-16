/*
* Hello! Copy paste this into a new app in buid.particle.io
* and follow the README to setup the server code
*
* To test calling your particle manually, copy paste the following in the terminal:
* (exclude the backticks ```)
```
curl https://api.particle.io/v1/devices/DEVICE_ID/state-change \
             -d access_token=ACCESS_TOKEN \
             -d "args=test"
```
*/

// You're probably going to have to delete this include line after copy-pasta'ing
#include <neopixel.h>

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_COUNT 8
#define PIXEL_PIN D5
#define PIXEL_TYPE WS2812B //for rgb stick

// some color macros (values are R,G and B)
#define PEACH 200,50,5
#define CYAN 10,150,70
#define PURPLE 180,3,180
#define BLUE 5,5,190
#define WHITE 150,150,150
#define GREEN 10,180,10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int waitTime = 25;
int i;
int brightness = 50;

String mode = "completed"; //default mode

// function declarations of all animations
void spinMode(String);
int stateChange(String);
void up_down_blink(int,int,int);
void steady_blink(int R, int G, int B);
void rainbow_up(int, int, int);
void rainbow_down(int, int, int);
void off();


void setup() {
  // publish Particle function
  Particle.function("state-change", stateChange);
  strip.begin();
  strip.setBrightness(brightness);
  strip.show();
}

void loop() {
  // start with this to test right away
  one_blink(PEACH);
  //uncomment below to make particle react to state changes!
  //spinMode(mode);
}

// Triggered when API call is made to:
// POST https://api.particle.io/v1/devices/DEVICE_ID/state-change?access_token=ACCESS_TOKEN&args=STATE
int stateChange(String state) {
  if( // only accept known statuses
      (state == "processing") ||
      (state == "accepted") ||
      (state == "arriving")  ||
      (state == "in_progress") ||
      (state == "completed") ||
      (state == "rider_canceled") ||
      (state == "test")
    )
  {
    mode = state;
  } else {
    return -1;
  }
  return 1;
}

// change animation depending on mode
void spinMode(String mode) {
  if(mode == "processing") {
    steady_blink(WHITE);
  } else if(mode == "accepted") {
    up_down_blink(GREEN);
  } else if (mode == "arriving") {
    rainbow_up(PEACH);
    rainbow_up(WHITE);
  } else if(mode == "in_progress") {
    // probably a better way to do this but oh well
    rainbow_down(PEACH);
    rainbow_down(0,0,0);
    rainbow_down(CYAN);
    rainbow_down(0,0,0);
    rainbow_down(PURPLE);
    rainbow_down(0,0,0);
    rainbow_down(BLUE);
    rainbow_down(0,0,0);
    rainbow_down(WHITE);
    rainbow_down(0,0,0);
    rainbow_down(GREEN);
    rainbow_down(0,0,0);
  } else if (mode == "test") {
    one_blink(PEACH);
  } else {
    off();
  }
}

// blink just the first pixel
void one_blink(int R, int G, int B) {
    //first pixel on
    strip.setPixelColor(0, R,G,B);
    delay(500);
    strip.show();

    //first pixel off
    strip.setPixelColor(i, 0,0,0);
    delay(500);
    strip.show();
}

// iterate over all pixels starting from 0
// lighting up at every tick
void rainbow_up(int R, int G, int B) {
  for(i=0; i < PIXEL_COUNT; i++) {
      strip.setPixelColor(i, R,G,B);
      strip.show();
      delay(waitTime);
  }
}

// iterate over all pixels starting from PIXEL_COUNT
// lighting up at every tick
void rainbow_down(int R, int G, int B) {
  for(i=PIXEL_COUNT-1; i >= 0; i--) {
      strip.setPixelColor(i, R,G,B);
      strip.show();
      delay(waitTime);
  }
}

// blink every other pixel on/off
// while moving up and down
void up_down_blink(int R, int G, int B) {
  for(i=0; i < PIXEL_COUNT; i=i+2) {
      strip.setPixelColor(i, R,G,B);
  }
  for(i=1; i < PIXEL_COUNT; i=i+2) {
      strip.setPixelColor(i, 0,0,0);
  }

  strip.show();
  delay(1000);

  for(i=0; i < PIXEL_COUNT; i=i+2) {
      strip.setPixelColor(i, 0,0,0);
  }
  for(i=1; i < PIXEL_COUNT; i=i+2) {
      strip.setPixelColor(i, R,G,B);
  }

  strip.show();
  delay(1000);
}

// blink every other pixel on and off
void steady_blink(int R, int G, int B) {
  for(i=1; i < PIXEL_COUNT; i=i+2) {
      strip.setPixelColor(i, 0,0,0);
  }

  for(i=0; i < PIXEL_COUNT; i=i+2) {
      strip.setPixelColor(i, R,G,B);
  }

  strip.show();
  delay(1000);

  for(i=0; i < PIXEL_COUNT; i=i+2) {
      strip.setPixelColor(i, 0,0,0);
  }

  strip.show();
  delay(1000);
}


//turn all pixels off
void off() {
  for(i=0; i < PIXEL_COUNT; i++) {
      strip.setPixelColor(i, 0,0,0);
      strip.show();
      delay(waitTime);
  }
}
