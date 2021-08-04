#include <FastLED.h>

#define LED_PIN0    0
#define LED_PIN1    1
#define LED_COUNT 158
int isClicked = isClicked;
bool initMode = initMode;
int mode = mode;
int MODECOUNT = 7;
int r = r;
int g = g;
int b = b;
int cycle = cycle;

CRGB leds0[LED_COUNT];
CRGB leds1[LED_COUNT];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, LED_PIN0, GRB>(leds0, LED_COUNT); //button 3
  FastLED.addLeds<WS2812B, LED_PIN1, GRB>(leds1, LED_COUNT); //button 4
  pinMode(3, INPUT_PULLUP); //led 0 button
  pinMode(4, INPUT_PULLUP); //led 1 button
}

void checkButtons() {
  int buttonVal0 = digitalRead(3);
  int buttonVal1 = digitalRead(4);

  //This is the reset function. If no buttons are pressed, set isClicked to 0.
  if (buttonVal0 == HIGH && buttonVal1 == HIGH && isClicked >= 1){
    isClicked = 0;
  }

  if (buttonVal0 == LOW && isClicked == 0){
    isClicked = 1;
    initMode = 1;
    if (mode < MODECOUNT){
      mode++;
    } else mode = 0;
  }
  
  if (buttonVal1 == LOW && isClicked == 0){
    isClicked = 2;
    initMode = 1;
    if (mode > 0){
      mode--;
    } else mode = MODECOUNT;
  }
}

void dopsRGB() { //Dops RGB (Flash 3)
  if (initMode == 1){
    r = 255;
    cycle = 0;
    initMode = 0;
  }
  switch(cycle){
    case 0:
      r = 255;
      cycle = 1;
      break;
    case 1:
      r = 0;
      cycle = 2;
      break;
    case 2:
      g = 255;
      cycle = 3;
      break;
    case 3:
      g = 0;
      cycle = 4;
      break;
    case 4:
      b = 255;
      cycle = 5;
      break;
    case 5:
      b = 0;
      cycle = 0;
      break;
  }
  for(int i = 0; i < LED_COUNT; i++){
    leds0[i] = CRGB(r, g, b);
    leds1[i] = CRGB(r, g, b);
  }
  FastLED.show();
  delay(100);
}

void rainbowFade() { //Rainbow fade (fade 7)
  if (initMode == 1){
      r = 255;
      initMode = 0;
  }
  if (r == 255 && g < 255 && b == 0){
    g++;
  }
  if (r <= 255 && g == 255 && b == 0){
    r--;
  }
  if (r == 0 && g == 255 && b < 255){
    b++;
  }
  if (r == 0 && g <= 255 && b == 255){
    g--;
  }
  if (r < 255 && g == 0 && b == 255){
    r++;
  }
  if (r == 255 && g == 0 && b <= 255){
    b--;
  }
  for(int i = 0; i < LED_COUNT; i++){
    leds0[i] = CRGB(r, g, b);
    leds1[i] = CRGB(r, g, b);
  }
  FastLED.show();
  delay(1);
}

void twinklePastel() { //twinkle including pastel colors and whites. (fully random colors)
  if (initMode == 1){
    initMode = 0;
    for(int i = 0; i < LED_COUNT; i++){
      leds0[i] = CRGB(0, 0, 0);
      leds1[i] = CRGB(0, 0, 0);
    }
  }
  leds0[random(LED_COUNT)] = CRGB(random(255), random(255), random(255));
  leds1[random(LED_COUNT)] = CRGB(random(255), random(255), random(255));
  leds0[random(LED_COUNT)] = CRGB(0, 0, 0);
  leds1[random(LED_COUNT)] = CRGB(0, 0, 0);
  leds0[random(LED_COUNT)] = CRGB(0, 0, 0);
  leds1[random(LED_COUNT)] = CRGB(0, 0, 0);
  FastLED.show();
  delay(1);
}

void twinkleRectified() { //twinkle random colors, colors adjusted to avoid pastels and whites
  if (initMode == 1){
      initMode = 0;
      for(int i = 0; i < LED_COUNT; i++){
        leds0[i] = CRGB(0, 0, 0);
        leds1[i] = CRGB(0, 0, 0);
      }
    }
  switch(random(2)){
    case 0:
      leds0[random(LED_COUNT)] = CRGB(random(255), random(255), 0);
      leds1[random(LED_COUNT)] = CRGB(random(255), random(255), 0);
      break;
    case 1:
      leds0[random(LED_COUNT)] = CRGB(random(255), 0, random(255));
      leds1[random(LED_COUNT)] = CRGB(random(255), 0, random(255));
      break;
    case 2:
      leds0[random(LED_COUNT)] = CRGB(0, random(255), random(255));
      leds1[random(LED_COUNT)] = CRGB(0, random(255), random(255));
      break;
  }
  
  leds0[random(LED_COUNT)] = CRGB(0, 0, 0);
  leds1[random(LED_COUNT)] = CRGB(0, 0, 0);
  leds0[random(LED_COUNT)] = CRGB(0, 0, 0);
  leds1[random(LED_COUNT)] = CRGB(0, 0, 0);
  FastLED.show();
  delay(1);
}

void dopsRandom() { //dops random, including pastels and whites.
  if (initMode == 1){
      initMode = 0;
      cycle = 0;
    }
  switch(cycle){
    case 0:
      r = random(200);
      g = random(200);
      b = random(200);
      cycle = 1;
      if(r+g+b>300){
        r -= 100;
        b -= 100;
        g -= 100;
      }
      break;
    case 1:
      r = 0;
      g = 0;
      b = 0;
      cycle = 0;
      break;
    }
  for(int i = 0; i < LED_COUNT; i++){
    leds0[i] = CRGB(r, g, b);
    leds1[i] = CRGB(r, g, b);
  }
  FastLED.show();
  delay(1);
}

void dopsRandomRectified() { //dops random, adjusted colors to avoid pastels and whites
  if (initMode == 1){
      initMode = 0;
      cycle = 0;
    }
  switch(cycle){
    case 0:
      r = random(200);
      g = random(200);
      b = 0;
      cycle++;
      break;
    case 1:
      r = 0;
      g = 0;
      b = 0;
      cycle++;
      break;
    case 2:
      r = random(200);
      g = 0;
      b = random(200);
      cycle++;
      break;
    case 3:
      r = 0;
      g = 0;
      b = 0;
      cycle++;
      break;
    case 4:
      r = 0;
      g = random(200);
      b = random(200);
      cycle++;
      break;
    case 5:
      r = 0;
      g = 0;
      b = 0;
      cycle = 0;
      break;
  }
  for(int i = 0; i < LED_COUNT; i++){
    leds0[i] = CRGB(r, g, b);
    leds1[i] = CRGB(r, g, b);
  }
  FastLED.show();
  delay(1);
}

void sinWave() {
  if (initMode == 1){
      initMode = 0;
      cycle = 0;
    }
  cycle++;
  for(int i = 0; i < LED_COUNT; i++){
    leds0[i] = CRGB(sin(i+cycle)), (sin(i+cycle)), (sin(i+cycle));
    leds1[i] = CRGB(sin(i+cycle)), (sin(i+cycle)), (sin(i+cycle));
  }
  FastLED.show();
  delay(50);
}

void slip() {
  if (initMode == 1){
    initMode = 0;
    cycle = 0;
  }
}

void loop() {
  checkButtons();

  switch(mode) {
    case 0:
      dopsRGB();
      break;
    case 1:
      rainbowFade();
      break;
    case 2:
      twinklePastel();
      break;
    case 3:
      twinkleRectified();
      break;
    case 4:
      dopsRandom();
      break;
    case 5:
      dopsRandomRectified();
      break;
    case 6:
      sinWave(); //currently broken
      break;
  }
}
