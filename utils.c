#include "utils.h"

void SetRed(void)
{
	printf("\33[0:31m");
}

void SetGreen(void)
{
	printf("\33[0:32m");
}

void ResetColor(void)
{
	printf("\e[0m");
}

void Intro(void)
{
	printf("  _____                   _             _ ____              _        \n");
	printf(" |_   _|__ _ __ _ __ ___ (_)_ __   __ _| / ___| _ __   __ _| | _____ \n");
	printf("   | |/ _ \\ '__| '_ ` _ \\| | '_ \\ / _` | \\___ \\| '_ \\ / _` | |/ / _ \\\n");
    printf("   | |  __/ |  | | | | | | | | | | (_| | |___) | | | | (_| |   <  __/\n");
    printf("   |_|\\___|_|  |_| |_| |_|_|_| |_|\\__,_|_|____/|_| |_|\\__,_|_|\\_\\___|\n");
    printf("                                                                     \n");
}

void GameOver(void)
{
    printf("   ____                       ___                 \n");
    printf("  / ___| __ _ _ __ ___   ___ / _ \\__   _____ _ __ \n");
    printf(" | |  _ / _` | '_ ` _ \\ / _ \\ | | \\ \\ / / _ \\ '__|\n");
    printf(" | |_| | (_| | | | | | |  __/ |_| |\\ V /  __/ |   \n");
    printf("  \\____|\\__,_|_| |_| |_|\\___|\\___/  \\_/ \\___|_|   \n");
    printf("                                                  \n");
}

int kbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;
 
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
	ch = getchar();
 
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
 
	if(ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}
 
	return 0;
}