#include "Engine.h"

Engine::Engine() {}
Engine::Engine(double dt) {
    // constructor with thrust duration argument
    this->dt = dt;
}
Engine::~Engine() {}

double Engine::calculate_Mass_Flow_Rate(double Mp, double Dt) {
    mdot = Mp / Dt;
    return mdot;
}




