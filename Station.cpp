/*-----------------------------------------------------------
Name: Shanyun Wang | Seneca email: swang308@myseneca.ca
Seneca Student ID: 133159228 | Date: 2024-04-06

OOP345 Milestone 3
Module: Station
Filename: Station.cpp
Version 1.0
Author	Shanyun Wang
-----------------------------------------------------------
Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>
#include "Station.h"
#include "Utilities.h"

namespace seneca {
    size_t Station::m_widthField{0};
    size_t Station::id_generator{0};

    Station::Station(const std::string &str) {
        Utilities util;
        size_t next_pos{0};
        bool more{false};

        try {
            m_id = ++id_generator;

            m_name = util.extractToken(str, next_pos, more);
            m_widthField = std::max(m_widthField, util.getFieldWidth());

            m_serial = std::stoi(util.extractToken(str, next_pos, more));
            m_quantity = std::stoi(util.extractToken(str, next_pos, more));
            m_desc = util.extractToken(str, next_pos, more);

            util.trim(m_name);
            util.trim(m_desc);

        } catch (const char* msg) {
            std::cerr << "Error: " << msg << std::endl;
        }
    }

    const std::string &Station::getItemName() const {
        return m_name;
    }

    size_t Station::getNextSerialNumber() {
        return m_serial++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0) {
            m_quantity--;
        }
    }

    void Station::display(std::ostream &os, bool full) const {

        os << std::setw(3) << std::setfill('0') << std::right << m_id << " | "
           << std::setw(static_cast<int>(m_widthField)) << std::setfill(' ') << std::left << m_name << " | "
           << std::setw(6) << std::setfill('0') << std::right << m_serial << " | ";
        if (full) {
            os << std::setw(4) << std::setfill(' ') << std::right << m_quantity << " | "
               << m_desc;
        }
        os << std::endl;
    }
}