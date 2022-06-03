#include <pch.h>
#include "Object.h"

Car::Car()
{
	name = "";
	type = "";
	cost = 0;
	mark = 0;
	power = 0;
	id = 0;
}

Car::Car(const Car& o)
{
	name = o.name;
	type = o.type;
	cost = o.cost;
	power = o.power;
	mark = o.mark;
	id = o.id;
}

Car::Car(string _name, string _type, double _cost, double _mark, int _power)
{
	name = _name;
	type = _type;
	mark = _mark;
	power = _power;
	cost = _cost;
}

void Car::SetName(const string& _name)
{
	name = _name;
}

string Car::GetName()const
{
	return name;
}

void Car::SetType(const string& _type)
{
	type = _type;
}

string Car::GetType()const
{
	return type;
}

void Car::SetMark(const double& _mark)
{
	mark = _mark;
}

const double& Car::GetMark() const
{
	return mark;
}

void Car::SetCost(const double& _cost)
{
	cost = _cost;
}

const double& Car::GetCost() const
{
	return cost;
}


void Car::SetPower(const double& _weight)
{
	power = _weight;
}

const double& Car::GetPower() const
{
	return power;
}

bool Car::operator==(const Car& o)
{
	return name == o.name && type == o.type;
}
