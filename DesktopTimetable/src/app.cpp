#include <wx/wx.h>

#include "main_frame.h"

class template_loader_app final : public wxApp {
public:
    bool OnInit() override {
        auto *frame = new main_frame();
        frame->Show(true);
        return true;

    }
};

wxIMPLEMENT_APP(template_loader_app);
