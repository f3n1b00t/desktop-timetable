#include "pair_list_frame.h"

#include <wx/file.h>
#include "pair_manager.h"
#include "codec_converter.h"

pair_list_frame::pair_list_frame() : wxFrame(nullptr, wxID_ANY, wxT("Pair list"), wxPoint(50, 50), wxSize(500, 150))
{
    auto* panel = new wxPanel(this, wxID_ANY);
    auto* scrolled_panel = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
        
    pair_list_box_ = new wxListBox(scrolled_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    for(const auto& pair: pair_manager::get_instance().get_all_pairs())
    {

        pair_list_box_->Append(
                pair.get_teacher() + L"," +
                pair.get_subject()+ L"," +
                pair.get_audience() + L"," +
                pair.get_type() + L"," +
                (pair.get_week() == week_type::even ? L"Чётная," : L"Нечётная,")
        );
    }

    auto* scrolled_sizer = new wxBoxSizer(wxVERTICAL);
    scrolled_sizer->Add(pair_list_box_, 1, wxEXPAND | wxALL, 5);
    scrolled_panel->SetSizer(scrolled_sizer);

    auto* delete_button = new wxButton(panel, wxID_ANY, wxT("Удалить"), wxDefaultPosition, wxDefaultSize);
    delete_button->Bind(wxEVT_BUTTON, &pair_list_frame::on_delete_button_click, this);
        
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(scrolled_panel, 1, wxEXPAND | wxALL, 5);
    sizer->Add(delete_button, 0, wxEXPAND | wxALL, 5);
    panel->SetSizerAndFit(sizer);
        
    SetSizeHints(wxDefaultSize, GetSize());
}
