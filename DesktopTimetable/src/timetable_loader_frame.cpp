#include "timetable_loader_frame.h"

timetable_loader_frame::timetable_loader_frame(const std::function<void()> &manager_refresh_callback) : wxFrame(nullptr,
                                                                                                                wxID_ANY,
                                                                                                                wxT("Template Manager"),
                                                                                                                wxPoint(50,
                                                                                                                        50),
                                                                                                                wxSize(500,
                                                                                                                       150)),
                                                                                                        manager_refresh_callback_(
                                                                                                                manager_refresh_callback) {
    auto *panel = new wxPanel(this, wxID_ANY);

    filename_input_ = new wxTextCtrl(panel, wxID_ANY, wxT("Имя файла"), wxDefaultPosition, wxDefaultSize);
    auto *filename_input_button = new wxButton(panel, wxID_ANY, wxT("Выбрать"), wxDefaultPosition, wxDefaultSize);
    filename_input_button->Bind(wxEVT_BUTTON, &timetable_loader_frame::on_choose_button_click, this);

    auto *input_sizer = new wxBoxSizer(wxHORIZONTAL);
    input_sizer->Add(filename_input_, 1, wxALL | wxEXPAND, 5);
    input_sizer->Add(filename_input_button, 0, wxALL, 5);

    template_combobox_ = new wxComboBox(panel, wxID_ANY, wxT("Шаблон"), wxDefaultPosition, wxDefaultSize);

    for (auto &[name, excel_template]: template_manager::get_instance().get_templates()) {
        template_combobox_->Append(name);
    }

    auto *create_button = new wxButton(panel, wxID_ANY, wxT("Загрузить"), wxDefaultPosition, wxDefaultSize);
    create_button->Bind(wxEVT_BUTTON, &timetable_loader_frame::on_load_button_click, this);

    auto *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(input_sizer, 0, wxALL | wxEXPAND, 3);
    sizer->Add(template_combobox_, 0, wxALL | wxEXPAND, 3);
    sizer->Add(create_button, 0, wxALL | wxEXPAND, 3);
    panel->SetSizerAndFit(sizer);

    SetSizeHints(wxDefaultSize, GetSize());
}
