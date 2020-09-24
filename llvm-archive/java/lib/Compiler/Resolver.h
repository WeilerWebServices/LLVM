//===-- Resolver.h - Class resolver for Java classes ------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file was developed by the LLVM research group and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of a Java class resolver. This
// object creates Class objects out of loaded ClassFiles.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_JAVA_RESOLVER_H
#define LLVM_JAVA_RESOLVER_H

#include "VMClass.h"
#include <llvm/Java/Bytecode.h>
#include <llvm/Module.h>
#include <llvm/Type.h>
#include <map>
#include <string>

namespace llvm { namespace Java {

  class Resolver {
    Module* module_;
    typedef std::map<std::string, VMClass> ClassMap;
    ClassMap classMap_;
    unsigned nextInterfaceIndex_;
    const Type* objectBaseLayoutType_;
    const Type* objectBaseType_;
    const Type* typeInfoType_;
    const Type* classRecordType_;
    const Type* classRecordPtrType_;

    const VMClass* getClassForDesc(const std::string& descriptor);

    const Type* getTypeHelper(const std::string&,
                              unsigned& i,
                              bool memberMethod = false) const;

    ClassMap::iterator insertClass(ClassMap::iterator i, const VMClass& clazz) {
      return classMap_.insert(i, std::make_pair(clazz.getDescriptor(), clazz));
    }

    friend class VMClass;

  public:
    static std::string canonicalizeClassName(const std::string& className) {
      if (className[0] == '[')
        return className;
      else
        return 'L' + className + ';';
    }

    Resolver(Module* module);

    const Type* getObjectBaseLayoutType() const {return objectBaseLayoutType_; }
    const Type* getObjectBaseType() const { return objectBaseType_; }
    const Type* getTypeInfoType() const { return typeInfoType_; }
    const Type* getClassRecordType() const { return classRecordType_; }
    const Type* getClassRecordPtrType() const { return classRecordPtrType_; }

    const Type* getType(const std::string& descriptor,
                        bool memberMethod = false) const;
    const Type* getStorageType(const Type* type) const;

    inline bool isTwoSlotType(const Type* type) const {
      return type == Type::LongTy || type == Type::DoubleTy;
    }

    inline bool isOneSlotType(const Type* type) const {
      return !isTwoSlotType(type);
    }

    const VMClass* getClass(const std::string& className) {
      return getClassForDesc(canonicalizeClassName(className));
    }

    const VMClass* getClass(JType type);

    const VMClass* getArrayClass(const VMClass* clazz) {
      return getClassForDesc('[' + clazz->getDescriptor());
    }

    unsigned getNextInterfaceIndex() { return nextInterfaceIndex_++; }
    Module* getModule() { return module_; }
    void emitClassRecordsArray() const;
  };

} } // namespace llvm::Java

#endif//LLVM_JAVA_RESOLVER_H
