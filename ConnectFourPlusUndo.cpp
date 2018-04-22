#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>

#include "ConnectFourPlusUndo.h"


void ConnectFourPlusUndo::undo(){
/*	cout<<"undoing..."<<endl;
	cout<<endl<<" displaying oldCell.."<<endl; 

	cout<<endl;
	for(j=0;j<width;j++){
		cout<<(char)('A'+j)<<" ";
	}
	cout<<endl;
	for(int k=0;k<oldCells.size();k++){
		Cell **elementCells=oldCells[k];
		for(int i=0;i<height;i++){
		
			for(int j=0;j<width;j++){
				cout<<elementCells[i][j].getValue();
				cout<<" ";
			}
			cout<<endl;
		}
	}*/
	if(oldCells.size()==1){ /* for the segment error control */
		gameCells = new Cell *[height];
	
		for (int i = 0; i < height; i++){
			gameCells[i] = new Cell[width];
			for(int j = 0; j < width; j++){
				gameCells[i][j].setValue('*');
			}
		}
		displayBoard();
		return;
	}
	/* deleting the undoed cell */
		oldCells.pop_back(); 
	/* Turns back to previus cell*/
	Cell **sourceCells=oldCells[oldCells.size()-1];
	for (int i = 0; i < height; i++){
		
		for(int j = 0; j < width; j++){
			gameCells[i][j].setRow(sourceCells[i][j].getRow());
			gameCells[i][j].setPosition(sourceCells[i][j].getPosition());
			gameCells[i][j].setValue(sourceCells[i][j].getValue());
		}
	} 
	
	displayBoard();

}


void ConnectFourPlusUndo::playTurn(){
	findUser();
	if(mode=='C' && player==2){
         play();
    }else{
            askPosition();
            play(position, user);
            
	}
	if(position=="SAVE"){ //SAVE
	
		saveGame();
		changeTurn();
	}
	if(position=="UNDO"){
		undo();
		changeTurn();		
		return;
	}
	if(position==filename){
		loadGame();
		return;
	}


	gameOver=checkGameOver(user);

	changeTurn();
	/* a temp cell for every moves recording*/
	Cell **copyCells= new Cell *[height];
	/* Copy the board (cell)*/
	for (int i = 0; i < height; i++){
		copyCells[i] = new Cell[width];
		for(int j = 0; j < width; j++){
			copyCells[i][j].setRow(gameCells[i][j].getRow());
			copyCells[i][j].setPosition(gameCells[i][j].getPosition());
			copyCells[i][j].setValue(gameCells[i][j].getValue());
		}
	}
	oldCells.push_back(copyCells); /*Addsthe current cell to another temp cell*/
	
	displayBoard();

}
