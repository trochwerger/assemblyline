// Name: Tomas Rochwerger
// Seneca Student ID: 159432210
// Seneca email: trochwerger@myseneca.ca
// Date of completion: 03/16/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"

namespace seneca {
    // Initialize class variables
    unsigned int Station::m_widthField = 0;
    unsigned int Station::id_generator = 1;

    Station::Station(const std::string &str) {
        //Local instance of Utilities
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        // name, serial number, quantity extraction
        m_name = util.extractToken(str, next_pos, more);
        m_serialNumber = std::stoi(util.extractToken(str, next_pos, more));
        m_quantity = std::stoi(util.extractToken(str, next_pos, more));

        // Update Station::m_widthField to the max value of Station::m_widthField and Utilities::m_widthField
        if (getWidthField() < util.getFieldWidth())
            setWidthField(util.getFieldWidth());


        // Lastly extract the description
        m_description = util.extractToken(str, next_pos, more);

        //Set the id
        m_id = id_generator++;
    }

    // Display information
    void Station::display(std::ostream &os, bool full) const {
        printFormatted(os, getId(), " | ", 3, '0');
        printFormatted(os, getItemName(), " | ", getWidthField(), ' ', Align::left);
        printFormatted(os, getSerialNumber(), " | ", 6, '0');

        if (full) {
            printFormatted(os, getQuantity(), " | ", 4, ' ');
            os << getDescription();
        }

        os << std::endl;
    }

} // seneca