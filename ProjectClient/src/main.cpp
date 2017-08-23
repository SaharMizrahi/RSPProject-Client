#include <Protocol.h>
#include <iostream>
#include <stdio.h>
#include "RSPGameClient.h"
#include "RSPClientCLI.h"

using namespace std;
using namespace networkingLab;

int main() {
	RSPGameClient* client=new RSPGameClient("gal","gal","login");
	RSPClientCLI* cli=new RSPClientCLI(client);
	cli->start();
	cli->waitForThread();
	/*RSPGameClient* client=new RSPGameClient("gal","gal","login");
	client->start();
	sleep(1000);*/
	/*ifstream in ("src/rank.txt");
	if(in.is_open())
	{
		char buffer[100];
		memset(buffer,0,100);
		string line;
		while(getline(in,line)&&strcmp(line.c_str(),"")!=0)
		{
			strcat(strcat(buffer,line.c_str())," ");


		}
		in.close();
		ofstream out;
		out.open("src/rank.txt", std::ofstream::out | std::ofstream::trunc);
		char* s=strtok(buffer," ");
		while(s!=NULL)
		{
			if(strcmp(s,"gal")==0)
			{
				out.write(s,strlen(s));
				out.write(" ",1);
				std::ostringstream oss;
			    oss<< 800;
			    out.write(oss.str().c_str(),strlen(oss.str().c_str()));
				out.write("\n",1);
				s=strtok(NULL," ");//read and throw the last rank
			}
			else
			{
				out.write(s,strlen(s));
				out.write(" ",1);
				s=strtok(NULL," ");
				out.write(s,strlen(s));
				out.write("\n",1);
			}
			s=strtok(NULL," ");


		}

		out.close();

	}
	else
		cout<<"check"<<endl;*/









	return 1;
}
