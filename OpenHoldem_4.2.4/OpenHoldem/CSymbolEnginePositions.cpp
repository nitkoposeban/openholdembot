//*****************************************************************************
//
// This file is part of the OpenHoldem project
//   Download page:         http://code.google.com/p/openholdembot/
//   Forums:                http://www.maxinmontreal.com/forums/index.php
//   Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//*****************************************************************************
//
// Purpose:
//
//*****************************************************************************

#include "stdafx.h"
#include "CSymbolEnginePositions.h"

#include <assert.h>
#include "CScraper.h"
#include "CStringMatch.h"
#include "CSymbolEngineActiveDealtPlaying.h"
#include "CSymbolEngineDealerchair.h"
#include "CSymbolEngineRaisersCallers.h"
#include "CSymbolEngineUserchair.h"
#include "NumericalFunctions.h"

CSymbolEnginePositions *p_symbol_engine_positions = NULL;

CSymbolEnginePositions::CSymbolEnginePositions()
{
	// The values of some symbol-engines depend on other engines.
	// As the engines get later called in the order of initialization
	// we assure correct ordering by checking if they are initialized.
	assert(p_symbol_engine_active_dealt_playing != NULL);
	assert(p_symbol_engine_dealerchair != NULL);
	assert(p_symbol_engine_userchair != NULL);
}

CSymbolEnginePositions::~CSymbolEnginePositions()
{}

void CSymbolEnginePositions::InitOnStartup()
{}

void CSymbolEnginePositions::ResetOnConnection()
{}

void CSymbolEnginePositions::ResetOnHandreset()
{}

void CSymbolEnginePositions::ResetOnNewRound()
{}

void CSymbolEnginePositions::ResetOnMyTurn()
{
	CalculatePositionForTheRaiser();
	CalculatePositionsForTheUserchair();
}

void CSymbolEnginePositions::ResetOnHeartbeat()
{
	CalculateNChairsDealtLeftRight();
}

void CSymbolEnginePositions::CalculateNChairsDealtLeftRight()
{
	_nchairsdealtright = 0;
	_nchairsdealtleft  = 0;

	if (!p_symbol_engine_userchair->userchair_confirmed())
	{
		// Nothing to search for
		return;
	}

	bool found_userchair = false;
	for (int i=DEALER_CHAIR+1; 
		i<=DEALER_CHAIR+p_tablemap->nchairs();
		i++)
	{
		int next_chair = i%p_tablemap->nchairs();
		double p_bet = p_scraper->player_bet(next_chair);

		if (next_chair == USER_CHAIR)
		{
			found_userchair = true;
		}
		else if (IsBitSet(p_symbol_engine_active_dealt_playing->playersdealtbits(), next_chair))
		{
			if (!found_userchair)
			{
				_nchairsdealtright++;
			}
			else
			{
				_nchairsdealtleft++;
			}
		}
	}
	AssertRange(_nchairsdealtright, 0, (k_max_number_of_players - 1));
	AssertRange(_nchairsdealtleft,  0, (k_max_number_of_players - 1));
}

void CSymbolEnginePositions::CalculatePositionForTheRaiser()
{
	_betpositionrais  = 0;
	_dealpositionrais = 0;

	for (int i=DEALER_CHAIR+1; 
		i<=(DEALER_CHAIR+p_tablemap->nchairs()) 
			&& (i%p_tablemap->nchairs())!=p_symbol_engine_raisers_callers->raischair(); 
		i++)
	{
		int next_chair = i%p_tablemap->nchairs();
		if (IsBitSet(p_symbol_engine_active_dealt_playing->nplayersdealt(), next_chair))
		{
			_betpositionrais++;
		}
		if (IsBitSet(p_symbol_engine_active_dealt_playing->playersdealtbits(), next_chair))
		{
			_dealpositionrais++;
		}
	}
	AssertRange(_betpositionrais,  k_undefined, k_max_number_of_players);
	AssertRange(_dealpositionrais, k_undefined, k_max_number_of_players);
}

void CSymbolEnginePositions::CalculatePositionsForTheUserchair()
{
	_betposition  = 0;
	_dealposition = 0;
	_callposition = 0;

	for (int i=DEALER_CHAIR+1; 
		i<=DEALER_CHAIR+p_tablemap->nchairs();
		i++)
	{
		int next_chair = i%p_tablemap->nchairs();
		if (IsBitSet(p_symbol_engine_active_dealt_playing->nplayersdealt(), next_chair))
		{
			_betposition++;
		}
		if (IsBitSet(p_symbol_engine_active_dealt_playing->playersdealtbits(), next_chair))
		{
			_dealposition++;
		}
		if ((i%p_tablemap->nchairs()) == USER_CHAIR)
		{
			// Stop searching
			break;
		}
	}

	int raischair = p_symbol_engine_raisers_callers->raischair();
	for (int i=raischair+1; i<=raischair+p_tablemap->nchairs(); i++)
	{
		int next_chair = i%p_tablemap->nchairs();
		if (IsBitSet(p_symbol_engine_active_dealt_playing->nplayersdealt(), next_chair))
		{
			_callposition++;
		}
	}
	AssertRange(_betposition,  k_undefined, k_max_number_of_players);
	AssertRange(_dealposition, k_undefined, k_max_number_of_players);
	AssertRange(_callposition, k_undefined, k_max_number_of_players);
}