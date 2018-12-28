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

#if !defined( USOLAIRE_LAMP_CONTROL_HPP )
#define USOLAIRE_LAMP_CONTROL_HPP

#include "Events.hpp"
#include "Lamp.hpp"
#include "LevelRegister.hpp"

#include <boost/mpl/list.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/in_state_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/transition.hpp>

#include <Arduino.h>

namespace usolaire
{


struct ModeAutomated;
struct ModeManualOff;
struct ModeManualOn;


//!
//! State machine.
//!

//! \brief ??
struct LampControl : boost::statechart::state_machine< LampControl, ModeManualOff >
{
};


//!
//! Top level states.
//!

//! \brief ??
struct ModeAutomated : boost::statechart::simple_state< ModeAutomated, LampControl >
{
	public:
		//! \brief ??
		ModeAutomated()
		{
			time_t currentTime = Time.now();
			LevelRegister::instance().initialise( millis(), Time.day( currentTime ),
				Time.minute( currentTime ), Time.second( currentTime ) );
		}

		//! \brief ??
		//! \param EVENT ??
		boost::statechart::result react(
			EvtButton0Short const & EVENT )
		{
			if ( Lamp::instance().getState() == Lamp::ON )
			{
				return transit< ModeManualOff >();
			}
			else
			{
				return transit< ModeManualOn >();
			}
		}

		//! \brief ??
		//! \param EVENT ??
		void secondTick(
			EvtSecondTick const & EVENT )
		{
			if ( LevelRegister::instance().changeBrightness( millis() ) )
			{
				Lamp::instance().setBrightness( LevelRegister::instance().getBrightness() );
			}
		}

	public:
		//! \brief ??
		typedef boost::mpl::list<
			boost::statechart::custom_reaction< EvtButton0Short >,
			boost::statechart::in_state_reaction< EvtSecondTick, ModeAutomated, &ModeAutomated::secondTick > > reactions;
};

//! \brief ??
struct ModeManualOff : boost::statechart::simple_state< ModeManualOff, LampControl >
{
	public:
		//! \brief ??
		ModeManualOff()
		{
			Lamp::instance().setState( Lamp::OFF );
			Lamp::instance().setBrightness( 0.0 );
		}

		//! \brief ??
		~ModeManualOff()
		{
			// Nothing to do on state exit.
		}

	public:
		//! \brief ??
		typedef boost::mpl::list<
			boost::statechart::transition< EvtButton0Long,  ModeAutomated >,
			boost::statechart::transition< EvtButton0Short, ModeManualOn > > reactions;
};

//! \brief ??
struct ModeManualOn : boost::statechart::simple_state< ModeManualOn, LampControl >
{
	public:
		//! \brief ??
		ModeManualOn()
		{
			Lamp::instance().setState( Lamp::ON );
			Lamp::instance().setBrightness( 100.0 );
		}

		//! \brief ??
		~ModeManualOn()
		{
			// Nothing to do on state exit.
		}

	public:
		//! \brief ??
		typedef boost::mpl::list<
			boost::statechart::transition< EvtButton0Long,  ModeAutomated >,
			boost::statechart::transition< EvtButton0Short, ModeManualOff > > reactions;
};

}

#endif
