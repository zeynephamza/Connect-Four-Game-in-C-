#include <iostream>
#include "ConnectFourDiag.h"

using namespace std;
using namespace diag;
int ConnectFourDiag::checkStone(char s){
	int i,j;
	
	for (i=0;i<height;i++){
		for(j=0;j<width;j++){
            if(sameAscending(i,j,s)){
                 markAscending(i,j,s);
                 return 1;
            }
               
            else if( sameDiscending(i,j,s)){
                markDiscending(i,j,s);
                return 1;
            }
        }
    }
    return 0;
}

