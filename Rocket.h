#ifndef ROCKET_H
#define ROCKET_H

#include <cmath>
#include <vector>
#include <iostream>
#include <optional>
#include "Engine.h"
#include "Environment.h"

class Rocket : public Engine, public Environment {

private:
    double M; //instantaneous mass
    double Mf; //full mass -> grams
    double Me; //empty mass -> grams
    double Mc; //current mass of fuel -> grams
    double u; //rocket velocity -> m/s
    double du; //delta velocity -> m/s ***
    double v; //exaust velocity -> m/s
    double Vi; //initial velocity
    double Vcout; //velocity at engine cut out
    double Ve; //equivalent exchange velocity
    double dt; //thrust duration
    double s; // cross-sectional area
    double A; //exaust area
    double p; //exaust pressure
    double F; //Thrust
    double a; //acceleration
    double Cd; //drag coefficient (around 0.35-0.75 for model rocket)
    double a_x; //instantanious acceleration x
    double a_y; //instantanious acceleration y
    double v_x; //velocity of x
    double v_y; //velocity of y
    double mdot; //mass flow rate
    double theta_L; //Launch angle
    double x; //horizontal position
    double y; //vertical position

    double Hmax; //max height
    bool include_Gravity;

public:
    //constructors are temporary and need ot be replaced by a builder configuration after testing
    Rocket();
    Rocket(double Mf, double Me, double Ve);
    Rocket(double Vi, double dt, double a, double g);
    Rocket(double v, double Mf, double Mc, double mdot, double theta, double s, double Cd);
    ~Rocket();

    double calculate_Delta_u();
    double calculate_Delta_u(double Mf, double Me, double Ve);
    double calculate_Equivalent_Exchange_Velocity();
    double calculate_Equivalent_Exchange_Velocity(double v, double A, double p, double Pa, double mdot);
    double calculate_Equivalent_Exchange_Velocity(double F, double mdot);
    double calculate_Acceleration(double v, double Mf, double mdot, double t, double g);
    double calculate_Acceleration(double v, double Mf, double mdot, double t); //usefull for laying out insdtantanious on x axis
    double calculate_Acceleration(double t);
    double calculate_Mass_Flow_rate(double Mf, double dt);

    //instantanious thrust acceleration
    double calculate_instantanious_acceleration_x(double a, double theta);
    double calculate_instantanious_acceleration_x(double a);
    double calculate_instantanious_acceleration_y(double a, double theta, double g);
    double calculate_instantanious_acceleration_y(double a, double g);
    double calculate_instantanious_acceleration_y(double a);

    //kenematic thrust calculations
    double calculate_instantaneous_velocity_x(double v_x, double a_x);
    double calculate_instantaneous_velocity_y(double v_y, double a_y);
    double calculate_instantaneous_position_x(double x, double v_x);
    double calculate_instantaneous_position_y(double y, double v_y);
    void update_burned_mass(double m, double mdot);


    //calculations relating to height (applicable for striaght up caluations)
    double calculate_Burning_Displacement(double Vi, double dt, double a); //from when engine starts to when it cuts out
    double calculate_Burning_Displacement(double Vi, double dt, double theta, double a); //for angle of launch
    double calculate_Engine_Cut_Out_Velocity(double Vi, double dt, double a); //velocity at engine cut out
    double calculate_Upward_Free_Fall_Displacement(double Vi, double g); //from when engine cuts out (freefall is upward)
    double calculate_Upward_Free_Fall_Displacement(double Vi, double theta, double g); //for angle of launch 

    //to calculate max height you need: initial velocity (most likely 0), burn/thrust time, acceleration, and gravity (9.81 for earth)
    double calculate_Max_Height(double Vi, double dt, double a, double g); //max height of the rocket in meters
    double calculate_Max_Height(double Vi, double dt, double a, double theta, double g); //max height of the rocket in meters with launch angle

    double apply_Drag_X(double a_x);
    double apply_Drag_Y(double a_y);
    
    // Getters and setters in the order of private field declarations

    double get_Mass();
    void set_Mass(double mass);

    double get_Full_Mass();
    void set_Full_Mass(double fullMass);

    double get_Empty_Mass();
    void set_Empty_Mass(double emptyMass);

    double get_Current_Mass_Fuel();
    void set_Current_Mass_Fuel(double currentMassFuel);

    double get_Velocity();
    void set_Velocity(double velocity);
    
    double get_Delta_Velocity();
    void set_Delta_Velocity(double deltaVelocity); // du
    
    double get_Exhaust_Velocity();
    void set_Exhaust_Velocity(double exhaustVelocity); // v
    
    double get_Initial_Velocity();
    void set_Initial_Velocity(double initialVelocity); // Vi
    
    double get_Engine_Cut_Out_Velocity();
    void set_Engine_Cut_Out_Velocity(double engineCutOutVelocity); // Vcout
    
    double get_Equivalent_Exchange_Velocity();
    void set_Equivalent_Exchange_Velocity(double equivalentExchangeVelocity);
    
    void set_Thrust_Duration(double thrustDuration); // dt
    
    double get_Cross_Sectional_Area();
    void set_Cross_Sectional_Area(double crossSectionalArea);
    
    double get_Exhaust_Area();
    void set_Exhaust_Area(double exhaustArea); // A
    
    double get_Exhaust_Pressure();
    void set_Exhaust_Pressure(double exhaustPressure); // p
   
    double get_Thrust();
    void set_Thrust(double thrust); // F
    
    double get_Acceleration();
    void set_Acceleration(double acceleration);
    
    double get_Drag_Coefficient();
    void set_Drag_Coefficient(double dragCoefficient);
    
    double get_Instantaneous_Acceleration_X();
    void set_Instantaneous_Acceleration_X(double a_x);
    
    double get_Instantaneous_Acceleration_Y();
    void set_Instantaneous_Acceleration_Y(double a_y);

    double get_Instantaneous_Velocity_X();
    void set_Instantaneous_Velocity_X(double velocityX);
    
    double get_Instantaneous_Velocity_Y();
    void set_Instantaneous_Velocity_Y(double velocityY);

    double get_Mass_Flow_Rate();
    void set_Mass_Flow_Rate(double massFlowRate);

    double get_Launch_Angle();
    void set_Launch_Angle(double launchAngle); // theta_L

    double get_Current_Position_X();
    void set_Current_Position_X(double positionX);

    double get_Current_Position_Y();
    void set_Current_Position_Y(double positionY);

    // given that the launch angle is perfectly perpendicular to the ground and no other force4s are action on the rocket
    // the only force acting on the rocket is gravity, what are the heights of the rocket at each second until its max height

};

#endif
