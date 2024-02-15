#include "timetable_manager_frame.h"

timetable_manager_frame::timetable_manager_frame() : wxFrame(nullptr, wxID_ANY, wxT("Timetable Manager")) {
    auto *panel = new wxPanel(this, wxID_ANY);
    auto *scrolled_panel = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);

    timetables_list_box_ = new wxListBox(scrolled_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    for (const auto &[pair_name, pair]: timetable_manager::get_instance().get_timetables()) {
        timetables_list_box_->Append(pair_name);
    }

    auto *scrolled_sizer = new wxBoxSizer(wxVERTICAL);
    scrolled_sizer->Add(timetables_list_box_, 1, wxALL | wxEXPAND, 5);
    scrolled_panel->SetSizer(scrolled_sizer);

    auto *add_button = new wxButton(panel, wxID_ANY, wxT("Загрузить"), wxDefaultPosition, wxDefaultSize);
    auto *delete_button = new wxButton(panel, wxID_ANY, wxT("Удалить"), wxDefaultPosition, wxDefaultSize);
    auto *view_button = new wxButton(panel, wxID_ANY, wxT("Просмотреть"), wxDefaultPosition, wxDefaultSize);

    auto *button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(add_button, 0, wxALL | wxEXPAND, 5);
    button_sizer->Add(delete_button, 0, wxALL | wxEXPAND, 5);
    button_sizer->Add(view_button, 0, wxALL | wxEXPAND, 5);

    add_button->Bind(wxEVT_BUTTON, &timetable_manager_frame::on_add_button_click, this);
    delete_button->Bind(wxEVT_BUTTON, &timetable_manager_frame::on_delete_button_click, this);
    view_button->Bind(wxEVT_BUTTON, &timetable_manager_frame::on_view_button_click, this);

    auto *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(scrolled_panel, 1, wxEXPAND | wxALL, 5);
    sizer->Add(button_sizer, 0, wxALL | wxALIGN_CENTER, 5);
    panel->SetSizerAndFit(sizer);

    SetSizeHints(wxDefaultSize, GetSize());
}
