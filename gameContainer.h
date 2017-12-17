class Position
{
private:
	;
public:
	Position();
	Position(int,int);

	int x,y;
};

class PlayerController
{
private:
	bool _isAIPlayer,_isBlackChess;
public:
	PlayerController();
	PlayerController(bool,bool);

	Position getXY();

	bool isBlackChess();
	bool isAIPlayer();
};

class GameDirector
{
private:
	int restBlank;

	//map contain
	int *map;

	//map details
	int mapX,mapY,startX,startY,endX,endY,blockX,blockY;

	//players' details
	int playerX,playerY,currentPlayerNumber,winnerNumber;

	//last operation recorder
	int lastX,lastY;

	//players handler
	PlayerController* player[2];

	//initialize the hole map
	void _makeMap();

public:
	GameDirector();
	GameDirector(Position,Position,Position);
	~GameDirector();

	PlayerController* getCurrentPlayer();

	void addPlayer(bool);
	void changePlayer();
	//true presents success
	bool putChess(Position);

	bool isTheGameEnded();

	void showResult();
};
