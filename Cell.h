#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
namespace cell{ 
class Cell{ 
	protected:
		string position;
		int row;
		char value;
	public:
	/* some constructers */
		Cell();
		Cell(string p, int r, char v);
		Cell(string p, int r);
		Cell(char v);
		void setPosition(string p);
		string getPosition();
		void setRow(int r);
		int getRow() const;
						
		void setValue(char v);
		char getValue()const;
		bool operator==(const Cell& rSide)const;
};
}

#endif 
