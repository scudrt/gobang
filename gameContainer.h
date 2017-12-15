namespace container
{
	enum EState
	{
		Playing,Exit
	};
	class playerController
	{
	private:
		;
	public:
		int x,y;
		void getX();
		void getY();
		init(bool);
	};
	class gameDirector
	{
		playerController *currentPlayer,*nextPlayer;
		int playerX,playerY;
		void putChess();
	};
}
