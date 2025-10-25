#pragma once 

#include "point.h"
#include <stdlib.h>
#include <string>
#include <initializer_list>
#include <memory>
#include <concepts>
#include <type_traits>



template<Scalar T>
class Figure {
    public:

        Figure() {}
        Figure(int pointsAmo)
            : pointsAmo(pointsAmo), points(std::make_unique<Point<T>[]>(pointsAmo)){}
    
        Figure(const std::initializer_list<Point<T>> &t) : Figure<T>(t.size()){

            int i = 0;
            for (Point<T> p: t) {
                points[i] = p;
                i++;
            }

        }

        Figure(const Figure<T>& other) : Figure<T>(other.pointsAmo) {
            for (int i = 0; i < pointsAmo; i++) {
                points[i] = other.points[i];
            }
        }

        Figure(Figure<T>&& other)
            : points(std::move(other.points)), pointsAmo(other.pointsAmo) {
                other.points = nullptr;
                other.pointsAmo = 0;
        }

        virtual ~Figure() noexcept {}

        virtual std::string to_string() const  {return "";}
        virtual std::string get_name() const  {return "";}
        virtual std::istream& read_from_stream(std::istream &is) {return is;}


        Point<T> calc_the_center_of_rotation() {
            T xSum = 0;
            T ySum = 0;
            for (int i = 0; i < pointsAmo; i++) {
                xSum += points[i].getX();
                ySum += points[i].getY();
            }
            return Point<T>(xSum / pointsAmo, ySum / pointsAmo);
        }

        void set_point(int index, Point<T> point) {
            points[index] = point;
        }

        virtual double calc_area() {return 0;}


        friend std::ostream& operator<<(std::ostream& os, const Figure<T>& figure) {
            os << figure.to_string();
            return os;
        }

        friend std::istream& operator>>(std::istream& is, Figure<T>& figure) {
            return figure.read_from_stream(is);
        }

        bool operator==(const Figure<T>& other) const {
            if (this == &other) return true;
            if(pointsAmo != other.pointsAmo) {
                return false;
            }
            for (int i = 0; i < pointsAmo; i++) {
                if (points[i] != other.points[i]) {
                    return false;
                }
            }
            return true;
        }

        Figure<T>& operator=(Figure<T>&& other) noexcept {
            if (this != &other) {
                points = std::move(other.points);
                pointsAmo = other.pointsAmo;
                other.pointsAmo = 0;
            }
            return *this;
        }

        operator double() {
            return this->calc_area();
        }

    protected:
        std::unique_ptr<Point<T>[]> points;
        int pointsAmo;
        Point<T> getCenterPoint() {
            double xSum = 0;
            double ySum = 0;
            for (int i = 0; i < pointsAmo; i++) {
                xSum += points[i].getX();
                ySum += points[i].getY();
            }
            return Point<T>(xSum / pointsAmo, ySum / pointsAmo);
        }

        std::string vertexes_to_string() const {
            std::string res = "";
            for (int i = 0; i < pointsAmo; i++) {
                res += "V" + std::to_string(i) + ": " + points[i].to_string() + " ";
            }
            return res;
        }
};