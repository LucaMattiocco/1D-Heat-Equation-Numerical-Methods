#include "ImplicitMethods.h"
#include <fstream>

std::vector<double> ImplicitMethods::thomasAlgorithm(std::vector<double> x_n, std::vector<double> lower_diag, std::vector<double> diag, std::vector<double> upper_diag)
{

	//! The thomasAlgorithm function implements the Thomas algorithm (also known as the Tridiagonal Matrix Algorithm or TDMA)
	//! to solve a tridiagonal system of linear equations of the form Ax = b.

	//! Parameters:
	//! - x_n: The solution vector, initially containing the right-hand side (b) and later storing the solution (x).
	//! - lower_diag: The vector representing the lower diagonal of the tridiagonal matrix A.
	//! - diag: The vector representing the main diagonal of A.
	//! - upper_diag: The vector representing the upper diagonal of A.

	//! The function first checks that the sizes of x_n, lower_diag, diag, and upper_diag are compatible.

	//! It then proceeds to perform the Thomas algorithm, which consists of a forward sweep and a back substitution.
	//! In the forward sweep, it computes intermediate values diag_star and x_star, which are used to update x_n.
	//! In the back substitution, it calculates the final solution for x_n.

	//! The function returns the solution vector x_n, which now contains the solution to the tridiagonal system.

	int size_of_x_n = x_n.size();

	if (diag.size() != size_of_x_n || lower_diag.size() != size_of_x_n || upper_diag.size() != size_of_x_n)
	{
		throw std::invalid_argument("Vectors x_n, diag, lower_diag, and  upper_diag must have the same size");
	}

	std::vector<double> diag_star(size_of_x_n, 0.0);
	std::vector<double> x_star(size_of_x_n, 0.0);

	//! Modify the coefficients in the first row
	diag_star[0] = upper_diag[0] / diag[0];
	x_star[0] = x_n[0] / diag[0];

	//! Forward sweep
	for (int i = 1; i < size_of_x_n; i++)
	{
		double m = 1.0 / (diag[i] - lower_diag[i] * diag_star[i - 1]);
		diag_star[i] = upper_diag[i] * m;
		x_star[i] = (x_n[i] - lower_diag[i] * x_star[i - 1]) * m;
	}

	//! Back substitution
	x_n[size_of_x_n - 1] = x_star[size_of_x_n - 1];
	for (int i = size_of_x_n - 2; i >= 0; i--)
	{
		x_n[i] = x_star[i] - diag_star[i] * x_n[i + 1];
	}

	return x_n;
};

std::vector<double> ImplicitMethods::laasonenMethod(double deltax, int numberOfPoint, double tsurf, double tinit, double D, double deltat, double t, std::vector<double> temperatureInit)
{
	//! This function, laasonenMethod, implements the Laasonen implicit method for solving a 1D heat conduction problem.
	//! It calculates the temperature distribution at discrete points in a rod over time, using implicit finite-difference equations.

	//! Parameters:
	//! - deltax: Spatial step size
	//! - numberOfPoint: Number of discrete points in the rod
	//! - tsurf: Surface temperature (boundary condition)
	//! - tinit: Initial temperature (Inside the wall)
	//! - D Thermal diffusivity
	//! - deltat: Time step size
	//! - t: Total simulation time
	//! - temperatureInit: Initial temperature distribution at discrete points

	//! The method starts by initializing the diagonals and the initial temperature distribution.

	//! It then performs time-stepping using the Laasonen implicit scheme.
	//! At each time step, it updates the boundary conditions, applies the implicit method using the Thomas algorithm,
	//! and proceeds to the next time step.

	//! Finally, it returns the temperature distribution at the end of the simulation.

	//! Define theta constant and the number time of time step
	double theta = D * (deltat / (deltax * deltax));
	int numStep = static_cast<int>(t / deltat);

	// clear the diagonal in case of an other call of this method without initialisation
	im_diagN_minus_1.clear();
	im_diag.clear();
	im_diagN_plus_1.clear();

	//! Fill out the initial vector
	im_temperatureL = temperatureInit;

	//! Fill out the three diagonals

	im_diagN_minus_1.push_back(0);
	im_diag.push_back(1 + (2 * theta));
	im_diagN_plus_1.push_back(-theta);

	for (int i = 1; i < numberOfPoint - 1; i++)
	{
		im_diagN_minus_1.push_back(-theta);
		im_diag.push_back(1 + (2 * theta));
		im_diagN_plus_1.push_back(-theta);
	}
	im_diagN_minus_1.push_back(-theta);
	im_diag.push_back(1 + (2 * theta));
	im_diagN_plus_1.push_back(0);

	//! resset of x_n at each time step
	for (int step = 1; step < numStep; step++)
	{
		//! Add boundary conditions for each time-step
		im_temperatureL[0] += theta * tsurf;				 // Left boundary Condition
		im_temperatureL[numberOfPoint - 1] += theta * tsurf; // Right Boundary Condition
		im_temperatureL = ImplicitMethods::thomasAlgorithm(im_temperatureL, im_diagN_minus_1, im_diag, im_diagN_plus_1);
	}

	return im_temperatureL;
};

std::vector<double> ImplicitMethods::crankNicholsonMethod(double deltax, int numberOfPoint, double tsurf, double tinit, double D, double deltat, double t, std::vector<double> temperatureInit)
{
	//! Define theta constant and the number of time steps
	double lambda = D * (deltat / (2.0 * deltax * deltax));
	int numStep = static_cast<int>(t / deltat);

	//! Fill out the initial vector
	im_temperatureCN = temperatureInit;

	//! Create intermediary vector for calculations
	std::vector<double> calculus_vector;

	//! Clear the diagonal in case of another call to this method without initialization
	im_diagN_minus_1.clear();
	im_diag.clear();
	im_diagN_plus_1.clear();

	//! Set up the tridiagonal matrix diagonals
	im_diagN_minus_1.push_back(0);
	im_diag.push_back(1 + 2 * lambda);
	im_diagN_plus_1.push_back(-lambda);

	for (int i = 1; i < numberOfPoint - 2; i++)
	{
		im_diagN_minus_1.push_back(-lambda);
		im_diag.push_back(1 + 2 * lambda);
		im_diagN_plus_1.push_back(-lambda);
	}

	im_diagN_minus_1.push_back(-lambda);
	im_diag.push_back(1 + 2 * lambda);
	im_diagN_plus_1.push_back(0);

	//! Perform the Crank-Nicholson method
	for (int step = 1; step < numStep; step++)
	{
		for (int i = 0; i < numberOfPoint - 1; i++)
		{
			if (i == 0)
			{
				calculus_vector.push_back((1 - 2 * lambda) * im_temperatureCN[i + 1] + lambda * im_temperatureCN[i + 2] + lambda * (im_temperatureCN[i] + tsurf));
			}
			else if (i == numberOfPoint - 2)
			{
				calculus_vector.push_back((1 - 2 * lambda) * im_temperatureCN[i - 1] + lambda * im_temperatureCN[i - 2] + lambda * (im_temperatureCN[i] + tsurf));
			}
			else
			{
				calculus_vector.push_back(lambda * im_temperatureCN[i] + (1 - 2 * lambda) * im_temperatureCN[i + 1] + lambda * im_temperatureCN[i + 2]);
			}
		}

		//! Use the Thomas algorithm to solve the tridiagonal system
		calculus_vector = ImplicitMethods::thomasAlgorithm(calculus_vector, im_diagN_minus_1, im_diag, im_diagN_plus_1);

		//! Update the 'temperatureInit' vector for the next time step
		for (int j = 0; j < calculus_vector.size(); j++)
		{
			im_temperatureCN[j + 1] = calculus_vector[j];
		}

		//! Clear the intermediary vector for the next iteration
		calculus_vector.clear();
	}

	return im_temperatureCN;
}

void ImplicitMethods::saveCSV(std::string e_fileName, std::vector<double> temperature)
{
	std::ofstream myfile;
	myfile.open(e_fileName);
	for (int i = 0; i < temperature.size(); i++)
	{
		myfile << temperature[i] << "\n";
	}
	myfile.close();
};