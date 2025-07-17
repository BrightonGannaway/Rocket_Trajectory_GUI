#ifndef ENVIROMENT
#define ENVIROMENT

#include <iostream>
#include <cmath>
#include <optional>

class Environment {
private:
    double gravity;
    double rho; // air density


public:
    Environment(/* args */);
    Environment(double gravity);// constructor with gravity argument
    ~Environment();

    /*receive x and y velocity and calculate drag using formula Dx = 0.5(rho)(v)^2 (Cd)(A)
    
    where:

        rho = air density
        v = speed relative to fluid
        Cd = drag coefficient (0.35-0.75 for model rockets)
        A = cross sectional area
    */

    void calculateDrag(double vx, double vy, double m, double rho, double Cd, double A,
    double& ax, double& ay );

    double getGravity() const;
    void setGravity(double g);
    double getAirDensity() const;
    void setAirDensity(double rho); 
};




#endif
