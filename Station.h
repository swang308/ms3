/*-----------------------------------------------------------
Name: Shanyun Wang | Seneca email: swang308@myseneca.ca
Seneca Student ID: 133159228 | Date: 2024-04-06

OOP345 Milestone 3
Module: Station
Filename: Station.h
Version 1.0
Author	Shanyun Wang
-----------------------------------------------------------
Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>

namespace seneca {
    class Station {
        size_t m_id{};
        std::string m_name{};
        std::string m_desc{};
        size_t m_serial{};
        size_t m_quantity{};

        static size_t m_widthField;
        static size_t id_generator;
    public:
        explicit Station(const std::string &str);
        const std::string &getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream &os, bool full) const;
    };
}
#endif //SENECA_STATION_H
