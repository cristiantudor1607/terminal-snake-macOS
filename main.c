#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

#include "utils.h"
#include "structs.h"
#include "world_utils.h"
#include "movement_utils.h"

int main(void)
{
    srand(time(NULL));

    char key;
    int units = 0;
    int status = 0;
    table_t Table;
    if (InitializeTable(&Table) == -1) {
        printf("Memory fail. Please try again.\n");
        return -1;
    }

    // Set the terminal to answer without pressing enter
    static struct termios old_terminal, new_terminal;
    tcgetattr(STDIN_FILENO, &old_terminal);
    new_terminal = old_terminal;
    new_terminal.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal);

    while (1) {
        system("clear");
        Intro();
        printf("Score: %d\n", Table.TailSize / UNIT);
        if (Collision(&Table)) {
            status = -1 ;
            break;
        }
        DrawTable(&Table);

        if (kbhit()) {
            key = getchar();
            
            moves_t NewAction = KeyToMove(key);
            if (NewAction == EXIT)
                break;

            MoveSnake(&Table, MoveToMotion(NewAction));
        }

        if (EatApple(&Table))
            units += UNIT;

        if (units > 0) {
            IncreaseTail(&Table);
            units--;
        }

        LoopTail(&Table);    
        LoopSnake(&Table);
        usleep(90 * 1000);
    }

    system("clear");
    if (status == -1)
        GameOver();

    // Reset the terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal);
    return 0;
}