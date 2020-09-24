//===-- AST ContainerType Class ---------------------------------*- C++ -*-===//
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
/// @file hlvm/AST/ContainerType.h
/// @author Reid Spencer <reid@hlvm.org> (original author)
/// @date 2006/05/04
/// @since 0.1.0
/// @brief Declares the class hlvm::AST::ContainerType
//===----------------------------------------------------------------------===//

#ifndef HLVM_AST_CONTAINERTYPE_H
#define HLVM_AST_CONTAINERTYPE_H

#include <hlvm/AST/Type.h>

namespace hlvm 
{

/// This class provides an Abstract Syntax Tree node that represents a uniform
/// container type.  Uniform container types are those types that reference 
/// another type. They may have multiple elements but all elements are of the
/// same type, hence they are uniform.  This is true of types such as 
/// PointerType, ArrayType, and VectorTYpe.
/// @brief AST Abstract Uniform Container Type Node
class UniformContainerType : public Type
{
  /// @name Constructors
  /// @{
  protected:
    UniformContainerType(NodeIDs id) : Type(id), elemType(0) {}
    virtual ~UniformContainerType();

  /// @}
  /// @name Accessors
  /// @{
  public:
    const Type* getElementType() const { return elemType; }
    virtual const char* getPrimitiveName() const; // asserting override
    /// Methods to support type inquiry via isa, cast, dyn_cast
    static inline bool classof(const UniformContainerType*) { return true; }
    static inline bool classof(const Type* T) { 
      return T->isUniformContainerType(); 
    }

  /// @}
  /// @name Mutators
  /// @{
  public:
    virtual void resolveTypeTo(const Type* from, const Type* to);
    void setElementType(const Type* t) { elemType = t; }

  /// @}
  /// @name Data
  /// @{
  protected:
    const Type* elemType; ///< The contained types
  /// @}
};

/// This class provides an Abstract Syntax Tree node that represents a storage 
/// location that is a pointer to another storage location of a specific type.
/// PointerType is a UniformContainerType meaning that the referrent object is
/// of only one type.
/// @brief AST Pointer Type Node
class PointerType : public UniformContainerType
{
  /// @name Constructors
  /// @{
  protected:
    PointerType() : UniformContainerType(PointerTypeID) {}
    virtual ~PointerType();

  /// @}
  /// @name Accessors
  /// @{
  public:
    /// Methods to support type inquiry via is, cast, dyn_cast
    static inline bool classof(const PointerType*) { return true; }
    static inline bool classof(const Node* T) { return T->is(PointerTypeID); }

  /// @}
  friend class AST;
};

/// This class provides an Abstract Syntax Tree note that represents an array of
/// some type.  An array is a sequential layout of multiple elements all of the
/// same type. Arrays in HLVM are dynamically resizeable but the type 
/// specification can indicate a maximum size beyond which the array cannot
/// grow.  Setting the maximum size to 0 indicates that the size of the array
/// is unbounded and it may grow to the limits of available memory. This 
/// usage is discouraged as knowing the maximum memory size can make the 
/// implementation of the array more efficient in its use of memory and limit
/// the amount of reallocation necessary when the array changes size. An
/// ArrayType is a UniformContainerType because it contains a number of elements
/// all of uniform type.
/// @brief AST Array Type Node
class ArrayType : public UniformContainerType
{
  /// @name Constructors
  /// @{
  protected:
    ArrayType() : UniformContainerType(ArrayTypeID), maxSize(0) {}
    virtual ~ArrayType();

  /// @}
  /// @name Accessors
  /// @{
  public:
    /// Get the maximum size the array can grow to.
    uint64_t getMaxSize()  const { return maxSize; }

    /// Methods to support type inquiry via is, cast, dyn_cast
    static inline bool classof(const ArrayType*) { return true; }
    static inline bool classof(const Node* T) { return T->is(ArrayTypeID); }
    
  /// @}
  /// @name Mutators
  /// @{
  public:
    /// Set the maximum size the array can grow to.
    void setMaxSize(uint64_t max) { maxSize = max; }

  /// @}
  /// @name Data
  /// @{
  protected:
    uint64_t maxSize; ///< The maximum number of elements in the array
  /// @}
  friend class AST;
};

/// This class provides an Abstract Syntax Tree Node that represents a fixed 
/// size, packed vector of some other type. Some languages call this an "array"
/// but arrays in HLVM can be dynamically resized. Vectors, however, cannot 
/// be resized.  Where possible, HLVM will attempt to generate code that makes 
/// use of a machines vector instructions to process vector types. Except for
/// the fixed size, VectorType objects are identical in functionality to 
/// ArrayType objects. VectorType is a UniformContainerType because it
/// represents a container of uniformly typed elements.
/// @brief AST Vector Type Node
class VectorType : public UniformContainerType
{
  /// @name Constructors
  /// @{
  protected:
    VectorType() : UniformContainerType(VectorTypeID), size(0) {}
    virtual ~VectorType();

  /// @}
  /// @name Accessors
  /// @{
  public:
    /// Get the maximum size the array can grow to.
    uint64_t getSize()  const { return size; }

    /// Methods to support type inquiry via is, cast, dyn_cast
    static inline bool classof(const VectorType*) { return true; }
    static inline bool classof(const Node* T) { return T->is(VectorTypeID); }

  /// @}
  /// @name Mutators
  /// @{
  public:
    /// Set the size of the vector.
    void setSize(uint64_t max) { size = max; }

  /// @}
  /// @name Data
  /// @{
  protected:
    uint64_t size; ///< The (fixed) size of the vector
  /// @}
  friend class AST;
};

/// This typedef is used to associate a name with a type. Although types have 
/// names, this provides another name such as used in the fields of a structure
/// or the formal parameters of a function.
/// @see Type
/// @see StructureType
/// @see SignatureType
/// @see DisparateContainerType
/// @brief A Named Type
class NamedType : public Documentable
{
  /// @name Constructors
  /// @{
  protected:
    NamedType() : Documentable(NamedTypeID), name(), type(0) {}
    virtual ~NamedType();

  /// @}
  /// @name Accessors
  /// @{
  public:
    /// Get the maximum size the array can grow to.
    const std::string& getName()  const { return name; }
    bool hasName() const { return !name.empty(); }
    const Type* getType() const { return type; }

    /// Methods to support type inquiry via is, cast, dyn_cast
    static inline bool classof(const NamedType*) { return true; }
    static inline bool classof(const Node* T) { return T->is(NamedTypeID); }

  /// @}
  /// @name Mutators
  /// @{
  public:
    /// Set the size of the vector.
    void setName(const std::string& N) { name = N; }
    void setType(const Type* Ty) { type = Ty; }
    void resolveTypeTo(const Type* from, const Type* to);

  /// @}
  /// @name Data
  /// @{
  protected:
    std::string name;
    const Type* type;
  /// @}
  friend class AST;
};

/// This class provides an Abstract Syntax Tree node that represents a Type that
/// contains elements of potentially disparate other types. 
/// @see ContinuationType
/// @see StructureType
/// @see SignatureType
/// @brief AST Abstract Disparate Container Type Node
class DisparateContainerType : public Type
{
  /// @name Types
  /// @{
  public:
    typedef std::vector<NamedType*> ContentsList;
    typedef ContentsList::iterator iterator;
    typedef ContentsList::const_iterator const_iterator;

  /// @}
  /// @name Constructors
  /// @{
  protected:
    DisparateContainerType(NodeIDs id) : Type(id), contents() {}
    virtual ~DisparateContainerType();

  /// @}
  /// @name Accessors
  /// @{
  public:
    virtual const char* getPrimitiveName() const;
    const NamedType* getField(unsigned index) const { return contents[index]; }

    /// Return the index of a named field starting at 1. If the field is not
    /// found, returns 0.
    unsigned getFieldIndex(const std::string& fldname) const;
    const Type* getFieldType(const std::string& fldname) const;
    /// Methods to support type inquiry via is, cast, dyn_cast
    static inline bool classof(const DisparateContainerType*) { return true; }
    static inline bool classof(const Node* N) { 
      return N->isDisparateContainerType(); }

  /// @}
  /// @name Mutators
  /// @{
  public:
    virtual void resolveTypeTo(const Type* from, const Type* to);
    void setTypes(const std::vector<NamedType*>& Types) { contents = Types; }
    void addType(NamedType* NT )
      { contents.push_back(NT); }

  /// @}
  /// @name Iterators
  /// @{
  public:
    iterator         begin()       { return contents.begin(); }
    const_iterator   begin() const { return contents.begin(); }
    iterator         end  ()       { return contents.end(); }
    const_iterator   end  () const { return contents.end(); }
    size_t           size () const { return contents.size(); }
    bool             empty() const { return contents.empty(); }
    NamedType*       front()       { return contents.front(); }
    const NamedType* front() const { return contents.front(); }
    NamedType*       back()        { return contents.back(); }
    const NamedType* back()  const { return contents.back(); }

  /// @}
  /// @name Data
  /// @{
  private:
    ContentsList contents; ///< The contained types
  /// @}
};

/// A convenience typedef so we can call NamedTypes as "Fields"
typedef NamedType Field;

/// This class provides an Abstract Syntax Tree node that represents an 
/// sequence type. A sequence type is a type that lays out its elements in 
/// sequential memory locations. Unlike ArrayType, SequenceType allows its 
/// elements to be of disparate type. Consequently, StructureType is a
/// DisparateContainerType.  
/// @brief AST Structure Type Node
class StructureType : public DisparateContainerType
{
  /// @name Constructors
  /// @{
  protected:
    StructureType(NodeIDs id = StructureTypeID ) : DisparateContainerType(id) {}
    virtual ~StructureType();

  /// @}
  /// @name Accessors
  /// @{
  public:
    /// Methods to support type inquiry via is, cast, dyn_cast
    static inline bool classof(const StructureType*) { return true; }
    static inline bool classof(const Node* T) 
      { return T->is(StructureTypeID); }

  /// @}
  /// @name Mutators
  /// @{
  public:
    void setFields(const std::vector<Field*>& fields) { setTypes(fields); }
    void addField(Field* Fld ) { addType(Fld); }

  /// @}
  /// @name Data
  /// @{
  protected:
  /// @}
  friend class AST;
};

/// This class provides an Abstract Syntax Tree node that represents data held
/// for a continuation.  A ContinutationType is a StructureType because it has
/// the same semantics as a structure. It allows the programmer to store various
/// bits of information that are to be restored at a later time, when the 
/// continuation is called. In addition, HLVM will (transparently) associate
/// the runtime context for the continutation with the programmer's 
/// ContinuationType.  
/// @brief AST Continuation Type Node
class ContinuationType : public StructureType
{
  /// @name Constructors
  /// @{
  protected:
    ContinuationType() : StructureType(ContinuationTypeID) {}
    virtual ~ContinuationType();

  /// @}
  /// @name Accessors
  /// @{
  public:
    /// Methods to support type inquiry via is, cast, dyn_cast
    static inline bool classof(const ContinuationType*) { return true; }
    static inline bool classof(const Node* T) 
      { return T->is(ContinuationTypeID); }
  /// @}

  friend class AST;
};

/// A convenience typedef so we can call NamedTypes as Parameters
typedef NamedType Parameter;

/// This class provides an Abstract Syntax Tree node that represents the call
/// signature of an HLVM function. A SignatureType encapsulates the
/// of varying type. 
/// @see Function
/// @brief AST Signature Type Node
class SignatureType : public DisparateContainerType
{
  /// @name Constructors
  /// @{
  protected:
    SignatureType() 
      : DisparateContainerType(SignatureTypeID), result(0) {}
    virtual ~SignatureType();

  /// @}
  /// @name Accessors
  /// @{
  public:
    const Type* getResultType() const { return result; }
    bool  isVarArgs() const { return flags & IsVarArgsTF; }

    /// Methods to support type inquiry via is, cast, dyn_cast
    static inline bool classof(const SignatureType*) { return true; }
    static inline bool classof(const Node* T) 
      { return T->is(SignatureTypeID); }

  /// @}
  /// @name Mutators
  /// @{
  public:
    void setResultType(const Type* ty) { result = ty; }
    void setIsVarArgs(bool is) { 
      if (is) flags |= IsVarArgsTF; else  flags &= ~IsVarArgsTF; }
    void setParameters(const std::vector<Parameter*>& param) { setTypes(param);}
    void addParameter(Parameter* param) { addType(param); }
    virtual void resolveTypeTo(const Type* from, const Type* to);

  /// @}
  /// @name Data
  /// @{
  protected:
    const Type* result;  ///< The result type of the function signature
  /// @}
  friend class AST;
};

} // hlvm
#endif
