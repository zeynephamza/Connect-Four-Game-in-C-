#include <iostream>
#include "ConnectFourPlus.h"

using namespace std;
//using namespace plus;

int ConnectFourPlus::checkStone(char s){
	int i,j;
	
	for (i=0;i<height;i++){
		for(j=0;j<width;j++){
            if(sameRow(i,j,s)){
                 markRow(i,j,s);
                 return 1;
            }
               
            else if( sameColumn(i,j,s)){
                markColumn(i,j,s);
                return 1;
            }
        }
    }
    return 0;
}



