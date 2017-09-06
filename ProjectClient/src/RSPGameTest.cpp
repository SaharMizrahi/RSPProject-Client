/*
 * RSPGameTest.cpp
 *
 *  Created on: Sep 6, 2017
 *      Author: user
 */

#include "RSPGameTest.h"
#include "RSPGameClient.h"
#include "UDPSocket.h"
#include "Protocol.h"
#include <string.h>

namespace networkingLab {

RSPGameTest::RSPGameTest() {
	// TODO Auto-generated constructor stub

}

bool RSPGameTest::test() {

	bool res=false;
	RSPGameClient* client1=new RSPGameClient("sahar","sahar","login");
	res=client1->loginOrRegister();
	if(res)
	{
		client1->setUserAvailability(true);
		RSPGameClient* client2=new RSPGameClient("gal","gal","login");
		res=client2->loginOrRegister();
		sleep(5);
		if(res)
		{
			int p1,p2;
			p2=client2->startGameWith(client1->getUsername());
			sleep(2);
			//get new ports
			char buf[100];
			int s;
			client1->getSocket()->read((char*)&s, 4);
			client1->getSocket()->read(buf, s);
			client1->getSocket()->read((char*)&p1, 4);
			//game start
			UDPSocket* sock1=new UDPSocket(client1->getSocket()->getPort());
			UDPSocket* sock2=new UDPSocket(client2->getSocket()->getPort());
			if(sock1!=NULL||sock2!=NULL)
			{
				char* msg1="s";
				char* msg2="p";
				sock1->sendTo(msg1, SERVER_IP, p1);
				sleep(1);
				char buf1[10],buf2[10];
				sock2->recv(buf1, 10);
				if(strcmp(msg1,buf1)==0)
				{
					sock2->sendTo(msg2, SERVER_IP, p2);
					sleep(2);
					sock1->recv(buf2, 10);
					if(strcmp(buf2,msg2)==0)
					{
						int x=client1->policy(SCISSORS, PAPER);
						if(x==1)
							return true;
						else
						{
							cout<<"game result don't correct"<<endl;
							return false;
						}
					}
					else
					{
						cout<<"client 2 msg didn't send properly"<<endl;
						return false;
					}
				}
				else
				{
					cout<<"client 1 msg didn't send properly"<<endl;
					return false;
				}
			}
			else
			{
				cout<<"one of the udp sockets is null"<<endl;
				return false;
			}



		}
		else
		{
			cout<<"client2 can't connect to server"<<endl;
			return false;
		}
	}
	else
	{
		cout<<"client1 can't connect to server"<<endl;
		return false;
	}
}

RSPGameTest::~RSPGameTest() {
	// TODO Auto-generated destructor stub
}

} /* namespace networkingLab */
