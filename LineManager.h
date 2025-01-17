/*-----------------------------------------------------------
Name: Shanyun Wang | Seneca email: swang308@myseneca.ca
Seneca Student ID: 133159228 | Date: 2024-04-06

OOP345 Milestone 3
Module: LineManager
Filename: LineManager.h
Version 1.0
Author	Shanyun Wang
-----------------------------------------------------------
Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <vector>
#include "Workstation.h"

namespace seneca {
    class LineManager {
        std::vector<Workstation*> m_activeLine{};
        size_t m_cntCustomerOrder{};
        Workstation* m_firstStation{};
    public:
        LineManager(const std::string& file, std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };
}

#endif //SENECA_LINEMANAGER_H
