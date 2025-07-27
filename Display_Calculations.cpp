#include "Display_Calculations.h"
#include "Constants.h"

Display_Calculations::Display_Calculations() {}
Display_Calculations::~Display_Calculations() {}


//helper method to assist with direction implementation
bool Maxima(double a, double b, Display_Calculations::MaximaDirection MD) {
    if (MD == Display_Calculations::Positive) {
        return a > b;
    } else {
        return a < b;
    }
}

//Todo, add a max min setting 1/-1 to track whether to find max or min

//considering further implementation that could yield multiple hills and valleys of a graph
// a sequential search is best suited as a binary search, while more effecient in certain cases - mostly position given standard flight trajectory
// ehh sure why not both
// graph is a 2d double vector with each inner vector having 2 elements, x and y
// pre: graph has at least one point and bridges downward (has mostly positive values)
// post: will return highest/furthest point
//
//direction -> 1 or -1 determining the scanning direction (forwards or upwards)
// measure direction -> 1 or -1 determinging wether we are searching for max or min
//
//maxima direction is used instead of absolute due to abs having the potential to hoist large negative values when not wanted
double find_Graph_Max(std::vector<std::vector<double>> graph, Display_Calculations::MaximaDirection MD, Display_Calculations::ScanType ST) {
    const int type = (ST == Display_Calculations::ScanType::Height) ? 1 : 0; // either element at 1 or 0 index (y and x)

    int increment = Constants::SCANINCREMENT;
    int n = graph.size();

    if (n == 1) {
        return graph.at(0).at(type);
    }

    double curr;
    double max_i = -1;
    double max = graph.at(0).at(type);

    //use increments to gain general knowledge of maximum
    for (int i = 0; i < graph.size(); i += increment) {
        curr = graph.at(i).at(type);

        if (Maxima(curr, max, MD)) {
            max = curr;
            max_i = i;
        }
    }


    int currentScandirection = 1; // incremental direction. 1 = right, -1 = left. Used to adjust direction to find maximum

    for (int i = max_i; i < graph.size() && i > -1; i += currentScandirection) {
        curr = graph.at(i).at(type);

        //scan in direction for border or if we are larger. If not,
        //continue in direction, otherwise,
        //scan in oppsoite direction for border or if we are larger. If not,
        //switch direction and continue that way, otherwise,
        //we are the max and return that value.
        if ((i + currentScandirection >= n || i + currentScandirection < 0) || Maxima(curr, graph.at(i + currentScandirection).at(type), MD)) {

            if ((i - currentScandirection >= n || i - currentScandirection < 0) || Maxima(curr, graph.at(i - currentScandirection).at(type), MD)) {

                max = curr;
                max_i = i;
                break;

            } else {

                currentScandirection = -currentScandirection;
            }

        }

        //1. first scan right
        //2. if greater, scan left (3), if smaller direction continues right
        //3. scan left
        //4. if greater and direction is
    }

    return max;
}



double Display_Calculations::find_Graph_Max_Height(std::vector<std::vector<double>> graph) {
    return find_Graph_Max(graph, Display_Calculations::Positive, Display_Calculations::Height);
}

double Display_Calculations::find_Graph_Min_Height(std::vector<std::vector<double>> graph) {
    return find_Graph_Max(graph , Display_Calculations::Negative, Display_Calculations::Height);
}
//just easier to put this here for codebase use all over
double Display_Calculations::find_Graph_Max_Length(std::vector<std::vector<double>> graph) {
    return find_Graph_Max(graph, Display_Calculations::Positive, Display_Calculations::Length);
}

double Display_Calculations::find_Graph_Min_Length(std::vector<std::vector<double>> graph) {
    return find_Graph_Max(graph, Display_Calculations::Negative, Display_Calculations::Length);
}
