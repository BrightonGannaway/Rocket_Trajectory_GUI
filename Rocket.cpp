#include "Rocket.h"
#include "Constants.h"
//#include "Round.h"


Rocket::Rocket() {}

Rocket::Rocket(double Mf, double Me, double Ve) {
    this->Mf = Mf;
    this->M = Mf;
    this->Mc = Mf;
    this->Me = Me;
    this->Ve = Ve;
}

//constructor to be able to find max height
Rocket::Rocket(double Vi, double dt, double a, double g) : Engine(dt), Environment(g) {
    this->Vi = Vi;
    this->a = a;
}

Rocket::Rocket(double v, double Mf, double Mc, double mdot, double theta_L, double s, double Cd) {
    this->v = v;
    this->Mf = Mf;
    this->Mc = Mc;
    this->mdot = mdot;
    this->theta_L = theta_L;
    this->s = s;
    this->Cd = Cd;
}

Rocket::~Rocket() {}

double Rocket::calculate_Delta_u(double Mf, double Me, double Ve) {
    du = Ve * std::log(Mf / Me);
    return du;
}

//consider the velocity of the exaust + the exaust area multiplied by the diffrence in pressure between
//the engines pressure and the surrounding enviorments pressure all over the flow of fuel/mass
double Rocket::calculate_Equivalent_Exchange_Velocity(double v, double A, double p, double Pa, double mdot) {
    this->Ve = (v + (A * (p - Pa))) / mdot;
    return this->Ve;
}


//calculate accelertation at given time
double Rocket::calculate_Acceleration(double v, double Mf, double mdot, double t, double g) {
    a = ((v / (Mf - mdot * t)) * mdot) - g;
    return a;
}

double Rocket::calculate_Acceleration(double t) {
    a = ((v / (Mf - mdot * t)) * mdot);
    return a;
}

//--------------------------------//
//---Instantanious acceleration---//
//--------------------------------//

double Rocket::calculate_instantanious_acceleration_x(double a, double theta) {
    a_x = a * std::cos(theta * (Constants::PI / 180));
    return a_x;
}

double Rocket::calculate_instantanious_acceleration_y(double a, double theta, double g) {
    a_y = a * std::sin(theta * (Constants::PI / 180)) - g;
    return a_y;
}

// Overloads using theta_L instead of theta
double Rocket::calculate_instantanious_acceleration_x(double a) {
    a_x = a * std::cos(theta_L * (Constants::PI / 180));
    return a_x;
}

double Rocket::calculate_instantanious_acceleration_y(double a, double g) {
    a_y = a * std::sin(theta_L * (Constants::PI / 180)) - g;
    return a_y;
}

double Rocket::calculate_instantanious_acceleration_y(double a) {
    a_y = a * std::sin(theta_L * (Constants::PI / 180)) - Constants::GRAVITY_EARTH;
    return a_y;
}

//-----------------------------//
//--- Kenematic calculations---//
//-----------------------------//

double Rocket::calculate_instantaneous_velocity_x(double v_x, double a_x) {
    this->v_x = v_x + a_x * Constants::DELTA_T;
    return this->v_x;
}

double Rocket::calculate_instantaneous_velocity_y(double v_y, double a_y) {
    this->v_y = v_y + a_y * Constants::DELTA_T;
    return this->v_y;
}

double Rocket::calculate_instantaneous_position_x(double x, double v_x) {
    this->x = x + v_x * Constants::DELTA_T;
    return this->x;
}

double Rocket::calculate_instantaneous_position_y(double y, double v_y) {
    this->y = y + v_y * Constants::DELTA_T;
    return this->y;
}

void Rocket::update_burned_mass(double Mc, double mdot) {
    this->Mc = Mc - mdot * Constants::DELTA_T;
    this->M = Me + Mc;
}
//-------------------------//
//---height calculations---//
//-------------------------//

//Burning displacement is the distance overcome by thrust
//Displacement is the sum of the initial velocity plus half the acceleration times the burn time squared
double Rocket::calculate_Burning_Displacement(double Vi, double dt, double a) {
    double d = Vi + (0.5 * a * std::pow(dt, 2));
    std::cout << "Burning displacement = " << d << " m\n";
    return d;
}

double Rocket::calculate_Burning_Displacement(double Vi, double dt, double theta, double a) {

    double d = (Vi + (0.5 * a * std::pow(dt, 2))) * std::sin(theta * (Constants::PI / 180));
    std::cout << "Burning displacement = " << d << " m\n";
    return d;
}

// Velocity at the end of burn time is the sumn of the initial velocity plus the change in velocity (a * burn time)
double Rocket::calculate_Engine_Cut_Out_Velocity(double Vi, double dt, double a) {
    double Vcout = (Vi + (a * dt));
    std::cout << "Engine cut out velocity = " << Vcout << " m/s\n";
    return Vcout;
}

//---------------------------//
//---external applications---//
//---------------------------//
double Rocket::apply_Drag_X(double a_x) {
    this->a_x += a_x;
    return this->a_x;
}

double Rocket::apply_Drag_Y(double a_y) {
    this->a_y += a_y;
    return this->a_y;
}


//Free fall disaplcement calculates the distance tarveled from the inertia left over since the cut out of fuel
//Calculated by the initial velocity squared divided by 2 times gravity
// rearanged from the formula Vf^2 = Vi^2 + 2 * a * d where a = -9.8 (or any other gravity)
//"Vi" is the velocity at engine cut out (use calculate_Engine_Cut_Out_Velocity to get this value)
double Rocket::calculate_Upward_Free_Fall_Displacement(double Vi, double g) {
    double d = (std::pow(Vi, 2)) / (2 * g);
    std::cout << "Upward free fall displacement = " << d << " m\n";
    return d;
}

double Rocket::calculate_Upward_Free_Fall_Displacement(double Vi, double theta, double g) {
    double d = (std::pow(Vi * std::sin(theta * (Constants::PI / 180)), 2)) / (2 * g);
    std::cout << "Upward free fall displacement = " << d << " m\n";
    return d;
}

//returns the sum of the displacement of the burning phase and the displacement of the free fall phase (upward)
double Rocket::calculate_Max_Height(double Vi, double dt, double a, double g) {
    double h1 = calculate_Burning_Displacement(Vi, dt, a);
    double Vcout = calculate_Engine_Cut_Out_Velocity(Vi, dt, a);
    double h2 = calculate_Upward_Free_Fall_Displacement(Vcout, g);
    return h1 + h2;
}

//returns the sum of the displacement of the burning phase and the displacement of the free fall phase (upward)
double Rocket::calculate_Max_Height(double Vi, double dt, double a, double theta, double g) {
    double h1 = calculate_Burning_Displacement(Vi, dt, a, theta);
    double Vcout = calculate_Engine_Cut_Out_Velocity(Vi, dt, a);
    double h2 = calculate_Upward_Free_Fall_Displacement(Vcout, g, theta);
    return h1 + h2;
}

//-----------------------------//
//--- Accessors and Setters ---//
//-----------------------------//

void Rocket::set_Initial_Velocity(double Vi) {
    this->Vi = Vi;
}

void Rocket::set_Launch_Angle(double theta_L) {
    this->theta_L = theta_L;
}

void Rocket::set_Cross_Sectional_Area(double s) {
    this->s = s;
}

void Rocket::set_Drag_Coefficient(double Cd) {
    this->Cd = Cd;
}

void Rocket::set_Mass_Flow_Rate(double mdot) {
    this->mdot = mdot;
}

void Rocket::set_Current_Mass_Fuel(double Mc) {
    this->Mc = Mc;
}

void Rocket::set_Mass(double M) {
    this->M = M;
}

void Rocket::set_Empty_Mass(double Me) {
    this->Me = Me;
}

void Rocket::set_Full_Mass(double Mf) {
    this->Mf = Mf;
}

void Rocket::set_Velocity(double u) {
    this->u = u;
}

void Rocket::set_Exhaust_Velocity(double v) {
    this->v = v;
}

void Rocket::set_Equivalent_Exchange_Velocity(double Ve) {
    this->Ve = Ve;
}

void Rocket::set_Thrust(double F) {
    this->F = F;
}

void Rocket::set_Acceleration(double a) {
    this->a = a;
}

void Rocket::set_Exhaust_Area(double A) {
    this->A = A;
}

void Rocket::set_Delta_Velocity(double du) {
    this->du = du;
}

void Rocket::set_Thrust_Duration(double dt) {
    this->dt = dt;
}

void Rocket::set_Exhaust_Pressure(double p) {
    this->p = p;
}

void Rocket::set_Instantaneous_Velocity_X(double v_x) {
    this->v_x = v_x;
}

void Rocket::set_Instantaneous_Velocity_Y(double v_y) {
    this->v_y = v_y;
}
double Rocket::get_Mass() {
    return M;
}

double Rocket::get_Full_Mass() {
    return Mf;
}

double Rocket::get_Empty_Mass() {
    return Me;
}

double Rocket::get_Velocity() {
    return u;
}

double Rocket::get_Initial_Velocity() {
    return Vi;
}

double Rocket::get_Exhaust_Velocity() {
    return v;
}

double Rocket::get_Equivalent_Exchange_Velocity() {
    return Ve;
}

double Rocket::get_Acceleration() {
    return a;
}

double Rocket::get_Cross_Sectional_Area() {
    return s;
}

double Rocket::get_Drag_Coefficient() {
    return Cd;
}

double Rocket::get_Instantaneous_Velocity_X() {
    return v_x;
}

double Rocket::get_Instantaneous_Velocity_Y() {
    return v_y;
}

double Rocket::get_Instantaneous_Acceleration_X() {
    return a_x;
}

void Rocket::set_Instantaneous_Acceleration_X(double a_x) {
    this->a_x = a_x;
}

double Rocket::get_Instantaneous_Acceleration_Y() {
    return a_y;
}

void Rocket::set_Instantaneous_Acceleration_Y(double a_y) {
    this->a_y = a_y;
}

double Rocket::get_Current_Mass_Fuel() {
    return Mc;
}

double Rocket::get_Mass_Flow_Rate() {
    return mdot;
}

double Rocket::get_Current_Position_X() {
    return x;
}

double Rocket::get_Current_Position_Y() {
    return y;
}

double Rocket::get_Launch_Angle() {
    return theta_L;
}

// Additional setters/getters from header file (if any):

void Rocket::set_Current_Position_X(double x) {
    this->x = x;
}

void Rocket::set_Current_Position_Y(double y) {
    this->y = y;
}




//
