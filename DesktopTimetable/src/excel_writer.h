#pragma once
#include <OpenXLSX.hpp>
#include <utility>

#include "pair.h"
#include "excel_template.h"

class excel_writer
{
public:
    explicit excel_writer(const std::string& path, excel_template excel_template) {
        doc_ = new OpenXLSX::XLDocument();
        doc_->open(path);
        auto wb = doc_->workbook();

        excel_template_ = std::move(excel_template);
        worksheet_ = wb.worksheet(wb.worksheetNames().at(0));
    }

    void write_pair(const pair& pair_to_write);

    void save(const std::string& path) {
        doc_->saveAs(path);
    }

    ~excel_writer() {
        delete doc_;
    }
private:
    excel_template excel_template_;
    OpenXLSX::XLDocument* doc_;
    OpenXLSX::XLWorksheet worksheet_;
};
