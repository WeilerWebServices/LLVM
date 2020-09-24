//===-- AST XML Writer Interface --------------------------------*- C++ -*-===//
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
/// @file hlvm/Writer/XMLWriter.h
/// @author Reid Spencer <rspencer@reidspencer.com>
/// @date 2006/05/12
/// @since 0.1.0
/// @brief Provides the interface to hlvm::XMLWriter
//===----------------------------------------------------------------------===//

#ifndef XPS_WRITER_XMLWRITER_H
#define XPS_WRITER_XMLWRITER_H

#include <hlvm/Writer/Writer.h>
#include <ostream>

namespace hlvm {

class XMLWriter: public Writer
{
public:
  /// This method instantiates an XMLReader that is prepared to read from
  /// the path provided.
  /// @brief Create a new XmlReader
  static XMLWriter* create(const char* fname);

  virtual ~XMLWriter() {}
};

}
#endif
