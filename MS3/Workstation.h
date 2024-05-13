// Name: Tomas Rochwerger
// Seneca Student ID: 159432210
// Seneca email: trochwerger@myseneca.ca
// Date of completion: 04/06/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include "CustomerOrder.h"
#include <deque>


namespace seneca {
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation{nullptr};
    public:
        Workstation(const std::string& str) : Station(str) {}

        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr) { m_pNextStation = station; }
        Workstation* getNextStation() const { return m_pNextStation; }
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& order);

        // Delete copy and move constructors and assignment operators
        Workstation(const Workstation&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(Workstation&&) = delete;
    };

} // seneca

#endif //SENECA_WORKSTATION_H
