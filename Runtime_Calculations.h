#ifndef RUNTIME_CALC
#define RUNTIME_CALC

#include "Rocket.h"
#include <vector>

class Runtime_Calculations
{
private:

public:
    Runtime_Calculations(/* args */);
    Runtime_Calculations(Environment env_sim);
    ~Runtime_Calculations();

    //calculate the path trajectory provided a rocket
    //T = total time the simulation is run, Ts = start time
    std::vector<std::vector<double>> plot_trajectory_path(Rocket* rocket, Environment* env, double T, double Ts = 0, double g= 9.81, bool drag = true);


};
#endif
