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
#include <iostream>
#include <deque>
#include <utility>

#include "Workstation.h"

namespace seneca {

    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    void Workstation::fill(std::ostream &os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder() {
        if (!m_orders.empty()) {
            if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
                if (m_pNextStation) {
                    m_pNextStation->m_orders.push_back(std::move(m_orders.front()));
                } else if (m_orders.front().isOrderFilled()) {
                    g_completed.push_back(std::move(m_orders.front()));
                } else {
                    g_incomplete.push_back(std::move(m_orders.front())); }

                m_orders.pop_front();
                return true;
            }
        }
        return false;
    }

    void Workstation::setNextStation(Workstation *station) {
        m_pNextStation = station;
    }

    Workstation *Workstation::getNextStation() const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream &os) const {
        os << getItemName() << " --> ";
        if (m_pNextStation) {
            os << m_pNextStation->getItemName();
        } else {
            os << "End of Line";
        }
        os << std::endl;
    }

    Workstation &Workstation::operator+=(CustomerOrder &&order) {
        m_orders.push_back(std::move(order));
        return *this;
    }
}
