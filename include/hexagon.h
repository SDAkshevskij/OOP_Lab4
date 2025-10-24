#pragma once
#include "figure.h"
#include <algorithm>
#include <stdexcept>
#include <cmath>

template<Scalar T>
class Hexagon : public Figure<T> {
public:
    Hexagon() : Figure<T>(6) {}
    
    Hexagon(const std::initializer_list<Point<T>> &t) : Figure<T>(t) {
        if(t.size() != 6) {
            throw std::length_error("Expected 6 points!");
        }
    }
    
    Hexagon(const Hexagon<T>& other) : Figure<T>(other) {}
    
    Hexagon(Hexagon<T>&& other) noexcept : Figure<T>(std::move(other)) {}

    std::string to_string() const override {
        return "Hexagon: " + this->vertexes_to_string();
    }

    virtual std::string get_name() const {
        return "Hexagon";
    }

    double calc_area() override {
        double a = this->points[0].getDistTo(this->points[1]);
        return (3.0 * sqrt(3.0) / 2.0) * a * a;
    }

    std::istream& read_from_stream(std::istream& is) override {
        for (int i = 0; i < 6; i++) {
            Point<T> p;
            is >> p;
            this->set_point(i, p);
        }
        return is;
    }

    friend std::istream& operator>>(std::istream& is, Hexagon<T>& hexagon) {
        return hexagon.read_from_stream(is);
    }

    Hexagon<T>& operator=(const Hexagon<T>& other) {
        Figure<T>::operator=(other);
        return *this;
    }

    Hexagon<T>& operator=(Hexagon<T>&& other) noexcept {
        Figure<T>::operator=(std::move(other));
        return *this;
    }

    bool operator==(const Hexagon<T>& other) {
        return Figure<T>::operator==(other);
    }

    operator double() {
        return this->calc_area();
    }
};