// Name: Tomas Rochwerger
// Seneca Student ID: 159432210
// Seneca email: trochwerger@myseneca.ca
// Date of completion: 03/16/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include "Utilities.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <string_view>

namespace seneca {


    class Station {
        // Instance variables
        unsigned int m_id;
        std::string m_name;
        std::string m_description;
        unsigned int m_serialNumber;
        unsigned int m_quantity;

        // Class variables
        static unsigned int m_widthField;
        static unsigned int id_generator;

    public:
        // Custom 1-argument constructor
        explicit Station(const std::string& str);

        //Queries
        unsigned int getId() const{
            return m_id;
        }

        const std::string& getItemName() const {
            return m_name;
        }

        const std::string& getDescription() const {
            return m_description;
        }

        unsigned int getSerialNumber() const {
            return m_serialNumber;
        }

        unsigned int getNextSerialNumber() {
            return m_serialNumber++;
        }

        size_t getQuantity() const {
            return m_quantity;
        }

        static unsigned int getWidthField(){
            return m_widthField;
        }

        //Modifiers
        void updateQuantity();

        static void setWidthField(unsigned int width){
            m_widthField = width;
        }

        // Ostream Insertion
        void display(std::ostream& os, bool full) const;

    };

} // seneca

#endif //SENECA_STATION_H
