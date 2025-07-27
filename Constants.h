#pragma once

#include <QLineEdit>
#include <QString>
#include <string>
#include <map>

namespace Constants {

    constexpr double PI = 3.141592653589793;
    constexpr double DELTA_T = 0.05;
    constexpr int SCANINCREMENT = 40; //for local maxima/minimum calculations, go fiven at a time
    constexpr double GRAVITY_EARTH = 9.81;

    namespace Enviorment {
        constexpr double AIR_DENSITY_EARTH_SEA_LEVEL = 1.225;
    }

    namespace Runtime {
        constexpr double RUNSECONDS = 100;
    }

    namespace Display {

        enum GraphTypes {
            XY,
            TY,
            TX,
            TA,
            UU,
        };

        const std::map<std::string, GraphTypes> GRAPHOPTIONS = {
            {"distance-x / distance-y", XY}, {"time / distance-y", TY}, {"time / distance-x", TX}, //{"time / accelerration", TA} not ready for release yet
        };

        const std::string distanceDisplayPrefix = "X-Axis: ";
        const std::string heightDisplayPrefix = "Y-Axis: ";
    }

}
