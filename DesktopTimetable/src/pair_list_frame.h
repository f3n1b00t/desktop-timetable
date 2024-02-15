#pragma once

#include <wx/wx.h>
#include <wx/listbox.h>

class pair_list_frame final : public wxFrame {
public:
    pair_list_frame();

    void on_delete_button_click(wxCommandEvent &event) {
        if (const int selected_index = pair_list_box_->GetSelection(); selected_index != wxNOT_FOUND) {
            pair_list_box_->Delete(selected_index);
        }
    }

private:
    wxListBox *pair_list_box_;
};