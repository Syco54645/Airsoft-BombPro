
char currentRedLed = -10; // the current red led that is lit in the animation
char currentBlueLed = -10; // the current blue led that is lit in the animation
long startAnimateRed;   // the last time that it was fired
long startAnimateBlue;   // the last time that it was fired
const uint8_t RED_LED_MAX = 5;
const uint8_t BLUE_LED_MAX = 5;
uint8_t chaseDirection;

void TPIC6B959N_write (void) {
  unsigned char i, numOfBytes;
  unsigned char loopLedValues;
  digitalWrite(SRCK, LOW);
  digitalWrite(RCK, LOW);
  /* shift out the bits */
  for (numOfBytes = sizeof(ledValues);numOfBytes > 0;--numOfBytes) {
    for (i = 8;i > 0;--i) {
      loopLedValues = (ledValues[numOfBytes - 1] >> (i - 1));
      loopLedValues = (loopLedValues & 1);
      digitalWrite(SER_OUT, loopLedValues);
      digitalWrite(SRCK, HIGH);
      digitalWrite(SRCK, LOW);
    }
  }
  digitalWrite(RCK, HIGH);  // enable outputs
  digitalWrite(RCK, LOW);
}

void setupTPIC (void) {
  pinMode(SER_OUT, OUTPUT);
  pinMode(SRCK, OUTPUT);
  pinMode(RCK, OUTPUT);
  LED_OFF // turn off all leds at start in case we trigger a reboot.
}

void zeroAnimations () {
  animatingRed = false;
  animatingBlue = false;
  currentRedLed = -10;
  currentBlueLed = -10;
  LED_OFF
}
void ledAnimations (uint8_t style, uint8_t delay) {
  if (animatingRed == true) {
    animateRed(style, delay);
  }
  if (animatingBlue == true) {
    animateBlue(style, delay);
  }
}

void animateRed (uint8_t style, uint8_t delay) {
  /*
   * 0 - low to high chase
   * 1 - high to low chase
   * 2 - low to high grow
   * 3 - high to low grow
   */
   if (millis() >= (startAnimateRed + delay)) {
    startAnimateRed = millis();
    bool grow;
    if (style == 0 || style == 1) {
      grow = false;
    } else {
      grow = true;
    }
    if (currentRedLed == -10 && (style == 0 || style == 2)) {
      currentRedLed = 0;
      chaseDirection = 0;
    } else if (currentRedLed == -10 && (style == 1 || style == 3)) {
      currentRedLed = RED_LED_MAX;
      chaseDirection = 1;
    }
    redChase(&currentRedLed, chaseDirection, grow);
   }
}

void animateBlue (uint8_t style, uint8_t delay) {
  /*
   * 0 - low to high chase
   * 1 - high to low chase
   * 2 - low to high grow
   * 3 - high to low grow
   */
   if (millis() >= (startAnimateBlue + delay)) {
    startAnimateBlue = millis();
    bool grow;
    if (style == 0 || style == 1) {
      grow = false;
    } else {
      grow = true;
    }
    if (currentBlueLed == -10 && (style == 0 || style == 2)) {
      currentBlueLed = 0;
      chaseDirection = 0;
    } else if (currentBlueLed == -10 && (style == 1 || style == 3)) {
      currentBlueLed = BLUE_LED_MAX;
      chaseDirection = 1;
    }
    blueChase(&currentBlueLed, chaseDirection, grow);
   }
}

void redChase (char *currentLED, uint8_t chaseDirection, bool grow) {
  /*
   * chaseDirection 0 - asc
   *           1 - desc
   */
  switch (*currentLED) {
    case -1:
      animatingRed = false;
      RED_LED_OFF
      *currentLED = -10;
      return;
      break;
    case 0:
      RED_LED0_ON;
      if (grow == false) {
        if (chaseDirection == 0){
          RED_LED1_OFF;
        }
      }
      break;
    case 1:
      RED_LED1_ON;
      if (grow == false) {
        if (chaseDirection == 0){
          RED_LED0_OFF;
        } else {
          RED_LED2_OFF;
        }
      }
      break;
    case 2:
      RED_LED2_ON;
      if (grow == false) {
        if (chaseDirection == 0){
          RED_LED1_OFF;
        } else {
          RED_LED3_OFF;
        }
      }
      break;
    case 3:
      RED_LED3_ON;
      if (grow == false) {
        if (chaseDirection == 0){
          RED_LED2_OFF;
        } else {
          RED_LED4_OFF;
        }
      }
      break;
    case 4:
      RED_LED4_ON;
      if (grow == false) {
        if (chaseDirection == 0){
          RED_LED3_OFF;
        } else {
          RED_LED5_OFF;
        }
      }
      break;
    case 5:
      RED_LED5_ON;
      if (grow == false) {
        if (chaseDirection == 0){
          RED_LED4_OFF;
        } else {
          RED_LED6_OFF;
        }
      }
      break;
    case 6:
      animatingRed = false;
      RED_LED_OFF
      *currentLED = -10;
      return;
      break;
  }
  if (chaseDirection == 0) {
    *currentLED += 1;
  } else {
    *currentLED -= 1;
  }
}

void blueChase (char *currentLED, uint8_t chaseDirection, bool grow) {
  /*
   * chaseDirection 0 - asc
   *           1 - desc
   */
  switch (*currentLED) {
    case -1:
      animatingBlue = false;
      BLUE_LED_OFF
      *currentLED = -10;
      return;
      break;
    case 0:
      BLUE_LED0_ON;
      if (grow == false) {
        if (chaseDirection == 0){
          BLUE_LED1_OFF;
        }
      }
      break;
    case 1:
      BLUE_LED1_ON;
      if (grow == false) {
        if (chaseDirection == 0){
          BLUE_LED0_OFF;
        } else {
          BLUE_LED2_OFF;
        }
      }
      break;
    case 2:
      BLUE_LED2_ON;
      if (grow == false) {
        if (chaseDirection == 0){
          BLUE_LED1_OFF;
        } else {
          BLUE_LED3_OFF;
        }
      }
      break;
    case 3:
      BLUE_LED3_ON;
      if (grow == false) {
        if (chaseDirection == 0){
          BLUE_LED2_OFF;
        } else {
          BLUE_LED4_OFF;
        }
      }
      break;
    case 4:
      BLUE_LED4_ON;
      if (grow == false) {
        if (chaseDirection == 0){
          BLUE_LED3_OFF;
        } else {
          BLUE_LED5_OFF;
        }
      }
      break;
    case 5:
      BLUE_LED5_ON;
      if (grow == false) {
        if (chaseDirection == 0){
          BLUE_LED4_OFF;
        } else {
          BLUE_LED6_OFF;
        }
      }
      break;
    case 6:
      animatingBlue = false;
      BLUE_LED_OFF
      *currentLED = -10;
      return;
      break;
  }
  if (chaseDirection == 0) {
    *currentLED += 1;
  } else {
    *currentLED -= 1;
  }
}

