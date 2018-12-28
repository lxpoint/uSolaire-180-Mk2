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

#include "Lcd.hpp"
#include "HardwareMap.hpp"
#include "Arduino.h"

using namespace usolaire;

Lcd::Lcd() :
	lcd_( LCD_RS, LCD_ENABLE, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7 )
{
}

Lcd & Lcd::instance()
{
	static Lcd instance;
	return instance;
}

void Lcd::initialise()
{
	this->lcd_.begin( Lcd::NUM_COLUMNS, Lcd::NUM_LINES );
}

/*
	pinMode( LCD_BACKLIGHT, OUTPUT );
	pinMode( LCD_DB7, 	 	OUTPUT );
	pinMode( LCD_DB6, 	 	OUTPUT );
	pinMode( LCD_DB5, 	 	OUTPUT );
	pinMode( LCD_DB4, 	 	OUTPUT );
	pinMode( LCD_ENABLE, 	OUTPUT );
	pinMode( LCD_RS, 	 	OUTPUT );

	digitalWrite( LCD_BACKLIGHT,	LOW );
	digitalWrite( LCD_DB7, 	 		LOW );
	digitalWrite( LCD_DB6, 	 		LOW );
	digitalWrite( LCD_DB5, 	 		LOW );
	digitalWrite( LCD_DB4, 	 		LOW );
	digitalWrite( LCD_ENABLE, 		LOW );
	digitalWrite( LCD_RS, 	 		LOW );
*/
