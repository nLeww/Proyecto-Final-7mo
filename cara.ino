#include <Adafruit_GFX.h> 
#include <MCUFRIEND_kbv.h>
#include <stdint.h>
#include "TouchScreen.h"
MCUFRIEND_kbv tft;


#define YP A1  
#define XM A2  
#define YM 7   
#define XP 6   

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define MINPRESSURE 10
#define MAXPRESSURE 1000
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
uint16_t identifier;
int touch=0;
unsigned long optime;
unsigned long blinktime;
unsigned long interaction;
unsigned long timenow;

void setup()
{
    Serial.begin(115200);
    tft.reset();
    identifier = tft.readID();
    Serial.print("ID = 0x");
    Serial.println(identifier, HEX);
    if (identifier == 0xEFEF) identifier = 0x9486;
    tft.begin(identifier);
    tft.setRotation(1);
    tft.fillScreen(BLACK);
    tft.fillRect(100, 150, 40, 40, WHITE);
    tft.fillRect(320, 150, 40, 40, WHITE);
}

void checkTouch()
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);
    pinMode(XM, OUTPUT);
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) 
    {
       touch=1;
       interaction = millis();
    }

}

void angy(){
//ENOJO
//LEFT EYE
    tft.fillRect(100, 150, 40, 40, WHITE);
  tft.drawLine(120, 100, 160, 120, WHITE);
  
//RIGHT EYE
  tft.fillRect(320, 150, 40, 40, WHITE);
  tft.drawLine(300, 120, 340, 100, WHITE);

 //CEJAS MAS ANCHAS
  tft.drawLine(300, 119, 340, 99, WHITE);
  tft.drawLine(120, 99, 160, 119, WHITE);

 //# ENOJADO
  tft.drawLine(50,30,50,100,RED);
  tft.drawLine(70,30,70,100,RED);
  tft.drawLine(25,50,95,50,RED);
  tft.drawLine(25,75,95,75,RED);
  Serial.println("im angy");

  delay(700);
  //bye bye cejas con C
  tft.drawLine(120, 100, 160, 120, BLACK);
  tft.drawLine(300, 120, 340, 100, BLACK);
  tft.drawLine(300, 119, 340, 99, BLACK);
  tft.drawLine(120, 99, 160, 119, BLACK);
  tft.drawLine(50,30,50,100,BLACK);
  tft.drawLine(70,30,70,100,BLACK);
  tft.drawLine(25,50,95,50,BLACK);
  tft.drawLine(25,75,95,75,BLACK);
  optime=millis();
}

void blinky(){
  //BLIMKING :3
  blinktime=millis();
  tft.fillRect(100, 150, 40, 40, BLACK);
  tft.fillRect(320, 150, 40, 40, BLACK);
  tft.fillRect(100, 180, 40, 10, WHITE);
  tft.fillRect(320, 180, 40, 10, WHITE);
  delay(100);
}

void normal(){
  //NO BLINK 
    tft.fillRect(100, 150, 40, 40, WHITE);
    tft.fillRect(320, 150, 40, 40, WHITE);
    tft.drawChar(380, 120, 'Z', BLACK, BLACK, 2);
    tft.drawChar(390, 100, 'Z', BLACK, BLACK, 3);
    tft.drawChar(400, 80, 'Z', BLACK, BLACK, 4);
}

void checkBlink(){
  if((millis()-blinktime)>=2500){
    blinky();
    blinktime=millis();
    Serial.print("I Blink (alone), time is:  "); Serial.println(blinktime);
    
  }
}

void checkSeepy(){
  if ((millis()-interaction)>=15000){
    Serial.println("ME DUERMO");
    seep();
    }
}

int wake= 0; 
void seep(){
  randomSeed()
  int waketries = random(1,7);
  tft.fillRect(100, 150, 40, 40, BLACK);
  tft.fillRect(320, 150, 40, 40, BLACK);
  tft.fillRect(100, 180, 40, 10, WHITE);
  tft.fillRect(320, 180, 40, 10, WHITE);
  wake = 0;
  while(wake < waketries){
  checkWakeTouch();
  zetas();
  }
  Serial.println("Me Desperte");
  blinky();
}

void zetas() {
    static unsigned long previousMillis = 0;
    static unsigned long interval = 300;
    static int step = 0;

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        switch (step) {
            case 0:
                tft.drawChar(380, 120, 'Z', WHITE, BLACK, 2);
                break;
            case 1:
                tft.drawChar(390, 100, 'Z', WHITE, BLACK, 3);
                break;
            case 2:
                tft.drawChar(400, 80, 'Z', WHITE, BLACK, 4);
                break;
            case 3:
                tft.drawChar(380, 120, 'Z', BLACK, BLACK, 2);
                tft.drawChar(390, 100, 'Z', BLACK, BLACK, 3);
                tft.drawChar(400, 80, 'Z', BLACK, BLACK, 4);
                break;
        }

        step++;

        if (step > 3) {
            step = 0;
        }
    }
}

void checkWakeTouch(){
  TSPoint p = ts.getPoint();
        pinMode(YP, OUTPUT);
        pinMode(XM, OUTPUT);

if(p.z > MINPRESSURE && p.z < MAXPRESSURE){
    wake++;
    Serial.print("Dejame dormir, ya me molestaste "); Serial.print(wake); Serial.println(" veces");
}

    
}

void loop()
{
  checkTouch();
  checkBlink();
  checkSeepy();
  if (touch==1){
    if ((millis()-optime)>=1500){
      angy();
      }
    else{
      blinky();
      touch=0;
      }
     }
     else{  
      optime=millis();
      normal();
      }
}