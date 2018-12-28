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

#include "Buttons.hpp"
#include "Events.hpp"
#include "HardwareMap.hpp"

namespace usolaire
{

char buttonMapping[] = {
    BUTTON_VALUE_0,
    BUTTON_VALUE_1,
    BUTTON_VALUE_2,
    BUTTON_VALUE_3, };
uint8_t buttonPins[] = {
    BUTTON_PIN_0,
    BUTTON_PIN_1,
    BUTTON_PIN_2,
    BUTTON_PIN_3, };
phi_button_groups buttonGroup( buttonMapping, buttonPins, NUMBER_BUTTONS );

bool buttonHeld = false;
uint8_t buttonPressed = NO_KEY;
uint8_t buttonValue = NO_KEY;

void initialiseButtons()
{
	pinMode( BUTTON_PIN_0, INPUT );
	pinMode( BUTTON_PIN_1, INPUT );
	pinMode( BUTTON_PIN_2, INPUT );
	pinMode( BUTTON_PIN_3, INPUT );
}

void processButtons(
	 LampControl & controller )
{
	uint8_t buttonValue = buttonGroup.getKey();
	if ( buttonGroup.get_status() == buttons_pressed )
	{
		buttonPressed = buttonValue;
	}

	if ( buttonGroup.get_status() == buttons_released )
	{
		if ( buttonHeld )
		{
			buttonHeld = false;
		}
		else
		{
			switch( buttonPressed )
			{
				case BUTTON_VALUE_0:
				{
					controller.process_event( EvtButton0Short() );
					break;
				}
				case BUTTON_VALUE_1:
				{
					controller.process_event( EvtButton1Short() );
					break;
				}
				case BUTTON_VALUE_2:
				{
					controller.process_event( EvtButton2Short() );
					break;
				}
				case BUTTON_VALUE_3:
				{
					controller.process_event( EvtButton3Short() );
					break;
				}
			}
		}
	}

	if ( ( buttonGroup.get_status() == buttons_held ) &&
		( !buttonHeld ) )
	{
		buttonHeld = true;
		switch( buttonPressed )
		{
			case BUTTON_VALUE_0:
			{
				controller.process_event( EvtButton0Long() );
				break;
			}
			case BUTTON_VALUE_1:
			{
				controller.process_event( EvtButton1Long() );
				break;
			}
			case BUTTON_VALUE_2:
			{
				controller.process_event( EvtButton2Long() );
				break;
			}
			case BUTTON_VALUE_3:
			{
				controller.process_event( EvtButton3Long() );
				break;
			}
		}
	}
}

}
