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
#include "HistogramPanel.h"
#include "Global.h"

/**
 * @brief constructor of the histogram panel. Connect the paint event with the method OnPaintHistogramPanel
 */	
HistogramPanel::HistogramPanel(wxWindow* parent):wxPanel(parent)
{
	mToneCounts = nullptr;
	mPauseCounts = nullptr;
	mMaxCount = 0;
	mMaxPeriod = 0.0;
	Connect( wxEVT_PAINT, wxPaintEventHandler( HistogramPanel::OnPaintHistogramPanel ), NULL, this );
}

/**
 * @brief constructor of the histogram panel. Connect the paint event with the method OnPaintHistogramPanel
 */	
HistogramPanel::HistogramPanel(wxWindow *parent,wxWindowID winid ,const wxPoint& pos,const wxSize& size,long style ,const wxString& name ):wxPanel(parent)
{
	mToneCounts = nullptr;
	mPauseCounts = nullptr;
	mMaxCount = 0;
	
	Connect( wxEVT_PAINT, wxPaintEventHandler( HistogramPanel::OnPaintHistogramPanel ), NULL, this );
}

/**
 * @brief destructor of the histogram panel. Disconnect the paint event with the method OnPaintHistogramPanel
 */	
HistogramPanel::~HistogramPanel()
{

	mMaxCount = 0;
	FreeBuffer();
	Disconnect( wxEVT_PAINT, wxPaintEventHandler( HistogramPanel::OnPaintHistogramPanel ), NULL, this );
}

/**
 * @brief free the allocated memory
 */	
void HistogramPanel::FreeBuffer()
{
	mBins = 0;
	if(mToneCounts != nullptr)
		delete[] mToneCounts;
	if(mPauseCounts != nullptr)
		delete[] mPauseCounts;
	mToneCounts = nullptr;
	mPauseCounts = nullptr;
}

/**
 * @brief reallocate the memory
 * @param elements: number of elements memory is allocated for
 */	
void HistogramPanel::ResizeBuffer(unsigned short elements)
{
	FreeBuffer();
	mToneCounts = new unsigned short[elements];
	mPauseCounts = new unsigned short[elements];
	
	if(mToneCounts != nullptr and mPauseCounts != nullptr)
		mBins = elements;
}

/**
 * @brief called on a paint event
 * @param event: the wxPaintEvent
 */
void HistogramPanel::OnPaintHistogramPanel( wxPaintEvent& event )
{
	wxPaintDC dc(this);
	Render(dc);
}

/**
 * @brief tries to get newest histogram data from the gloabal morse statistic class and stores it in local member variables
 */
void HistogramPanel::Update()
{
	if(Global::mMDMutex.try_lock())
	{
		mMaxCount=0;
		unsigned short bins = Global::mMD.GetNumberOfBins();
		if(bins != mBins)
			ResizeBuffer(bins);
		
		mMaxPeriod = Global::mMD.GetMaxPeriod();
		if(mToneCounts!= nullptr and mPauseCounts!= nullptr)
		{
			for(int i =1;i<mBins ;i++)
			{ 
				mToneCounts[i] = Global::mMD.GetHistToneBinCount(i);
				mPauseCounts[i] = Global::mMD.GetHistPauseBinCount(i);
				if(mToneCounts[i]>mMaxCount)
					mMaxCount = mToneCounts[i];
				if(mPauseCounts[i]>mMaxCount)
					mMaxCount = mPauseCounts[i];
			}
		}
		Global::mMDMutex.unlock();
	}
	if(mMaxCount==0)
		mMaxCount=1;
}

/**
 * @brief will paint the histogram
 * @param dc: device context of the panel to be painted
 */
void HistogramPanel::Render(wxDC& dc)
{
	Update();
		
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	
	wxRect rect = this->GetClientRect();
	const int width = rect.GetWidth()/static_cast<double>(mBins);
	const int bottom = rect.GetY()+rect.GetHeight()-20;
	
	DrawAxis(dc,rect);
	DrawBins(dc,rect,width,bottom);
}

/**
 * @brief will paint the histogram
 * @param dc: device context of the panel to be painted
 * @param rect: boarder coordinates of the panel
 * @param width: with of one bin in pixel
 * @param bottom: pixel position of the lower bin boundary 
 */
void HistogramPanel::DrawBins(wxDC& dc,wxRect &rect,const int width, const int bottom )
{
	if(mToneCounts!=nullptr and mPauseCounts!=nullptr)
	{
		for(int i =1;i<mBins;i++)
		{
			const int x1 	= (i-1)*width+rect.GetX();
			const int dyt 	= (mToneCounts[i]/static_cast<double>(mMaxCount))*(rect.GetHeight()-20);
			const int dyp 	= (mPauseCounts[i]/static_cast<double>(mMaxCount))*(rect.GetHeight()-20);
				
			dc.SetPen(*wxBLUE_PEN);
			dc.DrawRectangle(x1,bottom-dyp,width,dyp);
			dc.SetPen(*wxRED_PEN);
			dc.DrawRectangle(x1+3,bottom-dyt,width-6,dyt);
		}
	}
}

/**
 * @brief draw the x-axis on the bottom of the panel
 * @param dc: device context of the panel to be painted
 * @param rect: boarder coordinates of the panel
 */
void HistogramPanel::DrawAxis(wxDC& dc,wxRect &rect)
{
	for(double percent =0.1;percent<=0.95;percent=percent+0.1)
	{
		const int x = percent*rect.GetWidth();
		const int bottom = rect.GetY()+rect.GetHeight();
		dc.DrawLine(x,bottom,x,bottom-15);
		dc.DrawText(wxString::Format("%0.2f s",percent*mMaxPeriod),x+2, bottom-15);
	}
}
