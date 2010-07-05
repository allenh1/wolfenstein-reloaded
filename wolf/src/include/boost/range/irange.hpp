// Boost.Range library
//
//  Copyright Neil Groves 2010. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_IRANGE_HPP_INCLUDED
#define BOOST_RANGE_IRANGE_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost
{
    namespace range_detail
    {
        // integer_iterator is an iterator over an integer sequence that
        // is bounded only by the limits of the underlying integer
        // representation.
        //
        // This is useful for implementing the irange(first, last)
        // function.
        //
        // Note:
        // This use of this iterator and irange is appreciably less
        // performant than the corresponding hand-written integer
        // loop on many compilers.
        template<typename Integer>
        class integer_iterator
            : public boost::iterator_facade<
                        integer_iterator<Integer>,
                        Integer,
                        boost::random_access_traversal_tag,
                        Integer,
                        std::ptrdiff_t
                    >
        {
            typedef boost::iterator_facade<
                        integer_iterator<Integer>,
                        Integer,
                        boost::random_access_traversal_tag,
                        Integer,
                        std::ptrdiff_t
                    > base_t;
        public:
            typedef typename base_t::value_type value_type;
            typedef typename base_t::difference_type difference_type;
            typedef typename base_t::reference reference;

            integer_iterator() : m_value() {}
            explicit integer_iterator(value_type x) : m_value(x) {}

        private:
            void increment()
            {
                ++m_value;
            }

            void decrement()
            {
                --m_value;
            }

            void advance(difference_type offset)
            {
                m_value += offset;
            }

            difference_type distance_to(const integer_iterator& other) const
            {
                return other.m_value - m_value;
            }

            bool equal(const integer_iterator& other) const
            {
                return m_value == other.m_value;
            }

            reference dereference() const
            {
                return m_value;
            }

            friend class ::boost::iterator_core_access;
            value_type m_value;
        };

        // integer_iterator_with_step is similar in nature to the
        // integer_iterator but provides the ability to 'move' in
        // a number of steps specified at construction time.
        //
        // The three variable implementation provides the best guarantees
        // of loop termination upon various combinations of input.
        //
        // While this design is less performant than some less
        // safe alternatives, the use of ranges and iterators to
        // perform counting will never be optimal anyhow, hence
        // if optimal performance is desired a handcoded loop
        // is the solution.
        template<typename Integer>
        class integer_iterator_with_step
            : public boost::iterator_facade<
                        integer_iterator_with_step<Integer>,
                        Integer,
                        boost::random_access_traversal_tag,
                        Integer,
                        std::ptrdiff_t
                    >
        {
            typedef boost::iterator_facade<
                        integer_iterator_with_step<Integer>,
                        Integer,
                        boost::random_access_traversal_tag,
                        Integer,
                        std::ptrdiff_t
                    > base_t;
        public:
            typedef typename base_t::value_type value_type;
            typedef typename base_t::difference_type difference_type;
            typedef typename base_t::reference reference;

            integer_iterator_with_step(value_type first, value_type step, difference_type step_size)
                : m_first(first)
                , m_step(step)
                , m_step_size(step_size)
            {
                BOOST_ASSERT( step >= 0 );
                BOOST_ASSERT( step_size != 0 );
            }

        private:
            void increment()
            {
                ++m_step;
            }

            void decrement()
            {
                --m_step;
            }

            void advance(difference_type offset)
            {
                m_step += offset;
            }

            difference_type distance_to(const integer_iterator_with_step& other) const
            {
                return other.m_step - m_step;
            }

            bool equal(const integer_iterator_with_step& other) const
            {
                return m_step == other.m_step;
            }

            reference dereference() const
            {
                return m_first + (m_step * m_step_size);
            }

            friend class ::boost::iterator_core_access;
            value_type m_first;
            value_type m_step;
            difference_type m_step_size;
        };

    } // namespace range_detail

    template<typename Integer>
    iterator_range< range_detail::integer_iterator<Integer> >
        irange(Integer first, Integer last)
    {
        BOOST_ASSERT( first <= last );
        return boost::iterator_range< range_detail::integer_iterator<Integer> >(
                range_detail::integer_iterator<Integer>(first),
                range_detail::integer_iterator<Integer>(last));
    }

    template<typename Integer, typename StepSize>
    iterator_range< range_detail::integer_iterator_with_step<Integer> >
        irange(Integer first, Integer last, StepSize step_size)
    {
        BOOST_ASSERT( step_size != 0 );
        BOOST_ASSERT( (step_size > 0) ? (last >= first) : (last <= first) );
        typedef typename range_detail::integer_iterator_with_step<Integer> iterator_t;

        const std::ptrdiff_t last_step
            = (static_cast<std::ptrdiff_t>(last) - static_cast<std::ptrdiff_t>(first))
            / (static_cast<std::ptrdiff_t>(step_size));

        return boost::iterator_range< iterator_t >(
            iterator_t(first, 0, step_size),
            iterator_t(first, last_step, step_size));
    }

} // namespace boost

#endif // include guard
