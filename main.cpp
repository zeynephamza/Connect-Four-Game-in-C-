/*--------------------------------------------------------------------------*/
/* HW05_151044011_Zeynep_Hamza												*/
/*                                                                          */
/* ---------																*/
/* Created on 26/11/2017 by Zeynep Hamza									*/
/*																			*/
/* Description																*/
/* -----------																*/
/*    This is a continued game of Connect Four which is given in hw3. 		*/
/* 		   In this homework you can play the game 3 different mode 'U' undo,*/
/*		   'P' for horizontal and vertical, 'D' for diagonals.  			*/
/*		   															        */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*Includes																	*/
/*--------------------------------------------------------------------------*/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"

using namespace std;
using namespace connect;
using namespace diag;
//using namespace plus;

int main(){
    char choice;
    int width;
	int height; 
	
	cout<<"Choose a game mode (D for diagonal, P for plus, U for undo):";
    cin>>choice;
    while(!(choice=='D' || choice=='P' || choice=='U')){
    	cerr<<"Invalid choice!"<<endl;
    	cout<<"Choose a game mode (D for diagonal, P for plus, U for undo):";
   		cin>>choice;
    }
	
	cout<<"Enter width size: ";
	cin>>width;
	cout<<"Enter height size: ";
	cin>>height;

	while(width<=0 || height<=0 ){
		cerr<<"Invalid width or height!"<<endl;
		cin.clear();                   /* This is for taking board size only */
		cin.ignore(1000, '\n');		   /* integer values, not characters.    */
		cout<<"Enter width size: ";
		cin>>width;
		cout<<"Enter height size: ";
		cin>>height;

	}
    ConnectFourAbstract *cf;
    
    if(choice=='D'){
    	cf=new ConnectFourDiag(width,height);
    }else if(choice=='P'){
    	cf=new ConnectFourPlus(width,height);
    }
    else if(choice=='U'){
    	cf=new ConnectFourPlusUndo(width,height);
    }
    else{
    	cerr<<"Invalid choice!"<<endl;
    }
    cf->displayBoard();
	cf->playGame();
  
	return 0;
}

