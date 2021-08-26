#include <FastLED.h>

#define LED_PIN0    0
#define LED_PIN1    1
#define LED_COUNT 158
int isClicked = isClicked;
bool initMode = initMode;
int mode = mode;
int MODECOUNT = 15;
int r = r;
int g = g;
int b = b;
int cycle = cycle;
int subCycle = subCycle;
int dopsArr1[] = {150, 0, 0, 0, 0, 0, 0, 150, 0, 0, 0, 0, 0, 0, 150, 0, 0, 0};

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

void dops6(int red1, int green1, int blue1, int red2, int green2, int blue2, int red3, int green3, int blue3, int red4, int green4, int blue4, int red5, int green5, int blue5, int red6, int green6, int blue6) { //Dops RGB (Flash 3)
  if (initMode == 1){
    cycle = 0;
    initMode = 0;
  }
  switch(cycle){
    case 0:
      r = red1;
      g = green1;
      b = blue1;
      cycle = 1;
      break;
    case 1:
      r = red2;
      g = green2;
      b = blue2;
      cycle = 2;
      break;
    case 2:
      r = red3;
      g = green3;
      b = blue3;
      cycle = 3;
      break;
    case 3:
      r = red4;
      g = green4;
      b = blue4;
      cycle = 4;
      break;
    case 4:
      r = red5;
      g = green5;
      b = blue5;
      cycle = 5;
      break;
    case 5:
      r = red6;
      g = green6;
      b = blue6;
      cycle = 0;
      break;
  }
  for(int i = 0; i < LED_COUNT; i++){
    leds0[i] = CRGB(r, g, b);
    leds1[i] = CRGB(r, g, b);
  }
  FastLED.show();
  delay(50);
  blackout();
  FastLED.show();
  delay(50);
}

void dops(int colors[]) { //test this
  if (initMode == 1){
    blackout();
    cycle = 0;
    subCycle = 0;
    initMode = 0;
  }
  if(subCycle == 0){
    r = colors[cycle];
    g = colors[(cycle + 1)];
    b = colors[(cycle + 2)];
    cycle = cycle + 3;
    for(int i = 0; i < LED_COUNT; i++){
      leds0[i] = CRGB(r, g, b);
      leds1[i] = CRGB(r, g, b);
    }
    subCycle = 1;
    if (cycle >= *(&colors + 1) - colors){
      cycle = 0;
    }
  } else {
    subCycle = 0;
    blackout();
  }
  FastLED.show();
  delay(10);
}

void rainbowFade() { //Rainbow fade (fade 7)
  if (initMode == 1){
      r = 255;
      g = 0;
      b = 0;
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

void sinWave() { //WIP
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

void fillFade(int red, int green, int blue) { //WIP
  if (initMode == 1){
    r = red;
    g = green;
    b = blue;
    initMode = 0;
    cycle = 0;
    subCycle = 0;
  }
  switch(subCycle) {
    case 0:
      if (cycle >= LED_COUNT) {
        subCycle = 1;
        cycle = 0;
      } else {
        leds0[cycle] = CRGB(r, g, b);
        leds1[cycle] = CRGB(r, g, b);
        cycle++;
      }
      break;
    case 1:
      if (cycle >= LED_COUNT) {
        subCycle = 0;
        cycle = 0;
      } else {
        leds0[cycle] = CRGB(0, 0, 0);
        leds1[cycle] = CRGB(0, 0, 0);
        cycle++;
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
    subCycle = 1;
  }
  if (cycle >= LED_COUNT) {
    blackout();
    cycle = 0;
  }
  int line = 0;
  if((cycle + 5) % 5 == 0){
    line = 5;
  } else if ((cycle + 5) % 4 == 0) {
    line = 4;
  } else if ((cycle + 5) % 3 == 0) {
    line = 3;
  } else if ((cycle + 5) % 2 == 0) {
    line = 2;
  } else {
    line = 1;
  }
  switch(subCycle) {
    case 1:
      r = red1;
      g = green1;
      b = blue1;
      subCycle++;
      break;
    case 2:
      r = red2;
      g = green2;
      b = blue2;
      subCycle++;
      break;
    case 3:
      r = red3;
      g = green3;
      b = blue3;
      subCycle++;
      break;
    case 4:
      r = red4;
      g = green4;
      b = blue4;
      subCycle++;
      break;
    case 5:
      r = red5;
      g = green5;
      b = blue5;
      subCycle = 1;
      break;
  }
  leds0[cycle] = CRGB(r, g, b);
  leds1[cycle] = CRGB(r, g, b);
  cycle++;
  FastLED.show();
  delay(1);
}

void lightning(int red, int green, int blue){
  if (initMode == 1){
    blackout();
    r = red;
    g = green;
    b = blue;
    initMode = 0;
    cycle = 0;
    subCycle = 0;
  }
  if (cycle < LED_COUNT) {
    leds0[cycle] = CRGB(r, g, b);
    leds1[cycle] = CRGB(r, g, b);
    cycle = cycle + (random()%(5-4 + 1) + 4);
  } else {
    cycle = 0;
    FastLED.show();
    delay(70);
    blackout();
  }
}

void fire(int red1, int green1, int blue1, int red2, int green2, int blue2){
  if (initMode == 1){
    blackout();
    r = red1;
    g = green1;
    b = blue1;
    initMode = 0;
    cycle = 0;
    subCycle = 0;
  }
  if (cycle < LED_COUNT) {
    leds0[cycle] = CRGB(r, g, b);
    leds1[cycle] = CRGB(r, g, b);
    cycle = cycle + (random()%(5-4 + 1) + 4);
  } else {
    cycle = 0;
    FastLED.show();
    delay(90);
    blackout();
    for(int i = 0; i < LED_COUNT; i++){
      leds0[i] = CRGB(red2, green2, blue2);
      leds1[i] = CRGB(red2, green2, blue2);
    }
  }
}

void loop() {
  checkButtons();

  switch(mode) {
    case 0:
      fire(100, 25, 0, 0, 0, 20);
      break;
    case 1:
      fire(0, 25, 150, 0, 100, 25);
      break;
    case 2:
      lightning(50, 50, 150);
      break;
    case 3:
      twinkleRectified();
      break;
    case 4:
      fillFade(50, 50, 150);
      break;
    case 5:
      fillFive(0, 30, 75, 30, 0, 75, 0, 75, 30, 0, 0, 100, 75, 75, 0);
      break;
    case 6:
      fire(100, 25, 0, 0, 0, 20);
      break;
    case 7:
      fillFade(100, 0, 0);
      break;
    case 8:
      fillFive(150, 0, 0, 0, 150, 0, 0, 0, 150, 0, 150, 0, 0, 0, 150);
      break;
    case 9:
      dopsRandomRectified();
      break;
    case 10:
      dops6(100, 0, 10, 0, 0, 100, 0, 0, 100, 0, 100, 0, 0, 0, 100, 0, 0, 100);
      break;
    case 11:
      dops6(127, 8, 120, 4, 123, 128, 4, 123, 128, 127, 8, 120, 4, 123, 128, 4, 123, 128);
      break;
    case 12:
      dops6(30, 0, 75, 0, 20, 100, 0, 102, 20, 30, 0, 75, 0, 20, 100, 0, 102, 20);
      break;
    case 13:
      fire(100, 0, 0, 100, 25, 0);
      break;
    case 14:
      lightning(100, 0, 0);
      break;
    case 15:
      fillFade(25, 0, 100);
      break;
  }
}

//***List of finished modes***
//Dops RGB
//Dops Random
//Dops Random Rectified
//Rainbow Fade
//Twinkle Pastel
//Twinkle Rectified
//Fill*
//Fill Five*
//Lightning*

//***List of WIP modes***
//Dops
//Sine

/*
      Ξ⌇⌇Ǝ━━━━
       ⌇⌇
       ⌇⌇
       ⌇
 _______________
 \~~~~~~~~~~~~~/
  \___________/
*/
