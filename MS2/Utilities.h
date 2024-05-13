// Name: Tomas Rochwerger
// Seneca Student ID: 159432210
// Seneca email: trochwerger@myseneca.ca
// Date of completion: 03/16/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H
#include <iostream>
#include <fstream>

namespace seneca {
    // enum class used as parameter for printFormatted
    enum class Align {
        left,
        right
    };

    class Utilities {
        // Instance variables
        unsigned int m_widthField = 1;

        // Class variables
        static char m_delimiter;

        public:
        // Set field width to value passed
        void setFieldWidth(unsigned int newWidth){m_widthField = newWidth;}

        // Query field width
        size_t getFieldWidth() const{ return m_widthField; }

        // Token extraction
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

        // Class Functions

        // Set delimiter to value passed
        static void setDelimiter(char newDelimiter){m_delimiter = newDelimiter;}
        // Query delimiter
        static char getDelimiter(){return m_delimiter;}

        // String trimming helper function
        static std::string trim(const std::string& str);
    };

    template <typename T>
    const std::ostream& printFormatted(std::ostream& os, T item, const char* delim, unsigned int width = 0, char fill = ' ', Align direction = Align::right){
        // Set alignment based on direction parameter
        switch (direction) {
            case Align::left:
                os.unsetf(std::ios::right);
                os.setf(std::ios::left);
                break;
            case Align::right:
                os.unsetf(std::ios::left);
                os.setf(std::ios::right);
                break;
        }

        // Set fill and width
        os.fill(fill);
        os.width(width);

        // Print item and delimiter if not nullptr
        os << item;
        if(delim != nullptr){
            os << delim;
        }
        return os;
    }

} // seneca

#endif //SENECA_UTILITIES_H
