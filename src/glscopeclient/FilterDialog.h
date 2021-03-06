/***********************************************************************************************************************
*                                                                                                                      *
* glscopeclient                                                                                                        *
*                                                                                                                      *
* Copyright (c) 2012-2020 Andrew D. Zonenberg                                                                          *
* All rights reserved.                                                                                                 *
*                                                                                                                      *
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the     *
* following conditions are met:                                                                                        *
*                                                                                                                      *
*    * Redistributions of source code must retain the above copyright notice, this list of conditions, and the         *
*      following disclaimer.                                                                                           *
*                                                                                                                      *
*    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the       *
*      following disclaimer in the documentation and/or other materials provided with the distribution.                *
*                                                                                                                      *
*    * Neither the name of the author nor the names of any contributors may be used to endorse or promote products     *
*      derived from this software without specific prior written permission.                                           *
*                                                                                                                      *
* THIS SOFTWARE IS PROVIDED BY THE AUTHORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED   *
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL *
* THE AUTHORS BE HELD LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES        *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR       *
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
* POSSIBILITY OF SUCH DAMAGE.                                                                                          *
*                                                                                                                      *
***********************************************************************************************************************/

/**
	@file
	@author Andrew D. Zonenberg
	@brief Dialog for configuring filters
 */

#ifndef FilterDialog_h
#define FilterDialog_h

#include "../scopehal/Oscilloscope.h"
#include "WaveformArea.h"
#include "WaveformGroup.h"

class ChannelSelectorRow
{
public:
	Gtk::Label			m_label;
	Gtk::ComboBoxText	m_chans;

	std::map<std::string, StreamDescriptor> m_chanptrs;
};

class FilterDialog;

class ParameterRowBase
{
public:
	ParameterRowBase();
	virtual ~ParameterRowBase();

	Gtk::Label			m_label;
};

class ParameterRowString : public ParameterRowBase
{
public:
	ParameterRowString();
	virtual ~ParameterRowString();

	Gtk::Entry			m_entry;
};

class ParameterRowEnum : public ParameterRowBase
{
public:
	ParameterRowEnum();
	virtual ~ParameterRowEnum();

	Gtk::ComboBoxText	m_box;
};

class ParameterRowFilename : public ParameterRowString
{
public:
	ParameterRowFilename(Gtk::Dialog* parent, FilterParameter& param);
	virtual ~ParameterRowFilename();

	void OnBrowser();
	void OnClear();

	Gtk::Dialog*		m_parent;
	Gtk::Button			m_clearButton;
	Gtk::Button			m_browserButton;
	FilterParameter& 	m_param;
};

class ParameterRowFilenames : public ParameterRowBase
{
public:
	ParameterRowFilenames(Gtk::Dialog* parent, FilterParameter& param);
	virtual ~ParameterRowFilenames();

	Gtk::Dialog*		m_parent;

	Gtk::ListViewText	m_list;
	Gtk::Button			m_buttonAdd;
	Gtk::Button			m_buttonRemove;

	void OnAdd();
	void OnRemove();

	FilterParameter& 	m_param;
};

/**
	@brief Main application window class for an oscilloscope
 */
class FilterDialog	: public Gtk::Dialog
{
public:
	FilterDialog(OscilloscopeWindow* parent, Filter* filter, StreamDescriptor chan);
	virtual ~FilterDialog();

	Filter* GetFilter()
	{ return m_filter; }

	void ConfigureDecoder();

	static ParameterRowBase* CreateRow(
		Gtk::Grid& grid,
		std::string name,
		FilterParameter& param,
		Gtk::Widget*& last_label,
		Gtk::Dialog* parent);

	static void ConfigureInputs(FlowGraphNode* node, std::vector<ChannelSelectorRow*>& rows);
	static void ConfigureParameters(FlowGraphNode* node, std::vector<ParameterRowBase*>& rows);

protected:
	Filter* m_filter;

	Gtk::Grid m_grid;
		Gtk::Label m_channelDisplayNameLabel;
			Gtk::Entry m_channelDisplayNameEntry;
		Gtk::Label m_channelColorLabel;
			Gtk::ColorButton m_channelColorButton;

	std::vector<ChannelSelectorRow*> m_rows;
	std::vector<ParameterRowBase*> m_prows;
};

#endif
