/*-----------------------------------------------------------
Name: Shanyun Wang | Seneca email: swang308@myseneca.ca
Seneca Student ID: 133159228 | Date: 2024-04-06

OOP345 Milestone 3
Module: CustomerOrder
Filename: CustomerOrder.h
Version 1.0
Author	Shanyun Wang
-----------------------------------------------------------
Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include "Station.h"

namespace seneca {
    struct Item {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        explicit Item(const std::string &src) : m_itemName(src) {};
    };

    class CustomerOrder {
        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{};
        Item **m_lstItem{};
        static size_t m_widthField;
    public:
        CustomerOrder() = default;
        explicit CustomerOrder(const std::string &);

        CustomerOrder(const CustomerOrder &);
        CustomerOrder &operator=(const CustomerOrder &) = delete;

        CustomerOrder(CustomerOrder &&) noexcept;
        CustomerOrder &operator=(CustomerOrder &&) noexcept;

        ~CustomerOrder();

        bool isOrderFilled() const;
        bool isItemFilled(const std::string &itemName) const;
        void fillItem(Station &station, std::ostream &os);
        void display(std::ostream &os) const;

        const std::string &getName() const;
    };
}
#endif //SENECA_CUSTOMERORDER_H
