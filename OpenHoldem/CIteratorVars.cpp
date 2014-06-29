//******************************************************************************
//
// This file is part of the OpenHoldem project
//   Download page:         http://code.google.com/p/openholdembot/
//   Forums:                http://www.maxinmontreal.com/forums/index.php
//   Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose: Global class to hold variables that are used by the 
//   CIteratorThread class but need to persist between instantiations 
//   of the CIteratorThread class
//
//******************************************************************************

#include "stdafx.h"
#include "CIteratorVars.h"

#include "CPreferences.h"

CIteratorVars iter_vars; // TODO!! Bad: global object! Undefined sequence of initialization!


CIteratorVars::CIteratorVars()
{
	ResetVars();
}

CIteratorVars::~CIteratorVars()
{}

void CIteratorVars::ResetVars()
{
	__TRACE
	write_log(preferences.debug_prwin(), "[CiteratorVars] Resetting PrWin variables\n");
	_nit = 0;
	_prwin = 0;
	_prtie = 0;
	_prlos = 0;
	_iterator_thread_running = false;
	_iterator_thread_complete = true;
	_iterator_thread_progress = 0;
}


