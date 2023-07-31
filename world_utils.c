#include "world_utils.h"

void DrawTable(table_t *Table)
{
	int stop = 0;

	for (int i = 0; i < Table->height; i++) {
		for (int j = 0; j < Table->width; j++) {
			stop = 0;
			if (i == 0 || i == Table->height - 1) {
				printf("-");
				continue;
			}

			if (j == 0 || j == Table->width - 1) {
				printf("|");
				continue;
			}

			if (i == Table->Snake.y && j == Table->Snake.x) {
				SetGreen();
				printf("0");
				ResetColor();
				continue;
			}

			for (int k = 0; k < Table->TailSize; k++) {
				if (Table->Tail[k].x == j && Table->Tail[k].y == i) {
					printf("0");
					stop = 1;
					break;
				}
			}

			if (stop)
				continue;

			if (i == Table->Apple.y && j == Table->Apple.x) {
				SetRed();
				printf("@");
				ResetColor();
				continue;
			}

			for (int k = 0; k < Table->WallsNumber; k++) {
				if (Table->Walls[k].x == j && Table->Walls[k].y == i) {
					printf("#");
					stop = 1;
					break;
				}
			}

			if (stop)
				continue;


			printf(" ");
		}

		printf("\n");
	}
}

int InitializeTable(table_t *Table)
{
	// Add 2 to the actual size of the table, because of the border
	Table->width = WIDTH + 2;
	Table->height = HEIGHT + 2;

	// The padding is used to prevent apples to be generated to close
	// to the borders
	Table->padding = PADDING;

	// TODO: Walls generation should happen first
	if (SetWalls(Table) == -1)
		return -1;
	
	// Give the Snake a Location where to start
	SetSnake(Table);

	// Generate a random move to start with
	Table->Move = RandomMovement();

	// Set the Apple location
	SetApple(Table);

	// Set the initial tail
	if (InitTail(Table) == -1) {
		free(Table->Walls);
		return -1;
	}

	return 1;
}

point_t RandomLocation(int width, int height, int padding)
{
	// Calculate the boundaries
	int WidthLimit = width - 2 * padding;
	int HeightLimit = height - 2 * padding;

	// Declare the return structure
	point_t Location;
	
	// Generate the points
	Location.x = rand() % WidthLimit + padding;
	Location.y = rand() % HeightLimit + padding;

	return Location;
}

motion_t RandomMovement(void)
{
	// Declare the return struct
	motion_t Movement;

	// First select the axis
	int RandomAxis = rand() % 2;

	// Now, let the Snake move along the x-axis if the result is 0, or
	// let the Snake move along the y-axis if the result is 1

	if (RandomAxis == 0) {
		Movement.dx = 1;
		Movement.dy = 0;
	} else {
		Movement.dx = 0;
		Movement.dy = 1;
	}

	// Select the orientation

	int RandomWay = rand() % 2;

	// Let the Snake move in positive direction, if the result is 1. In this case,
	// we do nothing, because the dx and dy are already set.

	if (RandomWay == 0) {
		Movement.dx *= -1;
		Movement.dy *= -1;
	}

	return Movement;
}

int GetRandomNumber(int inf, int sup)
{
	srand(time(NULL));

	if (inf == sup)
		return inf;

	if (inf > sup) {
		int aux = inf;
		inf = sup;
		sup = aux;
	}

	int diff = sup - inf;

	int Random = rand() % diff + inf;

	return Random;
}

int SameLocation(point_t point1, point_t point2)
{
	if (point1.x == point2.x && point1.y == point2.y)
		return 1;

	return 0;
}

int Overlap(point_t *Walls, int n, point_t reference)
{
	for (int i = 0; i < n; i++) {
		if (SameLocation(Walls[i], reference))
			return 1;
	}

	return 0;
}

int SetWalls(table_t *Table)
{
	// Generate a number in range
	int n = GetRandomNumber(MIN_WALL, MAX_WALL);

	Table->WallsNumber = n;

	Table->Walls = (point_t *)malloc(n * sizeof(point_t));
	if (Table->Walls == NULL)
		return -1;

	for (int i = 0; i < n; i++) {
		Table->Walls[i] = RandomLocation(WIDTH, HEIGHT, 1);
	}

	return 1;
}

int Collision(table_t *Table)
{
	return Overlap(Table->Walls, Table->WallsNumber, Table->Snake) || 
		   Overlap(Table->Tail, Table->TailSize, Table->Snake);
}


void SetSnake(table_t *Table)
{
	point_t Location = RandomLocation(WIDTH, HEIGHT, PADDING);
	while (Overlap(Table->Walls, Table->WallsNumber, Location))
		Location = RandomLocation(WIDTH, HEIGHT, PADDING);

	Table->Snake = Location;
}

void SetApple(table_t *Table)
{
	point_t Location = RandomLocation(WIDTH, HEIGHT, PADDING);

	while (Overlap(Table->Walls, Table->WallsNumber, Location) || 
		   SameLocation(Table->Snake, Location))
		Location = RandomLocation(WIDTH, HEIGHT, PADDING);

	Table->Apple = Location;
}

int InitTail(table_t *Table)
{
	Table->TailSize = 0;
	
	Table->Tail = (point_t *)malloc(INC_SIZE * sizeof(point_t));
	if (!Table->Tail)
		return -1;

	Table->MaxTailSize = INC_SIZE;

	return 1;
}

// TODO: Check walls and tail for the apple to not spawn there
void GenerateNewApple(table_t *Table)
{
	point_t NewLocation = RandomLocation(WIDTH, HEIGHT, PADDING);

	// TODO: Check the tail too
	while (Overlap(Table->Walls, Table->WallsNumber, NewLocation) ||
		   SameLocation(NewLocation, Table->Apple) || 
		   Overlap(Table->Tail, Table->TailSize, NewLocation))
		NewLocation = RandomLocation(WIDTH, HEIGHT, PADDING);

	Table->Apple = NewLocation;
}

int EatApple(table_t *Table)
{
	if (!SameLocation(Table->Apple, Table->Snake))
		return 0;

	GenerateNewApple(Table);
	return 1;
}




