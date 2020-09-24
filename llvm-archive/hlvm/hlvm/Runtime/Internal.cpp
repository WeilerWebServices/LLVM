//===-- Runtime Internal Sharing Implementation -----------------*- C++ -*-===//
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
/// @file hlvm/Runtime/Internal.cpp
/// @author Reid Spencer <rspencer@reidspencer.com> (original author)
/// @date 2006/06/05
/// @since 0.1.0
/// @brief Declares the implementation to the internal runtime facilities
//===----------------------------------------------------------------------===//

#include <hlvm/Runtime/Internal.h>

extern "C" {

#include <hlvm/Runtime/Error.h>

apr_pool_t* _hlvm_pool = 0;
apr_file_t* _hlvm_stderr = 0;

void _hlvm_initialize()
{
  if (APR_SUCCESS != apr_initialize())
    hlvm_panic("Can't initialize apr");
  if (APR_SUCCESS != apr_pool_create(&_hlvm_pool, 0))
    hlvm_panic("Can't create the pool");
  if (APR_SUCCESS != apr_file_open_stderr(&_hlvm_stderr, _hlvm_pool))
    hlvm_panic("Can't open stderr");
}

bool hlvm_apr_error(apr_status_t stat, const char* whilst)
{
  if (APR_SUCCESS != stat) {
    char buffer[1024];
    apr_strerror(stat,buffer,1024);
    hlvm_error(E_APR_ERROR, buffer, whilst);
    return false;
  }
  return true;
}

bool hlvm_assert_fail(const char* expr, const char* file, int line)
{
  hlvm_error(E_ASSERT_FAIL,expr,file,line);
  return false;
}

}
