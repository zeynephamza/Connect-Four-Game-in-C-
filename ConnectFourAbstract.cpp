#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include "ConnectFourAbstract.h"
#include "Cell.h"

using namespace std;
using namespace connect;
using namespace cell;

const int maxRowCount=100; 
const int maxColumnCount=100;
const int connectedStones=4;

void ConnectFourAbstract::displayBoard(){
	int i,j;
	cout<<endl;
	for(j=0;j<width;j++){
		cout<<(char)('A'+j)<<" ";
	}
	cout<<endl;

	for(int i=0;i<height;i++){
		
		for(int j=0;j<width;j++){
			cout<<gameCells[i][j].getValue();
			cout<<" ";
		}
		cout<<endl;
	}
}
ConnectFourAbstract::ConnectFourAbstract(){
	initializeGame(5,5);
}
ConnectFourAbstract::ConnectFourAbstract(int width, int height){
	initializeGame(width,height);
}
ConnectFourAbstract::ConnectFourAbstract(string fn){
	filename=fn;
	char characters[maxRowCount][maxColumnCount];
	int rowCount=0, columnCount=0, columnCountBiggest=0;

	ifstream is(filename);     // open file

    char c;
	while (is.get(c)) {
		
		characters[rowCount][columnCount]=c;
		
		if(c=='\n'){
			rowCount++;
			if(columnCount>columnCountBiggest)
				columnCountBiggest=columnCount;
			columnCount=0;
		}
		else 
			columnCount++;
		
	} 
	is.close();
	initializeGame(columnCountBiggest,rowCount);
	for (int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			gameCells[i][j].setValue(characters[i][j]);
		}
	}
	displayBoard();
}
ConnectFourAbstract::~ConnectFourAbstract(){
	for (int i = 0; i < height; i++){
			delete[] gameCells[i];
			gameCells[i]=nullptr;
		
	}
	delete[] gameCells;
	gameCells=nullptr;
}
bool ConnectFourAbstract::operator==(const ConnectFourAbstract& connect)const{
	
	for (int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(!(gameCells[i][j]==connect.gameCells[i][j])) 
				return false;
		}
	} 
	return true;
}

void ConnectFourAbstract::initializeGame(int width, int height){
	cout<<"Enter 'P' for two player,"<<endl<<"'C' for againts computer: ";
    cin>>mode;
    cin.clear();                   
	cin.ignore(1000, '\n');	
    cout<<endl;
    while(mode!= 'P' && mode!= 'C'){
    	cerr<<"Invalid key entered!"<<endl;
    	cout<<"Please enter 'P' for two player, 'C' for againts computer: ";    
    	cin>>mode;  
    	cin.clear();                   
		cin.ignore(1000, '\n');	
	}
	
	setWidth(width);
	setHeight(height);
	/* initialize the 2D array */

	gameCells = new Cell *[height];
	
	for (int i = 0; i < height; i++){
		gameCells[i] = new Cell[width];
		for(int j = 0; j < width; j++){
			gameCells[i][j].setValue('*');
		}
	}
	player=1;	
	gameOver=0;
	srand(time(NULL));
	

}
void ConnectFourAbstract::findUser(){
	if(player==1){
		   user='X'; /* First player's stone */
		}
	else
	   user='O';
        

}
void ConnectFourAbstract::saveGame(){

	cout<<"Enter the filename you want to save: ";
	cin>>filename;
	cout<<"FILENAME"<<filename<<endl;
	write(filename,player,mode);            	
	cout<<"Game has been saved."<<endl;

}
void ConnectFourAbstract::loadGame(){
	
	read(filename,player,mode);
	cout<<"Loaded game:"<<endl;
	displayBoard();

}
void ConnectFourAbstract::askPosition(){
	cout<<"Player "<<player<<" position: "; /* which player's turn*/
    cin>>position;
    //cout<<"temp1:"<<position<<endl;
    if(position.length()==0 || cin.eof())
		exit(0);
}

void ConnectFourAbstract::changeTurn(){
	if(player==1)/*Changing the turn*/
		player=2;
	else
		player=1;
}
void ConnectFourAbstract::playTurn(){

	findUser();
	if(mode=='C' && player==2){
         play();         
    }else{
            askPosition();
            play(position, user);
            
      }
     if(position=="SAVE"){ //SAVE
        	
        	saveGame();
        	askPosition();
    	}
	
    	if(position=="LOAD"){
    		loadGame();
        	return;
    	}
        
        gameOver=checkGameOver(user);
        
        changeTurn();
        
        displayBoard();
}

void ConnectFourAbstract::playGame(){
	
	while(!isGameOver()){
		playTurn();
	}
}


int ConnectFourAbstract::checkGameOver(char user){
	
	if(checkStone(user)){
        cout<<"Player "<<player<<" won!\n";
        return 1;
    }
	else if(checkFull()){
		cout<<"Draw! All board cells are full.\n"<<endl;
		return 1;
	}
	else 
		return 0;
	
}


/* Calculates if the four stones next to each other in same rows, 
		same column, same cross*/
int ConnectFourAbstract::sameRow( int i,int j,char s){
    int same=0;
    int k;
    
    if(j+connectedStones>width){
    	return 0;
    }
    if( gameCells[i][j].getValue()==s){

        same=1;
        for(k=1; k<connectedStones && j+k<width;k++){					
            if(gameCells[i][j+k].getValue()!=s){
                same=0;
                break;
            }
        }
    }
    return same;
}
int ConnectFourAbstract::sameColumn( int i,int j,char s){
    int same=0;
    int k;
    if(i+connectedStones>height)
    	return 0;
    if( gameCells[i][j].getValue()==s){
        same=1;
        for(k=1; k<connectedStones && i+k<height;k++){	
            if(gameCells[i+k][j].getValue()!=s){
            	
                same=0;
                break;
            }
        }
    }
    return same;
}
int ConnectFourAbstract::sameAscending( int i,int j,char s){
    int same=0;
    int k;
    
    if(i+connectedStones>height || j+connectedStones>width )
    	return 0;
    
    if( gameCells[i][j].getValue()==s){
        same=1;
        for(k=1; k<connectedStones && i+k<height && j+k<width;k++){
        	cout<<gameCells[i+k][j+k].getValue();						
            if(gameCells[i+k][j+k].getValue()!=s){
                same=0;
                break;
            }
        }
    }
    return same;
}
int ConnectFourAbstract::sameDiscending( int i,int j,char s){
    int same=0;
    int k;
    
    if(i+connectedStones>height || j-connectedStones<=-1)
    	return 0;
    
    if( gameCells[i][j].getValue()==s){
        same=1;
        for(k=1; k<connectedStones && i+k<height && j-k>=0;k++){								
            if(gameCells[i+k][j-k].getValue()!=s){
                    same=0;
                    break;
            }
        }
    }
    return same;
}
/* Converting the stone to small which player has been won */
void ConnectFourAbstract::markRow(int i, int j, char s){
	char ss=s+('a'-'A');
    for (int k=0; k<connectedStones && j+k<width; k++){
        gameCells[i][j+k].setValue(ss);
    }
}
void ConnectFourAbstract::markColumn(int i, int j, char s){
	char ss=s+('a'-'A');
    for (int k=0; k<connectedStones && i+k<height; k++){
        gameCells[i+k][j].setValue(ss);
    }
}
void ConnectFourAbstract::markAscending(int i, int j, char s){
	char ss=s+('a'-'A');
    for (int k=0; k<connectedStones && i+k<height; k++){
        gameCells[i+k][j+k].setValue(ss);
    }
}
void ConnectFourAbstract::markDiscending(int i, int j, char s){
	char ss=s+('a'-'A');
    for (int k=0; k<connectedStones && i+k<height && j-k>=0; k++){
        gameCells[i+k][j-k].setValue(ss);
    }
}

int ConnectFourAbstract::checkFull(){
	int full=1;
	for (int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if(gameCells[i][j].getValue()=='*'){
				full=0;
			}
		}
	}
	
	return full;
}

void ConnectFourAbstract::play(string position, char user){

	int j;
	string temp;
	if(position=="SAVE" || position==filename || position=="LOAD" || position=="UNDO")
		return;
	j=((int)(position[0]-'A')); /* player's move converts to integer */
	
    //cout<<"p:"<<position<<"j: " <<j<<endl;
    if(j<0 || j>=width ){
        cerr<<"Invalid column: "<<position<<endl;
		cout<<"Player "<<player<<" position: "; /* which player's turn*/
		cin.clear();                   
		cin.ignore(1000, '\n');	
		cin>>position;
		if(position.length()==0 || cin.eof())
    		exit(0);
        play(position, user);
        
    }
  	
    if(!moveStone(j,user)){
        cerr<<"Selected column is full!"<<endl;
        cout<<"Player "<<player<<" position: "; /* which player's turn*/
    	cin>>position;
    	cout<<"temp4:"<<temp<<endl;
    	if(position.length()==0 || cin.eof())
    		exit(0);
        
        play(position,user);
        
    }

}

void ConnectFourAbstract::play(){
	string position;
	int j;
	position[0]='A'+rand()%width; /* computer move is 0 to board size    */
	j=((int)(position[0]-'A')); /*   player's move converts to integer   */
	if(!moveStone(j,'O')){
		play();
	}
}

/* Puts the stone where is chosen coloumn*/
int  ConnectFourAbstract::moveStone(int j, char user){
	int i;
	for (i=height-1;i>=0;i--){
		
		if(gameCells[i][j].getValue()=='*'){
			gameCells[i][j].setValue(user);
			break;
		}          
	}
    if(i<0)
        return 0;
    else 
        return 1;
         
}


void ConnectFourAbstract::read(string filename,int &player, char &mode){
	char c;
	int i,j;
	
	ifstream loadedFile;
	
	loadedFile.open(filename.c_str());
	loadedFile.get(c);	/* Reading a char from saved file first saved   */
	width=c-'0';	/*		character(which is board size).  		*/
	loadedFile.get(c);
	height=c-'0';		/*	And turns it to an integer value	   		*/
	
						
	loadedFile.get(c);  /* Takes and assignes second character in saved */
	player=c-'0';		/*	file(which is player data).					*/

	loadedFile.get(c);	/* Takes and assignes third char and assings it */
	mode=c;
	
	/* Loads the saved board */
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			
			loadedFile.get(c);
			gameCells[i][j].setValue(c);
		}
	}	
	loadedFile.close();
}
void ConnectFourAbstract::write(string filename, const int &player, const char &mode){
	int i,j;
	ofstream savedFile;
	
	savedFile.open(filename.c_str()); /* file opening*/
	savedFile<<width;    /*    saving board size,       */ 
	savedFile<<height;
	savedFile<<player;	     /*    which player's turn and  */
	savedFile<<mode;	     /*    pvp or pvc.              */
	
	 /*    saving board       */ 
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			savedFile<<gameCells[i][j].getValue();
		}
	}
	
	savedFile.close();
}

