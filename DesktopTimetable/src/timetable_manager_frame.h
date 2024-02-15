#pragma once

#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/button.h>

#include "pair_list_frame.h"
#include "timetable_loader_frame.h"

class timetable_manager_frame final : public wxFrame
{
public:
    timetable_manager_frame();

    void refresh() const
    {
        timetables_list_box_->Clear();
        for (const auto& [pair_name, pair]: timetable_manager::get_instance().get_timetables())
        {
            timetables_list_box_->Append(pair_name);
        }
    }
    
    void on_add_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        auto* loader_frame = new timetable_loader_frame([this]{this->refresh();});
        loader_frame->Show(true);
    }

    void on_delete_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        if (const int selected_index = timetables_list_box_->GetSelection(); selected_index != wxNOT_FOUND)
        {
            timetable_manager::get_instance().remove_timetable(timetables_list_box_->GetString(selected_index).ToStdString());
            timetables_list_box_->Delete(selected_index);
        }
    }

    void on_view_button_click([[maybe_unused]] wxCommandEvent& event)
    {
        auto* frame = new pair_list_frame();
        frame->Show();
    }

private:
    wxListBox* timetables_list_box_;
};

