#include <Protocol.h>
#include <iostream>
#include <stdio.h>
#include "RSPGameClient.h"
#include "RSPClientCLI.h"
#include "ClientTest.h"
#include "RSPGameTest.h"
#include <string.h>
using namespace std;
using namespace networkingLab;
RSPGameClient* firstInterview();
int main() {
	/*RSPGameTest* t=new RSPGameTest();
	bool res=t->test();
	if(res)
		cout<<"game Test Succeed"<<endl;
	else
		cout<<"game Test Failed"<<endl;*/

	RSPGameClient* client;
	bool ok=false;
	char u[100],p[100],c[100];
	memset(u,0,100);
	memset(p,0,100);
	memset(c,0,100);

	while(!ok)
	{
		cout<<"*****Login Page*****"<<endl;
		cout<<"Enter username: ";
		cin>>u;
		cout<<"Enter password: ";
		cin>>p;
		cout<<"Enter command: ";
		cin>>c;
		if(strcmp(c,"login")==0||strcmp(c,"register")==0)
			ok=true;
		cout<<"********************"<<endl;

	}
	client=new RSPGameClient(u,p,c);
	//RSPGameClient* client=new RSPGameClient("gal","gal","login");
	RSPClientCLI* cli=new RSPClientCLI(client);
	cli->start();
	cli->waitForThread();





	return 1;
}

RSPGameClient* firstInterview()
{
	RSPGameClient* client;
	bool ok=false;
	char u[100],p[100],c[100];
	memset(u,0,100);
	memset(p,0,100);
	memset(c,0,100);

	while(!ok)
	{
		cout<<"Enter username: ";
		cin>>u;
		cout<<"Enter password: ";
		cin>>p;
		cout<<"Enter command: ";
		cin>>c;
		if(strcmp(c,"login")==0||strcmp(c,"register")==0)
			ok=true;

	}
	char* username=new char[strlen(u)+1];
	char* password=new char[strlen(p)+1];
	char* command=new char[strlen(c)+1];

	client=new RSPGameClient(username,password,strdup(command));
	return client;

}


