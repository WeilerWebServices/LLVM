//===-- tools/hlvm-xml2xml/hlvm-xml2xml.cpp - Main Program ------*- C++ -*-===//
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
/// @file tools/hlvm-xml2xml/hlvm-xml2xml.cpp
/// @author Reid Spencer <reid@hlvm.org> (original author)
/// @date 2006/05/04
/// @since 0.1.0
/// @brief Implements the main program for the hlvm-xml2xml executable
//===----------------------------------------------------------------------===//

#include <hlvm/Base/Memory.h>
#include <hlvm/Reader/XMLReader.h>
#include <hlvm/Writer/XMLWriter.h>
#include <hlvm/Pass/Pass.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/System/Signals.h>
#include <fstream>
#include <iostream>

using namespace llvm;
using namespace hlvm;
static cl::opt<std::string>
InputFilename(cl::Positional, cl::desc("<input XML>"), cl::init("-"));

static cl::opt<std::string>
OutputFilename("o", cl::desc("Override output filename"),
               cl::value_desc("filename"));

int main(int argc, char**argv) 
{
  try {
    initialize(argc,argv);
    cl::ParseCommandLineOptions(argc, argv, 
      "hlvm-xml2xml XML->AST->XML translator\n");

    std::ostream *Out = &std::cout;  // Default to printing to stdout.

    if (OutputFilename != "") {   // Specified an output filename?
      if (OutputFilename != "-") { // Not stdout?
        Out = new std::ofstream(OutputFilename.c_str());
        sys::RemoveFileOnSignal(sys::Path(OutputFilename));
      }
    } else {
      if (InputFilename == "-") {
        OutputFilename = "-";
      } else {
        std::string IFN = InputFilename;
        OutputFilename = InputFilename + ".out";

        Out = new std::ofstream(OutputFilename.c_str());
        sys::RemoveFileOnSignal(sys::Path(OutputFilename));
      }
    }

    if (!Out->good()) {
      std::cerr << argv[0] << ": error opening " << OutputFilename
                << ": sending to stdout instead!\n";
      Out = &std::cout;
    }

    if (InputFilename == "-" ) {
      std::cerr << "Not supported yet: input from stdin\n";
      return 2;
    } else {
      llvm::sys::Path path(InputFilename);
      if (!path.canRead()) {
        std::cerr << argv[0] << ": can't read input file: " << InputFilename
                  << "\n";
        return 2;
      }
    }

    XMLReader* rdr = XMLReader::create(InputFilename);
    XMLWriter* wrtr = XMLWriter::create(OutputFilename.c_str());
    if (!rdr->read())
      return 3;
    AST* node = rdr->get();
    if (!node)
      return 4;
    if (!validate(node))
      return 5;
    wrtr->write(node);
    delete rdr;
    delete wrtr;

    if (Out != &std::cout) {
      static_cast<std::ofstream*>(Out)->close();
      delete Out;
    }
    return 0;
  } catch (const std::string& msg) {
    std::cerr << argv[0] << ": " << msg << "\n";
  } catch (...) {
    std::cerr << argv[0] << ": Unexpected unknown exception occurred.\n";
  }
  return 1;
}
