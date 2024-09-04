#include "ExplicitMethods.h"
#include <fstream>

std::vector<double> ExplicitMethods::richardsonMethods(double deltax, int numberOfPoint, double tsurf, double tinit, double D, double deltat, double t, std::vector<double> temperatureInit)
{

    //! Coefficient
    double beta = D * (deltat / (deltax * deltax));

    //! Number of time steps
    int numStep = static_cast<int>(t / deltat);

    //! Reset Values

    e_temperatureN_minus_1.clear();
    e_temperatureN.clear();
    ;
    e_temperatureN_plus_1.clear();
    ;

    //! Fill out the initial vector
    e_temperatureN_minus_1 = temperatureInit;

    //! Use the FTCS method to get the solution at the first time step
    e_temperatureN.push_back(tsurf);
    for (int i = 1; i < numberOfPoint - 1; i++)
    {
        e_temperatureN.push_back(e_temperatureN_minus_1[i] + beta * (e_temperatureN_minus_1[i + 1] - 2 * e_temperatureN_minus_1[i] + e_temperatureN_minus_1[i - 1]));
    }
    e_temperatureN.push_back(tsurf);

    //! Richardson Scheme
    for (int n = 2; n < numStep; n++)
    {
        e_temperatureN_plus_1.push_back(tsurf);
        for (int i = 1; i < numberOfPoint - 1; i++)
        {
            e_temperatureN_plus_1.push_back(e_temperatureN_minus_1[i] + beta * (e_temperatureN[i + 1] - 2 * e_temperatureN[i] + e_temperatureN[i - 1]));
        }
        e_temperatureN_plus_1.push_back(tsurf);

        //! Update T_prev and T with the new values
        e_temperatureN_minus_1 = e_temperatureN;
        e_temperatureN = e_temperatureN_plus_1;
        e_temperatureN_plus_1 = {};
    }

    //! Return the final temperature vector
    return e_temperatureN;
};

std::vector<double> ExplicitMethods::dufort_frankelMethods(double deltax, int numberOfPoint, double tsurf, double tinit, double D, double deltat, double t, std::vector<double> temperatureInit)
{

    //! Coefficient
    double beta = D * (deltat / (deltax * deltax));

    //! Number of time steps
    int numStep = static_cast<int>(t / deltat);

    //! Fill out the initial vector
    e_temperatureN_minus_1 = temperatureInit;

    //! Reset Values

    e_temperatureN_minus_1.clear();
    e_temperatureN.clear();
    ;
    e_temperatureN_plus_1.clear();
    ;

    //! Use the FTCS method to get the solution at the first time step
    e_temperatureN.push_back(tsurf);
    for (int i = 1; i < numberOfPoint - 1; i++)
    {
        e_temperatureN.push_back(e_temperatureN_minus_1[i] + beta * (e_temperatureN_minus_1[i + 1] - 2 * e_temperatureN_minus_1[i] + e_temperatureN_minus_1[i - 1]));
    }
    e_temperatureN.push_back(tsurf);

    //! Dufort-Frankel Scheme
    for (int n = 2; n < numStep; n++)
    {
        e_temperatureN_plus_1.push_back(tsurf);
        for (int i = 1; i < numberOfPoint - 1; i++)
        {
            e_temperatureN_plus_1.push_back(e_temperatureN_minus_1[i] * ((1 - 2 * beta) / (1 + 2 * beta)) + ((2 * beta) / (1 + 2 * beta)) * (e_temperatureN[i + 1] + e_temperatureN[i - 1]));
        }
        e_temperatureN_plus_1.push_back(tsurf);

        //! Update T_prev and T with the new values
        e_temperatureN_minus_1 = e_temperatureN;
        e_temperatureN = e_temperatureN_plus_1;
        e_temperatureN_plus_1 = {};
    }

    //! Return the final temperature vector
    return e_temperatureN;
}

void ExplicitMethods::saveCSV(std::string e_fileName, std::vector<double> temperature)
{
    std::ofstream myfile;
    myfile.open(e_fileName);
    for (int i = 0; i < temperature.size(); i++)
    {
        myfile << temperature[i] << "\n";
    }
    myfile.close();
};
