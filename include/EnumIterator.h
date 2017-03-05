
#pragma once

#include <vector>
#include <string>

enum ExampleContiguous
{
	One = 1,
	Two,
	Three,
};

class ExampleContiguousEnum
{
public:
	struct EnumData
	{
		ExampleContiguous	enumValue;
		std::string			enumString;

		EnumData( ExampleContiguous	_enumValue, const std::string &_enumString );
	};

private:
	static EnumData mSortedByEnum[3+1];
	static EnumData mSortedByString[3+1];

	struct OrderByEnum;
	struct OrderByStr;

public:
	static const EnumData* begin()		{ return &mSortedByEnum[0]; }
	static const EnumData* end()		{ return &mSortedByEnum[3]; }

	/// Returns the min value reached by this enumerator
	static int minValue();

	/// Returns the max value reached by this enumerator
	static int maxValue();

	/// Returns the number of elements in the enum
	static size_t count();

	/// Returns true if integer value can be represented by the enum.
	/// O(1) if enum is contiguous, O(log N) otherwise
	static bool isValidValue( int value );

	/// Only available if the enum is contiguous. Otherwise it's a compiler error
	/// It's O(1)
	/// Returns empty string if value is not a valid enum value
	static const std::string& get( ExampleContiguous value );

	/// Always available. O(1) if enum is contiguous, O(log N) otherwise
	/// Returns empty string if value is not a valid enum value
	static const std::string& find( ExampleContiguous value );

	/// Will find the enumerator value based on its string representation.
	/// Returns false if the string doesn't match any value, leaving the output
	/// 'outValue' untouched (i.e. left uninitialized).
	static bool find( const std::string &strValue, ExampleContiguous &outValue );

	/// Will find the enumerator value based on its string representation.
	/// Throws if the string doesn't match any value.
	static ExampleContiguous find( const std::string &strValue );
};
