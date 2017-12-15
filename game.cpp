#include <fstream>
#include <graphics.h>
#include "gameTrainer.h"
#include "gameContainer.h"
using namespace container;
#define WINDOWSIZE_X 764 //1024
#define WINDOWSIZE_Y 512 //640
void loadFile()
{
	;
}
void saveFile()
{
	;
}
void init()
{
	loadFile();
	initgraph(WINDOWSIZE_X,WINDOWSIZE_Y,0);
}
void switchPlayer()
{
	;
}
void play()
{
	;
}
void draw()
{
	;
}
bool judge()
{
	;
}
void tidyUp()
{
	saveFile();
	closegraph();
}
int main()
{
	init();
	do
	{
		draw();
		switchPlayer();
		play();
	}
	while (judge());
	tidyUp();
    return 0;
}
