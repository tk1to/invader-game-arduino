
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "ascii.h"

#define PIN_SCE   12 //pin GPIO12 ON ESP , pin SCE ON LCD
#define PIN_RESET 2 //pin GPI02 on ESP , pin RST on LCD
#define PIN_DC    16 //pin GPIO14 on ESP , pin DC on LCD
#define PIN_SDIN  4 //pin GPIO4 on ESP , pin SDIN on LCD
#define PIN_SCLK  5 //pin GPIO5 on ESP  , pin SLCK on LCD

#define PIN_RIGHT  13
#define PIN_LEFT   14
#define PIN_OK     0

//The DC pin tells the LCD if we are sending a command or data
#define LCD_COMMAND 0
#define LCD_DATA    1

//You may find a different size screen, but this one is 84 by 48 pixels
#define LCD_X     84
#define LCD_Y     48

#include "LCD.h"

//===================================
#include "Bullet.h"
int bullet_num = 10;
Bullet bullets[10];

#include "Player.h"
#include "Invader.h"

Player player = Player();
Invader invaders[2];
//===================================

void setup() {
  LCDInit(); //Init the LCD
  LCDClear();
  invaders[0] = Invader(10, 0, 5);
}

void loop() {
  LCDClear();

  inv.update();

  if (!digitalRead(PIN_LEFT))  {
    player.move_left();
  }
  if (!digitalRead(PIN_RIGHT)) {
    player.move_right();
  }
  if (!digitalRead(PIN_OK)) {
    player.shoot();
  }
  player.draw();

  for (int i = 0; i < bullet_num; i++) {
    if (bullets[i].running) {
      bullets[i].run();
    }
  }

  delay(300);
}


