#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define WIDTH 100
#define HEIGHT 50
#define PADDING 10

#define MIN_WALL 10
#define MAX_WALL 20

// For one apple eaten, it will add 4 more units in the tail, so
// INC_SIZE should be 4 times something
#define INC_UNITS 10
#define UNIT 4
#define INC_SIZE INC_UNITS * UNIT

#define MOVE_ERR -2

void SetRed(void);
void SetGreen(void);
void ResetColor(void);

void Intro(void);
void GameOver(void);

// function taken from GitHub
int kbhit(void);

#endif	// UTILS_H_