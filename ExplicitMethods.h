#pragma once
#ifndef EXPLICITMETHODS_H
#define EXPLICITMETHODS_H

#include <iostream>
#include <vector>
#include <string>

/**
 * @class ExplicitMethods
 * @brief This class employs Richarson and Dufort-Frankel explicit schemes to solve the 1D heat equation
 *
 */

class ExplicitMethods
{
private:
    //! Attribute for data storage at time step n-1
    std::vector<double> e_temperatureN_minus_1;
    //! Attribute for data storage at time step n
    std::vector<double> e_temperatureN;
    //! Attribute for data storage at time step n+1
    std::vector<double> e_temperatureN_plus_1;

public:
    //! Methods
    /**
     * @brief This function applies the Dufort-Frankel scheme to solve 1D heat equation
     * @param deltax grid step
     * @param numberOfPoint Total number of points to discretize
     * @param tsurf  Temperature at x=0 and x=L
     * @param tinit Temperature at t=0
     * @param D coefficient
     * @param deltat time step
     * @param t  total simulation time
     * @param temperatureInit Initial temperature distribution vector
     * @return Final temperature distribution at time t
     */
    std::vector<double> dufort_frankelMethods(double deltax, int numberOfPoint, double tsurf, double tinit, double D, double deltat, double t, std::vector<double> temperatureInit);
    /**
     * @brief This function applies the Richarson scheme to solve 1D heat equation
     * @param deltax grid step
     * @param numberOfPoint Total number of points to discretize
     * @param tsurf  Temperature at x=0 and x=L
     * @param tinit Temperature at t=0
     * @param D coefficient
     * @param deltat time step
     * @param t  total simulation time
     * @param temperatureInit Initial temperature distribution vector
     * @return Final temperature distribution at time t
     */
    std::vector<double> richardsonMethods(double deltax, int numberOfPoint, double tsurf, double tinit, double D, double deltat, double t, std::vector<double> temperatureInit);

    //! Write Methods
    /**
     * @brief Saves the values of the vector to a CSV file.
     * @param e_fileName Name of the CSV file.
     * @param temperature Vector to be filled in the CSV file.
     */
    void saveCSV(std::string e_fileName, std::vector<double> temperature);
};

#endif // EXPLICITMETHODS_H