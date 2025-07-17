#include "Environment.h"
#include "Constants.h"

//earth - std preassure and temp
Environment::Environment() {
    //earth is no arguement constructor
    this->gravity = 9.81;
    this->rho = Constants::Enviorment::AIR_DENSITY_EARTH_SEA_LEVEL;
}

Environment::Environment(double gravity) {
    //constructor with gravity argument
    this->gravity = gravity;
}

Environment::~Environment() {}

void Environment::calculateDrag(double vx, double vy,
                                double m, double rho, double Cd,
                                double A,
                                double& ax, double& ay ) {
    //first find velocity
    double v = std::sqrt(vx * vx + vy * vy);
    if (v == 0) {
        ax = 0.0;
        ay = 0.0;
        return;
    }

    double Dx = 0.5 * rho * v * v * Cd * A;
    double aDx = Dx / m;

    ax = -aDx * (vx / v);
    ay = -aDx * (vy / v);
    return;
}

double Environment::getGravity() const {
    return gravity;
}



double Environment::getAirDensity() const {
    return rho;
}
