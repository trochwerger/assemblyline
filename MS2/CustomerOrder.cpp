// Name: Tomas Rochwerger
// Seneca Student ID: 159432210
// Seneca email: trochwerger@myseneca.ca
// Date of completion: 03/23/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "CustomerOrder.h"
#include "Utilities.h"
namespace seneca{
    size_t CustomerOrder::m_widthField = 0;
    CustomerOrder::CustomerOrder(const std::string &str) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;
        m_name = util.extractToken(str, next_pos, more);
        m_product = util.extractToken(str, next_pos, more);
        std::string temp = str.substr(next_pos, str.length() - next_pos);
        m_cntItem = std::count(temp.begin(), temp.end(), util.getDelimiter()) + 1;
        m_lstItem = new Item *[m_cntItem];
        for (size_t i = 0; i < m_cntItem; i++) {
            m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
        }
        if (m_widthField < util.getFieldWidth()) {
            m_widthField = util.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&src) noexcept {
        *this = std::move(src);
    }

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&src) noexcept {
        //Check for self assignment
        if (this != &src) {
            // Cleanup
            for (size_t i = 0; i < m_cntItem; i++) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;


            //Shallow copy
            m_cntItem = src.m_cntItem;

            m_name = std::move(src.m_name);
            m_product = std::move(src.m_product);
            m_lstItem = src.m_lstItem;

            // Reset src
            src.m_name = "";
            src.m_product = "";
            src.m_cntItem = 0;
            src.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        std::for_each(m_lstItem, m_lstItem + m_cntItem, [](Item *item) { delete item; });
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        return std::all_of(m_lstItem, m_lstItem + m_cntItem, [](const Item *item) { return item->m_isFilled; });
    }

    bool CustomerOrder::isItemFilled(const std::string &itemName) const {
        if(itemExists(itemName)){
            return std::any_of(m_lstItem, m_lstItem + m_cntItem, [&](const Item *item) { return item->m_itemName == itemName && item->m_isFilled; });
        } else {
            return true;
        }
    }

    void CustomerOrder::fillItem(Station &station, std::ostream &os) {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == station.getItemName()) {
                if (!m_lstItem[i]->m_isFilled) {
                    if (station.getQuantity() >= 1) {
                        station.updateQuantity();
                        m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                        os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                        break;
                    } else {
                        os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    }
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream &os) const {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[";
            printFormatted(os, m_lstItem[i]->m_serialNumber, "] ", 6, '0', Align::left);
            printFormatted(os, m_lstItem[i]->m_itemName, " - ", m_widthField, ' ', Align::left);
            if (m_lstItem[i]->m_isFilled) {
                os << "FILLED";
            } else {
                os << "TO BE FILLED";
            }
            os << std::endl;
        }

    }

    bool CustomerOrder::itemExists(const std::string &itemName) const {
        return std::any_of(m_lstItem, m_lstItem + m_cntItem, [&](const Item *item) { return item->m_itemName == itemName; });
    }
}