#include "SpacePort.h"


Runtime_Calculations* SpacePort::rt = new Runtime_Calculations();
Rocket* SpacePort::rocket = new Rocket();
Environment* SpacePort::env = new Environment();

SpacePort::SpacePort() {
    rt = new Runtime_Calculations();
    rocket = nullptr;
    env= nullptr;
}

void SpacePort::dockRocket(Rocket* r) {
    rocket = r;
}

void SpacePort::addEnvironment(Environment* e) {
    env = e;
}

std::vector<std::vector<double>> SpacePort::launchRocketandPlotTrajectory() {


    if (rocket == NULL || rocket == nullptr) {
        return std::vector<std::vector<double>> {std::vector<double> {-1, -1}}; //default return -> point will not show
    }
    //create default env if none is set so that we can have a trajectory even if no env exists

    bool envWasNull = false;
    if (env == NULL || env == nullptr) {
        env = new Environment();
        envWasNull = true;
    }

    std::vector<std::vector<double>> points = rt->plot_trajectory_path(rocket, env, Constants::Runtime::RUNSECONDS);

    if (envWasNull) {
        env = nullptr;
    }

    return points;
}

void SpacePort::dismantleRocket() {
    rocket = nullptr;
}

void SpacePort::ruinEnvironment() {
    env= nullptr;
}
