#include <wx/dialog.h>

class Mode : public wxDialog {
 public:
  Mode(const wxString &title);
};

Mode::Mode(const wxString &title)
    : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(500, 300)) {
  wxPanel *panel = new wxPanel(this, -1);

  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

  wxStaticBox *st = new wxStaticBox(panel, -1, wxT("Game mode"), wxPoint(5, 5),
                                    wxSize(400, 250));
  wxRadioButton *rb =
      new wxRadioButton(panel, -1, wxT("Person 1 vs Person 2"), wxPoint(15, 30),
                        wxDefaultSize, wxRB_GROUP);

  wxRadioButton *rb1 =
      new wxRadioButton(panel, -1, wxT("Person vs Robot"), wxPoint(15, 55));
  wxRadioButton *rb2 =
      new wxRadioButton(panel, -1, wxT("Robot 1 vs Robot 2"), wxPoint(15, 80));
  // wxRadioButton *rb3 = new wxRadioButton(panel, -1,
  //                                        wxT("Custom"), wxPoint(15, 105));
  // wxTextCtrl *tc = new wxTextCtrl(panel, -1, wxT(""),
  //                                 wxPoint(95, 105));

  wxButton *okButton =
      new wxButton(this, -1, wxT("Ok"), wxDefaultPosition, wxSize(70, 30));
  // wxButton *closeButton = new wxButton(this, -1, wxT("Close"),
  //                                      wxDefaultPosition, wxSize(70, 30));

  hbox->Add(okButton, 1);
  // hbox->Add(closeButton, 1, wxLEFT, 5);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

  SetSizer(vbox);
  Centre();
  ShowModal();
  Destroy();
}