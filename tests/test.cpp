#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include "../include/point.h"
#include "../include/figure.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"
#include "../include/octagon.h"
#include "../include/figure_array.h"

// Тесты для Point
TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p.getX(), 3.5);
    EXPECT_DOUBLE_EQ(p.getY(), 4.2);
}

TEST(PointTest, DistanceCalculation) {
    Point<double> p1(0, 0);
    Point<double> p2(3, 4);
    EXPECT_DOUBLE_EQ(p1.getDistTo(p2), 5.0);
}

TEST(PointTest, EqualityOperators) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(1.1, 2.1);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);
    EXPECT_FALSE(p1 != p2);
}

TEST(PointTest, StreamOperators) {
    Point<int> p(10, 20);
    std::stringstream ss;
    ss << p;
    EXPECT_NE(ss.str().find("x: 10"), std::string::npos);
    EXPECT_NE(ss.str().find("y: 20"), std::string::npos);
    
    Point<int> p2;
    std::stringstream ss2("15 25");
    ss2 >> p2;
    EXPECT_EQ(p2.getX(), 15);
    EXPECT_EQ(p2.getY(), 25);
}

// Тесты для фигур
TEST(PentagonTest, ConstructorAndPoints) {
    Pentagon<double> pentagon{
        Point<double>(0, 0),
        Point<double>(1, 0),
        Point<double>(1.5, 0.8),
        Point<double>(0.5, 1.3),
        Point<double>(-0.5, 0.8)
    };
    
    EXPECT_EQ(pentagon.get_name(), "Pentagon");
    EXPECT_NO_THROW(pentagon.calc_area());
    EXPECT_NO_THROW(pentagon.calc_the_center_of_rotation());
}

TEST(PentagonTest, InvalidInitializerList) {
    EXPECT_THROW(
        Pentagon<double>({
            Point<double>(0, 0),
            Point<double>(1, 0)
        }),
        std::length_error
    );
}

TEST(HexagonTest, ConstructorAndPoints) {
    Hexagon<double> hexagon{
        Point<double>(0, 0),
        Point<double>(1, 0),
        Point<double>(1.5, 0.866),
        Point<double>(1, 1.732),
        Point<double>(0, 1.732),
        Point<double>(-0.5, 0.866)
    };
    
    EXPECT_EQ(hexagon.get_name(), "Hexagon");
    EXPECT_NO_THROW(hexagon.calc_area());
    EXPECT_NO_THROW(hexagon.calc_the_center_of_rotation());
}

TEST(HexagonTest, InvalidInitializerList) {
    EXPECT_THROW(
        Hexagon<double>({
            Point<double>(0, 0),
            Point<double>(1, 0)
        }),
        std::length_error
    );
}

TEST(OctagonTest, ConstructorAndPoints) {
    Octagon<double> octagon{
        Point<double>(0, 1), Point<double>(0.707, 0.707), Point<double>(1, 0),
        Point<double>(0.707, -0.707), Point<double>(0, -1), Point<double>(-0.707, -0.707),
        Point<double>(-1, 0), Point<double>(-0.707, 0.707)
    };
    
    EXPECT_EQ(octagon.get_name(), "Octagon");
    EXPECT_NO_THROW(octagon.calc_area());
    EXPECT_NO_THROW(octagon.calc_the_center_of_rotation());
}

TEST(OctagonTest, InvalidInitializerList) {
    EXPECT_THROW(
        Octagon<double>({
            Point<double>(0, 0),
            Point<double>(1, 0)
        }),
        std::length_error
    );
}


TEST(FigureArrayTest, InitializerListConstructor) {
    auto pentagon = new Pentagon<double>{Point<double>(0, 0), Point<double>(1, 0), Point<double>(1.5, 0.8),
                        Point<double>(0.5, 1.3), Point<double>(-0.5, 0.8)};

    auto hexagon = new Hexagon<double>{Point<double>(0, 0), Point<double>(1, 0), Point<double>(1.5, 0.866),
                       Point<double>(1, 1.732), Point<double>(0, 1.732), Point<double>(-0.5, 0.866)};
    
    FigureArray<Figure<double>> array{pentagon, hexagon};
    
    EXPECT_GT(array.calc_total_area(), 0);
}


// Тесты с разными скалярными типами
TEST(TemplateTest, DifferentScalarTypes) {
    // Тест с int
    Pentagon<int> pentagon_int{
        Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1),
        Point<int>(1, 2), Point<int>(-1, 1)
    };
    EXPECT_NO_THROW(pentagon_int.calc_area());
    
    // Тест с double
    Pentagon<double> pentagon_double{
        Point<double>(0, 0), Point<double>(1, 0), Point<double>(1.5, 0.8),
        Point<double>(0.5, 1.3), Point<double>(-0.5, 0.8)
    };
    EXPECT_NO_THROW(pentagon_double.calc_area());
}

// Тесты для оператора приведения к double
TEST(ConversionTest, DoubleConversion) {
    Pentagon<double> pentagon{
        Point<double>(0, 0), Point<double>(1, 0), Point<double>(1.5, 0.8),
        Point<double>(0.5, 1.3), Point<double>(-0.5, 0.8)
    };
    
    double area1 = pentagon.calc_area();
    double area2 = static_cast<double>(pentagon);
    
    EXPECT_DOUBLE_EQ(area1, area2);
}

// Тесты для проверки вычисления центра вращения
TEST(CenterOfRotationTest, PentagonCenter) {
    Pentagon<double> pentagon{
        Point<double>(0, 0), Point<double>(2, 0), Point<double>(3, 1),
        Point<double>(1.5, 2), Point<double>(-0.5, 1)
    };
    
    Point<double> center = pentagon.calc_the_center_of_rotation();
    EXPECT_NEAR(center.getX(), 1.2, 0.001);
    EXPECT_NEAR(center.getY(), 0.8, 0.001);
}

TEST(CenterOfRotationTest, HexagonCenter) {
    Hexagon<double> hexagon{
        Point<double>(0, 0), Point<double>(1, 0), Point<double>(1.5, 0.866),
        Point<double>(1, 1.732), Point<double>(0, 1.732), Point<double>(-0.5, 0.866)
    };
    
    Point<double> center = hexagon.calc_the_center_of_rotation();
    EXPECT_NEAR(center.getX(), 0.5, 0.001);
    EXPECT_NEAR(center.getY(), 0.866, 0.001);
}

// Тесты для проверки вычисления площади
TEST(AreaCalculationTest, RegularPentagonArea) {
    // Правильный пятиугольник со стороной 1
    Pentagon<double> pentagon{
        Point<double>(0, 0), Point<double>(1, 0), Point<double>(1.309, 0.9511),
        Point<double>(0.5, 1.5388), Point<double>(-0.309, 0.9511)
    };
    
    double area = pentagon.calc_area();
    EXPECT_NEAR(area, 1.720, 0.01); // Площадь правильного пятиугольника со стороной 1 ~1.720
}

// 

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}