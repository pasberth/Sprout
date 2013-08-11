/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_ALGORITHM_TEST_IS_STRICTLY_INCREASING_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_IS_STRICTLY_INCREASING_CPP

#include <sprout/algorithm/is_strictly_increasing.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_is_strictly_increasing_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 3, 5, 7, 9, 2, 4, 6, 8, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{{1, 1, 5, 7, 9, 2, 4, 6, 10, 10}};

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_increasing(
					sprout::begin(arr1),
					sprout::end(arr1)
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_increasing(
					sprout::begin(arr2),
					sprout::end(arr2)
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_increasing(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_increasing(
					sprout::begin(arr2),
					sprout::begin(arr2) + 5
					);
				TESTSPR_BOTH_ASSERT(!result);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_increasing(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::end(arr1))
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_increasing(
					testspr::reduct_forward(sprout::begin(arr2)),
					testspr::reduct_forward(sprout::end(arr2))
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_increasing(
					testspr::reduct_forward(sprout::begin(arr1)),
					testspr::reduct_forward(sprout::begin(arr1) + 5)
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_increasing(
					testspr::reduct_forward(sprout::begin(arr2)),
					testspr::reduct_forward(sprout::begin(arr2) + 5)
					);
				TESTSPR_BOTH_ASSERT(!result);
			}

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_increasing(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::end(arr1))
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_increasing(
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::end(arr2))
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_increasing(
					testspr::reduct_random_access(sprout::begin(arr1)),
					testspr::reduct_random_access(sprout::begin(arr1) + 5)
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::is_strictly_increasing(
					testspr::reduct_random_access(sprout::begin(arr2)),
					testspr::reduct_random_access(sprout::begin(arr2) + 5)
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_is_strictly_increasing_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_IS_STRICTLY_INCREASING_CPP
