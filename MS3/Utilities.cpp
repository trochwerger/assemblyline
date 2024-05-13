// Name: Tomas Rochwerger
// Seneca Student ID: 159432210
// Seneca email: trochwerger@myseneca.ca
// Date of completion: 03/16/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

namespace seneca {
    // Initialize delimiter to default value
    char Utilities::m_delimiter = {};

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        more = false;
        if (str[next_pos] == getDelimiter()) {
            throw std::runtime_error("Delimiter found at next_pos");
        }

        size_t next_delim_pos = str.find(getDelimiter(), next_pos);
        if (next_delim_pos == std::string::npos || next_pos >= str.length()){
            more = false;
            next_delim_pos = str.length();
        } else
            more = true;


        std::string token = str.substr(next_pos, next_delim_pos - next_pos);
        next_pos = next_delim_pos + 1;

        token = trim(token);

        if (token.length() > m_widthField) {
            setFieldWidth(token.length());
        }

        return token;
    }

    std::string Utilities::trim(const std::string &str) {
        // Remove leading and trailing spaces
        size_t start = str.find_first_not_of(' ');
        size_t end = str.find_last_not_of(' ');
        return str.substr(start, end - start + 1);
    }
} // seneca