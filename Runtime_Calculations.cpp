#include "Runtime_Calculations.h"
#include "Constants.h"
#include <vector>

Runtime_Calculations::Runtime_Calculations() {}
Runtime_Calculations::~Runtime_Calculations() {}
std::vector<std::vector<double>> Runtime_Calculations::plot_trajectory_path(Rocket* rocket, Environment* env, double T, double Ts, double g, bool drag) {

    std::cout << rocket->get_Exhaust_Velocity() << "\n";
    std::cout << rocket->get_Full_Mass() << "\n";
    std::cout << rocket->get_Current_Mass_Fuel() << "\n";
    std::cout << rocket->get_Mass_Flow_Rate() << "\n";
    std::cout << rocket->get_Launch_Angle() << "\n";
    std::cout << rocket->get_Cross_Sectional_Area() << "\n";
    std::cout << rocket->get_Drag_Coefficient() << "\n";

    std::vector<std::vector<double>> points;

    double t = Ts; //current time
    while (t < T && (rocket->get_Current_Position_Y() >= 0 || t == 0)) {


        if (rocket->get_Current_Mass_Fuel() > 0) {
            rocket->update_burned_mass(rocket->get_Current_Mass_Fuel(), rocket->get_Mass_Flow_Rate());
            double a = rocket->calculate_Acceleration(t);
            rocket->calculate_instantanious_acceleration_x(a);
            rocket->calculate_instantanious_acceleration_y(a, g);
            //std::cout << "current a = " << a << "\n";
        } else {
            rocket->set_Instantaneous_Acceleration_X(0);
            rocket->set_Instantaneous_Acceleration_Y(-g);
            //std::cout << "current a = " << -g << "\n";
        }

        //calculating and applying air resistance/drag
        if (drag) {
            double aDx, aDy;

            env->calculateDrag(
                rocket->get_Instantaneous_Velocity_X(),
                rocket->get_Instantaneous_Velocity_Y(),
                rocket->get_Mass(),
                env->getAirDensity(),
                rocket->get_Drag_Coefficient(),
                rocket->get_Cross_Sectional_Area(),
                aDx,
                aDy
                );

            rocket->apply_Drag_X(aDx);
            rocket->apply_Drag_Y(aDy);
        }

        rocket->calculate_instantaneous_velocity_x(rocket->get_Instantaneous_Velocity_X(), rocket->get_Instantaneous_Acceleration_X());
        rocket->calculate_instantaneous_velocity_y(rocket->get_Instantaneous_Velocity_Y(), rocket->get_Instantaneous_Acceleration_Y());

        double current_Position_X = rocket->calculate_instantaneous_position_x(rocket->get_Current_Position_X(), rocket->get_Instantaneous_Velocity_X());
        double current_Position_Y = rocket->calculate_instantaneous_position_y(rocket->get_Current_Position_Y(), rocket->get_Instantaneous_Velocity_Y());
        //std::cout << current_Position_X << " " << current_Position_Y << "\n";

        std::vector<double> point_2d = {current_Position_X, current_Position_Y}; //plot distance height vs time
        //std::vector<double> point_2d = {t, rocket.get_Acceleration()}; //plot acceleration over time
        // std::vector<double> point_2d = {t, current_Position_Y};
        // std::vector<double> point_2d = {t, current_Position_X};
        points.push_back(point_2d);

        t += Constants::DELTA_T;
        //std::cout << "Current time = " << t << "\n";
    }


    return points;

}
