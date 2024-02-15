#pragma once

#include <OpenXLSX.hpp>

#include "excel_template.h"
#include "pair_list.h"
#include "codec_converter.h"
#include "timetable.h"

class excel_reader {
public:
    explicit excel_reader(const timetable &timetable) {
        doc_ = new OpenXLSX::XLDocument();
        doc_->open(timetable.get_path());
        excel_template_ = timetable.get_template();
    }

    pair_list read_pairs();

    static std::string get_cell_value(const OpenXLSX::XLWorksheet &sheet, uint32_t row, uint16_t col) {
        auto cell = sheet.cell(row, col);

        switch (cell.value().type()) {
            case OpenXLSX::XLValueType::Empty:
                return "";
            case OpenXLSX::XLValueType::String:
                return cell.value().get<std::string>();
            case OpenXLSX::XLValueType::Integer:
                return std::to_string(cell.value().get<int>());
            default:
                return "";
        }
    }

    ~excel_reader() {
        delete doc_;
    }

private:
    OpenXLSX::XLDocument *doc_;
    excel_template excel_template_;
};
