#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H
#include "ConnectFourAbstract.h"

using namespace std;
using namespace connect;
namespace diag{
class ConnectFourDiag : public ConnectFourAbstract{
	private:
		int checkStone(char s);
	public:
	ConnectFourDiag() : ConnectFourAbstract(){
	};
	ConnectFourDiag(int width, int height):ConnectFourAbstract(width,height){
	};
};
}
#endif 
