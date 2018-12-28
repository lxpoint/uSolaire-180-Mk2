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

#if !defined( USOLAIRE_LEVEL_REGISTER_HPP )
#define USOLAIRE_LEVEL_REGISTER_HPP

#include <vector>

namespace usolaire
{

//! \brief ??
struct BrightnessChange
{
	public:
		//! \brief ??
        //! \param HOUR ??
        //! \param MINUTE ??
        //! \param SECOND ??
		//! \param BRIGHTNESS ??
		BrightnessChange(
			int const HOUR,
			int const MINUTE,
			int const SECOND,
			float const BRIGHTNESS ) :
				hour_( HOUR ),
				minute_( MINUTE ),
				second_( SECOND ),
				brightness_( BRIGHTNESS )
		{
		}

	public:
		//! \brief ??
		int hour_;

		//! \brief ??
		int minute_;

		//! \brief ??
		int second_;

		//! \brief ??
		float brightness_;

		//! \brief ??
//    	?? changeType_;
};

//! \brief ??
class LevelRegister
{
    public:
        //! \brief ??
        //! \return ??
		static LevelRegister & instance();

    public:
        //! \brief ??
 		LevelRegister( LevelRegister const & ) = delete;

        //! \brief ??
        void operator=( LevelRegister const & ) = delete;

    public:
        //! \brief ??
        //! \param TIME_NOW ??
        //! \param HOUR_NOW ??
        //! \param MINUTE_NOW ??
        //! \param SECOND_NOW ??
		void initialise(
			unsigned long const TIME_NOW,
			int const HOUR_NOW,
			int const MINUTE_NOW,
			int const SECOND_NOW );

        //! \brief ??
        //! \param TIME_NOW ??
		bool changeBrightness(
			unsigned long const TIME_NOW );

        //! \brief ??
		float getBrightness() const;

	private:
        //! \brief ??
		typedef std::vector< BrightnessChange > BrightnessArray;

	private:
        //! \brief ??
        LevelRegister();

        //! \brief ??
        //! \param CHANGE_POINT ??
        unsigned long convert2Milli(
			BrightnessChange const & CHANGE_POINT );

        //! \brief ??
        //! \param HOUR ??
        //! \param MINUTE ??
        //! \param SECOND ??
        unsigned long convert2Milli(
			int const HOUR,
			int const MINUTE,
			int const SECOND );

	private:
		//!\ brief ??
		static unsigned long const DURATION_DAY = 24 * 60 * 60 * 1000;

	private:
		//!\ brief ??
		float brightnessCurrent_;

		//!\ brief ??
		BrightnessArray changePoints_;

		//!\ brief ??
		unsigned long timeNext_;

		//!\ brief ??
		BrightnessArray::const_iterator pointNext_;
};

}

#endif
