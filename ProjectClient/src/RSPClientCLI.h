/*
 * RSPClientCLI.h
 *
 *  Created on: Aug 23, 2017
 *      Author: user
 */

#ifndef SRC_RSPCLIENTCLI_H_
#define SRC_RSPCLIENTCLI_H_
#include "MThread.h"
#include "RSPGameClient.h"
#include "UDPSocket.h"
#include<iostream>
#include<stdio.h>


using namespace std;
namespace networkingLab {

class RSPClientCLI: public MThread {
	RSPGameClient* client;
	bool isDone;
public:
	/**
	 * This method get the client choice for the RSP game ,send it to the other player and return it.
	 */
	int getClientRSPChoice(UDPSocket* sock,int port);
	/**
	 * After a game start this method handle the game order and policy
	 */
	void handleGame(int newPort);
	/**
	 * This method run the CLI interface for the user
	 */
	virtual void run();
	RSPClientCLI(RSPGameClient* c);
	virtual ~RSPClientCLI();
};

} /* namespace networkingLab */

#endif /* SRC_RSPCLIENTCLI_H_ */
