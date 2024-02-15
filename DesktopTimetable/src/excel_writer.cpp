#include "excel_writer.h"
#include "codec_converter.h"

void excel_writer::write_pair(const pair &pair_to_write) {
    const auto row = excel_template_[pair_to_write.get_day()] + pair_to_write.get_position();

    if(const auto audience_column = excel_template_[excel_marker::pair_audience][pair_to_write.get_week()]; audience_column != 65535)
    {
        worksheet_.cell(row, audience_column).value().set(codec_converter::wstr_to_utf8(pair_to_write.get_audience()));
    }

    if(const auto subject_column = excel_template_[excel_marker::pair_subject][pair_to_write.get_week()]; subject_column != 65535)
    {
        worksheet_.cell(row, subject_column).value().set(codec_converter::wstr_to_utf8(pair_to_write.get_subject()));
    }

    if(const auto group_column = excel_template_[excel_marker::pair_group][pair_to_write.get_week()]; group_column != 65535)
    {
        worksheet_.cell(row, group_column).value().set(codec_converter::wstr_to_utf8(pair_to_write.get_group()));
    }

    if(const auto type_column = excel_template_[excel_marker::pair_type][pair_to_write.get_week()]; type_column != 65535)
    {
        worksheet_.cell(row, type_column).value().set(codec_converter::wstr_to_utf8(pair_to_write.get_type()));
    }
}