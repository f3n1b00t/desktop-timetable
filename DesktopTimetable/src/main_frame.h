#pragma once

#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/textfile.h>
#include <fstream>
#include <string>

#include "generate_frame.h"
#include "template_manager_frame.h"
#include "timetable_manager_frame.h"
#include "timetable_manager.h"

class main_frame  final : public wxFrame
{
public:
    explicit main_frame();

    void on_open_template_manager([[maybe_unused]] wxCommandEvent& event)
    {
        auto* frame = new template_manager_frame();
        frame->Show(true);
    }
    
    void on_open_schedule_manager([[maybe_unused]] wxCommandEvent& event)
    {
        auto* frame = new timetable_manager_frame();
        frame->Show(true);
    }
    
    void on_about([[maybe_unused]] wxCommandEvent& event)
    {
        wxMessageBox(wxT("Автор: f3n1b00t"), wxT("О программе"), wxOK | wxICON_INFORMATION, this);
    }
    
    void on_load_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        wxFileDialog open_file_dialog(this, wxT("Выберите файл с именами преподователя"), wxEmptyString, wxEmptyString,
            wxT("Файлы текста (*.*)|*.*"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        if (open_file_dialog.ShowModal() == wxID_CANCEL)
        {
            return;
        }

        wxTextFile tfile;
        tfile.Open(open_file_dialog.GetPath());

        teacher_list_box_->Append(tfile.GetFirstLine());
        
        while(!tfile.Eof())
        {
            teacher_list_box_->Append(tfile.GetNextLine());
        }
    }
    
    
    void on_add_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        if (wxTextEntryDialog add_dialog(this, _("Имя преподавателя"), _("Добавление преподавателя"), _("Семёнов А.А.")); add_dialog.ShowModal() == wxID_OK)
        {
            teacher_list_box_->Append(add_dialog.GetValue());
        }
    }

    void on_delete_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        if (const int selected_index = teacher_list_box_->GetSelection(); selected_index != wxNOT_FOUND)
        {
            teacher_list_box_->Delete(selected_index);
        }
        
    }

    void on_generate_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        std::vector<std::wstring> teacher_names;

        for(const auto& teacher : teacher_list_box_->GetStrings())
        {
            teacher_names.push_back(teacher.ToStdWstring());
        }
        
        auto* frame = new generate_frame(teacher_names);
        frame->Show(true);
    }

private:
    wxListBox* teacher_list_box_;
};
