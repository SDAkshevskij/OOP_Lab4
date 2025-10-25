#pragma once
#include "figure.h"
#include <algorithm>
#include <cmath>  

template<Scalar T>
class Octagon : public Figure<T> {
    public:
        Octagon() : Figure<T>(8) {} 
        Octagon(const std::initializer_list<Point<T>> &t): Figure<T>(t) {
            if(t.size() != 8) {
                throw std::length_error("Expected 8 points!"); 
            }
        }
        Octagon(const Octagon<T>& other): Figure<T>(other) {}
        Octagon(Octagon<T>&& other) noexcept : Figure<T>(std::move(other)) {}


        std::string to_string() const override {
            std::string res = "Octagon: " + this->vertexes_to_string();
            return res;
        }

        virtual std::string get_name() const {
            return "Octagon";
        }

        double calc_area() override {
            double a = this->points[0].getDistTo(this->points[1]);
            return 2 * (1 + sqrt(2)) * a * a;
        }

        std::istream& read_from_stream(std::istream& is) {
            for (int i = 0; i < 8; i++) {
                Point<T> p;
                is >> p;
                this->set_point(i, p);
            }
            return is;
        }

        Octagon<T>& operator=(Octagon<T>& other) {
            Figure<T>::operator=(other);
            return *this;
        }

        bool operator==(Octagon<T>& other) {
            return Figure<T>::operator==(other);
        }

        operator double() {
            return this->calc_area();
        }
    
};