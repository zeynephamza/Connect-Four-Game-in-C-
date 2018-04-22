#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H

#include<vector>
#include "ConnectFourPlus.h"

using namespace std;


class ConnectFourPlusUndo : public ConnectFourPlus {
	private:
		void playTurn();
		void undo();
		vector <Cell**> oldCells; /* For keeping the all played cells for undo*/
	public:
		ConnectFourPlusUndo() : ConnectFourPlus(){
		};
		ConnectFourPlusUndo(int width, int height):ConnectFourPlus(width,height){
		};
	
};

#endif 
