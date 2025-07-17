#ifndef BUILDER_R_H
#define BUILDER_R_H
//acts as an interface to the builder class for the Rocket
class Builder_Rocket
{
private:
    bool test;
public:
    ~Builder_Rocket(){};

    // Virtual setters for builder interface
    virtual void SetM(double M) const = 0;
    virtual void SetMf(double Mf) const = 0;
    virtual void SetMe(double Me) const = 0;
    virtual void SetMc(double Mc) const = 0;
    virtual void SetU(double u) const = 0;
    virtual void SetDu(double du) const = 0;
    virtual void SetV(double v) const = 0;
    virtual void SetVi(double Vi) const = 0;
    virtual void SetVe(double Ve) const = 0;
    virtual void SetDt(double dt) const = 0;
    virtual void SetS(double s) const = 0;
    virtual void SetA(double A) const = 0;
    virtual void SetP(double p) const = 0;
    virtual void SetF(double F) const = 0;
    virtual void Seta(double a) const = 0;
    virtual void SetCd(double Cd) const = 0;
    virtual void SetAx(double a_x) const = 0;
    virtual void SetAy(double a_y) const = 0;
    virtual void SetVx(double v_x) const = 0;
    virtual void SetVy(double v_y) const = 0;
    virtual void SetMdot(double mdot) const = 0;
    virtual void SetThetaL(double theta_L) const = 0;
    virtual void SetX(double x) const = 0;
    virtual void SetY(double y) const = 0;

};


#endif
