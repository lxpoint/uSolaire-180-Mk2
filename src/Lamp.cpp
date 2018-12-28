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

#include "Lamp.hpp"
#include "HardwareMap.hpp"
#include "Arduino.h"

using namespace usolaire;

Lamp::Lamp() :
	brightness_( 0.0 ),
	state_( Lamp::OFF )
{
}

Lamp & Lamp::instance()
{
	static Lamp instance;
	return instance;
}

void Lamp::initialise()
{
	pinMode( RELAY_LAMP_LIVE, 	 		OUTPUT );
	pinMode( RELAY_LAMP_NEUTRAL, 		OUTPUT );
	pinMode( RELAY_INRUSH_BYPASS,		OUTPUT );
	pinMode( LAMP_BRIGHTNESS_PWM,		OUTPUT );

	digitalWrite( RELAY_LAMP_LIVE, 		LOW );
	digitalWrite( RELAY_LAMP_NEUTRAL, 	LOW );
	digitalWrite( RELAY_INRUSH_BYPASS, 	LOW );

	analogWrite( LAMP_BRIGHTNESS_PWM, 	0, FREQ_PWM );
}

float Lamp::getBrightness() const
{
	return this->brightness_;
}

uint8_t Lamp::getState() const
{
	return this->state_;
}

void Lamp::setBrightness(
	float const BRIGHTNESS )
{
	if ( ( BRIGHTNESS >= 0.0 ) && ( BRIGHTNESS <= 100.0 ) )
	{
		this->brightness_ = BRIGHTNESS;
	}
	float outputPwm = ( this->brightness_ / 100.0 ) * Lamp::PWM_OUTPUT_MAX;
	analogWrite( LAMP_BRIGHTNESS_PWM, static_cast< uint8_t >( outputPwm + 0.5 ), FREQ_PWM );
}

void Lamp::setState(
	uint8_t const STATE )
{
	this->state_ = STATE;
	if ( this->state_ == Lamp::ON )
	{
		// Activate both the active and neutral lines of the lamp supply.
		// Order is important to ensure a leading neutral pole, and to switch
		// on the inrush thermistor bypass relay as the last step. Timing is
		// also important and so put in an atomic block.
		ATOMIC_BLOCK()
		{
			digitalWrite( RELAY_LAMP_NEUTRAL, 	HIGH );
			delay( 50 );
			digitalWrite( RELAY_LAMP_LIVE, 	  	HIGH );
			delay( 50 );
			digitalWrite( RELAY_INRUSH_BYPASS, 	HIGH );
		}
	}
	else
	{
		// Similar to above except a leading live pole switch off.
		ATOMIC_BLOCK()
		{
			digitalWrite( RELAY_LAMP_LIVE, 	  	LOW );
			delay( 50 );
			digitalWrite( RELAY_LAMP_NEUTRAL, 	LOW );
			delay( 50 );
			digitalWrite( RELAY_INRUSH_BYPASS, 	LOW );
		}
	}
}
