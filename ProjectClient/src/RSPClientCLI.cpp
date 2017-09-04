/*
 * RSPClientCLI.cpp
 *
 *  Created on: Aug 23, 2017
 *      Author: user
 */

#include "RSPClientCLI.h"
#include <string.h>
#include "Protocol.h"
#include "TCPSocket.h"
namespace networkingLab {

RSPClientCLI::RSPClientCLI(RSPGameClient* c) {
	// TODO Auto-generated constructor stub
	client=c;
	isDone=true;

}

void RSPClientCLI::run() {

	isDone=false;
	if(client!=NULL)
	{
		bool res=client->loginOrRegister();
		if(res)
		{
			cout<<client->getUsername()<<" successfully connected to server"<<endl;
			while(!isDone)
			{
				cout<<"\n*****MENU*****\n<1> show online users <2> show high scores <3> <username> start game with user <4> start game with random user <5> set user available for game <6> set user un-available for games <7> exit\n";
				string str;
				cout<<this->client->getUsername()<<":";
				cin>>str;
				cin.clear();
				fflush(stdin);
				char buffer[strlen(str.c_str())+1];
				strcpy(buffer,str.c_str());
				char* cmd=strtok(buffer," ");
				int c=atoi(cmd);
				switch(c)
				{
				case SHOW_HS:
					client->showHighScores();
					break;
				case SHOW_USERS:
					client->showUsers();
					break;
				case START_GAME_WITH_USER:
				{
					string username;
					cin>>username;
					char u[100];
					strcpy(u,username.c_str());
					handleGame(client->startGameWith(u),u);
					break;
				}
				case START_GAME_WITH_RANDOM:
				{
					handleGame(client->startGameWith(NULL),"Random User");
					break;
				}
				case SET_USER_AVAILABLE:
					client->setUserAvailability(true);
					sleep(1);
					int otherPort;
					int s;
					char c[100];
					client->getSocket()->read((char*)&s, 4);
					client->getSocket()->read(c, s);
					client->getSocket()->read((char*)&otherPort, 4);//wait for incoming game
					if(otherPort!=-1)
					{
						handleGame(otherPort,c);

					}

					break;
				case SET_USER_UNAVAILABLE:
					client->setUserAvailability(false);
					break;
				case DISCONNECT:
					client->disconnectFromServer();
					cout<<"Disconnecting from the server, thank you for playing :-)"<<endl;
					sleep(2);
					isDone=true;
					break;
				default:
					cout<<"Wrong command,try again.."<<endl;
					break;
				}
			}

		}
		else
		{
			cout<<"Can't connect to server...try again, closing program!"<<endl;
			sleep(3);

		}
	}
}

void RSPClientCLI::handleGame(int newPort,char* username) {

	UDPSocket* mySock=new UDPSocket(this->client->getSocket()->getPort());
	int c1,c2;
	int res=0;
	if(mySock!=NULL)
	{
		cout<<"Starting a game with "<<username<<endl;
		if(this->client->getSocket()->getPort()>newPort)
		{
			c1=getClientRSPChoice(mySock,newPort);
			c2=client->recvFromOtherUser(mySock);

		}
		else
		{
			c2=client->recvFromOtherUser(mySock);
			c1=getClientRSPChoice(mySock,newPort);

		}
		if(c1==BYEBYE||c2==BYEBYE)//finish game
		{
			if(c2==BYEBYE)
				cout<<"Other player quit the game..game ends!"<<endl;
		}
		else
		{
			res+=client->policy(c1, c2);

		}

		char* result;
		if(res==0)
		{
			result="8 draw";
		}
		else if(res>0)
		{
			result="8 win";

		}
		else if(res<0)
		{
			result="8 lose";

		}
		int size=strlen(result);
		client->getSocket()->write((char*)&size, 4);
		client->getSocket()->write(result, size);
	}
	else
	{
		cout<<"Can't run RSP game,try again.."<<endl;
	}

}

int RSPClientCLI::getClientRSPChoice(UDPSocket* sock,int port) {
	cout<<"Choose one: r-rock s-scissors p-paper b-exit undefined choice will cause automatic choosing rock"<<endl;
		cout<<this->client->getUsername()<<": ";
		char buf[10];
		memset(buf,0,10);
		cin>>buf;

		if(strcmp(buf,"s")==0||strcmp(buf,"scissors")==0)
		{
			char*msg="s";
			sock->sendTo(msg, SERVER_IP, port);

			return SCISSORS;
		}
		else if(strcmp(buf,"p")==0||strcmp(buf,"paper")==0)
		{
			char*msg="p";
			sock->sendTo(msg, SERVER_IP, port);
			return PAPER;
		}
		else if(strcmp(buf,"b")==0||strcmp(buf,"exit")==0)
		{
			char*msg="b";
			sock->sendTo(msg, SERVER_IP, port);
			return BYEBYE;
		}
		else//rock
		{
			char*msg="r";
			sock->sendTo(msg, SERVER_IP, port);
			return ROCK;
		}
}

RSPClientCLI::~RSPClientCLI() {
	// TODO Auto-generated destructor stub
}

} /* namespace networkingLab */
