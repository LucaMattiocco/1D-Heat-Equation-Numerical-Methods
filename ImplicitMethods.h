#pragma once
#ifndef IMPLICITMETHODS_H
#define IMPLICITMETHODS_H

#include <iostream>
#include <vector>
#include <string>

/**
 * @class ImplicitMethods
 * @brief This class employs Laasonen and Cranck-Nicholson explicit schemes to solve the 1D heat equation
 *
 */

class ImplicitMethods
{
private:
    //! Attribute for data storage for lower diagonal coefficient
    std::vector<double> im_diagN_minus_1;
    //! Attribute for data storage for  diagonal coefficient
    std::vector<double> im_diag;
    //! Attribute for data storage for upper diagonal coefficient
    std::vector<double> im_diagN_plus_1;
    //! Attribute for storing Laasonen resulting temperature data.
    std::vector<double> im_temperatureL;
    //! Attribute for storing Crank-Nicholson resulting temperature data.
    std::vector<double> im_temperatureCN;

public:

    /**
     * @brief This function applies the thomas algorithm to solve tridiagonal system equation
     * @param  x_n Right part matrix of the system
     * @param lower_diag Lower diagonal of the tridiagonal matrix
     * @param diag Diagonal of the tridiagonal matrix
     * @param upper_diag Upper diagonal of the tridiagonal matrix
     * @return The solution vector of the systeme
    */
    // Thomas algorithm resolution: takes a vector T^{n} and return the vector T^{n+1}
    std::vector<double> thomasAlgorithm(std::vector<double> x_n, std::vector<double> lower_diag, std::vector<double> diag, std::vector<double> upper_diag);

    //! Methods
    /**
     * @brief This function utilizes the Dufort-Frankel scheme to solve the 1D heat equation using the Thomas algorithm.
     * @param deltax Grid step.
     * @param numberOfPoint Total number of points to discretize.
     * @param tsurf  Temperature at x=0 and x=L
     * @param tinit Temperature at t=0
     * @param D Coefficient.
     * @param deltat Time step.
     * @param t Total simulation time.
     * @param temperatureInit Initial temperature distribution vector.
     * @return The final temperature distribution at time t.
     */

    std::vector<double> laasonenMethod(double deltax, int numberOfPoint, double tsurf, double tinit, double D, double deltat, double t, std::vector<double> temperatureInit);

    //! Methods
    /**
     * @brief This function utilizes the Crank-Nichoslon scheme to solve the 1D heat equation using the Thomas algorithm.
     * @param deltax Grid step.
     * @param numberOfPoint Total number of points to discretize.
     * @param tsurf  Temperature at x=0 and x=L
     * @param tinit Temperature at t=0
     * @param D Coefficient.
     * @param deltat Time step.
     * @param t Total simulation time.
     * @param temperatureInit Initial temperature distribution vector.
     * @return The final temperature distribution at time t.
     */
    std::vector<double> crankNicholsonMethod(double deltax, int numberOfPoint, double tsurf, double tinit, double D, double deltat, double t, std::vector<double> temperatureInit);

    //! Write Methods

    /**
     * @brief Saves the values of the vector to a CSV file.
     * @param im_fileName Name of the CSV file.
     * @param temperature Vector to be filled in the CSV file.
     */
    void saveCSV(std::string im_fileName, std::vector<double> temperature);
};
#endif // IMPLICITMETHODS_H
