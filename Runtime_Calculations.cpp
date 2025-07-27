#include "Runtime_Calculations.h"
#include <vector>

Runtime_Calculations::Runtime_Calculations() {}
Runtime_Calculations::~Runtime_Calculations() {}
std::vector<std::vector<double>> Runtime_Calculations::plot_trajectory_path(Rocket* rocket, Environment* env, double T, std::string setting, double Ts, double g, bool drag) {

    std::vector<std::vector<double>> points;

    double t = Ts; //current time
    while (t < T && (rocket->get_Current_Position_Y() >= 0 )) {


        if (rocket->get_Current_Mass_Fuel() > 0) {
            rocket->update_burned_mass(rocket->get_Current_Mass_Fuel(), rocket->get_Mass_Flow_Rate());
            double a = rocket->calculate_Acceleration(t);
            rocket->calculate_instantanious_acceleration_x(a);
            rocket->calculate_instantanious_acceleration_y(a, g);
            //std::cout << "current a = " << a << "\n";
        } else {
            rocket->set_Acceleration(-g);
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

        // double current_Position_X = rocket->calculate_instantaneous_position_x(rocket->get_Current_Position_X(), rocket->get_Instantaneous_Velocity_X());
        // double current_Position_Y = rocket->calculate_instantaneous_position_y(rocket->get_Current_Position_Y(), rocket->get_Instantaneous_Velocity_Y());
        //std::cout << current_Position_X << " " << current_Position_Y << "\n";

        // std::vector<double> point_2d = {current_Position_X, current_Position_Y}; //plot distance height vs time
        //std::vector<double> point_2d = {t, rocket.get_Acceleration()}; //plot acceleration over time
        // std::vector<double> point_2d = {t, current_Position_Y};
        // std::vector<double> point_2d = {t, current_Position_X};
        std::vector<double> point_2d = display_trajectory_path_point(rocket, t, setting);
        points.push_back(point_2d);

        t += Constants::DELTA_T;
        //std::cout << "Current time = " << t << "\n";
    }

    return points;

}

std::vector<double> Runtime_Calculations::display_trajectory_path_point(Rocket* rocket, double time, std::string setting) {

    Constants::Display::GraphTypes graphtype = Constants::Display::GRAPHOPTIONS.count(setting) ? Constants::Display::GRAPHOPTIONS.at(setting) : Constants::Display::UU;

    double X, Y;

    //default values. Also makes sure the position gets calculated anyway so other values can use it
    X = rocket->calculate_instantaneous_position_x(rocket->get_Current_Position_X(), rocket->get_Instantaneous_Velocity_X());
    Y = rocket->calculate_instantaneous_position_y(rocket->get_Current_Position_Y(), rocket->get_Instantaneous_Velocity_Y());

    switch (graphtype) {
    case Constants::Display::XY:
        break;
    case Constants::Display::TY:
        X = time;
        break;
    case Constants::Display::TX:
        X = time;
        break;
    case Constants::Display::TA:
        X = time;
        Y = rocket->get_instantaneous_Acceleration();
        break;
    default:
        break;
    }

    // std::cout << "(" << X << ", " << Y << ")\n";
    // std::cout << "acc: " << rocket->get_Acceleration() << ", (X: " << rocket->get_Instantaneous_Acceleration_X() << ", " << rocket->get_Instantaneous_Acceleration_Y() << ")\n";
    std::vector<double> point = {X, Y};

    return point;
}

