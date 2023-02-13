#pragma once


#include <array>
#include <vcruntime.h>


template<class T,class N,size_t size = static_cast<size_t>(N::COUNT)>
class EnumArray : std::array<T,size>
{
private:
	using base_t = std::array<T,size>;
public:
	T& operator[](const N& i_idx) 
	{ 
		size_t idx = static_cast<size_t>(idx);
		return base_t::operator[](idx); 

	}
	const T& operator[](const N& i_idx) const 
	{
		size_t idx = static_cast<size_t>(idx);
		return base_t::operator[](idx); 
	}
};