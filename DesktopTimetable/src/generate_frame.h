#pragma once

#include <wx/wx.h>
#include <wx/button.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <OpenXLSX.hpp>

#include "excel_writer.h"
#include "pair_manager.h"
#include "codec_converter.h"

class generate_frame final : public wxFrame {
public:
    explicit generate_frame(const std::vector<std::wstring> &teacher_names);

    void on_choose_button_click(wxCommandEvent &event) {
        wxFileDialog open_file_dialog(this, wxT("Выберите файл шаблона"), wxEmptyString, wxEmptyString,
                                      wxT("Файлы excel (*.xlsx, *.xls)|*.xlsx;*.xls"), wxFD_SAVE);

        if (open_file_dialog.ShowModal() == wxID_CANCEL) {
            return;
        }

        filename_input_->Clear();
        filename_input_->WriteText(open_file_dialog.GetPath());
    }

    void on_choose_folder_button_click(wxCommandEvent &event) {
        wxDirDialog open_folder_dialog(this, "Выберите папку вывода", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

        if (open_folder_dialog.ShowModal() == wxID_CANCEL) {
            return;
        }

        output_folder_input->Clear();
        output_folder_input->WriteText(open_folder_dialog.GetPath());
    }

    void on_generate_button_click(wxCommandEvent &event) {
        excel_template default_template;

        default_template.add_day_marker(day_of_week::monday, 4);
        default_template.add_day_marker(day_of_week::tuesday, 13);
        default_template.add_day_marker(day_of_week::wednesday, 22);
        default_template.add_day_marker(day_of_week::thursday, 31);
        default_template.add_day_marker(day_of_week::friday, 40);
        default_template.add_day_marker(day_of_week::saturday, 49);

        default_template.add_marker(excel_marker::pair_audience, 4, week_type::even);
        default_template.add_marker(excel_marker::pair_type, 5, week_type::even);
        default_template.add_marker(excel_marker::pair_group, 6, week_type::even);
        default_template.add_marker(excel_marker::pair_subject, 7, week_type::even);

        default_template.add_marker(excel_marker::pair_subject, 8, week_type::odd);
        default_template.add_marker(excel_marker::pair_group, 9, week_type::odd);
        default_template.add_marker(excel_marker::pair_type, 10, week_type::odd);
        default_template.add_marker(excel_marker::pair_audience, 11, week_type::odd);


        for (const auto &name: teacher_names_) {
            excel_writer writer(
                    filename_input_->GetValue().ToStdString(),
                    default_template
            );

            for (auto &pair: pair_manager::get_instance().get_all_pairs()) {
                if (pair.get_teacher() == name) {
                    writer.write_pair(pair);
                }
            }

            const auto filename = output_folder_input->GetValue().ToStdString() +
                                  wxString(wxFileName::GetPathSeparator()).ToStdString() +
                                  codec_converter::wstr_to_utf8(name) + ".xlsx";
            writer.save(filename);
        }

        wxMessageBox(wxT("Расписания успешно сгенерированы"), wxT("Информация"), wxOK | wxICON_INFORMATION);
    }

private:
    wxTextCtrl *filename_input_;
    wxTextCtrl *output_folder_input;
    std::vector<std::wstring> teacher_names_;
};
