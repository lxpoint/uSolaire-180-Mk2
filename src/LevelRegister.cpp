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

#include "LevelRegister.hpp"

//! ASSUMMPTIONS:
//! - There is at least one change point in the array.
//! - The milli() counter doesn't roll over:
//!		- LevelRegister::changeBrightness
//!		- LevelRegister::initialise
//! THINGS TO CONSIDER:
//! - Change transition beyond a step change.

using namespace usolaire;

LevelRegister::LevelRegister() :
	brightnessCurrent_( 0.0 )
{
	this->changePoints_.reserve( 2 );
	this->changePoints_.push_back( BrightnessChange(  6,  0,  0, 100.0 ) );
	this->changePoints_.push_back( BrightnessChange( 22,  0,  0,   0.0 ) );
}

LevelRegister & LevelRegister::instance()
{
	static LevelRegister instance;
	return instance;
}

void LevelRegister::initialise(
	unsigned long const TIME_NOW,
	int const HOUR_NOW,
	int const MINUTE_NOW,
	int const SECOND_NOW )
{
	unsigned long const MILLI_SINCE_MIDNIGHT = this->convert2Milli( HOUR_NOW, MINUTE_NOW, SECOND_NOW );

	// Search for next change point based on the current time.
	this->pointNext_ = this->changePoints_.begin();
	BrightnessArray::const_iterator const END = this->changePoints_.end();
	for ( ; this->pointNext_ != END; ++this->pointNext_ )
	{
		if ( MILLI_SINCE_MIDNIGHT <= this->convert2Milli( *this->pointNext_ ) )
		{
			break;
		}
	}

	if ( this->pointNext_ == END )
	{
		this->pointNext_ = this->changePoints_.begin();
	}

	unsigned long const MILLI_NEXT = this->convert2Milli( *this->pointNext_ );
	this->timeNext_ = TIME_NOW + ( MILLI_NEXT - MILLI_SINCE_MIDNIGHT );
}

bool LevelRegister::changeBrightness(
	unsigned long const TIME_NOW )
{
	if ( TIME_NOW >= this->timeNext_ )
	{
		this->brightnessCurrent_ = this->pointNext_->brightness_;

		BrightnessArray::const_iterator currentPoint = this->pointNext_;
		this->pointNext_++;

		if ( this->pointNext_ == this->changePoints_.end() )
		{
			this->pointNext_ = this->changePoints_.begin();
			this->timeNext_ += DURATION_DAY - this->convert2Milli( *currentPoint );
			this->timeNext_ += this->convert2Milli( *this->pointNext_ );
		}
		else
		{
			this->timeNext_ += this->convert2Milli( *this->pointNext_ ) - this->convert2Milli( *currentPoint );

		}

		return true;
	}

	return false;
}

float LevelRegister::getBrightness() const
{
	return this->brightnessCurrent_;
}

unsigned long LevelRegister::convert2Milli(
	BrightnessChange const & CHANGE_POINT )
{
	return ( CHANGE_POINT.hour_ * 3600 +
		CHANGE_POINT.minute_ * 60 +
		CHANGE_POINT.second_ ) * 1000;
}

unsigned long LevelRegister::convert2Milli(
	int const HOUR,
	int const MINUTE,
	int const SECOND )
{
	return ( HOUR * 3600 + MINUTE * 60 + SECOND ) * 1000;
}
