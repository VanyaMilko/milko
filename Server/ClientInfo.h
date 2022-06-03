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

	SOCKET connectionSocket; //����� ���������� � ��������
	string lastIp; //��������� IP �������
	unsigned int clientId; //Id ������� � ���� ������
	TypeOfUser type;

public:

	//����� �� ��������� �������� �������� ��� ���� �����
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

