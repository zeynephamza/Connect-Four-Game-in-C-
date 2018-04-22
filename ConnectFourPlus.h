#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H
#include "ConnectFourAbstract.h"

using namespace std;
using namespace connect;

//namespace plus{
class ConnectFourPlus : public ConnectFourAbstract {
	private:
		int checkStone(char s);
	public:
	ConnectFourPlus() : ConnectFourAbstract(){
	};
	ConnectFourPlus(int width, int height):ConnectFourAbstract(width,height){
	};
};
//}
#endif 
