#include <fstream>
#include <graphics.h>
#include "gameTrainer.h"
#include "gameContainer.h"
//window's size
#define WINDOWSIZE_X 680
#define WINDOWSIZE_Y 680
//map's size
#define MAP_X 15
#define MAP_Y 15
#define START_X 40
#define START_Y 40
#define END_X 640
#define END_Y 640
//false presents human, true presents AI
#define PLAYER_0 false
#define PLAYER_1 false
GameDirector *director;
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

	director = new GameDirector(
	Position(MAP_X,MAP_Y),Position(START_X,START_Y),Position(END_X,END_Y));
	director->addPlayer(PLAYER_0);
	director->addPlayer(PLAYER_1);
}
void switchPlayer()
{
	director->changePlayer();
}
void play()
{
	Position pos;
	do
	{
		pos=director->getCurrentPlayer()->getXY();
	}while(director->putChess(pos) == false);
}
bool isEnded()
{
	return director->isTheGameEnded();
}
void tidyUp()
{
	director->showResult();
	saveFile();
	closegraph();
	delete director;
}
int main()
{
	init();
	do
	{
		switchPlayer();
		play();
	}
	while (!isEnded());
	tidyUp();
    return 0;
}
