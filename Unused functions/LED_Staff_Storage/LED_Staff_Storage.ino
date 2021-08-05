void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:


  //Problem: This mode only runs once (should loop). After the mode finishes, it turns on one light at the beginning of the strip, and stops button 1 from working. Button 0 still works.
  if (mode == 4){
    if (initMode == 1){
      r = 40;
      g = 40;
      b = 255;
      initMode = 0;
      cycle = 1;
      for(int i = 0; i < LED_COUNT; i++){
        leds0[i] = CRGB(0, 0, 0);
        leds1[i] = CRGB(0, 0, 0);
      }
    }
    if (cycle >= LED_COUNT){
      leds0[cycle] = CRGB(0, 0, 0);
      leds1[cycle] = CRGB(0, 0, 0);
      cycle = 1;
    }else{
      cycle++;
    }
    leds0[cycle] = CRGB(r, g, b);
    leds1[cycle] = CRGB(r, g, b);
    leds0[cycle - 1] = CRGB(0, 0, 0);
    leds1[cycle - 1] = CRGB(0, 0, 0);
    FastLED.show();
    delay(1);
  }

  //Problem: This mode should rotate, instead it only lights every tenth light and stays static.
  if (mode == 3){
    if (initMode == 1){
      r = 40;
      g = 40;
      b = 255;
      initMode = 0;
      cycle = 0;
    }
    if(cycle != 9){
      cycle++;
    }else{
      cycle = 0;
    }
    for(int i = 0; i < LED_COUNT; i++){
      int j = i + cycle;
      if (i % 10 == 0){
        leds0[j] = CRGB(r, g, b);
        leds1[j] = CRGB(r, g, b);
      }else{
        leds0[j] = CRGB(0, 0, 0);
        leds1[j] = CRGB(0, 0, 0);
      }
    }
    FastLED.show();
    delay(100);
  }
}
