#include "Builder_Rocket.h"
#include "Rocket.h"
#include "SpacePort.h"

class ConcreteBuilderRocket : public Builder_Rocket
{
private:
    Rocket *rocket;

    bool hasM; //instantaneous mass
    bool hasMf; //full mass -> grams
    bool hasMe; //empty mass -> grams
    bool hasMc; //current mass of fuel -> grams
    bool hasu; //rocket velocity -> m/s
    bool hasdu; //delta velocity -> m/s ***
    bool hasv; //exaust velocity -> m/s
    bool hasVi; //initial velocity
    bool hasVcout; //velocity at engine cut out
    bool hasVe; //equivalent exchange velocity
    bool hasdt; //thrust duration
    bool hass; // cross-sectional area
    bool hasA; //exaust area
    bool hasp; //exaust pressure
    bool hasF; //Thrust
    bool hasa; //acceleration
    bool hasCd; //drag coefficient (around 0.35-0.75 for model rocket)
    bool hasa_x; //instantanious acceleration x
    bool hasa_y; //instantanious acceleration y
    bool hasv_x; //velocity of x
    bool hasv_y; //velocity of y
    bool hasmdot; //mass flow rate
    bool hastheta_L; //Launch angle
    bool hasx; //horizontal position
    bool hasy; //vertical position

public:

    ConcreteBuilderRocket() {
        this->reset();
    };
    ~ConcreteBuilderRocket() {
        delete rocket;
    };

    void reset() {
        this->rocket = new Rocket();
    }

    void SetM(double M) const override {
        this->rocket->set_Mass(M);
    }
    void SetMf(double Mf) const override {
        this->rocket->set_Full_Mass(Mf);
    }
    void SetMe(double Me) const override {
        this->rocket->set_Empty_Mass(Me);
    }
    void SetMc(double Mc) const override {
        this->rocket->set_Current_Mass_Fuel(Mc);
    }
    void SetU(double u) const override {
        this->rocket->set_Velocity(u);
    }
    void SetDu(double du) const override {
        this->rocket->set_Delta_Velocity(du);
    }
    void SetV(double v) const override {
        this->rocket->set_Exhaust_Velocity(v);
    }
    void SetVi(double Vi) const override {
        this->rocket->set_Initial_Velocity(Vi);
    }
    void SetVe(double Ve) const override {
        this->rocket->set_Equivalent_Exchange_Velocity(Ve);
    }
    void SetDt(double dt) const override {
        this->rocket->set_Thrust_Duration(dt);
    }
    void SetS(double s) const override {
        this->rocket->set_Cross_Sectional_Area(s);
    }
    void SetA(double A) const override {
        this->rocket->set_Exhaust_Area(A);
    }
    void SetP(double p) const override {
        this->rocket->set_Exhaust_Pressure(p);
    }
    void SetF(double F) const override {
        this->rocket->set_Thrust(F);
    }
    void Seta(double a) const override {
        this->rocket->set_Acceleration(a);
    }
    void SetCd(double Cd) const override {
        this->rocket->set_Drag_Coefficient(Cd);
    }
    void SetAx(double a_x) const override {
        this->rocket->set_Instantaneous_Acceleration_X(a_x);
    }
    void SetAy(double a_y) const override {
        this->rocket->set_Instantaneous_Acceleration_Y(a_y);
    }
    void SetVx(double v_x) const override {
        this->rocket->set_Instantaneous_Velocity_X(v_x);
    }
    void SetVy(double v_y) const override {
        this->rocket->set_Instantaneous_Velocity_Y(v_y);
    }
    void SetMdot(double mdot) const override {
        this->rocket->set_Mass_Flow_Rate(mdot);
    }
    void SetThetaL(double theta_L) const override {
        this->rocket->set_Launch_Angle(theta_L);
    }
    void SetX(double x) const override {
        this->rocket->set_Current_Position_X(x);
    }
    void SetY(double y) const override {
        this->rocket->set_Current_Position_Y(y);
    }

    Rocket* getRocket() {
        Rocket* rocket_return = this->rocket;
        this->reset();
        return rocket_return;
    }

    void sendToSpacePort() {
        SpacePort::dismantleRocket();
        Rocket* rocket_return = this->rocket;
        this->reset();
        SpacePort::dockRocket(rocket_return);

    }
};
