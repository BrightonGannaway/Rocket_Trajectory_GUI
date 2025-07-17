#ifndef BUILDER_E_H
#define BUILDER_E_H

class Builderr_Enviroment
{
private:
    /* data */
public:
    ~Builderr_Enviroment();

    virtual void setG(double g) const = 0;
    virtual void setRHO(double rho) const = 0;
};




#endif 