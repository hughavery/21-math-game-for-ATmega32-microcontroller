/**
 * @file menu.c
 * @author Celia Allen (cal135), Hugh Avery (hav13)
 * @brief Set player and end screen
 * @date 8 October 2022
 */
/* Course-provided modules */
#include <avr/io.h>
#include <stdlib.h>
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "../fonts/font5x5_1.h"


/* Student-written modules */
#include "menu.h"
#include "io_extend.h"


/* Constants */
#define PACER_RATE 500
#define MESSAGE_RATE 500
#define MESSAGE_SPEED 15
#define RESET_CODE 'R'
#define QUIT_CODE 'Q'


/**
 * @brief Waits until a player presses button1, then they are set as 
 * the initial player, and the main game is started
 * 
 * @return int to indicate the game is ready to start
 */
int set_player (void) 
{
    while (1) {
        /** Check if button pressed */
        if (button_pressed_p()) {
            led_on();
            ir_uart_putc(QUIT_CODE);
            return 0;
        }

        /** Check if exit code recieved from other person */
        if (ir_uart_read_ready_p ()) {
            char recieved_char;
            recieved_char = ir_uart_getc ();
            if (recieved_char == QUIT_CODE) {
                return 0;
            }            
        }
    }

    return 0;
}


/**
 * @brief The end screen of the game, displaying to the players who won and who lost
 * 
 * @param flag 0 or 1 depending on whether the player lost or won the game, repesctively
 * @return int 
 */
int end(int flag) 
{
    tinygl_init (MESSAGE_RATE);
    tinygl_text_speed_set (MESSAGE_SPEED);
    tinygl_font_set (&font5x5_1);

    if (flag == 0) {
        tinygl_text ("LOSER");
    } else {
        tinygl_text ("WINNER");
    }

    pacer_init (PACER_RATE);
    led_off(); 

    while(1) {
        pacer_wait();
        tinygl_update();

        /** Check if button pressed, in which case exit end screen and send restart code */
        if (button_pressed_p()) {
            led_off();
            ir_uart_putc(RESET_CODE);
            return 0;
        }
        /** Check if restart code recieved from other person */
        if (ir_uart_read_ready_p ()) {
            char recieved_char;
            recieved_char = ir_uart_getc ();
            if (recieved_char == RESET_CODE) {
                return 0;
            }            
        }
    }

    return 0;
}

