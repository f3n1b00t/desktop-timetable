#pragma once

#include <string>

enum class week_type {
    odd,
    even
};

enum class day_of_week {
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday
};

class pair {
public:
    pair(const std::wstring &subject,
         const std::wstring &teacher,
         const std::wstring &audience,
         const std::wstring &group,
         const std::wstring &type,
         const day_of_week day,
         const week_type week,
         const unsigned int position)
            : subject_(subject),
              teacher_(teacher),
              audience_(audience),
              group_(group),
              type_(type),
              day_(day),
              week_(week),
              position_(position) {
    }

    const std::wstring &get_subject() const {
        return subject_;
    }

    const std::wstring &get_teacher() const {
        return teacher_;
    }

    const std::wstring &get_audience() const {
        return audience_;
    }

    const std::wstring &get_group() const {
        return group_;
    }

    const std::wstring &get_type() const {
        return type_;
    }

    const day_of_week get_day() const {
        return day_;
    }

    week_type get_week() const {
        return week_;
    }

    unsigned int get_position() const {
        return position_;
    }

    bool operator==(const pair &other) const {
        return subject_ == other.subject_
               && teacher_ == other.teacher_
               && audience_ == other.audience_
               && group_ == other.group_
               && type_ == other.type_
               && day_ == other.day_
               && week_ == other.week_
               && position_ == other.position_;
    }

    bool operator!=(const pair &other) const {
        return !(*this == other);
    }

private:
    const std::wstring subject_;
    const std::wstring teacher_;
    const std::wstring audience_;
    const std::wstring group_;
    const std::wstring type_;
    const day_of_week day_;
    const week_type week_;
    const unsigned int position_;
};

class pair_builder {
public:
    pair_builder() = default;

    pair_builder &with_subject(const std::wstring &subject) {
        subject_ = subject;
        return *this;
    }

    pair_builder &with_teacher(const std::wstring &teacher) {
        teacher_ = teacher;
        return *this;
    }

    pair_builder &with_audience(const std::wstring &audience) {
        audience_ = audience;
        return *this;
    }

    pair_builder &with_group(const std::wstring &group) {
        group_ = group;
        return *this;
    }

    pair_builder &with_type(const std::wstring &type) {
        type_ = type;
        return *this;
    }

    pair_builder &with_day(const day_of_week day) {
        day_ = day;
        return *this;
    }

    pair_builder &with_week(const week_type week) {
        week_ = week;
        return *this;

    }

    pair_builder &with_position(const unsigned int position) {
        position_ = position;
        return *this;
    }

    const std::wstring &get_subject() const {
        return subject_;
    }

    const std::wstring &get_teacher() const {
        return teacher_;
    }

    const std::wstring &get_audience() const {
        return audience_;
    }

    const std::wstring &get_group() const {
        return group_;
    }

    const std::wstring &get_type() const {
        return type_;
    }

    day_of_week get_day() const {
        return day_;
    }

    week_type get_week() const {
        return week_;
    }

    unsigned get_position() const {
        return position_;
    }

    pair build() const {
        return pair{subject_, teacher_, audience_, group_, type_, day_, week_, position_};
    }


private:
    std::wstring subject_;
    std::wstring teacher_;
    std::wstring audience_;
    std::wstring group_;
    std::wstring type_;
    day_of_week day_;
    week_type week_;
    unsigned int position_;
};
