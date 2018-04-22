#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>

#include "Cell.h"

using namespace std;
using namespace cell;
Cell::Cell(){
	position[0]='A';
	row=0;
	value='.';
}
Cell::Cell(string p, int r, char v){
	position=p;
	row=r;
	value=v;
}
Cell::Cell(string p, int r){
	position=p;
	row=r;
}
Cell::Cell(char v){
	value=v;
}
void Cell::setPosition(string p){
	position=p;
}
string Cell::getPosition(){
	return position;
}
void Cell::setRow(int r){
	row=r;
}
int Cell::getRow() const{
	return row;
}
			
void Cell::setValue(char v){
	value=v;
}
char Cell::getValue()const{
	return value;
}

bool Cell::operator==(const Cell& rside)const{
	if(row==rside.row && position==rside.position && value==rside.value)
		return true;
	else 
		return false;
}
