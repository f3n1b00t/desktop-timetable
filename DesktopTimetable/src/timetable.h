#pragma once

#include <string>

#include "excel_template.h"

class timetable {
public:
    timetable(std::string path, excel_template template_) : path_(std::move(path)), template_(std::move(template_)) {}

    [[nodiscard]] const std::string &get_path() const {
        return path_;
    }

    [[nodiscard]] const excel_template &get_template() const {
        return template_;
    }

    friend bool operator==(const timetable &lhs, const timetable &rhs) {
        return lhs.path_ == rhs.path_;
    }

    friend bool operator!=(const timetable &lhs, const timetable &rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const timetable &lhs, const timetable &rhs) {
        if (lhs.path_ < rhs.path_)
            return true;
        if (rhs.path_ < lhs.path_)
            return false;
        return true;
    }

    friend bool operator<=(const timetable &lhs, const timetable &rhs) {
        return rhs >= lhs;
    }

    friend bool operator>(const timetable &lhs, const timetable &rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const timetable &lhs, const timetable &rhs) {
        return !(lhs < rhs);
    }

private:
    const std::string path_;
    const excel_template template_;
};
