#ifndef WORLD_UTILS_H_
#define WORLD_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "structs.h"
#include "utils.h"

void DrawTable(table_t *Table);
int InitializeTable(table_t *Table);

point_t RandomLocation(int width, int height, int padding);
motion_t RandomMovement(void);
int GetRandomNumber(int inf, int sup);
int SameLocation(point_t point1, point_t point2);
int Overlap(point_t *Walls, int n, point_t reference);
int Collision(table_t *Table);

int SetWalls(table_t *Table);
void SetSnake(table_t *Table);
void SetApple(table_t *Table);

int InitTail(table_t *Table);
void GenerateNewApple(table_t *Table);
int EatApple(table_t *Table);



#endif	// WORLD_UTILS_H_