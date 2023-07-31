#include "movement_utils.h"

void LoopSnake(table_t *Table)
{
    Table->Snake.x += Table->Move.dx;
    Table->Snake.y += Table->Move.dy;

    // Check if it goes out of the table
    if (Table->Snake.x < 1 && Table->Move.dx == -1)
        Table->Snake.x = Table->width - 1;

    if (Table->Snake.x >= Table->width - 1 && Table->Move.dx == 1)
        Table->Snake.x = 1;

    if (Table->Snake.y < 1 && Table->Move.dy == -1)
        Table->Snake.y = Table->height - 1;

    if (Table->Snake.y >= Table->height - 1 && Table->Move.dy == 1)
        Table->Snake.y = 1;
}

moves_t KeyToMove(char key)
{
    if (key == 'w' || key == 'W')
        return UP;

    if (key == 's' || key == 'S')
        return DOWN;

    if (key == 'a' || key == 'A')
        return LEFT;
    
    if (key == 'd' || key == 'D')
        return RIGHT;
    
    if (key == 'q' || key == 'Q')
        return EXIT;

    return UNDEFINED;
}

motion_t MoveToMotion(moves_t move)
{
    motion_t NewMove;

    // UNDEFINED base case
    NewMove.dx = MOVE_ERR;
    NewMove.dy = MOVE_ERR;

    if (move == UP) {
        NewMove.dx = 0;
        NewMove.dy = -1;
    }

    if (move == DOWN) {
        NewMove.dx = 0;
        NewMove.dy = 1;
    }

    if (move == LEFT) {
        NewMove.dx = -1;
        NewMove.dy = 0;
    }

    if (move == RIGHT) {
        NewMove.dx = 1;
        NewMove.dy = 0;
    }

    return NewMove;
}

void MoveSnake(table_t *Table, motion_t NewMove)
{
    if (NewMove.dx == MOVE_ERR || NewMove.dy == MOVE_ERR)
        return;

    Table->Move = NewMove;
}

int IncreaseTail(table_t *Table)
{
    if (Table->TailSize == 0) {
        Table->Tail[0] = Table->Snake;
        Table->TailSize++;
        return 1;
    }

    Table->TailSize++;
    if (Table->TailSize == Table->MaxTailSize) {
        Table->MaxTailSize += INC_SIZE;
        Table->Tail = realloc(Table->Tail, Table->MaxTailSize * sizeof(point_t));
        if (Table->Tail == 0)
            return 0;

    }

    Table->Tail[Table->TailSize] = Table->Tail[Table->TailSize - 1];
    return 1;
}

void LoopTail(table_t *Table)
{
    if (Table->TailSize == 0)
        return;

    for (int i = Table->TailSize - 1; i >= 1; i--)
        Table->Tail[i] = Table->Tail[i - 1];

    Table->Tail[0] = Table->Snake;
}