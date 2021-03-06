//  Copyright (c) 2007-2015 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file hpx/runtime/get_os_thread_count.hpp

#if !defined(HPX_RUNTIME_GET_OS_THREAD_COUNT_AUG_15_2015_1119AM)
#define HPX_RUNTIME_GET_OS_THREAD_COUNT_AUG_15_2015_1119AM

#include <hpx/config.hpp>
#include <hpx/runtime/threads/thread_data_fwd.hpp>

#include <cstdlib>

namespace hpx
{
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Return the number of OS-threads running in the runtime instance
    ///        the current HPX-thread is associated with.
    HPX_API_EXPORT std::size_t get_os_thread_count();

    /// \brief Return the number of worker OS- threads used by the given
    ///        executor to execute HPX threads
    ///
    /// This function returns the number of cores used to execute HPX
    /// threads for the given executor. If the function is called while no HPX
    /// runtime system is active, it will return zero. If the executor is not
    /// valid, this function will fall back to retrieving the number of OS
    /// threads used by HPX.
    ///
    /// \param id [in] The id of the object to locate.
    HPX_API_EXPORT std::size_t get_os_thread_count(threads::executor const& exec);
}

#endif
