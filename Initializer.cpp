#include "Initializer.h"

// Constructor
Initializer::Initializer(double newDeltat, double newt)
{

	i_deltat = newDeltat;
	i_t = newt;
};

// Delta t function
double Initializer::getDeltat()
{
	return i_deltat;
};

void Initializer::setDeltat(double newDeltat)
{
	i_deltat = newDeltat;
};

// t function
double Initializer::gett()
{
	return i_t;
};

void Initializer::sett(double new_t)
{
	i_t = new_t;
};

// Initializer Tinit vector function

std::vector<double> Initializer::getT_values(int numberOfPoints, double T_surf, double T_init)
{
	std::vector<double> temperature;
	temperature.push_back(T_surf);
	for (int i = 1; i < numberOfPoints - 1; i++)
	{
		temperature.push_back(T_init);
	}
	temperature.push_back(T_surf);

	return temperature;
};
