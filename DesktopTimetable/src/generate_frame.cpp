#include "generate_frame.h"

generate_frame::generate_frame(const std::vector<std::wstring> &teacher_names) :
        wxFrame(nullptr, wxID_ANY, wxT("Generator"), wxPoint(50, 50), wxSize(500, 170)),
        teacher_names_(teacher_names) {
    auto *panel = new wxPanel(this, wxID_ANY);

    filename_input_ = new wxTextCtrl(panel, wxID_ANY, "Имя файла шаблона", wxDefaultPosition, wxDefaultSize);
    auto *filename_input_button = new wxButton(panel, wxID_ANY, wxT("Выбрать"), wxDefaultPosition, wxDefaultSize);
    filename_input_button->Bind(wxEVT_BUTTON, &generate_frame::on_choose_button_click, this);

    output_folder_input = new wxTextCtrl(panel, wxID_ANY, wxT("Имя папки с расписаниями"), wxDefaultPosition,
                                         wxDefaultSize);
    auto *folder_input_button = new wxButton(panel, wxID_ANY, wxT("Выбрать"), wxDefaultPosition, wxDefaultSize);
    folder_input_button->Bind(wxEVT_BUTTON, &generate_frame::on_choose_folder_button_click, this);

    auto *input_sizer = new wxBoxSizer(wxHORIZONTAL);
    input_sizer->Add(filename_input_, 1, wxALL | wxEXPAND, 5);
    input_sizer->Add(filename_input_button, 0, wxALL, 5);

    auto *folder_input_sizer = new wxBoxSizer(wxHORIZONTAL);
    folder_input_sizer->Add(output_folder_input, 1, wxALL | wxEXPAND, 5);
    folder_input_sizer->Add(folder_input_button, 0, wxALL, 5);


    auto *create_button = new wxButton(panel, wxID_ANY, wxT("Сгенерировать"), wxDefaultPosition, wxDefaultSize);
    create_button->Bind(wxEVT_BUTTON, &generate_frame::on_generate_button_click, this);

    auto *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(input_sizer, 0, wxALL | wxEXPAND, 3);
    sizer->Add(folder_input_sizer, 0, wxALL | wxEXPAND, 3);
    sizer->Add(create_button, 0, wxALL | wxEXPAND, 3);
    panel->SetSizerAndFit(sizer);

    SetSizeHints(wxDefaultSize, GetSize());
}