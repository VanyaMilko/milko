#pragma once
#include<string>
using namespace std;
class Client
{
protected:

	int id;
	string login;
	string password;

public:

	Client();
	Client(const string& login, const string& password);
	Client(const Client& other);
	virtual ~Client();
	void setId(int id);
	int getId()const;
	void setLogin(const string& login);
	void setPassword(const string& password);
	string getPasword()const;
	string getLogin()const;

	template<class Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar& id;
		ar& login;
		ar& password;
	}

};

