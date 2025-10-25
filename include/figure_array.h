#pragma once 

#include <stdlib.h>
#include <string>
#include <initializer_list>
#include <vector>
#include "figure.h"

template<typename T>
class FigureArray {
    public:
        FigureArray() {};

        FigureArray(const std::initializer_list<T*> &t) {
            elementsAmo = t.size();
            elements = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[elementsAmo]);

            int i = 0;
            for (T* elem : t) {
                elements[i] = std::shared_ptr<T>(elem);
                i++;
            }
        }
        FigureArray(const std::initializer_list<std::shared_ptr<T>> &t) {
            elementsAmo = t.size();
            elements = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[elementsAmo]);

            int i = 0;
            for (T elem : t) {
                elements[i] = elem;
                i++;
            }
        }
        
        FigureArray(const FigureArray& other) {
            elementsAmo = other.elementsAmo;
            elements = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[elementsAmo]);

            for (int i = 0; i < elementsAmo; i++) {
                elements[i] = other.elements[i];
            }
        }

        FigureArray(FigureArray&& other) noexcept
            :elements(other.elements), elementsAmo(other.elementsAmo) {
            other.elementsAmo = 0;
            other.elements = nullptr;
        }


        friend std::ostream& operator<<(std::ostream& os, const FigureArray& array) {
            for (int i = 0; i < array.elementsAmo; i++) {
                os << *(array.elements[i]) << std::endl;
                os << "Center: " << array.elements[i]->calc_the_center_of_rotation().to_string() << std::endl;
                os << "Area: " << array.elements[i]->calc_area() << std::endl;
            }
            return os;
        }

        void print_the_center_of_rotation() {
            for (int i = 0; i < elementsAmo; i++) {
                std::cout << this->elements[i]->get_name() << " " << this->elements[i]->calc_the_center_of_rotation().to_string() << std::endl;
            }
        }

        void print_the_area_of_each() {
            for (int i = 0; i < elementsAmo; i++) {
                std::cout << this->elements[i]->get_name() << " " << this->elements[i]->calc_area() << std::endl;
            }
        }
        
        double calc_total_area() {
            double totalArea = 0;
            for (int i = 0; i < elementsAmo; i++) {
                totalArea += elements[i]->calc_area();
            }
            return totalArea;
        }
        
        void removeElem(int index) {
            auto newElements = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[elementsAmo - 1]);
            for (int i = 0; i < index; i++) {
                newElements[i] = std::move(elements[i]);
            }
            for(int i = index + 1; i < elementsAmo; i++) {
                newElements[i - 1] = std::move(elements[i]);
            }
            elementsAmo--;
            elements = newElements;
        }

        void addElem(T *elem, int index) {
            auto newElements = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[elementsAmo + 1]);
            for (int i = 0; i < index; i++) {
                newElements[i] = std::move(elements[i]);
            }
            newElements[index] = std::shared_ptr<T>(elem);
            for(int i = index + 1; i <= elementsAmo; i++) {
                newElements[i] = std::move(elements[i - 1]);
            }
            elementsAmo++;
            elements = newElements;
        }
       
    private:

        std::shared_ptr<std::shared_ptr<T>[]> elements;
        int elementsAmo = 0;
       
};