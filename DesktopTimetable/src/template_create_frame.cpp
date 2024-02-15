#include "template_create_frame.h"

template_create_frame::template_create_frame(const std::function<void()> &manager_refresh_callback) : wxFrame(nullptr,
                                                                                                              wxID_ANY,
                                                                                                              "Create Template",
                                                                                                              wxPoint(50,
                                                                                                                      50),
                                                                                                              wxSize(500,
                                                                                                                     325)),
                                                                                                      manager_refresh_callback_(
                                                                                                              manager_refresh_callback) {
    auto *panel = new wxPanel(this, wxID_ANY);

    monday_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    tuesday_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    wednesday_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    thursday_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    friday_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    saturday_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);

    auto *day_sizer = new wxFlexGridSizer(8, 2, 5, 5);

    day_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Пн")));
    day_sizer->Add(monday_input_);
    day_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Вт")));
    day_sizer->Add(tuesday_input_);
    day_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Ср")));
    day_sizer->Add(wednesday_input_);
    day_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Чт")));
    day_sizer->Add(thursday_input_);
    day_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Пт")));
    day_sizer->Add(friday_input_);
    day_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Сб")));
    day_sizer->Add(saturday_input_);

    teacher_even_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    teacher_odd_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    audience_even_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    audience_odd_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    subject_even_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    subject_odd_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    type_even_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    type_odd_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);

    auto *marker_sizer = new wxFlexGridSizer(8, 3, 5, 5);

    marker_sizer->Add(new wxStaticText(panel, wxID_ANY, wxEmptyString));
    marker_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Чётная неделя")), 0, wxALIGN_CENTER | wxALL, 5);
    marker_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Нечётная неделя")), 0, wxALIGN_CENTER | wxALL, 5);

    marker_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Преподаватель")));
    marker_sizer->Add(teacher_even_input_);
    marker_sizer->Add(teacher_odd_input_);
    marker_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Аудитория")));
    marker_sizer->Add(audience_even_input_);
    marker_sizer->Add(audience_odd_input_);
    marker_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Предмет")));
    marker_sizer->Add(subject_even_input_);
    marker_sizer->Add(subject_odd_input_);
    marker_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Тип")));
    marker_sizer->Add(type_even_input_);
    marker_sizer->Add(type_odd_input_);

    auto *row_sizer = new wxBoxSizer(wxVERTICAL);
    row_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Строки")), 0, wxALIGN_CENTER | wxALL, 5);
    row_sizer->Add(day_sizer);

    template_name_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    pair_count_input_ = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);

    auto *other_sizer = new wxFlexGridSizer(2, 2, 5, 5);
    other_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Название шаблона")));
    other_sizer->Add(template_name_input_);
    other_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Кол-во пар в день")));
    other_sizer->Add(pair_count_input_);


    auto *column_sizer = new wxBoxSizer(wxVERTICAL);
    column_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Колонки")), 0, wxALIGN_CENTER | wxALL, 5);
    column_sizer->Add(marker_sizer);
    column_sizer->Add(new wxStaticText(panel, wxID_ANY, wxEmptyString), 0, wxALL, 5);
    column_sizer->Add(other_sizer);

    auto *panel_sizer = new wxBoxSizer(wxHORIZONTAL);
    panel_sizer->Add(row_sizer, 1, wxEXPAND | wxALL, 5);
    panel_sizer->Add(column_sizer, 1, wxEXPAND | wxALL, 5);

    auto *create_button = new wxButton(panel, wxID_ANY, wxT("Создать"));
    create_button->Bind(wxEVT_BUTTON, &template_create_frame::on_create_button_click, this);

    auto *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(panel_sizer, 1, wxEXPAND | wxALL, 5);
    vbox->Add(create_button, 0, wxEXPAND | wxALL, 5);

    panel->SetSizerAndFit(vbox);
    SetSizeHints(wxDefaultSize, GetSize());
}

template_create_frame::template_create_frame(const std::function<void()> &manager_refresh_callback,
                                             excel_template &excel_template) : template_create_frame(
        manager_refresh_callback) {
    monday_input_->SetValue(std::to_string(excel_template[day_of_week::monday]));
    tuesday_input_->SetValue(std::to_string(excel_template[day_of_week::tuesday]));
    wednesday_input_->SetValue(std::to_string(excel_template[day_of_week::wednesday]));
    thursday_input_->SetValue(std::to_string(excel_template[day_of_week::thursday]));
    friday_input_->SetValue(std::to_string(excel_template[day_of_week::friday]));
    saturday_input_->SetValue(std::to_string(excel_template[day_of_week::saturday]));

    teacher_even_input_->SetValue(std::to_string(excel_template[excel_marker::pair_teacher][week_type::even]));
    teacher_odd_input_->SetValue(std::to_string(excel_template[excel_marker::pair_teacher][week_type::odd]));
    audience_even_input_->SetValue(std::to_string(excel_template[excel_marker::pair_audience][week_type::even]));
    audience_odd_input_->SetValue(std::to_string(excel_template[excel_marker::pair_audience][week_type::odd]));
    subject_even_input_->SetValue(std::to_string(excel_template[excel_marker::pair_subject][week_type::even]));
    subject_odd_input_->SetValue(std::to_string(excel_template[excel_marker::pair_subject][week_type::odd]));
    type_even_input_->SetValue(std::to_string(excel_template[excel_marker::pair_type][week_type::even]));
    type_odd_input_->SetValue(std::to_string(excel_template[excel_marker::pair_type][week_type::odd]));

    pair_count_input_->SetValue(std::to_string(excel_template.get_pairs_per_day()));
    template_name_input_->SetValue(excel_template.get_template_name());
}

void template_create_frame::on_create_button_click(wxCommandEvent &event) {
    excel_template excel_template;

    unsigned int monday_row;
    unsigned int tuesday_row;
    unsigned int wednesday_row;
    unsigned int thursday_row;
    unsigned int friday_row;
    unsigned int saturday_row;

    monday_input_->GetValue().ToUInt(&monday_row);
    tuesday_input_->GetValue().ToUInt(&tuesday_row);
    wednesday_input_->GetValue().ToUInt(&wednesday_row);
    thursday_input_->GetValue().ToUInt(&thursday_row);
    friday_input_->GetValue().ToUInt(&friday_row);
    saturday_input_->GetValue().ToUInt(&saturday_row);

    excel_template.add_day_marker(day_of_week::monday, monday_row);
    excel_template.add_day_marker(day_of_week::tuesday, tuesday_row);
    excel_template.add_day_marker(day_of_week::wednesday, wednesday_row);
    excel_template.add_day_marker(day_of_week::thursday, thursday_row);
    excel_template.add_day_marker(day_of_week::friday, friday_row);
    excel_template.add_day_marker(day_of_week::saturday, saturday_row);

    unsigned int teacher_even_column;
    unsigned int teacher_odd_column;
    unsigned int audience_even_column;
    unsigned int audience_odd_column;
    unsigned int subject_even_column;
    unsigned int subject_odd_column;
    unsigned int type_even_column;
    unsigned int type_odd_column;

    teacher_even_input_->GetValue().ToUInt(&teacher_even_column);
    teacher_odd_input_->GetValue().ToUInt(&teacher_odd_column);
    audience_even_input_->GetValue().ToUInt(&audience_even_column);
    audience_odd_input_->GetValue().ToUInt(&audience_odd_column);
    subject_even_input_->GetValue().ToUInt(&subject_even_column);
    subject_odd_input_->GetValue().ToUInt(&subject_odd_column);
    type_even_input_->GetValue().ToUInt(&type_even_column);
    type_odd_input_->GetValue().ToUInt(&type_odd_column);

    excel_template.add_marker(excel_marker::pair_teacher, teacher_even_column, teacher_odd_column);
    excel_template.add_marker(excel_marker::pair_audience, audience_even_column, audience_odd_column);
    excel_template.add_marker(excel_marker::pair_subject, subject_even_column, subject_odd_column);
    excel_template.add_marker(excel_marker::pair_type, type_even_column, type_odd_column);

    unsigned int pairs_per_day;
    pair_count_input_->GetValue().ToUInt(&pairs_per_day);

    excel_template.set_pairs_per_day(pairs_per_day);
    excel_template.set_template_name(template_name_input_->GetValue().ToStdString());

    template_manager::get_instance().add_template(template_name_input_->GetValue().ToStdString(), excel_template);
    manager_refresh_callback_();

    wxMessageBox(wxT("Шаблон успешно создан!"), wxT("Информация"), wxOK | wxICON_INFORMATION);
}
