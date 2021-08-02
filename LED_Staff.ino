
#include <FastLED.h>



#define LED_PIN0    0
#define LED_PIN1    1
#define LED_COUNT 158
bool isClicked = isClicked;
bool button = button;
bool demoMode = demoMode;
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
  // put your setup code here, to run once:
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, LED_PIN0, GRB>(leds0, LED_COUNT); //button 3
  FastLED.addLeds<WS2812B, LED_PIN1, GRB>(leds1, LED_COUNT); //button 4
  pinMode(3,INPUT_PULLUP); //led 0 button
  pinMode(4,INPUT_PULLUP); //led 1 button
}

void loop() {
  int buttonVal0 = digitalRead(3);
  int buttonVal1 = digitalRead(4);

  //Button logic
  if (buttonVal0 == HIGH && buttonVal1 == HIGH && isClicked == 1){
    isClicked = 0;
  }

  //Problem: This button only activates modes 1-3. 
  if (buttonVal0 == LOW && isClicked == 0){
    button = 0;
    isClicked = 1;
    initMode = 1;
    if (mode < MODECOUNT){
      mode++;
    }else mode = 0;
  }
  
  if (buttonVal1 == LOW && isClicked == 0){
    button = 1;
    isClicked = 1;
    initMode = 1;
    if (mode > 0){
      mode--;
    }else mode = MODECOUNT;
  }

  //Mode logic
  if (mode == 0){
    demoMode = 1;
    delay(1);
  }else{
    demoMode = 0;
  }

  if (mode == 1){ //Dops RGB (Flash 3)
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

  if (mode == 2){ //Rainbow fade (fade 7)
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





  if (mode == 3){//twinkle random
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

  if (mode == 4){//twinkle random, color quanitized
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

  if (mode == 5){ //Dops Random
    if (initMode == 1){
      initMode = 0;
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
    delay(50);
  }

  if (mode == 6){ //Dops Random, color quanitzed
    if (initMode == 1){
      initMode = 0;
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
    delay(50);
  }

  if (mode == 7){
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
  
  //FastLED.show();
  //delay(10);
}
