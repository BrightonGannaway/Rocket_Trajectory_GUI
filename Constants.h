#pragma once

#include <map>
#include <QLineEdit>
#include <string>

namespace Constants {

    constexpr double PI = 3.141592653589793;
    constexpr double DELTA_T = 0.05;
    constexpr double GRAVITY_EARTH = 9.81;

    namespace Enviorment {
        constexpr double AIR_DENSITY_EARTH_SEA_LEVEL = 1.225;
    }

    namespace Runtime {
        constexpr double RUNSECONDS = 100;
    }

    namespace Display {
        const std::vector<QString*> GRAPHOPTIONS =
        {
        new QString("distance-x / distance-y"),
        new QString("time / distance-y"),
        new QString("distance-x / time"),
        new QString("time / accelerration"),
        };
    }
}
