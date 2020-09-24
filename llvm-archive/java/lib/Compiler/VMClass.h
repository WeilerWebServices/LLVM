//===-- VMClass.h - Compiler representation of a Java class -----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file was developed by the LLVM research group and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the VMClass class that represents a
// compile time representation of a Java class (java.lang.Class).
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_JAVA_VMCLASS_H
#define LLVM_JAVA_VMCLASS_H

#include "VMField.h"
#include "VMMethod.h"
#include <llvm/Constant.h>
#include <llvm/Module.h>
#include <llvm/Type.h>
#include <llvm/Java/ClassFile.h>
#include <map>
#include <string>
#include <vector>

namespace llvm { namespace Java {

  class Resolver;

  class VMClass {
    static const int INVALID_INTERFACE_INDEX = -1;

    const std::string name_;
    const std::string descriptor_;
    Resolver* resolver_;
    const ClassFile* classFile_;
    const VMClass* componentClass_;
    Type* layoutType_;
    const Type* type_;
    int interfaceIndex_;
    typedef std::map<std::string, VMField> FieldMap;
    FieldMap fieldMap_;
    typedef std::map<std::string, VMMethod> MethodMap;
    MethodMap methodMap_;
    mutable std::vector<void*> resolvedConstantPool_;
    std::vector<const VMClass*> superClasses_;
    std::vector<const VMClass*> interfaces_;
    std::vector<const VMField*> memberFields_;
    std::vector<const VMField*> staticFields_;
    std::vector<const VMMethod*> dynamicMethods_;
    std::vector<const VMMethod*> staticMethods_;
    GlobalVariable* classRecord_;

    void init();

    void computeLayout();
    void computeClassRecord();

    llvm::Constant* buildClassName() const;
    llvm::Constant* buildSuperClassRecords() const;
    llvm::Constant* buildInterfaceClassRecord(const VMClass* interface) const;
    llvm::Constant* buildInterfaceClassRecords() const;
    llvm::Constant* buildFieldDescriptors() const;
    llvm::Constant* buildFieldOffsets() const;
    llvm::Constant* buildStaticFieldDescriptors() const;
    llvm::Constant* buildStaticFieldPointers() const;
    llvm::Constant* buildMethodDescriptors() const;
    llvm::Constant* buildMethodPointers() const;
    llvm::Constant* buildStaticMethodDescriptors() const;
    llvm::Constant* buildStaticMethodPointers() const;
    llvm::Constant* buildClassTypeInfo() const;

    const VMField* lookupField(const std::string& name) const;
    const VMMethod* lookupMethod(const std::string& nameAndType) const;
    
    friend class Resolver;

    // Resolver interface.

    // Load primitive class for type.
    VMClass(Resolver* resolver, const Type* type);

    // Load class by name.
    VMClass(Resolver* resolver, const std::string& className);

    // Load array class of component the passed class.
    VMClass(Resolver* resolver, const VMClass* componentClass);

    // Link the class.
    void link();
    // Resolve the class.
    void resolve();
    // Initialize the class.
    void initialize();

  public:
    const std::string& getName() const { return name_; }
    const std::string& getDescriptor() const { return descriptor_; }
    Resolver* getResolver() const { return resolver_; }
    const Type* getLayoutType() const { return layoutType_; }
    const Type* getType() const { return type_; }
    const ClassFile* getClassFile() const { return classFile_; }
    unsigned getNumSuperClasses() const { return superClasses_.size(); }
    const VMClass* getSuperClass(unsigned i) const { return superClasses_[i]; }
    const VMClass* getSuperClass() const {
      return getNumSuperClasses() ? getSuperClass(0) : NULL;
    }
    unsigned getNumInterfaces() const { return interfaces_.size(); }
    const VMClass* getInterface(unsigned i) const { return interfaces_[i]; }
    const VMClass* getComponentClass() const { return componentClass_; }
    bool isArray() const { return getComponentClass(); }
    bool isPrimitive() const { return getType() == getLayoutType(); }
    bool isInterface() const { return classFile_ && classFile_->isInterface(); }
    int getInterfaceIndex() const { return interfaceIndex_; }
    unsigned getNumDynamicMethods() const {
      return dynamicMethods_.size();
    }
    const VMMethod* getDynamicMethod(unsigned i) const {
      return dynamicMethods_[i];
    }
    unsigned getNumStaticMethods() const {
      return staticMethods_.size();
    }
    const VMMethod* getStaticMethod(unsigned i) const {
      return staticMethods_[i];
    }
    llvm::Constant* getClassRecord() const { return classRecord_; }

    llvm::Constant* getConstant(unsigned index) const;
    const VMClass* getClass(unsigned index) const;
    const VMField* getField(unsigned index) const;
    const VMField* getField(const std::string& name) const {
      FieldMap::const_iterator it = fieldMap_.find(name);
      return it == fieldMap_.end() ? NULL : &it->second;
    }
    const VMMethod* getMethod(unsigned index) const;
    const VMMethod* getMethod(const std::string& nameAndType) const {
      MethodMap::const_iterator it = methodMap_.find(nameAndType);
      return it == methodMap_.end() ? NULL : &it->second;
    }
  };

} } // namespace llvm::Java

#endif//LLVM_JAVA_VMCLASS_H
