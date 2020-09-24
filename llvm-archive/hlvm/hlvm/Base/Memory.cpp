//===-- HLVM Memory Facilities ----------------------------------*- C++ -*-===//
//
//                      High Level Virtual Machine (HLVM)
//
// Copyright (C) 2006 Reid Spencer. All Rights Reserved.
//
// This software is free software; you can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License as published by 
// the Free Software Foundation; either version 2.1 of the License, or (at 
// your option) any later version.
//
// This software is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for 
// more details.
//
// You should have received a copy of the GNU Lesser General Public License 
// along with this library in the file named LICENSE.txt; if not, write to the 
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, 
// MA 02110-1301 USA
//
//===----------------------------------------------------------------------===//
/// @file hlvm/Base/Memory.cpp
/// @author Reid Spencer <rspencer@reidspencer.com> (original author)
/// @date 2006/05/04
/// @since 0.1
/// @brief Declares the HLVM Memory Facilities
//===----------------------------------------------------------------------===//

#include <hlvm/Base/Memory.h>
#include <hlvm/Base/Assert.h>
#include <hlvm/Base/Configuration.h>
#include <apr-1/apr_general.h>
#include <memory>
#include <new>
#include <iostream>

namespace hlvm {

// The following provides a 64KByte emergency memory reserve for the program 
// heap.  Application writers are encouraged to use the memory facilities 
// provided in this module but XPS itself can utilize the heap with  
// malloc/free and new/delete.  This memory reserve helps to avoid situations 
// where new/delete might fail.

static char * _memory_reserve = 0;

static void
the_new_handler( void )
{
  if ( _memory_reserve )
  {
    delete [] _memory_reserve;
    _memory_reserve = 0;
  }
  else
  {
    panic("No memory");
  }
}

static void
the_unexpected_handler( void )
{
  hlvmNotImplemented("Unexpected Handler");
}

static void
the_terminate_handler( void )
{
  hlvmNotImplemented("Terminate Handler");
}

static void
ensure_emergency_reserve( void )
{
  if ( _memory_reserve == 0 )
  {
    _memory_reserve = ::new char [ 64 * 1024 ];
  }
}

bool
memory_is_low( void )
{
  return _memory_reserve == 0;
}

static bool initialized = false;

void
initialize(int& /*argc*/, char** /*argv*/)
{
  if ( ! initialized )
  {
    try
    {
      // Reserve memory for emergencies
      ensure_emergency_reserve();

      // Specify the new_handler for C++ memory allocation
      std::set_new_handler( the_new_handler );

      // Specify the unexpected handler for unexpected C++ exceptions
      std::set_unexpected( the_unexpected_handler );

      // Specify the terminate handler for abnormal terminations
      std::set_terminate( the_terminate_handler );

      // Initialize APR
      if (APR_SUCCESS != apr_initialize())
        hlvmAssert(!"Can't initialize APR");

    }
    catch ( ... )
    {
      hlvmAssert(!"Unexpected exception during initialization.");
    }

    if (0 != atexit(terminate))
      hlvmAssert(!"Can't register termination at exit");

    // We've made it through initialization .. indicate that.
    initialized = true;
  }
}

void
terminate( void )
{
  if (initialized)
  {
    // Terminate APR
    apr_terminate();

    // Release the memory reserve
    ::delete [] _memory_reserve;

    // Done.
    initialized = false;
  }
}

void
panic(const char* msg)
{
  std::cerr << "HLVM PANIC: " << msg << "\n";
  exit(99);
}

void print_version()
{
  std::cout << "HLVM " << HLVM_Version << " (see http://hlvm.org)\n";
}

} // end hlvm namespace
