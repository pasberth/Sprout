#ifndef SPROUT_STRING_TUPLE_HPP
#define SPROUT_STRING_TUPLE_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <sprout/string/string.hpp>

namespace std {
	//
	// tuple_size
	//
	template<typename T, std::size_t N, typename Traits>
	class tuple_size<sprout::basic_string<T, N, Traits> >
		: public std::integral_constant<std::size_t, N>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename T, std::size_t N, typename Traits>
	class tuple_element<I, sprout::basic_string<T, N, Traits> > {
	public:
		static_assert(I < N, "tuple_element<>: index out of range");
		typedef T type;
	};
}	// namespace std

#endif	// #ifndef SPROUT_STRING_TUPLE_HPP
