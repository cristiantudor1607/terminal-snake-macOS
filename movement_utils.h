#ifndef MOVEMENT_UTILS_H_
#define MOVEMENT_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "structs.h"

void LoopSnake(table_t *Table);
void MoveSnake(table_t *Table, motion_t NewMove);

int IncreaseTail(table_t *Table);
void LoopTail(table_t *Table);

moves_t KeyToMove(char key);
motion_t MoveToMotion(moves_t move);

#endif	// MOVEMENT_UTILS_H_