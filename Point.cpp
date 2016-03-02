//
// Created by Jijo on 2/27/2016.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include "Point.h"
// using namespace Clustering;


// iostream
using std::cout;
using std::endl;

// fstream
using std::ifstream;

// sstream
using std::stringstream;
using std::string;
namespace Clustering {
    unsigned int Point::__idGen = 0; // id generator

    Point::Point(int d) : __values{}
    {
        __dim = d;
        __id = __idGen;
        __idGen++;
        __values = new double[d];
        for (int i = 0; i < __dim; i++)
        {
            setValue(i, 0);
        }
    }

    Point::Point(const Point &point)
    {
        __id = point.__id;
        __dim = point.__dim;
        __values = new double[__dim];
        for (int i = 0; i < __dim; i++)
        {
            __values[i] = point.__values[i];
        }
    }

    Point& Point::operator= (const Point &point)
    {
        if (this == &point)
        {
            return *this;
        }
        this->__dim = point.__dim;
        this->__id = point.__id;
        this->__values = new double[point.__dim];

        for (int i = 0; i < __dim; i++)
        {
            this->__values[i] = point.__values[i];
        }
        return *this;
    }

    Point::~Point()
    {
        delete[] __values;
    }

    int Point::getId() const
    {
        return __id;
    }

    int Point::getDims() const
    {
        return __dim;
    }

    void Point::setValue(int index, double value)
    {
        __values[index] = value;
    }

    double Point::getValue(int index) const
    {
        return __values[index];
    }

    // Distance Formula
    double Point::distanceTo(const Point& point) const
    {
        double answer = 0;
        for (int count = 0; count < __dim; count++)
        {
            answer += pow(point.__values[count] - __values[count], 2);
        }
        return sqrt(answer);
    }

    Point& Point::operator*=(double multi)
    {
        for (int i = 0; i < __dim; i++)
        {
            __values[i] *= multi;
        }
        return *this;
    }

    Point& Point::operator/=(double div)
    {
        for (int i = 0; i < __dim; i++)
        {
            __values[i] /= div;
        }
        return *this;
    }

    const Point Point::operator*(double multi) const
    {
        Point p(*this);
        return p *= multi;
    }

    const Point Point::operator/(double div) const
    {
        Point p(*this);
        return p /= div;
    }

    double &Point::operator[] (int index)
    {
        return __values[index];
    }

    Point &operator+=(Point &lhs, const Point &rhs)
    {

        for (int i = 0; i < lhs.__dim; i++)
        {
            lhs.__values[i] += rhs.__values[i];
        }
        return lhs;
    }

    Point &operator-=(Point &lhs, const Point &rhs)
    {


        for (int i = 0; i < lhs.__dim; i++)
        {
            lhs.__values[i] -= rhs.__values[i];
        }
        return lhs;
    }

    const Point operator+(const Point &lhs, const Point &rhs)
    {
        Point p(lhs);
        return p += rhs;
    }

    const Point operator-(const Point &lhs, const Point &rhs)
    {
        Point p(lhs);
        return p -= rhs;
    }

    bool operator==(const Point &lhs, const Point &rhs)
    {
        if (lhs.__id != rhs.__id)
        {
            return false;
        }

        for (int i = 0; i < lhs.__dim; i++)
        {
            if (lhs.__values[i] != rhs.__values[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Point &lhs, const Point &rhs)
    {
        return (!(lhs == rhs));
    }

    bool operator<(const Point &lhs, const Point &rhs)
    {

        for (int i = 0; i < lhs.__dim; i++)
        {
            if (lhs.__values[i] < rhs.__values[i])
            {
                return true;
            }
        }
        return false;
    }

    bool operator>(const Point &lhs, const Point &rhs)
    {
        return !(lhs < rhs);
    }

    bool operator>=(const Point &lhs, const Point &rhs)
    {
        if (!(lhs<rhs) && (lhs>rhs))
            return true;
        return !(lhs < rhs);
    }

    bool operator<=(const Point &lhs, const Point &rhs)
    {
        if (!(lhs<rhs) && (lhs>rhs))
            return true;
        return !(lhs > rhs);
    }

    std::ostream &operator<<(std::ostream &out, const Point &point)
    {
        int i = 0;
        for (; i < point.__dim - 1; i++)
        {
            out << point.getValue(i) << ", ";
        }
        out << point.__values[i];
        return out;
    }

    std::istream &operator>>(std::istream &in, Point &p)
    {
        std::string value;
        int i = 0;
        while (getline(in, value, ','))
        {
            double d;

            d = std::stod(value);

            cout << "Value: " << d << endl;

            p.setValue(i++, d);
        }


        return in;
    }
}