
#include "EnumIterator.h"
#include <algorithm>
#include <stdexcept>

const std::string BLANKSTRING = "";

ExampleContiguousEnum::EnumData ExampleContiguousEnum::mSortedByEnum[3+1] =
{
	ExampleContiguousEnum::EnumData( One,		"One" ),
	ExampleContiguousEnum::EnumData( Two,		"Two" ),
	ExampleContiguousEnum::EnumData( Three,		"Three" ),
	ExampleContiguousEnum::EnumData( Three,		"__INVALID" )
};

ExampleContiguousEnum::EnumData ExampleContiguousEnum::mSortedByString[3+1] =
{
	ExampleContiguousEnum::EnumData( One,		"One" ),
	ExampleContiguousEnum::EnumData( Three,		"Three" ),
	ExampleContiguousEnum::EnumData( Two,		"Two" ),
	ExampleContiguousEnum::EnumData( Three,		"__INVALID" )
};
//---------------------------------------------------------------------------------------
ExampleContiguousEnum::EnumData::EnumData( ExampleContiguous _enumValue,
										   const std::string &_enumString ) :
	enumValue( _enumValue ),
	enumString( _enumString )
{
}
//---------------------------------------------------------------------------------------
struct ExampleContiguousEnum::OrderByEnum
{
	bool operator () ( const ExampleContiguousEnum::EnumData &_l, ExampleContiguous _r ) const
	{
		return _l.enumValue < _r;
	}

	bool operator () ( ExampleContiguous _l, const ExampleContiguousEnum::EnumData &_r ) const
	{
		return _l < _r.enumValue;
	}

	bool operator () ( const ExampleContiguousEnum::EnumData &_l, int _r ) const
	{
		return _l.enumValue < _r;
	}

	bool operator () ( int _l, const ExampleContiguousEnum::EnumData &_r ) const
	{
		return _l < _r.enumValue;
	}
};
//---------------------------------------------------------------------------------------
struct ExampleContiguousEnum::OrderByStr
{
	bool operator () ( const ExampleContiguousEnum::EnumData &_l, const std::string &_r ) const
	{
		return _l.enumString < _r;
	}

	bool operator () ( const std::string &_l, const ExampleContiguousEnum::EnumData &_r ) const
	{
		return _l < _r.enumString;
	}
};
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
int ExampleContiguousEnum::minValue()
{
	return mSortedByEnum[0].enumValue;
}
//---------------------------------------------------------------------------------------
int ExampleContiguousEnum::maxValue()
{
	return mSortedByEnum[3-1].enumValue;
}
//---------------------------------------------------------------------------------------
size_t ExampleContiguousEnum::count()
{
	return 3u;
}
//---------------------------------------------------------------------------------------
bool ExampleContiguousEnum::find( const std::string &strValue, ExampleContiguous &outValue )
{
	const EnumData* itor = std::lower_bound( &mSortedByString[0],
											 &mSortedByString[3],
											 strValue, OrderByStr() );

	if( itor != &mSortedByString[3] && itor->enumString == strValue )
	{
		outValue = itor->enumValue;
		return true;
	}
	else
	{
		return false;
	}
}
//---------------------------------------------------------------------------------------
ExampleContiguous ExampleContiguousEnum::find( const std::string &strValue )
{
	ExampleContiguous retVal;
	const bool bFound = find( strValue, retVal );
	if( !bFound )
	{
		throw std::invalid_argument( "String: " + strValue +
									 " is not a valid enum of type ExampleContiguous" );
	}

	return retVal;
}

#ifndef CONTIGUOUS
//---------------------------------------------------------------------------------------
bool ExampleContiguousEnum::isValidValue( int value )
{
	const EnumData* itor = std::lower_bound( &mSortedByString[0],
											 &mSortedByString[3],
											 value, OrderByEnum() );

	if( itor != &mSortedByString[3] && itor->enumValue == value )
		return true;

	return false;
}
//---------------------------------------------------------------------------------------
const std::string& ExampleContiguousEnum::find( ExampleContiguous value )
{
	const EnumData *itor = std::lower_bound( begin(), end(), value, OrderByEnum() );

	if( itor != end() && itor->enumValue == value )
	{
		return itor->enumString;
	}
	else
	{
		return BLANKSTRING;
	}
}
#else
//---------------------------------------------------------------------------------------
bool ExampleContiguousEnum::isValidValue( int value )
{
	return minValue() >= idx && idx <= maxValue();
}
//---------------------------------------------------------------------------------------
const std::string& ExampleContiguousEnum::get( ExampleContiguous value )
{
	const int idx = value - mSortedByEnum[0].enumValue;
	if( idx >= count() )
		return BLANKSTRING;

	return mSortedByEnum[idx].enumString;
}
//---------------------------------------------------------------------------------------
const std::string& ExampleContiguousEnum::find( ExampleContiguous value )
{
	return get( value );
}
#endif
