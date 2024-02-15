#pragma once

#include <map>
#include <OpenXLSX.hpp>

#include "excel_reader.h"
#include "pair_list.h"
#include "timetable.h"

class pair_manager {
public:
    void load_pairs_from_file(const timetable &timetable) {
        excel_reader reader(timetable);
        loaded_pairs_[timetable] = reader.read_pairs();
    }

    [[nodiscard]] std::vector<pair> get_all_pairs() const {
        std::vector<pair> result;

        for (const auto &pair_list: loaded_pairs_) {
            for (const auto &pair: pair_list.second.get_pairs()) {
                result.push_back(pair);
            }
        }

        return result;
    }

    static pair_manager &get_instance() {
        static pair_manager instance;
        return instance;
    }

private:
    std::map<timetable, pair_list> loaded_pairs_;
};
