/*-----------------------------------------------------------
Name: Shanyun Wang | Seneca email: swang308@myseneca.ca
Seneca Student ID: 133159228 | Date: 2024-04-06

OOP345 Milestone 3
Module: Workstation
Filename: Workstation.cpp
Version 1.0
Author	Shanyun Wang
-----------------------------------------------------------
Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <deque>

#include "CustomerOrder.h"
#include "Station.h"

namespace seneca {
        extern std::deque<CustomerOrder> g_pending;
        extern std::deque<CustomerOrder> g_completed;
        extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders{};
        Workstation* m_pNextStation{};
    public:
        explicit Workstation(const std::string& src) : Station(src) {}
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& order);
    };
}

#endif //SENECA_WORKSTATION_H
