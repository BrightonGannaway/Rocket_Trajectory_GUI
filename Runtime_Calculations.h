#ifndef RUNTIME_CALC
#define RUNTIME_CALC

#include "Rocket.h"
#include "Constants.h"
#include <vector>

class Runtime_Calculations
{
private:

public:
    Runtime_Calculations(/* args */);
    Runtime_Calculations(Environment env_sim);
    ~Runtime_Calculations();

    std::vector<std::vector<double>> plot_trajectory_path(Rocket* rocket, Environment* env, double T, std::string setting = "distance-x / distance-y", double Ts = 0, double g= 9.81, bool drag = true);
    std::vector<double> display_trajectory_path_point(Rocket* rocket, double time, std::string setting = "distance-x / distance-y");

};
#endif
