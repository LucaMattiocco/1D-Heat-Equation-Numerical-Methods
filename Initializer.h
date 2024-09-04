#pragma once
#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <iostream>
#include <vector>

/**
 * @class Initializer
 * @brief This class initializes the initial temperature vector, total simulation time, and time step value.
 *
 */

class Initializer
{

private:
	//! Time step
	double i_deltat;
	//! Total time of the simulation
	double i_t;

public:
	Initializer(double new_deltat, double new_t);

	//! Get and set Methods for delta t
	double getDeltat();
	void setDeltat(double new_deltat);

	//! Get and set Methods for t
	double gett();
	void sett(double new_t);

	/**
	 * @brief This function sets up the initial temperature vector.
	 * @param numberOfPoints Total number of points to discretize.
	 * @param T_surf Temperature at x=0 and x=L
	 * @param T_init Temperature at t=0
	 * @return Initial temperature distribution
	 */
	std::vector<double> getT_values(int numberOfPoints, double T_surf, double T_init);
};
#endif //