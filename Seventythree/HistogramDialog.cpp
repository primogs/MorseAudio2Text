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
#include "HistogramDialog.h"
#include "Global.h"

/**
 * @brief constructor of the histogram dialog class
 */
HistogramDialog::HistogramDialog(wxWindow* parent, wxWindowID id , const wxString& title , const wxPoint& pos , const wxSize& size , long style):
				Histogram(parent,id,title,pos,size,style)
{
	this->SetTitle(title);
	
	m_cbTone->SetValue(Global::mMD.IsToneEvaluatedInHistogram());
	m_cbPause->SetValue(Global::mMD.IsPauseEvaluatedInHistogram());	
}

/**
 * @brief default destructor
 */
HistogramDialog::~HistogramDialog()
{
}

/**
 * @brief close the dialog if user close the window
 * @param event: the wxCommandEvent
 */
void HistogramDialog::OnCloseDialog( wxCommandEvent& event )
{
	this->Close();
}

/**
 * @brief event that is triggered by a timer to update the histogram repeadly
 * @param event: the wxTimerEvent
 */
void HistogramDialog::OnHistogramTimer( wxTimerEvent& event )
{
	Histogram::Refresh();
}

/**
 * @brief event that is triggered if the tone check box is clicked.Periods of tones are evaluated if the box is checked.
 * @param event: the wxCommandEvent
 */
void HistogramDialog::OnCbTone( wxCommandEvent& event )
{
	Global::mMD.EvaluateToneInHistogram(m_cbTone->IsChecked());
}

/**
 * @brief event that is triggered if the pause check box is clicked.Periods of pauses are evaluated if the box is checked.
 * @param event: the wxCommandEvent
 */
void HistogramDialog::OnCbPause( wxCommandEvent& event )
{
	Global::mMD.EvaluatePauseInHistogram(m_cbPause->IsChecked());
}