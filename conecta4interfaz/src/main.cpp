// Incluye bibliotecas:
#include <wx/wx.h>
#include <cctype>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>
#include "wx/event.h"
#include <wx/wxprec.h>
#include <mode.hpp>

// Incluye encabezados:
/*#include <jugadores.hpp>
#include <controlador.hpp>
#include <tablero.hpp>*/

// Encabezado
#ifndef WX_PRECOMP
#endif

using namespace std;

enum { ID_PLAY = wxID_HIGHEST + 1, ID_ABOUT, ID_EXIT };

class MyApp : public wxApp {
 public:
  virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame {
 public:
  MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

 private:
  void OnPlayButton(wxCommandEvent &event);
  void OnAboutButton(wxCommandEvent &event);
  void OnExitButton(wxCommandEvent &event);

  wxButton *playButton;
  wxButton *aboutButton;
  wxButton *exitButton;

  wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame) EVT_BUTTON(ID_PLAY, MyFrame::OnPlayButton)
    EVT_BUTTON(ID_ABOUT, MyFrame::OnAboutButton)
        EVT_BUTTON(ID_EXIT, MyFrame::OnExitButton) wxEND_EVENT_TABLE()

            bool MyApp::OnInit() {
  MyFrame *frame = new MyFrame("Conect 4", wxDefaultPosition, wxSize(800, 600));
  frame->Show(true);
  return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size) {
  wxPanel *panel =
      new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
  panel->SetBackgroundColour(wxColor(100, 250, 200));

  // Botón "Jugar"
  playButton =
      new wxButton(panel, ID_PLAY, "Play", wxPoint(325, 200), wxSize(150, 40));

  // Botón "Acerca de"
  aboutButton = new wxButton(panel, ID_ABOUT, "About", wxPoint(325, 250),
                             wxSize(150, 40));

  // Botón "Salir"
  exitButton =
      new wxButton(panel, ID_EXIT, "Exit", wxPoint(325, 300), wxSize(150, 40));
}

void MyFrame::OnPlayButton(wxCommandEvent &event) {
  Mode *custom = new Mode(wxT("Mode"));
  custom->Show(true);
  /*Mode dlg();
  if (dlg.ShowModal() == wxID_OK)
  {
      wxMessageBox("Conecta 4 es un juego en el que dos jugadores\n"
                   "o diagonal antes que el oponente.",
                   "Acerca de");
  }*/
}

void MyFrame::OnAboutButton(wxCommandEvent &event) {
  wxMessageBox(
      "Connect 4 tiles of the same color vertically, horizontally,\n"
      "or diagonal, or its inverses.",
      "About");
}

void MyFrame::OnExitButton(wxCommandEvent &event) { Close(true); }