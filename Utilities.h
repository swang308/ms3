/*-----------------------------------------------------------
Name: Shanyun Wang | Seneca email: swang308@myseneca.ca
Seneca Student ID: 133159228 | Date: 2024-04-06

OOP345 Milestone 3
Module: Utilities
Filename: Utilities.h
Version 1.0
Author	Shanyun Wang
-----------------------------------------------------------
Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

namespace seneca {
    class Utilities {
        size_t m_widthField{1};
        static char m_delimiter;    // share the same delimiter among all Utilities objects
    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string &str, size_t &next_pos, bool &more);
        void trim(std::string &str);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };
}
#endif //SENECA_UTILITIES_H
