// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include <EEPROM.h>
FASTLED_USING_NAMESPACE

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6
#define NUM_LEDS 349
#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define BRIGHTNESS  200
#define FRAMES_PER_SECOND 60

// constants won't change. They're used here to set pin numbers:
const int buttonPin2 = 2;  // the number of the pushbutton pin
const int buttonPin3 = 3;  // the number of the pushbutton pin
int buttonState = 0;
int mode=0;



//FastLed
bool gReverseDirection = false;
CRGB leds[NUM_LEDS];

// setup() function -- runs once at startup --------------------------------

// Set storage variables
uint8_t adres[2] = {0, 2};
int savedColor;

void setup() {
Serial.begin(9600);


EEPROM.get(adres[0], mode);
  if (mode < 0 || mode > 8) {
    mode = 0; // Ustaw domyślną wartość, jeśli wczytana wartość jest nieprawidłowa
    EEPROM.put(adres[0], mode); // Zapisz domyślną wartość do pamięci EEPROM
  }
EEPROM.get(adres[1], savedColor);
  if (savedColor < 0 || savedColor > 255) {
    savedColor = 0; // Ustaw domyślną wartość, jeśli wczytana wartość jest nieprawidłowa
    EEPROM.put(adres[1], savedColor); // Zapisz domyślną wartość do pamięci EEPROM
  }
// delay(3000);
FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
FastLED.setBrightness( BRIGHTNESS );
  // END of Trinket-specific code.

  // BUTTON SETUP
  // initialize the LED pin as an output:
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin2, INPUT);
  // END of button setup
  for(int i=0, j=NUM_LEDS-1; i<NUM_LEDS/2, j>NUM_LEDS/2; i++, j--){
    leds[i]=CHSV(savedColor,255,255);
    leds[j]=CHSV(savedColor,255,255);
    FastLED.show();
  }
}


// loop() function -- runs repeatedly as long as board is on ---------------
boolean checkButton1(){
    buttonState = digitalRead(buttonPin2);
    if (buttonState == HIGH) {
    if(mode<8)mode++;
    else mode=0;
    EEPROM.put(adres[0], mode);
    delay(500);
    return true;
    }
    else return false;
}

boolean checkButton2(){
    buttonState = digitalRead(buttonPin3);
    if (buttonState == HIGH) return true;
    else return false;
}
void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(250);
  }
}

void fullFade(){
  for (int i=0; i < 100; i++){
    fadeall();
    delay(1);
    FastLED.show();
  }
}

void brightenall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(5);  // Przykładowa wartość, można dostosować
  }
}

void fullBright(){
  for (int i=0; i < NUM_LEDS; i++){
    brightenall();
    delay(1);
    FastLED.show();
  }
}



void loop() {
  Serial.println(savedColor); // Debug
  switch (mode) {
    case 0:
      rainbow_wave(5, 1);
      if(checkButton1()) break;
      FastLED.show();
      break;
    case 1:
      waves(150, 40);
      break;
    case 2:
      buttonColor(savedColor);
      break;
    case 3:
      white();
      break;
    case 4:
      cylonAnimation(10, 10);
      break;
    case 5:
      simpleFade();
      break;
    case 6:
      fireEffect();
      break;
    case 7:
      ThreeSegment();
      break;
    case 8:
      partyMode();
      break;
  }
}

void buttonColor(int color){
  int brightness=255;
  while (true){
    if (checkButton1()) return;
    if(checkButton2()){
      if(color<=250){
        color+=1;
      }
      else color=0;
      EEPROM.put(adres[1], color);
    }
    for(int i=0; i<NUM_LEDS; i++){
      leds[i] = CHSV(color,255,255);
    }
    FastLED.show();
  }
}


// void rnbw(int DelayDuration, int ColorWidth){
//   while(true){
//     if (checkButton1()) return;
//     rainbowCycle(DelayDuration, ColorWidth);
//   }
// }

// void rainbowCycle(int DelayDuration, int ColorWidth) {
//   byte *c;
//   uint16_t i, j;

//   for(j = 0; j < 256; j++) {
//     for(i = 0; i < NUM_LEDS; i++) {
//       c = Wheel(fmod(((i * 256.0 / NUM_LEDS) + j) / ColorWidth, 1.0));
//       leds[NUM_LEDS - 1 - i].setRGB(*c, *(c + 1), *(c + 2));
//     }
//     FastLED.show();
//     delay(DelayDuration);
//   }
// }

// byte *Wheel(double WheelPosition) {
//   static byte c[3];

//   WheelPosition = fmod(WheelPosition, 1.0);  // Ensure WheelPosition is within [0, 1)

//   if (WheelPosition < 1.0 / 3.0) {
//     c[0] = WheelPosition * 3 * 255;
//     c[1] = 255 - WheelPosition * 3 * 255;
//     c[2] = 0;
//   } else if (WheelPosition < 2.0 / 3.0) {
//     WheelPosition -= 1.0 / 3.0;
//     c[0] = 255 - WheelPosition * 3 * 255;
//     c[1] = 0;
//     c[2] = WheelPosition * 3 * 255;
//   } else {
//     WheelPosition -= 2.0 / 3.0;
//     c[0] = 0;
//     c[1] = WheelPosition * 3 * 255;
//     c[2] = 255 - WheelPosition * 3 * 255;
//   }

//   return c;
// }



void myRainbow() {
  int numWaves = 10;
  int counter = 0;
  int wavePosition[numWaves];
  int waveColor[numWaves];
  
  for (int i = 0; i < numWaves; i++) {
    wavePosition[i] = NUM_LEDS / numWaves * i;
    if(i!=0) waveColor[i] = waveColor[i-1]+10;
    else waveColor[i]=0;
    
  }
  
  while (true) {
    if (checkButton1()) return;
    
    if (counter < 5000) {
      counter++;
    } else {
      counter = 0;
    }
    
    for (int i = 0; i < numWaves; i++) {
      leds[wavePosition[i]] = CHSV(waveColor[i], 255, 255);
      
      if (wavePosition[i] < NUM_LEDS) {
        wavePosition[i]++;
      } else {
        wavePosition[i] = 0;
      }

      if (counter % 1 == 0 && waveColor[i] < 255) {
        waveColor[i]++;
      } else if (waveColor[i] >= 255) {
        waveColor[i] = 0;
      }
    }

    FastLED.show();
    delay(1);
  }
}

void cylonAnimation(uint8_t speed, uint8_t delayTime) {
  static uint8_t hue = 0;

  for (int i = 0, j = (NUM_LEDS)-1; i < NUM_LEDS, j >= 0; i++, j--) {
    if(checkButton1()) return;
    leds[i] = CHSV(hue++, 255, 255);
    leds[j] = CHSV(hue++, 255, 255);
    FastLED.show();
    fadeall();
    delay(speed);
  }

  // for (int i = (NUM_LEDS)-1; i >= 0; i--) {
  //   if(checkButton1()) return;
  //   leds[i] = CHSV(hue++, 255, 255);
  //   FastLED.show();
  //   fadeall();
  //   delay(speed);
  // }

  delay(delayTime);
}

void simpleFade() {
  int counter = 0;

  while (true) {
    if(checkButton1()) return;

    int color = random() % 255;

    if (counter == 0) {
      for (int i = 0; i < NUM_LEDS; i++) {
        if(checkButton1()) return;
        leds[i] = CHSV(color, 255, 255);
        FastLED.show();
        delay(30);
      }
    }

    if (counter < 255) {
      counter++;
    } else {
      counter = 0;
    }
    delay(10);
  }
}

void ThreeSegment(){
  while(true){
    int color=random()%255;
    
    // dół 0-110
    for(int i=0, j=109; i<110; i++, j--){
      leds[i] = CHSV(color, 255, 255);
      leds[j] = CHSV(color, 255, 255); // Set LED color for variable j
      FastLED.show(); 
      fadeall();
      if (checkButton1()) return;
    }
    
    // delay(amount);
    color=random()%255;
    
    // środek 111-202
    for(int i=111, j=201; i<202; i++, j--){
      leds[i] = CHSV(color, 255, 255);
      leds[j] = CHSV(color, 255, 255); // Set LED color for variable j
      FastLED.show(); 
      fadeall();
      if (checkButton1()) return;
    }
    
    color=random()%255;
    
    // góra 203-348
    for(int i=203, j=348; i<=348; i++, j--){
      leds[i] = CHSV(color, 255, 255);
      leds[j] = CHSV(color, 255, 255); // Set LED color for variable j
      FastLED.show(); 
      fadeall();
      if (checkButton1()) return;
    }
}
}

void partyMode(){
  int counter=0;
  int color=0;
  int brightness;
  int saturation;
  while (true){
    if (checkButton1()) return;

    if(counter<1000) counter++;
    else counter=0;

    if(counter<900){
      for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CHSV(color,255,255);
      }
      color+=5;
    }
    if(counter>=900 && counter<1000){
      if(counter%2==0) brightness=255;
      else brightness=0;
      delay(50);
      for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CHSV(255,0,brightness);
      }
    }
    brightness=255;
    FastLED.show();
  }
}
void white(){
  int brightness=255;
  while (true){
    if (checkButton1()) return;
    
    if (checkButton2()){
      if(brightness>=15) brightness-=15;
      else brightness=255;
      delay(100);
    }
    for(int i=0; i<NUM_LEDS; i++){
      leds[i] = CHSV(60,130,brightness);
    }
    FastLED.show();
  }
}


void waves(int color, int amount) {
  int numWaves = 20;  // Możesz dostosować ilość fal
  int minDistance = 40;  // Minimalny odstęp między falami

  int wavePosition[numWaves];
  int waveBrightness[numWaves];
  int waveSaturation[numWaves];
  int startTime[numWaves];
  bool waveStarted[numWaves];

  for(int i=0; i<numWaves; i++){ // initial setup for variables
    waveSaturation[i]=255; // setting max saturation for all waves
    waveBrightness[i]=255; // setting max brightness for all waves
    waveStarted[i] = false; // setting status all waves to not started
    wavePosition[i]=0; // setting starting position of waves to first led
    if(i!=0) startTime[i] =  startTime[i-1]+rand()%90+minDistance; // generating random start time of wave
    else startTime[0]=0; // setting first wave to start immediately
  }
  int timer=0; // timer variable needed for determining if wave should already start
    while(true){
      if (checkButton1()) return;
      if(checkButton2()){ // 2nd button color change
        if(color<=245){
          color+=2;
        }
        else color=0;
      }
      for(int i=0; i<numWaves; i++){ // loop for setting all waves
        if(timer>startTime[i]){ // checking whether wave should already start
          waveStarted[i]=true;
        }
        if(waveStarted[i] && wavePosition[i]<NUM_LEDS){ // setting led position and color
          wavePosition[i]++;
          leds[wavePosition[i]] = CHSV(color, waveSaturation[i], waveBrightness[i]);
        }
        else{ // if wave reaches end of a strip it's set up to begin again from the 1st led
          wavePosition[i]=0;
          waveBrightness[i]=255;
          waveSaturation[i]=255;
        }

        if(wavePosition[i]>NUM_LEDS-100 && waveSaturation[i]>=100) waveSaturation[i]-=3; // setting wave color to brighter when wave is near end of strip
        if(wavePosition[i]>NUM_LEDS-50 && waveBrightness[i]>=5) waveBrightness[i]-=5; // dimming wave at the end of strip

        // flicker effect of sea foam (disabled by default because I don't like it)
        int flicker_effect=1; // to enable this effect simply set value to 1
        if(flicker_effect==1){
          if(wavePosition[i]>NUM_LEDS-50 && wavePosition[i]%2==0){
            waveSaturation[i]-=random()%100;
          }
          if(wavePosition[i]>NUM_LEDS-50 && wavePosition[i]%2==1){
            waveSaturation[i]+=random()%100;
          }
        }
      }
      if(timer<512){ // simple timer
        timer++;
      }
      else timer=0;
      FastLED.show(); 
      fadeall();


      delay(amount);
    }
}

// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void rainbow_wave(uint8_t thisSpeed, uint8_t deltaHue) {
  uint8_t thisHue = beat8(thisSpeed, 255);
  fill_rainbow(leds, NUM_LEDS, thisHue, deltaHue);
}

// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
//// 
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation, 
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking. 
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100 
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120

void fireEffect(){
  Fire2012();
}

void Fire2012()
{
// Array of temperature readings at each simulation cell
  static uint8_t heat[NUM_LEDS];
  for (int i = 0; i < NUM_LEDS; i++) {
      heat[i] = random8(160, 255);
    }
  while(true){
    if(checkButton1()) return;
  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND);
  }
}


