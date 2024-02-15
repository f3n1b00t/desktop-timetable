#pragma once

#include <wx/wx.h>
#include <wx/grid.h>

#include "excel_template.h"
#include "template_manager.h"

class template_create_frame final : public wxFrame {
public:
    explicit template_create_frame(const std::function<void()> &manager_refresh_callback);

    explicit template_create_frame(const std::function<void()> &manager_refresh_callback,
                                   excel_template &excel_template);

    void on_create_button_click(wxCommandEvent &event);

private:
    wxTextCtrl *monday_input_;
    wxTextCtrl *tuesday_input_;
    wxTextCtrl *wednesday_input_;
    wxTextCtrl *thursday_input_;
    wxTextCtrl *friday_input_;
    wxTextCtrl *saturday_input_;
    wxTextCtrl *teacher_even_input_;
    wxTextCtrl *teacher_odd_input_;
    wxTextCtrl *audience_even_input_;
    wxTextCtrl *audience_odd_input_;
    wxTextCtrl *subject_even_input_;
    wxTextCtrl *subject_odd_input_;
    wxTextCtrl *type_even_input_;
    wxTextCtrl *type_odd_input_;
    wxTextCtrl *template_name_input_;
    wxTextCtrl *pair_count_input_;
    std::function<void()> manager_refresh_callback_;
};
