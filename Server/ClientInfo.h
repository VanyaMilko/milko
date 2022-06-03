#pragma once
#include<winsock2.h>
#pragma comment (lib, "ws2_32.lib")
#include<thread>
#include<string>
#include"../SerializableEntities/CommandsBetweenServerAndClient.h"

using namespace std;
class ClientInfo
{
protected:

	SOCKET connectionSocket; //—окет соединени€ с клиентом
	string lastIp; //ѕоследний IP клиента
	unsigned int clientId; //Id клиента в базе данных
	TypeOfUser type;

public:

	// ласс не выполн€ет никакого контрол€ над этим полем
	thread* clientThread;

	ClientInfo();

	ClientInfo(SOCKET connectionSocket, const string& lastIp);

	void setClientId(unsigned int clientId);

	unsigned int getClientId()const;

	SOCKET getConnectionSocket() const;

	string getLastIp()const;

	TypeOfUser getType()const;

	void setTypeOfUser(TypeOfUser type);

	bool operator == (const ClientInfo& other) const;

	bool operator != (const ClientInfo& other) const;

};

