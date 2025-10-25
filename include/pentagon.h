#pragma once
#include "figure.h"
#include <algorithm>
#include <stdexcept>
#include <cmath>

template<Scalar T>
class Pentagon : public Figure<T> {
public:
    Pentagon() : Figure<T>(5) {}
    
    
    Pentagon(const std::initializer_list<Point<T>> &t) : Figure<T>(t) {
        if(t.size() != 5) {
            throw std::length_error("Expected 5 points!");
        }
    }
    
    Pentagon(const Pentagon<T>& other) : Figure<T>(other) {}
    
    Pentagon(Pentagon<T>&& other) noexcept : Figure<T>(std::move(other)) {}

    std::string to_string() const override {
        return "Pentagon: " + this->vertexes_to_string();
    }

    virtual std::string get_name() const {
        return "Pentagon";
    }

    double calc_area() override {
        double a = this->points[0].getDistTo(this->points[1]);
        return (1.0/4.0) * sqrt(5.0 * (5.0 + 2.0 * sqrt(5.0))) * a * a;
    }

    std::istream& read_from_stream(std::istream& is) override {
        for (int i = 0; i < 5; i++) {
            Point<T> p;
            is >> p;
            this->set_point(i, p);
        }
        return is;
    }

    friend std::istream& operator>>(std::istream& is, Pentagon<T>& pentagon) {
        return pentagon.read_from_stream(is);
    }

    Pentagon<T>& operator=(const Pentagon<T>& other) {
        Figure<T>::operator=(other);
        return *this;
    }

    Pentagon<T>& operator=(Pentagon<T>&& other) noexcept {
        Figure<T>::operator=(std::move(other));
        return *this;
    }

    bool operator==(const Pentagon<T>& other) {
        return Figure<T>::operator==(other);
    }

    operator double() {
        return this->calc_area();
    }
};