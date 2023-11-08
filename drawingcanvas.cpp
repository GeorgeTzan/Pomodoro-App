#include "DrawingCanvas.h"
#include <wx/wx.h>
wxBEGIN_EVENT_TABLE(DrawingCanvas, wxPanel)
EVT_PAINT(DrawingCanvas::OnPaint)
wxEND_EVENT_TABLE()

DrawingCanvas::DrawingCanvas(wxWindow* parent)
    : wxPanel(parent)
{
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    textX = 0;
    textY = 0;
}

void DrawingCanvas::LoadImage(const wxString& imagePath)
{
    if (image.LoadFile(imagePath, wxBITMAP_TYPE_ANY))
    {
        Refresh();
    }
    else
    {
        wxLogError("Failed to load the image from: %s", imagePath);
    }
}

void DrawingCanvas::SetText(const wxString& text, int x, int y)
{
    displayText = text;
    textX = x;
    textY = y;
    Refresh();
}

wxString DrawingCanvas::GetText() const
{
    return displayText;
}

void DrawingCanvas::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    int canvasWidth, canvasHeight;
    GetSize(&canvasWidth, &canvasHeight);

    if (image.IsOk())
    {
        dc.DrawBitmap(image, 0, 0, true);
    }

    if (!displayText.IsEmpty())
    {
        wxSize textSize = dc.GetTextExtent(displayText);
        dc.SetTextForeground(wxColour(*wxWHITE));
        dc.DrawText(displayText, textX, textY);
    }
}
