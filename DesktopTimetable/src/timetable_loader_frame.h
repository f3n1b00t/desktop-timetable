#pragma once

#include <wx/wx.h>
#include <wx/button.h>
#include <wx/filedlg.h>

#include "pair_manager.h"
#include "template_manager.h"
#include "timetable_manager.h"

class timetable_loader_frame final : public wxFrame
{
public:
    explicit timetable_loader_frame(const std::function<void()>& manager_refresh_callback);

    explicit timetable_loader_frame(const std::function<void()>& manager_refresh_callback, [[maybe_unused]] const timetable& selected_timetable) : timetable_loader_frame(manager_refresh_callback)
    {
        
    }

    void on_choose_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        wxFileDialog open_file_dialog(this, wxT("Выберите файл расписания"), wxEmptyString, wxEmptyString,
                    wxT("Файлы excel (*.xlsx, *.xls)|*.xlsx;*.xls"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        if (open_file_dialog.ShowModal() == wxID_CANCEL)
        {
            return;
        }

        filename_input_->Clear();
        filename_input_->WriteText(open_file_dialog.GetPath());
    }
    
    void on_load_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        if(!wxFileExists(filename_input_->GetValue()))
        {
            wxMessageBox(wxT("Файла не существует"), wxT("Информация"), wxOK | wxICON_INFORMATION);
            return; 
        }
        
        if(template_combobox_->GetSelection() == -1)
        {
            wxMessageBox(wxT("Выберите шаблон"), wxT("Информация"), wxOK | wxICON_INFORMATION);
            return;
        }

        const timetable loaded_timetable(
            filename_input_->GetValue().ToStdString(),
            template_manager::get_instance().get_template(
                template_combobox_->GetString(template_combobox_->GetSelection()).ToStdString()
            )
        );
        
        timetable_manager::get_instance().add_timetable(
            wxFileNameFromPath(wxString(filename_input_->GetValue())).ToStdString(),
            loaded_timetable
        );

        pair_manager::get_instance().load_pairs_from_file(loaded_timetable);
        manager_refresh_callback_();
        
        wxMessageBox(wxT("Расписание успешно загружено!"), wxT("Информация"), wxOK | wxICON_INFORMATION);
        Close();
    }

private:
    std::function<void()> manager_refresh_callback_;
    wxTextCtrl* filename_input_;
    wxComboBox* template_combobox_;
};
