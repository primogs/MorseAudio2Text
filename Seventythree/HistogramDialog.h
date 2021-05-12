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
#ifndef HISTOGRAMDIALOG_H
#define HISTOGRAMDIALOG_H

#include "MorseGUI.h"

//!  Window of a dialog that shows the histogram.
/**
 * @class HistogramDialog
 * @author Matthias Hund
 * @date 02/20/21
 * @file HistogramDialog.h
 */

class HistogramDialog: public Histogram
{
public:
	HistogramDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Period Histogram"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
	virtual ~HistogramDialog();
private:
	void OnCloseDialog( wxCommandEvent& event);
	void OnHistogramTimer( wxTimerEvent& event );
	void OnCbTone( wxCommandEvent& event );
	void OnCbPause( wxCommandEvent& event );
};

#endif // HISTOGRAMDIALOG_H
