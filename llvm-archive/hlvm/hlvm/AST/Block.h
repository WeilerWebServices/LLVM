//===-- AST Function Class --------------------------------------*- C++ -*-===//
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
/// @file hlvm/AST/Block.h
/// @author Reid Spencer <reid@hlvm.org> (original author)
/// @date 2006/05/04
/// @since 0.1.0
/// @brief Declares the class hlvm::AST::Block
//===----------------------------------------------------------------------===//

#ifndef HLVM_AST_BLOCK_H
#define HLVM_AST_BLOCK_H

#include <hlvm/AST/Operator.h>
#include <map>

namespace hlvm 
{

class AutoVarOp;

/// This class represents an block of operators in the HLVM Abstract Syntax 
/// Tree.  A block is simply a sequential list of Operator nodes that are
/// executed in sequence. Block itself is an operator. Its result value is
/// is provided by a ResultOp operator. This approach allows processing to
/// continue after a result for the block has been determined. Blocks can be
/// nested within other blocks and used as the operands of other operators.
/// @see ResultOp
/// @brief AST Block Node
class Block : public MultiOperator
{
  /// @name Constructors
  /// @{
  protected:
    Block() : MultiOperator(BlockID), label(), result(0), autovars() {}
    virtual ~Block();

  /// @}
  /// @name Accessors
  /// @{
  public:
    virtual const Type* getType() const { return (result?result->getType():0); }
    const std::string& getLabel() const { return label; }
    AutoVarOp* getAutoVar(const std::string& name) const; 
    const Operator* getResult() const { return result; }
    Block* getParentBlock() const;
    bool isTerminated() const { 
      if (empty()) return false; 
      return back()->isTerminator();
    }
    static inline bool classof(const Block*) { return true; }
    static inline bool classof(const Node* N) { return N->is(BlockID); }

  /// @}
  /// @name Mutators
  /// @{
  public:
    void setLabel(const std::string& l) { label = l; }

  protected:
    virtual void insertChild(Node* child);
    virtual void removeChild(Node* child);
  /// @}
  /// @name Data
  /// @{
  private:
    typedef std::map<std::string,AutoVarOp*> AutoVarMap;
    std::string label;
    Operator* result;
    AutoVarMap  autovars;
  /// @}
  friend class AST;
};

/// This class provides an Abstract Syntax Tree node that indicates the result
/// of a Block operator. The result operator may be utilized anywhere in the 
/// block. The last such result executed provides the value for the block.
/// @see Block
/// @brief AST Result Operator Node
class ResultOp : public UnaryOperator
{
  /// @name Constructors
  /// @{
  protected:
    ResultOp() : UnaryOperator(ResultOpID)  {}
    virtual ~ResultOp();

  /// @}
  /// @name Accessors
  /// @{
  public:
    Operator* getResult() { return UnaryOperator::op1; }
    static inline bool classof(const ResultOp*) { return true; }
    static inline bool classof(const Node* N) { return N->is(ResultOpID); }

  /// @}
  /// @name Accessors
  /// @{
  public:
    void setResult(Operator* op) { op->setParent(this); }
  /// @}
  friend class AST;
};

} // hlvm 
#endif
