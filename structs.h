#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct point_t point_t;
struct point_t {
    int x, y;
};

typedef struct motion_t motion_t;
struct motion_t {
    int dx;
    int dy;
};

typedef struct moving_cell_t moving_cell_t;
struct moving_cell_t {
    int x, y;
    int dx, dy;
};

typedef struct table_t table_t;
struct table_t {
    point_t Snake;
    point_t *Tail;
    point_t Apple;
    point_t *Walls;
    motion_t Move;
    int width, height;
    int padding;
    int TailSize;
    int MaxTailSize;
    int WallsNumber;
};

typedef enum moves_t moves_t;
enum moves_t {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    EXIT,
    UNDEFINED
};



#endif	// STRUCTS_H_