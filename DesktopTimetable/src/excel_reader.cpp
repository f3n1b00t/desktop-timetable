#include "excel_reader.h"

pair_list excel_reader::read_pairs() {
    pair_list pairs;
    auto woorkbook = doc_->workbook();

    for(const auto& sheetName : woorkbook.worksheetNames())
    {

        auto sheet = woorkbook.worksheet(sheetName);

        const auto day_markers = excel_template_.get_day_markers();
        for(auto iter = day_markers.begin(); iter != day_markers.end(); ++iter)
        {

            for(unsigned int offset = 0; offset < excel_template_.get_pairs_per_day() * 2; offset ++)
            {
                pair_builder even_pair;
                pair_builder odd_pair;

                const auto row = iter->second + offset;

                even_pair.with_audience(codec_converter::utf8_to_wstr(get_cell_value(sheet, row, excel_template_[excel_marker::pair_audience][week_type::even])));
                odd_pair.with_audience(codec_converter::utf8_to_wstr(get_cell_value(sheet, row, excel_template_[excel_marker::pair_audience][week_type::odd])));

                even_pair.with_type(codec_converter::utf8_to_wstr(get_cell_value(sheet, row, excel_template_[excel_marker::pair_type][week_type::even])));
                odd_pair.with_type(codec_converter::utf8_to_wstr(get_cell_value(sheet, row, excel_template_[excel_marker::pair_type][week_type::odd])));

                even_pair.with_teacher(codec_converter::utf8_to_wstr(get_cell_value(sheet, row, excel_template_[excel_marker::pair_teacher][week_type::even])));
                odd_pair.with_teacher(codec_converter::utf8_to_wstr(get_cell_value(sheet, row, excel_template_[excel_marker::pair_teacher][week_type::odd])));

                even_pair.with_subject(codec_converter::utf8_to_wstr(get_cell_value(sheet, row, excel_template_[excel_marker::pair_subject][week_type::even])));
                odd_pair.with_subject(codec_converter::utf8_to_wstr(get_cell_value(sheet, row, excel_template_[excel_marker::pair_subject][week_type::odd])));

                even_pair.with_week(week_type::even);
                odd_pair.with_week(week_type::odd);

                even_pair.with_day(iter->first);
                odd_pair.with_day(iter->first);

                even_pair.with_position(offset / 2 == 0 ? offset / 2 + 1: offset / 2);
                odd_pair.with_position(offset / 2 == 0 ? offset / 2 + 1 : offset / 2);

                even_pair.with_group(codec_converter::utf8_to_wstr(sheetName));
                odd_pair.with_group(codec_converter::utf8_to_wstr(sheetName));


                if(!even_pair.get_audience().empty())
                {
                    pairs.add(even_pair.build());
                    offset++;
                }

                if(!odd_pair.get_audience().empty())
                {
                    pairs.add(odd_pair.build());
                    offset++;
                }
            }
        }
    }

    return pairs;
}
