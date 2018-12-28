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

#if !defined( USOLAIRE_BUTTONS_HPP )
#define USOLAIRE_BUTTONS_HPP

#include "LampControl.hpp"
#include "phi_interfaces.h"

namespace usolaire
{

uint8_t const NUMBER_BUTTONS		= 4;

char const BUTTON_VALUE_0           = 0x01;
char const BUTTON_VALUE_1           = 0x02;
char const BUTTON_VALUE_2           = 0x03;
char const BUTTON_VALUE_3           = 0x04;

extern char buttonMapping[];
extern uint8_t buttonPins[];
extern phi_button_groups buttonGroup;

//! \brief ??
void initialiseButtons();

//! \brief ??
//! \param CONTROLLER ??
void processButtons(
	LampControl & controller );

}

#endif
