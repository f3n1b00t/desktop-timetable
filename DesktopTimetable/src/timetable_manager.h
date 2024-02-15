#pragma once

#include <map>
#include <string>

#include "timetable.h"

class timetable_manager {
public:
    void add_timetable(const std::string &name, const timetable &timetable) {
        timetables_.insert({name, timetable});
    }

    [[nodiscard]] const timetable &get_timetable(const std::string &name) const {
        return timetables_.at(name);
    }

    void remove_timetable(const std::string &name) {
        timetables_.erase(name);
    }

    [[nodiscard]] const std::map<std::string, timetable> &get_timetables() const {
        return timetables_;
    }

    static timetable_manager &get_instance() {
        static timetable_manager instance;
        return instance;
    }

private:
    std::map<std::string, timetable> timetables_;
};
