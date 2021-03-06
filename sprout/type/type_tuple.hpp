/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TYPE_TUPLE_HPP
#define SPROUT_TYPE_TYPE_TUPLE_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/index_n.hpp>
#include <sprout/index_tuple/make_index_tuple.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/iterator.hpp>
#include <sprout/type/iterator/index_iterator.hpp>
#include <sprout/type/rebind_types.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace types {
		//
		// type_tuple
		//
		template<typename... Types>
		struct type_tuple {
		public:
			typedef type_tuple type;
			typedef sprout::types::index_iterator<type_tuple, 0> begin;
			typedef sprout::types::index_iterator<type_tuple, sizeof...(Types)> end;
		public:
			SPROUT_STATIC_CONSTEXPR std::size_t static_size = sizeof...(Types);
		};
		template<typename... Types>
		SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::types::type_tuple<Types...>::static_size;

		//
		// rebind_types
		//
		template<typename... Ts>
		struct rebind_types<sprout::types::type_tuple<Ts...> > {
		public:
			template<typename... Types>
			struct apply {
			public:
				typedef sprout::types::type_tuple<Types...> type;
			};
		};

		namespace detail {
			template<typename Tup>
			struct head_element;
			template<typename Head, typename... Tail>
			struct head_element<sprout::types::type_tuple<Head, Tail...> >
				: public sprout::identity<Head>
			{};

			template<typename Tup>
			struct tuple_head;
			template<typename Head, typename... Tail>
			struct tuple_head<sprout::types::type_tuple<Head, Tail...> >
				: public sprout::identity<sprout::types::type_tuple<Head> >
			{};

			template<typename Tup>
			struct tuple_tail;
			template<typename Head, typename... Tail>
			struct tuple_tail<sprout::types::type_tuple<Head, Tail...> >
				: public sprout::identity<sprout::types::type_tuple<Tail...> >
			{};

			template<sprout::index_t, typename T = void>
			struct dummy_index
				: public sprout::identity<T>
			{};

			template<typename Tup1, typename Tup2>
			struct tuple_cat;
			template<typename... Types1, typename... Types2>
			struct tuple_cat<sprout::types::type_tuple<Types1...>, sprout::types::type_tuple<Types2...> >
				: public sprout::identity<sprout::types::type_tuple<Types1..., Types2...> >
			{};

			template<typename IndexTuple>
			struct tuple_drop_helper;
			template<sprout::index_t... Indexes>
			struct tuple_drop_helper<sprout::index_tuple<Indexes...> > {
				template<typename... Types>
				static sprout::types::type_tuple<typename Types::type...>
				eval(typename sprout::types::detail::dummy_index<Indexes>::type*..., Types*...);
			};
			template<std::size_t I, typename Tup>
			struct tuple_drop_impl;
			template<std::size_t I, typename... Types>
			struct tuple_drop_impl<I, sprout::types::type_tuple<Types...> >
				: public sprout::identity<decltype(
					sprout::types::detail::tuple_drop_helper<typename sprout::index_n<0, I>::type>
						::eval(static_cast<sprout::identity<Types>*>(0)...)
				)>::type
			{};
			template<std::size_t I, typename Tup>
			struct tuple_drop;
			template<std::size_t I, typename... Types>
			struct tuple_drop<I, sprout::types::type_tuple<Types...> >
				: public sprout::types::detail::tuple_drop_impl<I, sprout::types::type_tuple<Types...> >
			{};

			template<std::size_t I, typename Tup>
			struct tuple_element;
			template<std::size_t I, typename... Types>
			struct tuple_element<I, sprout::types::type_tuple<Types...> >
				: public sprout::types::detail::head_element<
					typename sprout::types::detail::tuple_drop<I, sprout::types::type_tuple<Types...> >::type
				>
			{};

			template<std::size_t I, typename Tup, typename IndexTuple>
			struct tuple_take_impl;
			template<std::size_t I, typename... Types, sprout::index_t... Indexes>
			struct tuple_take_impl<I, sprout::types::type_tuple<Types...>, sprout::index_tuple<Indexes...> >
				: public sprout::identity<
					sprout::types::type_tuple<
						typename sprout::types::detail::tuple_element<Indexes, sprout::types::type_tuple<Types...> >::type...
					>
				>::type
			{};
			template<std::size_t I, typename Tup>
			struct tuple_take;
			template<std::size_t I, typename... Types>
			struct tuple_take<I, sprout::types::type_tuple<Types...> >
				: public sprout::types::detail::tuple_take_impl<I, sprout::types::type_tuple<Types...>, typename sprout::make_index_tuple<I>::type>
			{};
		}	// namespace detail
	}	// namespace types

	using sprout::types::type_tuple;
	using sprout::types::rebind_types;
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<typename... Types>
	struct tuple_size<sprout::types::type_tuple<Types...> >
		: public sprout::integral_constant<std::size_t, sizeof...(Types)>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename... Types>
	struct tuple_element<I, sprout::types::type_tuple<Types...> >
		: public sprout::types::detail::tuple_element<I, sprout::types::type_tuple<Types...> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_TYPE_TYPE_TUPLE_HPP
