/*
 * ClientTest.cpp
 *
 *  Created on: Sep 4, 2017
 *      Author: user
 */

#include "ClientTest.h"
#include "RSPGameClient.h"
#include <string.h>
#include <sstream>
namespace networkingLab {

ClientTest::ClientTest() {
	// TODO Auto-generated constructor stub

}

bool ClientTest::test() {

	RSPGameClient* client=new RSPGameClient("sahar","sahar","login");
	bool res=client->loginOrRegister();
	if(res)
	{
		char* msg="9";//It's TEST_ECHO (Protocol.h)
		int s=strlen(msg);
		TCPSocket* sock=client->getSocket();
		sock->write((char*)&s, 4);
		sock->write(msg, s);
		char buf[100];
		memset(buf,0,100);
		sock->read((char*)&s, 4);
		sock->read(buf, s);
		if(strcmp("TEST ECHO",buf)==0)
			return true;
		else
			return false;
	}
	else
		return false;
}

ClientTest::~ClientTest() {
	// TODO Auto-generated destructor stub
}

} /* namespace networkingLab */
