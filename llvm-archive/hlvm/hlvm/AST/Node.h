//===-- Abstract Node Class Interface ---------------------------*- C++ -*-===//
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
/// @file hlvm/AST/Node.h
/// @author Reid Spencer <rspencer@reidspencer.com> (original author)
/// @date 2006/05/04
/// @since 0.1.0
/// @brief Declares the class hlvm::AST::Node and basic subclasses
//===----------------------------------------------------------------------===//

#ifndef HLVM_AST_NODE_H
#define HLVM_AST_NODE_H

#include <llvm/Support/Casting.h>
#include <hlvm/AST/Locator.h>
#include <vector>

namespace hlvm
{

class Type;
class AST;
class Bundle;

/// This enumeration is used to identify the various kinds of Abstract Syntax
/// Tre nodes. Its organization is very specific and dependent on the class 
/// hierarchy. In order to use these values as ranges for class identification 
/// (classof methods), we need to group things by inheritance rather than by 
/// function. Items beginning with "First" or "Last" identify a useful range
/// of node types and do not introduce any value of their own.
/// @brief Identifiers of th AST Node Types.
enum NodeIDs 
{
  NoNodeID = 0,            ///< Use this for an invalid node ID.

  // SUBCLASSES OF NODE
  TreeTopID,               ///< The AST node which is always root of the tree
FirstNodeID = TreeTopID,
  DocumentationID,         ///< XHTML Documentation Node
  NamedTypeID,             ///< An association of a name with a type
FirstDocumentableID = NamedTypeID,
  BundleID,                ///< The Bundle Node (a group of other declarations)
  ImportID,                ///< A bundle's Import declaration

  // SUBCLASSES OF TYPE
  // Basic Types 
  AnyTypeID,               ///< The Any Type (Union of any type)
FirstTypeID          = AnyTypeID,
  BooleanTypeID,           ///< The Boolean Type (A simple on/off boolean value)
  CharacterTypeID,         ///< The Character Type (UTF-8 encoded character)
  EnumerationTypeID,       ///< The Enumeration Type (set of enumerated ids)
  IntegerTypeID,           ///< The Integer Type (A # of bits of integer data)
  OpaqueTypeID,            ///< A placeholder for unresolved types
  RangeTypeID,             ///< The Range Type (A Range of Integer Values)
  RealTypeID,              ///< The Real Number Type (Any Real Number)
  RationalTypeID,          ///< The Rational Number Type (p/q type number)
  StringTypeID,            ///< A string of characters type

  // Uniform Container Types
  PointerTypeID,           ///< The Pointer Type (Pointer To object of Type)
FirstContainerTypeID = PointerTypeID,
FirstUniformContainerTypeID = PointerTypeID,
  ArrayTypeID,             ///< The Array Type (Linear array of some type)
  VectorTypeID,            ///< The Vector Type (Packed Fixed Size Vector)
LastUniformContainerTypeID = VectorTypeID,

  // Disparate Container Types
  StructureTypeID,         ///< The Structure Type (Sequence of various types)
FirstDisparateContainerTypeID = StructureTypeID,
  SignatureTypeID,         ///< The Function Signature Type
  ContinuationTypeID,      ///< A Continuation Type (data to continuations)
LastDisparateContainerTypeID  = ContinuationTypeID,
LastContainerTypeID = ContinuationTypeID,

  // Runtime Types
  BufferTypeID,            ///< A buffer of octets for I/O
FirstRuntimeTypeID = BufferTypeID,
  StreamTypeID,            ///< A stream handle
  TextTypeID,              ///< A UTF-8 or UTF-16 encoded text string
LastRuntimeTypeID = TextTypeID,
LastTypeID = TextTypeID,

  // Class Constructs (TBD)
  InterfaceID,             ///< The Interface Type (set of Signatures)
  ClassID,                 ///< The Class Type (OO Class Definition)
  MethodID,                ///< The Method Node (define a method)
  ImplementsID,            ///< Specifies set of Interfaces implemented by class

  // SUBCLASSES OF VALUE
  ArgumentID,              ///< An argument to a function
FirstValueID = ArgumentID,

  // Constants
  ConstantAnyID,           ///< A constant any value
FirstConstantID = ConstantAnyID,
FirstConstantValueID = ConstantAnyID,
  ConstantBooleanID,       ///< A constant boolean value
  ConstantCharacterID,     ///< A constant UTF-8 character value
  ConstantEnumeratorID,    ///< A constant enumeration value
  ConstantIntegerID,       ///< A constant integer value
  ConstantRealID,          ///< A constant real value
  ConstantStringID,        ///< A constant string value
  ConstantPointerID,       ///< A constant pointer value
  ConstantArrayID,         ///< A constant array value
FirstConstantAggregateID = ConstantArrayID,
  ConstantVectorID,        ///< A constant vector value
  ConstantStructureID,     ///< A constant structure value
  ConstantContinuationID,  ///< A constant continuation value
LastConstantAggregateID = ConstantContinuationID,
  ConstantExpressionID,    ///< A constant expression
LastConstantValueID = ConstantExpressionID,

  // Linkage Items
  VariableID,              ///< The Variable Node (a storage location)
FirstLinkableID = VariableID,
  FunctionID,              ///< The Function Node (a callable function)
  ProgramID,               ///< The Program Node (a program starting point)
LastLinkableID = ProgramID,
LastConstantID = ProgramID,

  // Operator
  BlockID,                 ///< A Block Of Operators
FirstOperatorID = BlockID,

  // Nilary Operators (those taking no operands)
  BreakOpID,               ///< Break out of the enclosing block
FirstNilaryOperatorID = BreakOpID,
  ContinueOpID,            ///< Continue from start of enclosing loop
  ReturnOpID,              ///< Return to the function's caller
  GetOpID,                 ///< Obtain value of Variable/Function/Constant
LastNilaryOperatorID = GetOpID,

  // Control Flow Unary Operators
  ResultOpID,              ///< Specify the result of a block or function
FirstUnaryOperatorID = ResultOpID,
  ThrowOpID,               ///< Throw an exception out of the function

  // Integer Arithmetic Unary Operators
  NotOpID,                 ///< Not Unary Boolean Operator
  NegateOpID,              ///< Negation Unary Integer Operator
  ComplementOpID,          ///< Bitwise Complement Unary Integer Operator
  PreIncrOpID,             ///< Pre-Increment Unary Integer Operator
  PostIncrOpID,            ///< Post-Increment Unary Integer Operator
  PreDecrOpID,             ///< Pre-Decrement Unary Integer Operator
  PostDecrOpID,            ///< Post-Decrement Unary Integer Operator
  SizeOfOpID,              ///< Size of a constant
  ConvertOpID,             ///< Convert one type to another

  // Real Arithmetic Unary Operators
  IsPInfOpID,              ///< Real Number Positive Infinity Test Operator
  IsNInfOpID,              ///< Real Number Negative Infinity Test Operator
  IsNanOpID,               ///< Real Number Not-A-Number Test Operator
  TruncOpID,               ///< Real Number Truncation Operator
  RoundOpID,               ///< Real Number Rounding Operator
  FloorOpID,               ///< Real Number Floor Operator
  CeilingOpID,             ///< Real Number Ceiling Operator
  LogEOpID,                ///< Real Number Base e (Euler's Number) logarithm 
  Log2OpID,                ///< Real Number Base 2 logarithm Operator
  Log10OpID,               ///< Real Number Base 10 logarithm Operator
  SquareRootOpID,          ///< Real Number Square Root Operator
  CubeRootOpID,            ///< Real Number Cube Root Operator
  FactorialOpID,           ///< Real Number Factorial Operator

  // Memory Unary Operators
  LoadOpID,                ///< The Load Operator (load a value from a location)
  AllocateOpID,            ///< The Allocate Memory Operator 
  DeallocateOpID,          ///< The Deallocate Memory Operator
  AutoVarOpID,             ///< Declaration of an automatic (stack) variable

  // Input/Output Unary Operators
  TellOpID,                ///< Tell the position of a stream
  CloseOpID,               ///< Close a stream previously opened.

  // Other Unary Operators
  LengthOpID,              ///< Extract Length of a Text/Array/Vector
LastUnaryOperatorID = LengthOpID,

  // Arithmetic Binary Operators
  AddOpID,                 ///< Addition Binary Operator
FirstBinaryOperatorID = AddOpID,
  SubtractOpID,            ///< Subtraction Binary Operator
  MultiplyOpID,            ///< Multiplcation Binary Operator
  DivideOpID,              ///< Division Binary Operator
  ModuloOpID,              ///< Modulus Binary Operator
  BAndOpID,                ///< Bitwise And Binary Operator
  BOrOpID,                 ///< Bitwise Or Binary Operator
  BXorOpID,                ///< Bitwise XOr Binary Operator
  BNorOpID,                ///< Bitwise Nor Binary Operator

  // Boolean Binary Operators
  AndOpID,                 ///< And Binary Boolean Operator
  OrOpID,                  ///< Or Binary Boolean Operator
  NorOpID,                 ///< Nor Binary Boolean Operator
  XorOpID,                 ///< Xor Binary Boolean Operator
  LessThanOpID,            ///< <  Binary Comparison Operator
  GreaterThanOpID,         ///< >  Binary Comparison Operator
  LessEqualOpID,           ///< <= Binary Comparison Operator
  GreaterEqualOpID,        ///< >= Binary Comparison Operator
  EqualityOpID,            ///< == Binary Comparison Operator
  InequalityOpID,          ///< != Binary Comparison Operator

  // Real Arithmetic Binary Operators
  PowerOpID,               ///< Real Number Power Operator
  RootOpID,                ///< Real Number Arbitrary Root Operator
  GCDOpID,                 ///< Real Number Greatest Common Divisor Operator
  LCMOpID,                 ///< Real Number Least Common Multiplicator Operator
  
  // Memory Binary Operators
  ReallocateOpID,          ///< The Reallocate Memory Operator 
  StoreOpID,               ///< The Store Operator (store a value to a location)
  GetIndexOpID,            ///< The GetIndex Operator for indexing an array
  GetFieldOpID,            ///< The GetField Operator for indexing an structure

  // Binary Control Flow Operators
  WhileOpID,               ///< While expression is true loop
  UnlessOpID,              ///< Unless expression is true loop
  UntilOpID,               ///< Do block until expression is true loop

  // Other Binary Operators
  OpenOpID,                ///< Open a stream from a URL
  ReadOpID,                ///< Read from a stream
  WriteOpID,               ///< Write to a stream
  CreateContOpID,          ///< The Create Continutation Operator
LastBinaryOperatorID = CreateContOpID,

  // Ternary Operators
  SelectOpID,                  ///< The select an alternate operator
FirstTernaryOperatorID = SelectOpID,
  StrInsertOpID,           ///< Insert(str1,where,str2)
  StrEraseOpID,            ///< Erase(str,at,len)
  StrReplaceOpID,          ///< Replace(str,at,len,what)
  StrConcatOpID,           ///< str3 = Concat(str1,str2)
  PositionOpID,            ///< Position a stream (stream,where,relative-to)
  LoopOpID,                ///< The General Purpose Loop Operator
LastTernaryOperatorID = LoopOpID,

  // Multi Operators
  CallOpID,                ///< The Call Operator (n operands)
FirstMultiOperatorID = CallOpID,
  InvokeOpID,              ///< The Invoke Operator (n operands)
  DispatchOpID,            ///< The Object Method Dispatch Operator (n operands)
  CallWithContOpID,        ///< The Call with Continuation Operator (n operands)
  SwitchOpID,              ///< The Switch Operator (n operands)
LastMultiOperatorID = SwitchOpID,
LastOperatorID = SwitchOpID,
LastValueID = SwitchOpID,
LastDocumentableID = SwitchOpID,
LastNodeID = SwitchOpID,

  NumNodeIDs               ///< The number of node identifiers in the enum
};

/// This class is the abstract base class of all the Abstract Syntax Tree (AST)
/// node types. All other AST nodes are subclasses of this class. This class
/// must only provide functionality that is common to all AST Node subclasses.
/// It provides for class identification, insertion of nodes, management of a
/// set of flags, 
/// @brief Abstract Base Class of All HLVM AST Nodes
class Node
{
  /// @name Constructors
  /// @{
  protected:
    Node(NodeIDs ID) : id(ID), flags(0), parent(0), loc(0) {}
  public:
    virtual ~Node();

  /// @}
  /// @name Accessors
  /// @{
  public:
    /// Get the AST root node that this Node is part of.
    AST* getRoot(); 

    /// Return the bundle that contains this Node.
    Bundle* getContainingBundle() const;

    /// Get the type of node
    NodeIDs getID() const { return NodeIDs(id); }

    /// Get the parent node
    Node* getParent() const { return parent; }

    /// Get the flags
    unsigned getFlags() const { return flags; }

    /// Get the Locator
    const Locator* getLocator() const { return loc; }

    /// Determine if the node is a specific kind
    bool is(NodeIDs kind) const { return id == unsigned(kind); }

    /// Determine if the node is a Type
    bool isType() const {
      return id >= FirstTypeID && 
             id <= LastTypeID; }

    bool isIntegralType()  const { 
      return (id == IntegerTypeID) || (id == RangeTypeID) || 
        (id == EnumerationTypeID) || (id == BooleanTypeID) ||
        (id == CharacterTypeID); }

    bool isNumericType() const {
      return isIntegralType() || id == RealTypeID; }

    /// Determine if the node is a uniform container type
    bool isUniformContainerType() const {
      return id >= FirstUniformContainerTypeID && 
             id <= LastUniformContainerTypeID;
    }

    /// Determine if the node is a disparate container type
    bool isDisparateContainerType() const {
      return id >= FirstDisparateContainerTypeID && 
             id <= LastDisparateContainerTypeID; }

    /// Determine if the node is a runtime type
    bool isRuntimeType() const {
      return id >= FirstRuntimeTypeID &&
             id <= LastRuntimeTypeID; }

    /// Determine if the node is a container type
    bool isContainerType() const {
      return id >= FirstContainerTypeID && id <= LastContainerTypeID;
    }
    /// Determine if the node is one of the Constant values.
    bool isConstant() const {
      return id >= FirstConstantID && id <= LastConstantID; }

    /// Determine if the node is one of the Constant values.
    bool isConstantValue() const {
      return id >= FirstConstantValueID && id <= LastConstantValueID; }

    /// Determine if the node is one of the ConstantAggregate values.
    bool isConstantAggregate() const {
      return id >= FirstConstantAggregateID && id <= LastConstantAggregateID; }

    /// Determine if the node is a Linkable
    bool isLinkable() const {
      return id >= FirstLinkableID && id <= LastLinkableID; }

    /// Determine if the node is any of the Operators
    bool isOperator() const { 
      return id >= FirstOperatorID && id <= LastOperatorID; }

    bool isTerminator() const {
      return (id >= BreakOpID && id <= ReturnOpID) || (id == ThrowOpID); }

    bool isLoop() const {
      return id == LoopOpID || (id >= WhileOpID && id <= UntilOpID); }

    bool isNilaryOperator() const {
      return id >= FirstNilaryOperatorID && id <= LastNilaryOperatorID; }

    bool isUnaryOperator() const {
      return id >= FirstUnaryOperatorID && id <= LastUnaryOperatorID; }

    bool isBinaryOperator() const {
      return id >= FirstBinaryOperatorID && id <= LastBinaryOperatorID; }

    bool isTernaryOperator() const {
      return id >= FirstTernaryOperatorID && id <= LastTernaryOperatorID; }

    bool isMultiOperator() const {
      return id >= FirstMultiOperatorID && id <= LastMultiOperatorID; }

    /// Determine if the node is a Documentable Node
    bool isDocumentable() const { 
      return id >= FirstDocumentableID && id <= LastDocumentableID; }

    /// Determine if the node is a Value
    bool isValue() const { 
      return id >= FirstValueID && id <= LastValueID; }

    bool isFunction() const 
      { return id == FunctionID || id == ProgramID; }

    /// Provide support for isa<X> and friends
    static inline bool classof(const Node*) { return true; }

  /// @}
  /// @name Mutators
  /// @{
  public:
    void setLocator(const Locator* l) { loc = l; }
    void setFlags(uint16_t f) { flags = f; }
    virtual void setParent(Node* parent);

  protected:
    virtual void insertChild(Node* child);
    virtual void removeChild(Node* child);

  /// @}
  /// @name Data
  /// @{
  protected:
    uint16_t id;         ///< Really a value in NodeIDs
    uint16_t flags;      ///< 16 flags, subclass dependent interpretation
    Node* parent;        ///< The node that owns this node.
    const Locator* loc;  ///< The source location corresponding to node.
  /// @}
  friend class AST;
};

/// This class provides an Abstract Syntax Tree node that represents program
/// documentation. Documentation nodes may be attached to any Documentable which
/// is an abstract base class of nearly every type of AST node. This construct
/// permits documentation (not just comments) to be included directly into the
/// nodes of the Abstract Syntax Tree as first class objects, not just addenda.
/// Each Documentation node simply contains a block of text that provides the
/// documentation for the Documentable to which the Documentation is attached.
/// The intended use is that the text contain XHTML markup. In this way, an 
/// automated documentation facility can translate the AST into XHTML 
/// documentation with great accuracy in associating documentation with the
/// nodes of the AST. Since the documentation node can be associated with 
/// nearly any kind of node, this affords a complete system for documenting 
/// HLVM programs with XHTML markup. There is, however, no firm requirement 
/// that XHTML be used for the documentation. Any kind of documentation that is
/// expressible in UTF-8 notation can be accommodated including other markup
/// languages or simple ASCII text.
/// @see Documentable
/// @brief AST Documentation Node
class Documentation : public Node
{
  /// @name Constructors
  /// @{
  protected:
    Documentation() : Node(DocumentationID) {}
    virtual ~Documentation();

  /// @}
  /// @name Accessors
  /// @{
  public:
    const std::string& getDoc() const { return doc; }
    static inline bool classof(const Documentation*) { return true; }
    static inline bool classof(const Node* N) 
    { return N->is(DocumentationID); }

  /// @}
  /// @name Mutators
  /// @{
  public:
    void setDoc(const std::string& d) { doc = d; }
    void addDoc(const std::string& d) { doc += d; }

  /// @}
  /// @name Data
  /// @{
  protected:
    std::string doc;
  /// @}
  friend class AST;
};

/// This class is an abstract base class in the Abstract Syntax Tree for any 
/// node type that can be documented. That is, it provides a facility for
/// attaching a Documentation node. This is the base class of most definitions
/// in the AST. 
/// @see Documentation
/// @brief AST Documentable Node
class Documentable : public Node
{
  /// @name Constructors
  /// @{
  protected:
    Documentable(NodeIDs id) : Node(id), doc(0) {}
  public:
    virtual ~Documentable();

  /// @}
  /// @name Accessors
  /// @{
  public:
    /// Get the name of the node
    inline Documentation* getDoc() const { 
      return const_cast<Documentation*>(doc); }

    static inline bool classof(const Documentable*) { return true; }
    static inline bool classof(const Node* N) { return N->isDocumentable(); }

  /// @}
  /// @name Mutators
  /// @{
  public:
    void setDoc(Documentation* d) { doc = d; }

  /// @}
  /// @name Data
  /// @{
  protected:
    Documentation* doc;///< All named nodes can have documentation
  /// @}
  friend class AST;
};

/// This class is an abstract base class in the Abstract Syntax Tree for things
/// that have a value at runtime. Every Value has a Type. All Operators, and
/// Linkables are Values.
/// @see Type
/// @see Linkable
/// @see Operator
/// @brief AST Value Node
class Value : public Documentable
{
  /// @name Constructors
  /// @{
  protected:
    Value(NodeIDs id) : Documentable(id), type(0)  {}
  public:
    virtual ~Value();

  /// @}
  /// @name Accessors
  /// @{
  public:
    // Get the type of the value
    virtual const Type* getType() const { return type; }
    template<class C>
    bool typeis() const { return llvm::isa<C>(type); }
    const Type* getConcreteType() const;

    static inline bool classof(const Value*) { return true; }
    static inline bool classof(const Node* N) { return N->isValue(); }

  /// @}
  /// @name Mutators
  /// @{
  public:
    void setType(const Type* t) { type = t; }
    virtual void resolveTypeTo(const Type* from, const Type* to);

  /// @}
  /// @name Data
  /// @{
  protected:
    const Type* type; ///< The type of this value.
  /// @}
  friend class AST;
};

} // end hlvm namespace
#endif
