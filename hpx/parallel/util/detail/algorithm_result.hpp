//  Copyright (c) 2007-2014 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_PARALLEL_DETAIL_ALGORITHM_RESULT_MAY_28_2014_1020PM)
#define HPX_PARALLEL_DETAIL_ALGORITHM_RESULT_MAY_28_2014_1020PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/lcos/future.hpp>
#include <hpx/parallel/execution_policy.hpp>
#include <hpx/util/unused.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>

namespace hpx { namespace parallel { namespace util { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename ExPolicy, typename T>
    struct algorithm_result_impl
    {
        // The return type of the initiating function.
        typedef T type;

        // Obtain initiating function's return type.
        static type get(T && t)
        {
            return t;
        }

        static type get(hpx::future<T> && t)
        {
            return t.get();
        }
    };

    template <typename ExPolicy>
    struct algorithm_result_impl<ExPolicy, void>
    {
        // The return type of the initiating function.
        typedef void type;

        // Obtain initiating function's return type.
        static void get() {}

        static void get(hpx::util::unused_type) {}

        static type get(hpx::future<void> && t)
        {
            t.get();
        }

        template <typename T>
        static type get(hpx::future<T> && t)
        {
            t.get();
        }
    };

    template <typename T>
    struct algorithm_result_impl<sequential_task_execution_policy, T>
    {
        // The return type of the initiating function.
        typedef hpx::future<T> type;

        // Obtain initiating function's return type.
        static type get(T && t)
        {
            return hpx::make_ready_future(std::move(t));
        }

        static type get(hpx::future<T> && t)
        {
            return std::move(t);
        }
    };

    template <typename T>
    struct algorithm_result_impl<parallel_task_execution_policy, T>
    {
        // The return type of the initiating function.
        typedef hpx::future<T> type;

        // Obtain initiating function's return type.
        static type get(T && t)
        {
            return hpx::make_ready_future(std::move(t));
        }

        static type get(hpx::future<T> && t)
        {
            return std::move(t);
        }
    };

    template <>
    struct algorithm_result_impl<sequential_task_execution_policy, void>
    {
        // The return type of the initiating function.
        typedef hpx::future<void> type;

        // Obtain initiating function's return type.
        static type get()
        {
            return hpx::make_ready_future();
        }

        static type get(hpx::util::unused_type)
        {
            return hpx::make_ready_future();
        }

        static type get(hpx::future<void> && t)
        {
            return std::move(t);
        }

        template <typename T>
        static type get(hpx::future<T> && t)
        {
            return hpx::future<void>(std::move(t));
        }
    };

    template <>
    struct algorithm_result_impl<parallel_task_execution_policy, void>
    {
        // The return type of the initiating function.
        typedef hpx::future<void> type;

        // Obtain initiating function's return type.
        static type get()
        {
            return hpx::make_ready_future();
        }

        static type get(hpx::util::unused_type)
        {
            return hpx::make_ready_future();
        }

        static type get(hpx::future<void> && t)
        {
            return std::move(t);
        }

        template <typename T>
        static type get(hpx::future<T> && t)
        {
            return hpx::future<void>(std::move(t));
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Executor, typename Parameters, typename T>
    struct algorithm_result_impl<
            sequential_task_execution_policy_shim<Executor, Parameters>, T>
      : algorithm_result_impl<sequential_task_execution_policy, T>
    {};

    template <typename Executor, typename Parameters>
    struct algorithm_result_impl<
            sequential_task_execution_policy_shim<Executor, Parameters>, void>
      : algorithm_result_impl<sequential_task_execution_policy, void>
    {};

    template <typename Executor, typename Parameters, typename T>
    struct algorithm_result_impl<
            parallel_task_execution_policy_shim<Executor, Parameters>, T>
      : algorithm_result_impl<parallel_task_execution_policy, T>
    {};

    template <typename Executor, typename Parameters>
    struct algorithm_result_impl<
            parallel_task_execution_policy_shim<Executor, Parameters>, void>
      : algorithm_result_impl<parallel_task_execution_policy, void>
    {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename ExPolicy, typename T = void>
    struct algorithm_result
      : algorithm_result_impl<typename hpx::util::decay<ExPolicy>::type, T>
    {
        BOOST_STATIC_ASSERT_MSG(!boost::is_lvalue_reference<T>::value,
            "T shouldn't be a lvalue reference");
    };
}}}}

#endif
