#pragma once

#include <map>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iomanip>

#include "pair.h"
#include "excel_marker.h"

class excel_template
{
public:
    void add_marker(const excel_marker::type marker, const uint16_t column, const week_type week)
    {
        all_markers_[marker][week] = column;
    }

    void add_marker(const excel_marker::type marker, const uint16_t even_column, const uint16_t odd_column)
    {
        all_markers_[marker] = {even_column, odd_column};
    }

    void add_day_marker(day_of_week day, uint32_t row)
    {
        day_markers_.insert({day, row});
    }
    
    const excel_marker& operator[](const excel_marker::type marker)
    {
        return all_markers_[marker];
    }

    uint32_t operator[](const day_of_week day)
    {
        return day_markers_[day];
    }

    void set_template_name(const std::string& name)
    {
        template_name_ = name;
    }

    void set_pairs_per_day(const unsigned int pairs_per_day)
    {
        pairs_per_day_ = pairs_per_day;
    }

    [[nodiscard]] const std::string& get_template_name() const {
        return template_name_;
    }

    [[nodiscard]] const std::map<day_of_week, uint32_t>& get_day_markers() const
    {
        return day_markers_;
    }

    [[nodiscard]] unsigned int get_pairs_per_day() const
    {
        return pairs_per_day_;
    }
    
    void save_to_file(const std::string& path) const
    {
        nlohmann::json data;

        data["template_name"] = template_name_;
        data["day_markers"] = day_markers_;
        data["pairs_per_day"] = pairs_per_day_;

        nlohmann::json markers;

        for(const auto& [key, marker] : all_markers_)
        {
            markers[excel_marker::get_name(key)] = {
                    marker[week_type::even],
                    marker[week_type::odd]
            };
        }

        data["all_markers"] = markers;

        std::ofstream f(path);
        f << std::setw(4) << data << std::endl;
    }

    excel_template& load_from_file(const std::string& path)
    {

        std::ifstream f(path);
        auto data = nlohmann::json::parse(f);

        template_name_ = data.at("template_name").get<std::string>();
        day_markers_ = data.at("day_markers").get<std::map<day_of_week, uint32_t>>();
        pairs_per_day_ = data.at("pairs_per_day").get<unsigned int>();

        for(const auto& [key, value] : data.at("all_markers").get<std::map<std::string, nlohmann::json>>())
        {
            auto marker_type = excel_marker::get_by_name(key);
            all_markers_[marker_type][week_type::even] = value.at(0).get<uint16_t>();
            all_markers_[marker_type][week_type::odd] = value.at(1).get<uint16_t>();
        }

        return *this;
    }

private:
    std::string template_name_ { "shablon" };
    unsigned int pairs_per_day_ { 0 };
    std::map<excel_marker::type, excel_marker> all_markers_;
    std::map<day_of_week, uint32_t> day_markers_;
};

