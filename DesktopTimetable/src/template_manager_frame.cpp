#include "template_manager_frame.h"

template_manager_frame::template_manager_frame(): wxFrame(nullptr, wxID_ANY, wxT("Template Manager"), wxPoint(50, 50), wxSize(500, 225))
{
    auto* panel = new wxPanel(this, wxID_ANY);
    auto* scrolled_panel = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
        
    templates_list_box_ = new wxListBox(scrolled_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    for (const auto& [pair_name, pair]: template_manager::get_instance().get_templates())
    {
        templates_list_box_->Append(pair_name);
    }

    auto* scrolled_sizer = new wxBoxSizer(wxVERTICAL);
    scrolled_sizer->Add(templates_list_box_, 1, wxEXPAND | wxALL, 5);
    scrolled_panel->SetSizer(scrolled_sizer);
        
    auto* load_button = new wxButton(panel, wxID_ANY, wxT("Загрузить"), wxDefaultPosition, wxDefaultSize);
    auto* save_button = new wxButton(panel, wxID_ANY, wxT("Сохранить"), wxDefaultPosition, wxDefaultSize);
    auto* edit_button = new wxButton(panel, wxID_ANY, wxT("Редактировать"), wxDefaultPosition, wxDefaultSize);
    auto* delete_button = new wxButton(panel, wxID_ANY, wxT("Удалить"), wxDefaultPosition, wxDefaultSize);
    auto* create_button = new wxButton(panel, wxID_ANY, wxT("Создать"), wxDefaultPosition, wxDefaultSize);

    auto* button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(load_button, 0, wxALL | wxEXPAND, 5);
    button_sizer->Add(save_button, 0, wxALL | wxEXPAND, 5);
    button_sizer->Add(edit_button, 0, wxALL | wxEXPAND, 5);
    button_sizer->Add(delete_button, 0, wxALL | wxEXPAND, 5);
    button_sizer->Add(create_button, 0, wxALL | wxEXPAND, 5);
        
    load_button->Bind(wxEVT_BUTTON, &template_manager_frame::on_load_button_click, this);
    save_button->Bind(wxEVT_BUTTON, &template_manager_frame::on_save_button_click, this);
    edit_button->Bind(wxEVT_BUTTON, &template_manager_frame::on_edit_button_click, this);
    delete_button->Bind(wxEVT_BUTTON, &template_manager_frame::on_delete_button_click, this);
    create_button->Bind(wxEVT_BUTTON, &template_manager_frame::on_create_button_click, this);
        
    auto* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(scrolled_panel, 1, wxEXPAND | wxALL, 5);
    sizer->Add(button_sizer, 0, wxEXPAND | wxALL, 5);
    panel->SetSizerAndFit(sizer);

    SetSizeHints(wxDefaultSize, GetSize());
}
