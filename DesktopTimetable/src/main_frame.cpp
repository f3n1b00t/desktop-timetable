#include "main_frame.h"

main_frame::main_frame() : wxFrame(nullptr, wxID_ANY, wxT("Timetable Generator")) {
    auto *menu_settings = new wxMenu();
    auto *menu_help = new wxMenu();

    int id = 0;
    auto *test = menu_settings->Append(id++, wxT("Менеджер Шаблонов"));
    menu_settings->Append(id++, wxT("Менджер Расписаний"));
    menu_help->Append(id, wxT("О программе"));

    auto *menu_bar = new wxMenuBar();
    menu_bar->Append(menu_settings, wxT("Настройки"));
    menu_bar->Append(menu_help, wxT("Справка"));

    id = 0;
    menu_settings->Bind(wxEVT_COMMAND_MENU_SELECTED, &main_frame::on_open_template_manager, this, id++);
    menu_settings->Bind(wxEVT_COMMAND_MENU_SELECTED, &main_frame::on_open_schedule_manager, this, id++);
    menu_help->Bind(wxEVT_COMMAND_MENU_SELECTED, &main_frame::on_about, this, id);

    SetMenuBar(menu_bar);

    auto *panel = new wxPanel(this, wxID_ANY);
    auto *scrolled_panel = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);

    teacher_list_box_ = new wxListBox(scrolled_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    auto *scrolled_sizer = new wxBoxSizer(wxVERTICAL);
    scrolled_sizer->Add(teacher_list_box_, 1, wxEXPAND | wxALL, 5);
    scrolled_panel->SetSizer(scrolled_sizer);

    auto *load_button = new wxButton(panel, wxID_ANY, wxT("Загрузить"), wxDefaultPosition, wxDefaultSize);
    auto *add_button = new wxButton(panel, wxID_ANY, wxT("Добавить"), wxDefaultPosition, wxDefaultSize);
    auto *delete_button = new wxButton(panel, wxID_ANY, wxT("Удалить"), wxDefaultPosition, wxDefaultSize);
    auto *generate_button = new wxButton(panel, wxID_ANY, wxT("Сгенерировать"), wxDefaultPosition, wxDefaultSize);

    auto *button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(load_button, 0, wxALL | wxEXPAND, 5);
    button_sizer->Add(add_button, 0, wxALL | wxEXPAND, 5);
    button_sizer->Add(delete_button, 0, wxALL | wxEXPAND, 5);
    button_sizer->Add(generate_button, 0, wxALL | wxEXPAND, 5);

    load_button->Bind(wxEVT_BUTTON, &main_frame::on_load_button_click, this);
    add_button->Bind(wxEVT_BUTTON, &main_frame::on_add_button_click, this);
    delete_button->Bind(wxEVT_BUTTON, &main_frame::on_delete_button_click, this);
    generate_button->Bind(wxEVT_BUTTON, &main_frame::on_generate_button_click, this);

    auto *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(scrolled_panel, 1, wxEXPAND | wxALL, 5);
    sizer->Add(button_sizer, 0, wxALL | wxALIGN_CENTER, 5);
    panel->SetSizerAndFit(sizer);

    SetSizeHints(wxDefaultSize, GetSize());
}
