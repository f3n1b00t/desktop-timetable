#pragma once

#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/button.h>
#include <wx/filedlg.h>

#include "template_create_frame.h"
#include "template_manager.h"

class template_manager_frame final : public wxFrame
{
public:
    template_manager_frame();

    void on_load_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        wxFileDialog open_file_dialog(this, wxT("Выберите файл шаблона"), wxEmptyString, wxEmptyString,
                                    wxT("Все файлы (*.*)|*.*"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        if (open_file_dialog.ShowModal() == wxID_CANCEL)
            return;

        const wxString selected_file = open_file_dialog.GetPath();
        const auto file_name = wxFileNameFromPath(selected_file).ToStdString();
        auto loaded_template = excel_template().load_from_file(selected_file.ToStdString());

        template_manager::get_instance().add_template(
                loaded_template.get_template_name(),
                loaded_template
        );

        templates_list_box_->Append(loaded_template.get_template_name());

        wxMessageBox(wxString(wxT("Шаблон успешно загружен!")) + selected_file, wxT("Информация"), wxOK | wxICON_INFORMATION);
    }

    void on_save_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        wxFileDialog save_file_dialog(this, wxT("Сохранить шаблон"), wxEmptyString, wxEmptyString,
                            wxT("Все файлы (*.json)|*.json"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

        if (save_file_dialog.ShowModal() == wxID_CANCEL)
        {
            return;
        }

        if (const int selected_index = templates_list_box_->GetSelection(); selected_index != wxNOT_FOUND)
        {
            template_manager::get_instance().get_template(
                templates_list_box_->GetString(selected_index).ToStdString()
            ).save_to_file(save_file_dialog.GetPath().ToStdString());

            wxMessageBox(wxT("Шаблон успешно сохранен!"), wxT("Информация"), wxOK | wxICON_INFORMATION);
        }
        
    }

    void refresh() const
    {
        templates_list_box_->Clear();

        for (const auto& [pair_name, pair]: template_manager::get_instance().get_templates())
        {
            templates_list_box_->Append(pair_name);
        }
    }

    void on_edit_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        if (const int selected_index = templates_list_box_->GetSelection(); selected_index != wxNOT_FOUND)
        {
            const auto template_name = templates_list_box_->GetString(selected_index).ToStdString();
            
            auto selected_template = template_manager::get_instance().get_template(
                template_name
            );

            auto* frame = new template_create_frame(
                [this]{this->refresh();},
                selected_template
            );

            frame->Show(true);
        }
    }
    
    void on_delete_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        if (const int selected_index = templates_list_box_->GetSelection(); selected_index != wxNOT_FOUND)
        {
            template_manager::get_instance().remove_template(
                templates_list_box_->GetString(selected_index).ToStdString()
            );
            
            templates_list_box_->Delete(selected_index);
        }
    }

    void on_create_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        excel_template default_template;
        default_template.add_day_marker(day_of_week::monday, 16);
        default_template.add_day_marker(day_of_week::tuesday, 29);
        default_template.add_day_marker(day_of_week::wednesday, 42);
        default_template.add_day_marker(day_of_week::thursday, 55);
        default_template.add_day_marker(day_of_week::friday, 68);
        default_template.add_day_marker(day_of_week::saturday, 81);

        default_template.add_marker(excel_marker::pair_audience, 4, week_type::even);
        default_template.add_marker(excel_marker::pair_type, 5, week_type::even);
        default_template.add_marker(excel_marker::pair_teacher, 6, week_type::even);
        default_template.add_marker(excel_marker::pair_subject, 7, week_type::even);

        default_template.add_marker(excel_marker::pair_subject, 8, week_type::odd);
        default_template.add_marker(excel_marker::pair_teacher, 9, week_type::odd);
        default_template.add_marker(excel_marker::pair_type, 10, week_type::odd);
        default_template.add_marker(excel_marker::pair_audience, 11, week_type::odd);

        default_template.set_pairs_per_day(6);

        auto* frame = new template_create_frame([this]{this->refresh();}, default_template);
        frame->Show(true);
    }

private:
    wxListBox* templates_list_box_;
};

