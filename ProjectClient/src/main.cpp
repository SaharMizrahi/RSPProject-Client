#include <Protocol.h>
#include <iostream>
#include <stdio.h>
#include "RSPGameClient.h"
#include "RSPClientCLI.h"
#include "ClientTest.h"
using namespace std;
using namespace networkingLab;

int main() {

	ClientTest* t=new ClientTest();
	bool res=t->test();
	if(res)
		cout<<"Client Test Succeed"<<endl;
	else
		cout<<"Client Test Failed"<<endl;

	/*RSPGameClient* client=new RSPGameClient("gal","gal","login");
	RSPClientCLI* cli=new RSPClientCLI(client);
	cli->start();
	cli->waitForThread();*/





	return 1;
}


