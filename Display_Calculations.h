#ifndef DISPLAY_CALCULATIONS_H
#define DISPLAY_CALCULATIONS_H

#include <vector>
#include <iostream>

class Display_Calculations
{
public:
    Display_Calculations();
    ~Display_Calculations();

    static double find_Graph_Max_Height(std::vector<std::vector<double>> graph); //direction used to calculate either top or bottom values, in case values go below 0
    static double find_Graph_Min_Height(std::vector<std::vector<double>> graph);
    static double find_Graph_Max_Length(std::vector<std::vector<double>> graph); // ~~~^
    static double find_Graph_Min_Length(std::vector<std::vector<double>> graph);

    enum MaximaDirection {
        Positive,
        Negative
    };

    enum ScanType {
        Height,
        Length,
    };

};

#endif // DISPLAY_CALCULATIONS_H
