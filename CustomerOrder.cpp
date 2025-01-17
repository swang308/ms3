/*-----------------------------------------------------------
Name: Shanyun Wang | Seneca email: swang308@myseneca.ca
Seneca Student ID: 133159228 | Date: 2024-04-06

OOP345 Milestone 3
Module: CustomerOrder
Filename: CustomerOrder.cpp
Version 1.0
Author	Shanyun Wang
-----------------------------------------------------------
Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>

#include "CustomerOrder.h"
#include "Utilities.h"

namespace seneca {
    size_t CustomerOrder::m_widthField{0};

    CustomerOrder::CustomerOrder(const std::string &src) {
        Utilities util;
        size_t next_pos{0};
        bool more{true};

        m_name = util.extractToken(src, next_pos, more);
        m_product = util.extractToken(src, next_pos, more);

        while (more) {
            m_cntItem = std::count(src.begin(), src.end(), seneca::Utilities::getDelimiter()) - 1;
            m_lstItem = new Item *[m_cntItem];
            for (size_t i = 0; i < m_cntItem; i++) {
                m_lstItem[i] = new Item(util.extractToken(src, next_pos, more));
            }
        }

        if (util.getFieldWidth() > m_widthField) {
            m_widthField = util.getFieldWidth();
        }
    }


    CustomerOrder::CustomerOrder(const CustomerOrder &src) {
        throw std::string("Copy Constructor is not allowed");
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&src) noexcept {
        *this = std::move(src);
    }

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&src) noexcept {
        if (this != &src) {
            for (size_t i = 0; i < m_cntItem; i++) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;

            src.m_name.clear();
            src.m_product.clear();
            src.m_cntItem = 0;
            src.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string &itemName) const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station &station, std::ostream &os) {
        bool found = false;
        for (size_t i = 0; i < m_cntItem && !found; i++) {
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]"
                       << std::endl;
                    found = true;
                } else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName
                       << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream &os) const {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber
               << std::setfill(' ') << "] "
               << std::left << std::setw(static_cast<int>(m_widthField)) << m_lstItem[i]->m_itemName
               << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }

    const std::string &CustomerOrder::getName() const {
        return m_name;
    }

}
