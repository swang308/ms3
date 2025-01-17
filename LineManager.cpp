/*-----------------------------------------------------------
Name: Shanyun Wang | Seneca email: swang308@myseneca.ca
Seneca Student ID: 133159228 | Date: 2024-04-06

OOP345 Milestone 3
Module: LineManager
Filename: LineManager.cpp
Version 1.0
Author	Shanyun Wang
-----------------------------------------------------------
Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>

#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"

namespace seneca {

    LineManager::LineManager(const std::string &file, std::vector<Workstation *> &stations)
            : m_cntCustomerOrder(0), m_firstStation(nullptr) {
        std::ifstream ifstr(file);
        if (!ifstr) {
            throw std::runtime_error("File not found: " + file);
        } else {
            std::string t_line, t_item, f_item, s_item;
            size_t pos{0};
            bool more{true};

            std::vector<Workstation *> t_vector;
            Utilities t_util;
            seneca::Utilities::setDelimiter('|');

            while (getline(ifstr, t_line)) {
                pos = 0;
                more = true;
                f_item = t_util.extractToken(t_line, pos, more);

                auto f_item_wsp = *std::find_if(stations.begin(), stations.end(), [&](Workstation *sp) {
                    return sp->getItemName() == f_item;
                });
                m_activeLine.push_back(f_item_wsp);
                t_vector.push_back(f_item_wsp);

                if (more) {
                    s_item = t_util.extractToken(t_line, pos, more);
                    auto s_item_wsp = *std::find_if(stations.begin(), stations.end(), [&](Workstation *sp) {
                        return sp->getItemName() == s_item;
                    });

                    f_item_wsp->setNextStation(s_item_wsp);
                }
            }

            // reorder the stations in the active line, find the first station
            auto t_ws = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *sp1) {
                return std::none_of(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *sp2) {
                    return sp2->getNextStation() == sp1;
                });
            });

            if (t_ws != m_activeLine.end()) {
                m_firstStation = *t_ws;
            }

            m_cntCustomerOrder = g_pending.size();
        }
    }

    void LineManager::reorderStations() {
        std::vector<Workstation *> v_wsp;
        v_wsp.push_back(m_firstStation);

        while (auto t_wsp = v_wsp.back()->getNextStation()) {
            v_wsp.push_back(t_wsp);
        }

        m_activeLine = std::move(v_wsp);
    }

    bool LineManager::run(std::ostream &os) {
        static size_t iteration{1};

        os << "Line Manager Iteration: " << iteration++ << std::endl;
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *ws) {
            ws->fill(os);
        });

        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *ws) {
            ws->attemptToMoveOrder();
        });

        return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }

    void LineManager::display(std::ostream &os) const {
        for (auto i: m_activeLine) {
            i->display(os);
        }
    }
}
