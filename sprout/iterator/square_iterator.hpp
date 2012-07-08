#ifndef SPROUT_ITERATOR_SQUARE_ITERATOR_HPP
#define SPROUT_ITERATOR_SQUARE_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/numeric/dft/fixed/square.hpp>

namespace sprout {
	//
	// square_iterator
	//
	template<typename Value>
	class square_iterator
		: public std::iterator<
			std::random_access_iterator_tag,
			Value,
			std::ptrdiff_t,
			Value*,
			Value
		>
	{
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef Value value_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type reference;
	private:
		difference_type index_;
		value_type frequency_;
		value_type amplitude_;
		value_type phase_;
		value_type duty_;
	private:
		explicit SPROUT_CONSTEXPR square_iterator(square_iterator const& other, difference_type index)
			: index_(index)
			, frequency_(other.frequency_)
			, amplitude_(other.amplitude_)
			, phase_(other.phase_)
			, duty_(other.duty_)
		{}
	public:
		SPROUT_CONSTEXPR square_iterator()
			: index_()
			, frequency_(1)
			, amplitude_(1)
			, phase_(0)
			, duty_(0.5)
		{}
		square_iterator(square_iterator const&) = default;
		explicit SPROUT_CONSTEXPR square_iterator(
			difference_type index,
			value_type const& frequency = 1,
			value_type const& amplitude = 1,
			value_type const& phase = 0,
			value_type const& duty = 0.5
			)
			: index_(index)
			, frequency_(frequency)
			, amplitude_(amplitude)
			, phase_(phase)
			, duty_(duty)
		{}
		template<typename U>
		SPROUT_CONSTEXPR square_iterator(square_iterator<U> const& it)
			: index_(it.index_)
			, frequency_(it.frequency_)
			, amplitude_(it.amplitude_)
			, phase_(it.phase_)
			, duty_(it.duty_)
		{}
		template<typename U>
		square_iterator& operator=(square_iterator<U> const& it) {
			square_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR difference_type index() const {
			return index_;
		}
		SPROUT_CONSTEXPR value_type const& frequency() const {
			return frequency_;
		}
		SPROUT_CONSTEXPR value_type const& amplitude() const {
			return amplitude_;
		}
		SPROUT_CONSTEXPR value_type const& phase() const {
			return phase_;
		}
		SPROUT_CONSTEXPR value_type const& duty() const {
			return duty_;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return amplitude_ * sprout::fixed::detail::square_value(frequency_ * value_type(index_) + phase_, duty_);
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &operator*()();
		}
		square_iterator& operator++() {
			++index_;
			return *this;
		}
		square_iterator operator++(int) {
			square_iterator result(*this);
			++index_;
			return result;
		}
		square_iterator& operator--() {
			--index_;
			return *this;
		}
		square_iterator operator--(int) {
			square_iterator temp(*this);
			--index_;
			return temp;
		}
		SPROUT_CONSTEXPR square_iterator operator+(difference_type n) const {
			return square_iterator(*this, index_ + n);
		}
		SPROUT_CONSTEXPR square_iterator operator-(difference_type n) const {
			return square_iterator(*this, index_ - n);
		}
		square_iterator& operator+=(difference_type n) {
			square_iterator temp(*this, index_ + n);
			temp.swap(*this);
			return *this;
		}
		square_iterator& operator-=(difference_type n) {
			square_iterator temp(*this, index_ - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return amplitude_ * sprout::fixed::detail::square_value(frequency_ * value_type(index_ + n) + phase_, duty_);
		}
		SPROUT_CONSTEXPR square_iterator next() const {
			return square_iterator(*this, index_ + 1);
		}
		SPROUT_CONSTEXPR square_iterator prev() const {
			return square_iterator(*this, index_ - 1);
		}
		void swap(square_iterator& other) {
			using std::swap;
			swap(index_, other.index_);
			swap(frequency_, other.frequency_);
			swap(amplitude_, other.amplitude_);
			swap(phase_, other.phase_);
			swap(duty_, other.duty_);
		}
	};

	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR bool operator==(
		sprout::square_iterator<Value1> const& lhs,
		sprout::square_iterator<Value2> const& rhs
		)
	{
		return lhs.index() == rhs.index();
	}
	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR bool operator!=(
		sprout::square_iterator<Value1> const& lhs,
		sprout::square_iterator<Value2> const& rhs
		)
	{
		return !(lhs == rhs);
	}
	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR bool operator<(
		sprout::square_iterator<Value1> const& lhs,
		sprout::square_iterator<Value2> const& rhs
		)
	{
		return lhs.index() < rhs.index();
	}
	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR bool operator>(
		sprout::square_iterator<Value1> const& lhs,
		sprout::square_iterator<Value2> const& rhs
		)
	{
		return rhs < lhs;
	}
	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR bool operator<=(
		sprout::square_iterator<Value1> const& lhs,
		sprout::square_iterator<Value2> const& rhs
		)
	{
		return !(rhs < lhs);
	}
	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR bool operator>=(
		sprout::square_iterator<Value1> const& lhs,
		sprout::square_iterator<Value2> const& rhs
		)
	{
		return !(lhs < rhs);
	}
	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR typename sprout::square_iterator<Value1>::difference_type operator-(
		sprout::square_iterator<Value1> const& lhs,
		sprout::square_iterator<Value2> const& rhs
		)
	{
		return lhs.index() - rhs.index();
	}
	template<typename Value>
	SPROUT_CONSTEXPR sprout::square_iterator<Value> operator+(
		typename sprout::square_iterator<Value>::difference_type n,
		sprout::square_iterator<Value> const& it
		)
	{
		return it + n;
	}

	//
	// swap
	//
	template<typename Value>
	void swap(sprout::square_iterator<Value>& lhs, sprout::square_iterator<Value>& rhs) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs))) {
		lhs.swap(rhs);
	}

	//
	// next
	//
	template<typename Value>
	SPROUT_CONSTEXPR sprout::square_iterator<Value> next(
		sprout::square_iterator<Value> const& it
		)
	{
		return it.next();
	}
	template<typename Value>
	SPROUT_CONSTEXPR sprout::square_iterator<Value> next(
		sprout::square_iterator<Value> const& it,
		typename sprout::square_iterator<Value>::difference_type n
		)
	{
		return it + n;
	}

	//
	// prev
	//
	template<typename Value>
	SPROUT_CONSTEXPR sprout::square_iterator<Value> prev(
		sprout::square_iterator<Value> const& it
		)
	{
		return it.prev();
	}
	template<typename Value>
	SPROUT_CONSTEXPR sprout::square_iterator<Value> prev(
		sprout::square_iterator<Value> const& it,
		typename sprout::square_iterator<Value>::difference_type n
		)
	{
		return it - n;
	}

	//
	// distance
	//
	template<typename Value>
	SPROUT_CONSTEXPR typename std::iterator_traits<sprout::square_iterator<Value> >::difference_type
	distance(
		sprout::square_iterator<Value> first,
		sprout::square_iterator<Value> last
		)
	{
		return last - first;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_SQUARE_ITERATOR_HPP
