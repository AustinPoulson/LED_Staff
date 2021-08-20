#include <FastLED.h>

#define LED_PIN0    0
#define LED_PIN1    1
#define LED_COUNT 158
int isClicked = isClicked;
bool initMode = initMode;
int mode = mode;
int MODECOUNT = 8;
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

//******************************* Utility Functions ******************************* 
void blackout() {
  for(int i = 0; i < LED_COUNT; i++){
    leds0[i] = CRGB(0, 0, 0);
    leds1[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

//********************************* Mode Functions ********************************* 
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

void dops(int red1, int green1, int blue1, int red2, int green2, int blue2, int red3, int green3, int blue3, int red4, int green4, int blue4, int red5, int green5, int blue5, int red6, int green6, int blue6, int red7, int green7, int blue7, int red8, int green8, int blue8, int red9, int green9, int blue9, int red10, int green10, int blue10) {
  if (initMode == 1){
    blackout();
    cycle = 0;
    initMode = 0;
  }
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

void slip() { //WIP
  if (initMode == 1){
    initMode = 0;
    cycle = 0;
  }
}

void fill(int red, int green, int blue) {
  if (initMode == 1){
    r = red;
    g = green;
    b = blue;
    initMode = 0;
    cycle = 0;
  }
  if (cycle >= LED_COUNT) {
    blackout();
    cycle = 0;
  }
  leds0[cycle] = CRGB(r, g, b);
  leds1[cycle] = CRGB(r, g, b);
  cycle++;
  FastLED.show();
  delay(1);
}

void fillBounce(int red, int green, int blue) { //WIP
  if (initMode == 1){
    r = red;
    g = green;
    b = blue;
    initMode = 2;
    cycle = 0;
  }
  switch(initMode) {
    case 2:
      leds0[cycle] = CRGB(r, g, b);
      leds1[cycle] = CRGB(r, g, b);
      cycle++;
      if (cycle >= LED_COUNT) {
        initMode = 3;
        cycle = 0;
      }
      break;
    case 3:
      leds0[cycle] = CRGB(0, 0, 0);
      leds1[cycle] = CRGB(0, 0, 0);
      cycle++;
      if (cycle >= LED_COUNT) {
        initMode = 2;
        cycle = 0;
      }
      break;
  }
  FastLED.show();
  delay(1);
}

void fillFive(int red1, int green1, int blue1, int red2, int green2, int blue2, int red3, int green3, int blue3, int red4, int green4, int blue4, int red5, int green5, int blue5) {
  if (initMode == 1){
    blackout();
    initMode = 0;
    cycle = 0;
  }
  if (cycle >= LED_COUNT) {
    blackout();
    cycle = 0;
  }
  int line = cycle/5;
  switch(line) {
    case 1:
      r = red1;
      g = green1;
      b = blue1;
      break;
    case 2:
      r = red2;
      g = green2;
      b = blue2;
      break;
    case 3:
      r = red3;
      g = green3;
      b = blue3;
      break;
    case 4:
      r = red4;
      g = green4;
      b = blue4;
      break;
    case 5:
      r = red5;
      g = green5;
      b = blue5;
      break;
  }
  leds0[cycle] = CRGB(r, g, b);
  leds1[cycle] = CRGB(r, g, b);
  cycle++;
  FastLED.show();
  delay(1);
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
    case 7:
      fill(50, 50, 150);
      break;
    case 8:
      fillFive(150, 0, 0, 0, 150, 0, 0, 0, 150, 150, 0, 150, 150, 150, 0);
      break;
  }
}
