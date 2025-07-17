#include "Builder_Enviroment.h"
#include "Environment.h"

class ConcreteBuillderEnviroment
{
private:
    Environment *env;
public:
    ConcreteBuillderEnviroment() {
        this->reset();
    }

    ~ConcreteBuillderEnviroment() {
        delete env;
    };

    void reset() {
        this->env = new Environment();
    }

    void setG(double g) {
        this->env->setGravity(g);
    }

    Environment* getEnviroment() {
        Environment* returnEnv = this->env;
        this->reset();
        return returnEnv;
    }
};

