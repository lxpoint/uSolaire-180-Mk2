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

#if !defined( USOLAIRE_HARDWARE_MAP_HPP )
#define USOLAIRE_HARDWARE_MAP_HPP

#include <Arduino.h>

namespace usolaire
{

uint16_t const BUTTON_PIN_0         = D3;
uint16_t const BUTTON_PIN_1         = D2;
uint16_t const BUTTON_PIN_2         = D1;
uint16_t const BUTTON_PIN_3         = D0;

uint16_t const RELAY_LAMP_LIVE      = A0;
uint16_t const RELAY_LAMP_NEUTRAL   = A1;
uint16_t const RELAY_INRUSH_BYPASS  = DAC;

uint16_t const LAMP_BRIGHTNESS_PWM 	= A5;

uint16_t const LCD_BACKLIGHT	   	= A4;
uint16_t const LCD_DB7   			= A3;
uint16_t const LCD_DB6   			= A2;
uint16_t const LCD_DB5   			= D7;
uint16_t const LCD_DB4   			= D6;
uint16_t const LCD_ENABLE   		= D5;
uint16_t const LCD_RS				= D4;

}

#endif
