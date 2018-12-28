/////////////////////////////////////////////////////////////////////////////
//
// uSolaire 180 Mk2
//
// Copyright (c) 2018 lagrangianpoint
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// For all other enquiries, contact Colin Irwin at lagrangianpoint:
// colin@lagrangianpoint.net.
//
/////////////////////////////////////////////////////////////////////////////

#include "system.hpp"
#include "Buttons.hpp"
#include "Lamp.hpp"
#include "LampControl.hpp"
#include "Lcd.hpp"

#include <application.h>

using namespace usolaire;

// Timer for updating the current time every hour.
bool flagUpdateTime = false;
uint32_t const TIME_HOUR_MS = 12 * 60 * 60 * 1000;
Timer timeUpdateTimer( TIME_HOUR_MS, callbackUpdateTime );

// Timer for updating the clock model every second.
bool flagSecondTick = false;
uint32_t const TIME_SECOND_MS = 1000;
Timer secondTimer( TIME_SECOND_MS, callbackSecondTick );

//
LampControl controller;

void loop()
{
	if ( flagUpdateTime )
	{
		Particle.syncTime();
		flagUpdateTime = false;
	}

	if ( flagSecondTick )
	{
		controller.process_event( EvtSecondTick() );
		flagSecondTick = false;
	}

	processButtons( controller );
}

void setup()
{
	// Initialise all the hardware.
	Lamp::instance().initialise();
	Lcd::instance().initialise();
	initialiseButtons();

	// Start the lamp controller state machine.
	controller.initiate();

	// Start the timers.
	timeUpdateTimer.start();
	secondTimer.start();
}

void callbackSecondTick()
{
	flagSecondTick = true;
}

void callbackUpdateTime()
{
	flagUpdateTime = true;
}
