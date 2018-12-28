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

#if !defined( USOLAIRE_LAMP_HPP )
#define USOLAIRE_LAMP_HPP

#include <cstdint>

namespace usolaire
{

//! \brief ??
class Lamp
{
    public:
        //! \brief ??
        //! \return ??
		static Lamp & instance();

    public:
        //! \brief ??
 		Lamp( Lamp const & ) = delete;

        //! \brief ??
        void operator=( Lamp const & ) = delete;

    public:
        //! \brief ??
        //! \return ??
		float getBrightness() const;

        //! \brief ??
        //! \return ??
		uint8_t getState() const;

        //! \brief ??
		void initialise();

        //! \brief ??
        //! \param STATE ??
        //! \return ??
		void setBrightness(
			float const BRIGHTNESS );

        //! \brief ??
        //! \param STATE ??
        //! \return ??
		void setState(
			uint8_t const STATE );

    public:
        //! \brief ??
		static uint8_t const OFF = 0x00;

        //! \brief ??
		static uint8_t const ON = 0x01;

	private:
        //! \brief ??
        Lamp();

	private:
        //! \brief ??
		static uint16_t const FREQ_PWM = 500;

        //! \brief ??
		static uint8_t const PWM_OUTPUT_MAX = 222;

        //! \brief ??
		static uint8_t const PWM_OUTPUT_MIN = 0;

	private:
        //! \brief ??
		float brightness_;

        //! \brief ??
		uint8_t state_;
};

}

#endif
