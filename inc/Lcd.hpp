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

#if !defined( USOLAIRE_LCD_HPP )
#define USOLAIRE_LCD_HPP

#include "LiquidCrystal.h"

#include <cstdint>

namespace usolaire
{

//! \brief ??
class Lcd
{
    public:
        //! \brief ??
        //! \return ??
		static Lcd & instance();

    public:
        //! \brief ??
 		Lcd( Lcd const & ) = delete;

        //! \brief ??
        void operator=( Lcd const & ) = delete;

    public:
        //! \brief ??
		void initialise();

    public:
        //! \brief ??
		static uint8_t const NUM_LINES = 2;

        //! \brief ??
		static uint8_t const NUM_COLUMNS = 16;

	private:
        //! \brief ??
        Lcd();

	private:
        //! \brief ??
		LiquidCrystal lcd_;
};

}

#endif
