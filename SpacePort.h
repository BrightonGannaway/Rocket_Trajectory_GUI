#pragma once

#include <vector>

#include "Rocket.h"
#include "Runtime_Calculations.h"
#include "Environment.h"
#include "Runtime_Calculations.h"
#include "Constants.h"


namespace garage {
class SpacePort;
}


class SpacePort
{
private:
    static Rocket* rocket;
    static Environment* env;
    static Runtime_Calculations* rt;


public:
    SpacePort();

    static void dockRocket(Rocket* r);
    static void addEnvironment(Environment* env);

    static std::vector<std::vector<double>> launchRocketandPlotTrajectory();
    static void dismantleRocket(); //nulls rokcet pointer
    static void ruinEnvironment(); //nulls env pointer


};

