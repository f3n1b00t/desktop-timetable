#pragma once

#include <map>
#include "pair.h"

class excel_marker
{
public:
    enum type
    {
        pair_subject,
        pair_teacher,
        pair_audience,
        pair_group,
        pair_type,
        week,
        none
    };
    
    excel_marker(const uint16_t even_week_column, const uint16_t odd_week_column) : even_week_column_(even_week_column), odd_week_column_(odd_week_column) {}
    excel_marker() : even_week_column_(-1), odd_week_column_(-1) {}
    
    static std::string get_name(const type type)
    {
        return excel_marker_names[type];
    }

    static type get_by_name(const std::string& name)
    {
        for(const auto& [key, value] : excel_marker_names)
        {
            if(value == name)
            {
                return key;
            }
        }

        return type::none;
    }

    uint16_t operator[](const week_type week) const
    {
        return week == week_type::even ? even_week_column_ : odd_week_column_;
    }

    uint16_t& operator[](const week_type week)
    {
        return week == week_type::even ? even_week_column_ : odd_week_column_;
    }

    bool operator==(const excel_marker& other) const
    {
        return even_week_column_ == other.even_week_column_ && odd_week_column_ == other.odd_week_column_;
    }

private:
    uint16_t even_week_column_;
    uint16_t odd_week_column_;

    inline static std::map<excel_marker::type, std::string> excel_marker_names = {
            {excel_marker::pair_subject, "subject"},
            {excel_marker::pair_teacher, "teacher"},
            {excel_marker::pair_audience, "audience"},
            {excel_marker::pair_group, "group"},
            {excel_marker::pair_type, "type"},
            {excel_marker::week, "week"},
            {excel_marker::none, "none"}
    };
};