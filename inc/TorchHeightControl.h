#ifndef TORCHHEIGHTCONTROL_H_
#define TORCHHEIGHTCONTROL_H_



/*
 *  Main libraries
 */
// already contains all necessary AVR's and C standard library functions
#include <Arduino.h>

/*
 *  User libraries
 */
// We use custom ADC library instead of Arduino's analogRead()
// because second takes some unwanted for us periphery (timer)
// and it is actually quite simple to write your own lightweight version
// of analogRead() so why not?
#include <ADC.h>
// Abstraction layer for the way we rule the motor. There can be a driver
// for a stepper motor plus set of switches, a stepper motor with
// "intelligent" step-direction driver, simply DC motor or whatever you wants to.
#include <MotorDriver.h>


/*
 *  Control signals definitions (all of them are inputs)
 *  Free (unused) pins:
 *    - PB5 (can be used as a test LED)
 *    - PD0
 *    - PD1
 */
#define SIGNALS_DDR DDRB
#define SIGNALS_PIN PINB
#define UP_SIGNAL_PIN PB2 // PIN 10
#define UP_SIGNAL_INT PCINT2
#define DOWN_SIGNAL_PIN PB3 //PIN 11
#define DOWN_SIGNAL_INT PCINT3
#define PLASM_SIGNAL_PIN PB4 //PIN 12
#define PLASM_SIGNAL_INT PCINT4
#define TOUCH_SIGNAL_PIN PB1 //PIN 9
#define TOUCH_SIGNAL_INT PCINT1
#define SETTINGS_BUTTON_PIN PB0 //PIN 8
#define SETTINGS_BUTTON_INT PCINT0
// initial state: all signals are pulled up to Vcc
uint8_t signals_port_history = 0xFF;


/*
 *  Menu definitions
 */
enum Menu {
    WORK_MENU,
    IDLE_MENU,
    cutting_height_MENU,
    SETPOINT_OFFSET_MENU,
    PIERCE_TIME_MENU,

    NUM_OF_MENUS
};
uint8_t menu = IDLE_MENU;  // initial state


/*
 *  LCD definitions. We use Arduino's standard library LiquidCrystal for this
 *  because of its robustness and widespread
 */
//#include <LiquidCrystal.h> // Enlever Louis
//#include <LiquidCrystal_I2C.h> //LG
#include <Wire.h>  // Teste LG
#include <hd44780.h>  // Teste LG
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header // Teste LG
hd44780_I2Cexp lcd; // auto detect backpack and pin mappin
// RS, RW (optional, faster in general), E, D4-7
//LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display //LG
//LiquidCrystal lcd(1, 2, 3, 4, 5, 6, 7); //EN LG 
// we need slightly more than the length of a string (16 in our case)
// due to the inner structure of the sprintf(). Otherwise, displayed
// values can be corrupted
#define BUFFER_SIZE 25
char bufferA[BUFFER_SIZE];  // 1st raw of LCD
char bufferB[BUFFER_SIZE];  // 2nd raw of LCD


/*
 *  LED for testing purposes. PB5 is built-in on UNO and NANO
 */
// #define TEST_LED
#ifdef TEST_LED
    #define TEST_LED_DDR DDRB
    #define TEST_LED_PORT PORTB
    #define TEST_LED_PIN PB5
#endif



#endif /* TORCHHEIGHTCONTROL_H_ */
