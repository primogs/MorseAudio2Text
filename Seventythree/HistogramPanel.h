/////////////////////////////////////////////////////////////////////////////////////////
//    This file is part of Seventythree.
//
//    Copyright (C) 2020 - 2021 Matthias Hund
//    
//    This program is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 2
//    of the License, or (at your option) any later version.
//    
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//    
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef HISTOGRAMPANEL_H
#define HISTOGRAMPANEL_H
#include <list>
#include <tuple>
#include <wx/wx.h>

//!  Customized wxPanel to display the histogram.
/**
 * @class HistogramPanel
 * @author Matthias Hund
 * @date 02/20/21
 * @file HistogramPanel.h
 */
class HistogramPanel: public wxPanel
{
public:
	HistogramPanel(wxWindow* parent);
	HistogramPanel(wxWindow *parent,wxWindowID winid = wxID_ANY,const wxPoint& pos = wxDefaultPosition,const wxSize& size = wxDefaultSize,long style = wxTAB_TRAVERSAL | wxNO_BORDER,const wxString& name = wxPanelNameStr);
	virtual ~HistogramPanel();
	
	void	Render(wxDC& dc);
	void	OnPaintHistogramPanel( wxPaintEvent& event );
private:
	void 	FreeBuffer();
	void 	ResizeBuffer(unsigned short elements);
	void 	Update();
	void 	DrawAxis(wxDC& dc,wxRect &rect);
	void 	DrawBins(wxDC& dc,wxRect &rect,const int width, const int bottom );

	unsigned short *mToneCounts;	//!< local copy of the tone histogram
	unsigned short *mPauseCounts;	//!< local copy of the pause histogram
	unsigned short  mBins;			//!< number of bins
	double			mMaxPeriod;
	unsigned short  mMaxCount;		//!< maximum value of tone and paus histogram used for normalization.Is at least one to avoid division by zero.
};

#endif // HISTOGRAMPANEL_H
