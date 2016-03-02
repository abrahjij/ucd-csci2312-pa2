//
// Created by Jijo on 2/27/2016.
//

#include <iostream>
#include <string>
#include<sstream>
#include <algorithm>
#include "Cluster.h"
#include "Point.h"
using namespace Clustering;
namespace Clustering
{
    typedef Point * PointPtr;

    LNode::LNode(const Point &p, LNodePtr n) : point(p), next(n) {}

    Cluster::Cluster()
    {
        __size = 0;
        __points = NULL;
    }

    Cluster::Cluster(const Cluster &cluster) : Cluster()
    {
        for (int count = 0; count < cluster.__size; ++count)
        {
            add(cluster[count]);
        }
    }

    Cluster &Cluster::operator=(const Cluster &cluster)
    {
        if (this == &cluster)
            return *this;
        else
        {
            if (__points != NULL)
            {
                LNodePtr currPtr = __points;
                LNodePtr nextPtr = NULL;
                while (currPtr != NULL)
                {
                    nextPtr = currPtr->next;
                    delete currPtr;
                    currPtr = nextPtr;
                }
                __size = 0;
                __points = NULL;
            }
            for (int count = 0; count < cluster.__size; ++count) {
                add(cluster[count]);
            }
        }
        return *this;
    }

    Cluster::~Cluster()
    {	if (__points != NULL)
        {
            LNodePtr prevPtr = __points;
            LNodePtr currPtr = NULL;
            while (prevPtr != NULL)
            {
                currPtr = prevPtr->next;
                delete  prevPtr;
                prevPtr = currPtr;
            }
        }
        // simple an easy
    }

    int Cluster::getSize() const
    {
        return __size;
    }

    void Cluster::add(const Point &point) {
        Point p(point);
        LNodePtr newP = new LNode(p, NULL);
        LNodePtr prev = __points;
        LNodePtr next = __points;
        if (__points == NULL) {
            __points = newP;
            __size++;
        }
        else if (__points->next == NULL) {
            if (point < __points->point) {
                __points = newP;
                newP->next = prev;
                __size++;
            }
            else {
                __points->next = newP;
                __size++;
            }
        }
        else {
            next = next->next;
            if (point < prev->point) {
                __points = newP;
                newP->next = prev;
                __size++;
                return;
            }
            while (next != NULL) {
                if (point < next->point) {
                    prev->next = newP;
                    newP->next = next;
                    __size++;
                    return;
                }
                next = next->next;
                prev = prev->next;
            }
            prev->next = newP;
            __size++;
        }
    }

    const Point &Cluster::remove(const Point &cIn)
    {
        LNodePtr prev = __points;

        if (prev->next == NULL)
        {
            if (prev->point == cIn)
            {
                __points = NULL;
                __size = 0;
                delete prev;
            }
        }
        else
        {
            bool found = false;
            prev = __points;
            LNodePtr current = __points->next;

            if (__points->point == cIn)
            {
                found = true;
                __points = current;
                --__size;
                delete prev;
            }
            for (current ; !found && current != NULL; current = current->next)
            {
                if (current->point == cIn)
                {
                    found = true;
                    prev->next = current->next;
                    --__size;
                    delete current;
                }
                else
                {
                    prev = current;
                }
            }
        }
        return cIn;
    }

    bool Cluster::contains(const Point &cIn)
    {
        bool found = false;

        LNodePtr current = __points;

        for (current ; !found && current != NULL; current = current->next)
            if (current->point == cIn)
            {
                found = true;
            }

        return found;
    }

    const Point &Cluster::operator[](unsigned int index) const
    {

        if (__points != NULL && index < __size && index >= 0)
        {
            LNodePtr current = __points;

            for (int position = 0; position < index; ++position)
            {
                current = current->next;
            }

            return current->point;
        }
        else return NULL;
    }

    Cluster &Cluster::operator+=(const Point &point)
    {
        add(point);
        return *this;
    }

    Cluster &Cluster::operator-=(const Point &cIn)
    {
        remove(cIn);
        return *this;
    }

    Cluster &Cluster::operator+=(const Cluster &clusterIn)
    {

        LNodePtr current_rhs = clusterIn.__points;

        for (current_rhs; current_rhs != NULL; current_rhs = current_rhs->next)
        {
            if (!(this->contains(current_rhs->point)))
                add(current_rhs->point);
        }
        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &clusterIn)
    {

        LNodePtr current_rhs = clusterIn.__points;

        for (current_rhs; current_rhs != NULL; current_rhs = current_rhs->next)
        {
            if ((this->contains(current_rhs->point)))
                remove(current_rhs->point);
        }
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const Cluster &clusterIn)
    {
        LNodePtr current = clusterIn.__points;

        if (&current != NULL)
        {
            for (current; &current->point != NULL; current = current->next)
            {
                os << current->point;
                if (&current->next != NULL)
                    os << "\n";
            }
        }
        return os;
    }

    std::istream &operator>>(std::istream &istream, Clustering::Cluster &cluster)
    {
        std::string line;
        while (getline(istream, line))
        {
            int d = std::count(line.begin(),line.end(),',');
            Point *pointPtr = new Point(d + 1);
            std::stringstream lineStream(line);

            lineStream >> *pointPtr;

            cluster.add(*pointPtr);
        }
        return istream;
    }

    bool operator==(const Cluster &cluster1, const Cluster &cluster2)
    {
        if (cluster1.__size != cluster2.__size)
        {
            return false;
        }
        LNodePtr current1 = cluster1.__points;
        LNodePtr current2 = cluster2.__points;
        bool equal = true;
        while (current1 != NULL && current2 != NULL)
        {
            if (current1->point != current2->point)
            {
                equal = false;
            }
            current1 = current1->next;
            current2 = current2->next;
        }

        return equal;
    }

    const Cluster operator+(const Cluster &clusterIn, const Point &cIn)
    {
        Cluster newCluster(clusterIn);
        return newCluster += cIn;
    }

    bool operator!=(const Cluster &lhs, const Cluster &rhs)
    {
        return (!(lhs == rhs));
    }

    const Cluster operator-(const Cluster &clusterIn, const Point &cIn)
    {
        Cluster newCluster(clusterIn);
        return newCluster -= cIn;
    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) // (asymmetric) difference
    {
        Cluster newCluster(lhs);
        return newCluster -= rhs;
    }

    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) // union
    {
        Cluster newCluster(lhs);
        return newCluster += rhs;
    }

}
