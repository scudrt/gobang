#include <graphics.h>
#include "gameContainer.h"

Position::Position(int nowx,int nowy)
{
	x=nowx;
	y=nowy;
}

Position::Position()
{
	x=y=0;
}

PlayerController::PlayerController(bool _isAIPlayer_,bool _isBlackChess_)
{
	_isAIPlayer = _isAIPlayer_;
	_isBlackChess = _isBlackChess_;
}

bool PlayerController::isAIPlayer()
{
	return _isAIPlayer;
}

bool PlayerController::isBlackChess()
{
	return _isBlackChess;
}

Position PlayerController::getXY()
{
	Position pos;
	mouse_msg msg={0};
	if (isAIPlayer())
	{
		;
	}
	else
	{
		while (1)
		{
			msg=getmouse();
			if (msg.is_down())
			{
				pos.x=msg.x;
				pos.y=msg.y;
				break;
			}
		}
	}
	return pos;
}

GameDirector::GameDirector()
{
	mapX = mapY = 0;
	currentPlayerNumber = 1;
	player[0] = player[1] = NULL;
}

GameDirector::GameDirector(Position _map,Position start,Position end)
{
	mapX = _map.x;
	mapY = _map.y;
	startX = start.x;
	startY = start.y;
	endX = end.x;
	endY = end.y;
	blockX = (endX - startX) / mapX;
	blockY = (endY - startY) / mapY;
	map = new int[mapX*mapY];
	restBlank = mapX*mapY;
	for (int i=0;i<restBlank;++i)
	{
		map[i]=-1;
	}

	currentPlayerNumber = 1;
	player[0] = player[1] = NULL;

	_makeMap();
}

GameDirector::~GameDirector()
{
	for (int i=0;i<=1;++i)
	{
		if (player[i] != NULL)
		{
			delete player[i];
		}
	}
	delete[] map;
}

void GameDirector::_makeMap()
{
	//background color
	setbkcolor(EGERGB(120,120,120)); //grey
	//draw the lines
	setcolor(EGERGB(180,180,180));
	for (int i=1;i<=mapX+1;++i)
	{
		//row
		line(startX,startY+(i-1)*blockY,endX,startY+(i-1)*blockY);
	}
	for (int i=1;i<=mapY+1;++i)
	{
		//column
		line(startX+(i-1)*blockX,startY,startX+(i-1)*blockX,endY);
	}
}

void GameDirector::addPlayer(bool isAI)
{
	if (player[0]==NULL) //no this player yet
	{
		player[0] = new PlayerController(isAI,true);
	}
	else if (player[1]==NULL) //no this player yet
	{
		player[1] = new PlayerController(isAI,false);
	}
}

void GameDirector::changePlayer()
{
	//1 to 0 , 0 to 1
	currentPlayerNumber = 1 - currentPlayerNumber;
	setfont(20,0,"Atarix");
	setcolor(currentPlayerNumber?WHITE:BLACK);
	xyprintf((startX+endX)/2-60,10,"player:%s",(currentPlayerNumber==1?"White":"Black"));
}

bool GameDirector::putChess(Position pos)
{
	if (player[currentPlayerNumber]->isAIPlayer() == false)
	{ //people with mouse input
		if (pos.x>=startX && pos.x<=endX && pos.y>=startY && pos.y<=endY)
		{
			//legal mouse position
			pos.x=(pos.x-startX) / blockX;
			pos.y=(pos.y-startY) / blockY;
		}
		else
		{
			return false;
		}
	}
	int *currentPosition=map+pos.y*mapX+pos.x;
	if (*currentPosition != -1)
	{
		//occupied position
		return false;
	}
	else
	{
		//record this operation
		lastX = pos.x;
		lastY = pos.y;
	}
	*currentPosition = currentPlayerNumber;
	if (currentPlayerNumber == 1) //white
	{
		setfillcolor(WHITE);
	}
	else //color is black
	{
		setfillcolor(BLACK);
	}
	//draw a chess in the blank
	int chessx=startX+pos.x*blockX;
	int chessy=startY+pos.y*blockY;
	bar(chessx+1,chessy+1,chessx+blockX,chessy+blockY);
	--restBlank;
	return true;
}

void GameDirector::showResult()
{
	setfont(60,0,"Atarix");
	setbkmode(TRANSPARENT);
	if (winnerNumber==-1)
	{
		setcolor(EGERGB(255,0,0));
		outtextxy((startX+endX)/2-40,(startY+endY)/2-40,"tie");
	}
	else if (winnerNumber==1)
	{
		setcolor(WHITE);
		outtextxy((startX+endX)/2-160,20,"white win!!");
	}
	else //winnerNumber == 0
	{
		setcolor(BLACK);
		outtextxy((startX+endX)/2-160,20,"black win!!");
	}
	while (1)
	{
		if (getmouse().is_down())
			break;
	}
}

bool GameDirector::isTheGameEnded()
{
	//check whether the player wins
	//win first , tie next
	int tick=0; //record the chess number
	//row
	tick=0;
	for (int i=0;i<mapX;++i)
	{
		if (*(map+mapX*lastY+i) == currentPlayerNumber)
		{
			++tick;
			if (tick>=5)
			{
				winnerNumber = currentPlayerNumber;
				return true;
			}
		}
		else
		{
			tick=0;
		}
	}
	//column
	tick=0;
	for (int i=0;i<mapY;++i)
	{
		if (*(map+i*mapY+lastX) == currentPlayerNumber)
		{
			++tick;
			if (tick>=5)
			{
				winnerNumber = currentPlayerNumber;
				return true;
			}
		}
		else
		{
			tick=0;
		}
	}
	//diagonal
	for (int i=(lastX>lastY?lastX-lastY:0),j=(i?0:lastY-lastX);i<mapX && j<mapY;++i,++j)
	{
		if (*(map+mapX*j+i) == currentPlayerNumber)
		{
			++tick;
			if (tick>=5)
			{
				winnerNumber = currentPlayerNumber;
				return true;
			}
		}
		else
		{
			tick=0;
		}
	}
	for (int i=(lastX>mapY-lastY?lastX+lastY-mapY:0),j=(i?mapY:lastY+lastX);i<mapX && j>=0;++i,--j)
	{
		if (*(map+mapX*j+i) == currentPlayerNumber)
		{
			++tick;
			if (tick>=5)
			{
				winnerNumber = currentPlayerNumber;
				return true;
			}
		}
		else
		{
			tick=0;
		}
	}
	//tie
	if (restBlank <= 0)
	{
		winnerNumber = -1;
		return true;
	}
	return false;
}

PlayerController* GameDirector::getCurrentPlayer()
{
	return player[currentPlayerNumber];
}
