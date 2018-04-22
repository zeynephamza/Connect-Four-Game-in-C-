#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include "Cell.h"

using namespace std;
using namespace cell;
namespace connect{ /*namespaces*/

class ConnectFourAbstract{
	protected:
		Cell **gameCells;
		int gameOver;
		int width;
		int height;
	    int player;
    	char mode;
		string position;
		char user;
		int j;
		string filename; 
		void findUser();
		void askPosition();
		void saveGame();
		void loadGame();
		void changeTurn();
	public:
		ConnectFourAbstract();
		ConnectFourAbstract(int width, int height);
		ConnectFourAbstract(string filename);
		~ConnectFourAbstract();
		int isGameOver(){
			return gameOver;
		}
		inline void setWidth(int w){
			width=w;
		}
		inline int getWidth()const{
			return width;
		}
		inline void setHeight(int h){
			height=h;
		}
		inline int getHeight() const{
			return height;
		}
		int checkGameOver(char user);
		virtual void read(string filename,int &player, char &mode); /* load */
		virtual void write(string filename,const int &player, const char &mode);/*save*/
		void displayBoard();
		void playGame();
		void play(string position, char user); /* user*/
		void play(); /* Computer */
		int moveStone(int j, char user);
		virtual int checkStone(char s)=0;
		int sameRow( int i,int j,char s);
		int sameColumn( int i,int j,char s);
		int sameAscending(int i,int j,char s);
		int sameDiscending(int i,int j,char s);
		void markRow(int i,int j,char s);
		void markColumn(int i,int j,char s);
		void markAscending(int i, int j, char s);
		void markDiscending(int i, int j, char s);
		int checkFull();
		void initializeGame(int width, int height);
		virtual void playTurn();
		bool operator==(const ConnectFourAbstract& rSide)const;
		
};
}

#endif 
