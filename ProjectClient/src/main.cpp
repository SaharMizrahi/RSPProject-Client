#include <Protocol.h>
#include <iostream>
#include <stdio.h>
#include "RSPGameClient.h"
#include "RSPClientCLI.h"
#include "ClientTest.h"
#include "RSPGameTest.h"
using namespace std;
using namespace networkingLab;

int main() {
	/*RSPGameTest* t=new RSPGameTest();
	bool res=t->test();
	if(res)
		cout<<"game Test Succeed"<<endl;
	else
		cout<<"game Test Failed"<<endl;*/

	RSPGameClient* client=new RSPGameClient("gal","gal","login");
	RSPClientCLI* cli=new RSPClientCLI(client);
	cli->start();
	cli->waitForThread();





	return 1;
}


