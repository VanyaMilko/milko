#pragma once
#include <pch.h>
#include <iostream>

using namespace std;

class Car
{
	string name;
	string type;
	double cost;
	double mark;
	int power;
	int id;

public:
	Car();
	Car(const Car& o);
	Car(string _name, string _type, double _cost, double _mark, int _kalory);

	void SetName(const string& _name);
	string GetName() const;

	void SetType(const string& _type);
	string GetType() const;

	void SetMark(const double& _mark);
	const double& GetMark() const;

	void SetCost(const double& _cost);
	const double& GetCost() const;

	void SetPower(const double& _kalory);
	const double& GetPower() const;

	void SetId(const int i) { id = i; }
	int GetId()const { return id; }

	bool operator==(const Car& o);

	template<class Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar& name;
		ar& type;
		ar& cost;
		ar& mark;
		ar& power;
		ar& id;
	}
};

