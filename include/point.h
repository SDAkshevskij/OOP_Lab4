#pragma once
#include <string>
#include <iostream>
#include <cmath>
#include <concepts>
#include <type_traits>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point {
    public:
        Point() {}


        Point(T x, T y)
            : x(x), y(y) {}


        T getX(){
            return x;
        }


        T getY(){
            return y;
        }


        void setX(T x){
            this->x = x;
        }


        void setY(T y) {
            this->y = y;
        }


        T getDistTo(Point &other) {
            T xDiff = abs(other.x - x);
            T yDiff = abs(other.y - y);

            return sqrt(xDiff * xDiff + yDiff * yDiff);
        }


        std::string to_string() {
            return "x: " + std::to_string(x) + " y: " + std::to_string(y);
        }



        bool operator==(Point &other) {
            double eps = 0.00001;
            return abs(x - other.x) < eps && abs(y - other.y) < eps;
        }


        
        bool operator!=(Point &other) {
            return !(*this == other);
        }


        friend std::istream& operator>>(std::istream& is, Point& point) {
            is >> point.x >> point.y;
            return is;
        }


        friend std::ostream& operator<<(std::ostream& os, Point& point) {
            os << point.to_string();
            return os;
        }

        
    private:
        T x = 0;
        T y = 0;
};