/**
 * @file io_init.h
 * @author Celia Allen (cal135), Hugh Avery (hav13)
 * @brief Support for functions for button and LED
 * @date 8 October 2022
 */
#ifndef IO_EXTEND_H
#define IO_EXTEND_H


/** Turn LED1 on.  */
void led_on (void);


/** Turn LED1 off.  */
void led_off (void);


/** Initialise LED1.  */
void led_init (void);


/** Return 1 if LED1 is on  */
int check_led (void);


/** Return 1 if button pressed.  */
int button_pressed_p (void);


/** Initialise button1.  */
void button_init (void);


#endif
