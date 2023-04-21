/** @file   game.c
    @author Celia Allen (cal135)
    @author Hugh Avery (hav13)
    @date   8 October 2022
    @brief  Main game function for the game 21 

        21 (Bagram, or Twenty Plus One)

        One player must press button1 to indicate they will start. The blue LED will 
        light up on the board of the current player, and is used throughout the game
        to indicate whose turn it is.

        The game starts at the number zero, after which the first player can increment 
        by either one, two, or three by pushing the navstick towards the top of the board.
        The player will then press the navstick down, sending the current number to the
        other player, who can then also increment by one, two, or three.
        The game continues as such until one player must increment to 21, in which case 
        the other player wins.
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
#include "io_extend.h"
#include "menu.h"

/* Constants */
#define PACER_RATE 500
#define MESSAGE_RATE 500
#define MAX_INCREMENT 3
#define MIN_INCREMENT 1
#define MAX_NUM 21
#define WIN_CODE 'W'
#define WIN_NUM 1
#define LOSE_NUM 0



/**
 * @brief Set the up board object
 * 
 */
void set_up_board(void) 
{
    tinygl_init (MESSAGE_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_speed_set (10);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    system_init ();
    navswitch_init ();
    ir_uart_init();
    led_init();
    button_init();
    led_off();   
    pacer_init (PACER_RATE);
}


/**
 * @brief The main game logic
 * 
 * @return int 
 */
int game_logic (void)
{
    int counter = 0;
    int current_num = 0;
    char str_current_num[5];
    itoa(current_num, str_current_num, 10);
    set_up_board();
    set_player();
    tinygl_text (str_current_num);

    while (1) {   
        pacer_wait();
        tinygl_update ();
        navswitch_update ();

        /** If LED1 is on, and the navswitch is pushed, send current number to the other player. */
        if (check_led()) {
            if (navswitch_push_event_p (NAVSWITCH_NORTH) && counter < MAX_INCREMENT) {
                counter++;
                current_num++;
                itoa(current_num, str_current_num, 10);
            }

            if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                if (counter >= MIN_INCREMENT) {
                    ir_uart_putc(current_num);
                    led_off();  
                    counter = 0;
                }
            }
        }
        
        /** If player has recieved data, LED1 is turned on and the data displayed. */
        if (ir_uart_read_ready_p ()) {
            current_num = ir_uart_getc ();

            if (current_num == WIN_CODE) {
                return WIN_NUM;
            }

            led_on();
            itoa(current_num, str_current_num, 10);
        }  

        tinygl_text (str_current_num);

        /** If the current number is 21, then the game is over. */
        if (current_num == MAX_NUM) {
            ir_uart_putc(WIN_CODE);
            return LOSE_NUM;
        }
    }
    
    return 0;
}


/**
 * @brief Runs the game
 * 
 * @return int 
 */
int main (void)
{
    while(1) {
        int result = game_logic();
        end(result);
    }

    return 0;
}









