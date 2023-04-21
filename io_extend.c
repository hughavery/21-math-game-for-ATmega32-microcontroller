/**
 * @file io_extend.c
 * @author Celia Allen (cal135), Hugh Avery (hav13)
 * @brief Functions for button and LED
 * @date 8 October 2022
 */
/* Course-provided modules */
#include <avr/io.h>
#include "io_extend.h"


/* Constants */
#define LED_NUM 2
#define BUTTON_NUM 7


/** Turn LED1 on.  */
void led_on (void)
{
    PORTC |= (1 << LED_NUM);
}


/** Turn LED1 off.  */
void led_off (void)
{
    PORTC &= ~(1 << LED_NUM);
}


/** Initialise LED1.  */
void led_init (void)
{
    DDRC |= (1 << LED_NUM);
}


/** Return 1 if LED1 is on  */
int check_led (void)
{
    return ((PINC & (1 << LED_NUM)) != 0);
}


/** Return non-zero if button pressed.  */
int button_pressed_p (void)
{
    return ((PIND & (1 << BUTTON_NUM)) != 0);
}


/** Initialise button1.  */
void button_init (void)
{
    DDRD &= ~(1 << BUTTON_NUM);
}

