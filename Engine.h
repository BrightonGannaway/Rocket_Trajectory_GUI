#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <optional>

class Engine {
    private:
        std::string prod_no;
        std::string engine_type;
        double i; //Total impulse - Newtons per sec
        double d; //delay - sec
        double lm; //Max lift weightgrams
        double tm; //Max trhust Newtons
        double dt; // Thrust duration seconds
        double mi; // Initial wight grams
        double mp; //Propellent weight - grams
        double mdot; //mass flow rate

    public:
        Engine();
        Engine(double dt); // constructor with thrust duration argument
        ~Engine();

        double calculate_Mass_Flow_Rate(double mp, double dt);
        double calculate_Thrust(double i, double d);
        double calculate_Exit_Velocity(double F, double mdot); //this is a gross oversimplification and ignores pressure
        

        // Accessors
        std::string get_prod_no() const;
        std::string get_engine_type() const;
        double get_i() const;
        double get_d() const;
        double get_lm() const;
        double get_tm() const;
        double get_dt() const;
        double get_mi() const;
        double get_mp() const;
        double get_mdot() const;

};;

#endif
