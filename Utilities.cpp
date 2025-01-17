/*-----------------------------------------------------------
Name: Shanyun Wang | Seneca email: swang308@myseneca.ca
Seneca Student ID: 133159228 | Date: 2024-04-06

OOP345 Milestone 3
Module: Utilities
Filename: Utilities.cpp
Version 1.0
Author	Shanyun Wang
-----------------------------------------------------------
Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <algorithm>
#include <string>
#include "Utilities.h"

namespace seneca {
    char Utilities::m_delimiter = ',';

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    void Utilities::setDelimiter(const char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }

std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more) {
    more = false;
    std::string token;

    // find the next delimiter
    if (next_pos < str.length()) {
        size_t end_pos = str.find(m_delimiter, next_pos);
        // if no delimiter is found, the token is the last token in the string
        if (end_pos == next_pos) {
            throw std::string("No token between delimiters");
        }
        //if no delimiter is found, the token is the last token in the string
        if (end_pos == std::string::npos) {
            token = str.substr(next_pos);
        } else {
            // if a delimiter is found, the token is the substring between next_pos and end_pos
            token = str.substr(next_pos, end_pos - next_pos);
            more = true;
            next_pos = end_pos + 1;
        }

        trim(token);
        m_widthField = std::max(m_widthField, token.length());
    } else {
        throw std::string("next_pos is out of range");
    }
    return token;
}

void Utilities::trim(std::string &str) {
str.erase(0, str.find_first_not_of(' '));
str.erase(str.find_last_not_of(' ') + 1);
}
}
