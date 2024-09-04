#include <iostream>
#include <cmath>
#include <vector>

#include "Initializer.h"
#include "ExplicitMethods.h"
#include "ImplicitMethods.h"

#define DELTAX 0.05
#define TSURF 149.0
#define TINIT 38.0
#define D 93.0
#define XMIN 0
#define XMAX 31
#define NUMBER_OF_POINTS 1 + ((XMAX - XMIN) / DELTAX)

using namespace std;

int main()
{

    // Initialize the initial values and initial vector
    Initializer values = Initializer(0.01, 0.05);
    vector<double> temperatureInit = values.getT_values(NUMBER_OF_POINTS, TSURF, TINIT);

    // Create an object of ExplicitMethods
    ExplicitMethods explicitMethods;

    // Create an object of ImplicitMethods
    ImplicitMethods ImplicitMethods;

    double timevalues[5] = {0.1, 0.2, 0.3, 0.4, 0.5};

    for (int i = 0; i < 5; i++)
    {
        values.sett(timevalues[i]);
        vector<double> richardson = explicitMethods.richardsonMethods(DELTAX, NUMBER_OF_POINTS, TSURF, TINIT, D, values.getDeltat(), values.gett(), temperatureInit);
        vector<double> dufort_Frankel = explicitMethods.dufort_frankelMethods(DELTAX, NUMBER_OF_POINTS, TSURF, TINIT, D, values.getDeltat(), values.gett(), temperatureInit);
        explicitMethods.saveCSV("Richardson" + to_string(timevalues[i]) + ".csv", richardson);
        explicitMethods.saveCSV("DufortFrankelt" + to_string(timevalues[i]) + ".csv", dufort_Frankel);

        vector<double> laasonen = ImplicitMethods.laasonenMethod(DELTAX, NUMBER_OF_POINTS, TSURF, TINIT, D, values.getDeltat(), values.gett(), temperatureInit);
        vector<double> cn = ImplicitMethods.crankNicholsonMethod(DELTAX, NUMBER_OF_POINTS, TSURF, TINIT, D, values.getDeltat(), values.gett(), temperatureInit);
        ImplicitMethods.saveCSV("Laasonen" + to_string(timevalues[i]) + ".csv", laasonen);
        ImplicitMethods.saveCSV("Cn" + to_string(timevalues[i]) + ".csv", cn);
    }

    // Laasonen  Convergence Study
    values.sett(0.5);

    double deltatvalues[4] = {0.1, 0.05, 0.025, 0.01};

    for (int i = 0; i < 4; i++)
    {
        values.setDeltat(deltatvalues[i]);
        vector<double> laasonen_deltat = ImplicitMethods.laasonenMethod(DELTAX, NUMBER_OF_POINTS, TSURF, TINIT, D, values.getDeltat(), values.gett(), temperatureInit);
        ImplicitMethods.saveCSV("laasonenDeltat" + to_string(timevalues[i]) + ".csv", laasonen_deltat);
    }

    // Call the dufort_frankelMethods method for deltat = 0.0000005h
    values.sett(0.5);
    values.setDeltat(0.0000005);
    vector<double> dufort_Frankel_test = explicitMethods.dufort_frankelMethods(DELTAX, NUMBER_OF_POINTS, TSURF, TINIT, D, values.getDeltat(), values.gett(), temperatureInit);
    explicitMethods.saveCSV("DufortFrankeldeltat_0.0000005.csv", dufort_Frankel_test);

    return 0;
}
