// Name: Tomas Rochwerger
// Seneca Student ID: 159432210
// Seneca email: trochwerger@myseneca.ca
// Date of completion: 04/06/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"
#include "Station.h"
#include "CustomerOrder.h"

namespace seneca {
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    void Workstation::fill(std::ostream &os) {
        if(!m_orders.empty())
            m_orders.front().fillItem(*this, os);
    }

    bool Workstation::attemptToMoveOrder() {
        if (!m_orders.empty()) {
            if (m_orders.front().isItemFilled(getItemName()) || getQuantity()==0) {
                if (m_pNextStation) {
                    *m_pNextStation += std::move(m_orders.front());
                } else {
                    if (m_orders.front().isOrderFilled()) {
                        g_completed.push_back(std::move(m_orders.front()));
                    } else
                        g_incomplete.push_back(std::move(m_orders.front()));
                }
                m_orders.pop_front();
                return true;
            }
        }
        return false;
    }

    void Workstation::display(std::ostream& os) const {
        os << getItemName() << " --> ";
        if (m_pNextStation) {
            os << m_pNextStation->getItemName();
        } else
            os << "End of Line";

        os << std::endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& order) {
        m_orders.push_back(std::move(order));
        return *this;
    }
} // seneca