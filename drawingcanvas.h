#pragma once

#include <wx/wx.h>

class DrawingCanvas : public wxPanel
{
public:
    DrawingCanvas(wxWindow* parent);

    void LoadImage(const wxString& imagePath);
    void SetText(const wxString& text, int x, int y);
    void UpdateText(const wxString& text);
    wxString GetText() const;

private:
    void OnPaint(wxPaintEvent& event);
    int textX;
    int textY;
    wxBitmap image;
    wxString displayText;


    wxDECLARE_EVENT_TABLE();
};
