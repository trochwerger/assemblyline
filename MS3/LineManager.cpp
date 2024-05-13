// Name: Tomas Rochwerger
// Seneca Student ID: 159432210
// Seneca email: trochwerger@myseneca.ca
// Date of completion: 04/06/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"
#include "LineManager.h"
#include "Workstation.h"

namespace seneca {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {

        Utilities util;
        std::string line;
        size_t nextPos;
        bool hasMoreTokens = false;

        // Opening the file
        std::ifstream fileStream(file);
        if (!fileStream)
            throw std::string("Unable to open file"); // NOLINT(*-exception-baseclass)


        while (getline(fileStream, line)){
            nextPos = 0;
            hasMoreTokens = true;
            Workstation* currStation{};
            Workstation* nextStation{};
            std::string item;
            std::string next;

            item = util.extractToken(line, nextPos, hasMoreTokens);
            auto stationIter = find_if(stations.begin(), stations.end(), [&](const auto& ws) {
                return ws->getItemName() == item;
            });
            if (stationIter != stations.end()) {
                currStation = *stationIter;
                m_activeLine.push_back(currStation);
            }

            if (hasMoreTokens) {
                next = util.extractToken(line, nextPos, hasMoreTokens);
                stationIter = find_if(stations.begin(), stations.end(), [&](const auto& s) {
                    return s->getItemName() == next;
                });
                if (stationIter != stations.end()) {
                    nextStation = *stationIter;
                    currStation->setNextStation(nextStation);
                }
            }
        }

        for_each(m_activeLine.begin(), m_activeLine.end(), [&](const auto& ws) {
            auto firstStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](const auto& other) {
                return ws == other->getNextStation();
            });
            if (firstStation == m_activeLine.end())
                m_firstStation = ws;

        });

        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations() {
        std::vector<Workstation*> reorderedStations;
        Workstation* currStation = nullptr;

        // Find the first station
        auto it = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
            return std::none_of(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* checkStation) {
                return checkStation->getNextStation() == station;
            });
        });

        if (it != m_activeLine.end())
            currStation = *it;


        // Follow the chain of stations
        while (currStation) {
            reorderedStations.push_back(currStation);
            currStation = currStation->getNextStation();
        }

        // Replace m_activeLine with the reordered stations
        m_activeLine = reorderedStations;
    }

    bool LineManager::run(std::ostream& os) {
        static size_t count;
        count++;

        os << "Line Manager Iteration: " << count << std::endl;
        // Move the order at the front of the queue onto the starting point of the line
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto& i : m_activeLine)
            i->fill(os);

        for (auto& i : m_activeLine)
            i->attemptToMoveOrder();

        return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }

    void LineManager::display(std::ostream& os) const {
        for (auto& i : m_activeLine)
            i->display(os);
    }

}