#include <iostream>
#include "../include/octagon.h"
#include "../include/hexagon.h"
#include "../include/pentagon.h"
#include "../include/figure_array.h"
#include "../include/point.h"

using namespace std;


int main(int argc, char** argv){
    Hexagon<double> *hex = new Hexagon<double>{Point<double>(1, 1), Point<double>(2, 2), Point<double>(3, 3), Point<double>(4, 4), Point<double>(5, 5), Point<double>(6, 6)};
    Pentagon<double> *pent =  new Pentagon<double>{Point<double>(0, 0), Point<double>(1, 1), Point<double>(2, 2), Point<double>(3, 3), Point<double>(4, 4)};
    FigureArray<Figure<double>> array{hex};
    array.addElem(pent, 1);
    array.calc_total_area();
    cout << array;
    // cout << array << endl << endl;
    // cout << array.calc_total_area() << endl;
    // array.removeElem(1);
    // cout << array;
}