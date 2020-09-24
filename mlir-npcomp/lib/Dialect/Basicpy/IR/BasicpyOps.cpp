//===- BasicpyOps.cpp - Core numpy dialect ops -------------------*- C++-*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "npcomp/Dialect/Basicpy/IR/BasicpyOps.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/Function.h"
#include "mlir/IR/FunctionImplementation.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/IR/PatternMatch.h"
#include "npcomp/Dialect/Basicpy/IR/BasicpyDialect.h"

#include "npcomp/Dialect/Basicpy/IR/BasicpyOpsEnums.cpp.inc"

namespace mlir {
namespace NPCOMP {
namespace Basicpy {

//===----------------------------------------------------------------------===//
// BoolConstantOp
//===----------------------------------------------------------------------===//

OpFoldResult BoolConstantOp::fold(ArrayRef<Attribute> operands) {
  return valueAttr();
}

//===----------------------------------------------------------------------===//
// BytesConstantOp
//===----------------------------------------------------------------------===//

OpFoldResult BytesConstantOp::fold(ArrayRef<Attribute> operands) {
  return valueAttr();
}

//===----------------------------------------------------------------------===//
// ExecOp
//===----------------------------------------------------------------------===//

void ExecOp::build(OpBuilder &builder, OperationState &result) {
  OpBuilder::InsertionGuard guard(builder);
  Region *body = result.addRegion();
  builder.createBlock(body);
}

static ParseResult parseExecOp(OpAsmParser &parser, OperationState *result) {
  Region *bodyRegion = result->addRegion();
  if (parser.parseOptionalAttrDictWithKeyword(result->attributes) ||
      parser.parseRegion(*bodyRegion, /*arguments=*/{}, /*argTypes=*/{}))
    return failure();
  return success();
}

static void printExecOp(OpAsmPrinter &p, ExecOp op) {
  p << op.getOperationName();
  p.printOptionalAttrDictWithKeyword(op.getAttrs());
  p.printRegion(op.body());
}

//===----------------------------------------------------------------------===//
// FuncTemplateCallOp
//===----------------------------------------------------------------------===//

static LogicalResult verifyBasicpyOp(FuncTemplateCallOp op) {
  auto argNames = op.arg_names();
  if (argNames.size() > op.args().size()) {
    return op.emitOpError() << "expected <= kw arg names vs args";
  }

  for (auto it : llvm::enumerate(argNames)) {
    auto argName = it.value().cast<StringAttr>().getValue();
    if (argName == "*" && it.index() != 0) {
      return op.emitOpError() << "positional arg pack must be the first kw arg";
    }
    if (argName == "**" && it.index() != argNames.size() - 1) {
      return op.emitOpError() << "kw arg pack must be the last kw arg";
    }
  }
  return success();
}

//===----------------------------------------------------------------------===//
// FuncTemplateOp
//===----------------------------------------------------------------------===//

void FuncTemplateOp::build(OpBuilder &builder, OperationState &result) {
  OpBuilder::InsertionGuard guard(builder);
  ensureTerminator(*result.addRegion(), builder, result.location);
}

static ParseResult parseFuncTemplateOp(OpAsmParser &parser,
                                       OperationState *result) {
  Region *bodyRegion = result->addRegion();
  StringAttr symbolName;

  if (parser.parseSymbolName(symbolName, SymbolTable::getSymbolAttrName(),
                             result->attributes) ||
      parser.parseOptionalAttrDictWithKeyword(result->attributes) ||
      parser.parseRegion(*bodyRegion, /*arguments=*/{}, /*argTypes=*/{}))
    return failure();

  FuncTemplateOp::ensureTerminator(*bodyRegion, parser.getBuilder(),
                                   result->location);

  return success();
}

static void printFuncTemplateOp(OpAsmPrinter &p, FuncTemplateOp op) {
  p << op.getOperationName() << " ";
  p.printSymbolName(op.getName());
  p.printOptionalAttrDictWithKeyword(op.getAttrs(),
                                     {SymbolTable::getSymbolAttrName()});
  p.printRegion(op.body());
}

static LogicalResult verifyBasicpyOp(FuncTemplateOp op) {
  Block *body = op.getBody();
  for (auto &childOp : body->getOperations()) {
    if (!llvm::isa<FuncOp>(childOp) &&
        !llvm::isa<FuncTemplateTerminatorOp>(childOp)) {
      return childOp.emitOpError() << "illegal operation in func_template";
    }
  }
  return success();
}

//===----------------------------------------------------------------------===//
// SlotObjectMakeOp
//===----------------------------------------------------------------------===//

static ParseResult parseSlotObjectMakeOp(OpAsmParser &parser,
                                         OperationState *result) {
  llvm::SmallVector<OpAsmParser::OperandType, 4> operandTypes;
  if (parser.parseOperandList(operandTypes, OpAsmParser::Delimiter::Paren) ||
      parser.parseOptionalAttrDict(result->attributes) ||
      parser.parseArrowTypeList(result->types)) {
    return failure();
  }

  if (result->types.size() != 1 ||
      !result->types.front().isa<SlotObjectType>()) {
    return parser.emitError(parser.getNameLoc(),
                            "custom assembly form requires SlotObject result");
  }
  auto slotObjectType = result->types.front().cast<SlotObjectType>();
  result->addAttribute("className", slotObjectType.getClassName());
  return parser.resolveOperands(operandTypes, slotObjectType.getSlotTypes(),
                                parser.getNameLoc(), result->operands);
}

static void printSlotObjectMakeOp(OpAsmPrinter &p, SlotObjectMakeOp op) {
  // If the argument types do not match the result type slots, then
  // print the generic form.
  auto canCustomPrint = ([&]() -> bool {
    auto type = op.result().getType().dyn_cast<SlotObjectType>();
    if (!type)
      return false;
    auto args = op.slots();
    auto slotTypes = type.getSlotTypes();
    if (args.size() != slotTypes.size())
      return false;
    for (unsigned i = 0, e = args.size(); i < e; ++i) {
      if (args[i].getType() != slotTypes[i])
        return false;
    }
    return true;
  })();
  if (!canCustomPrint) {
    p.printGenericOp(op);
    return;
  }

  p << op.getOperationName() << "(";
  p.printOperands(op.slots());
  p << ")";
  p.printOptionalAttrDict(op.getAttrs(), {"className"});

  // Not really a symbol but satisfies same rules.
  p.printArrowTypeList(op.getOperation()->getResultTypes());
}

//===----------------------------------------------------------------------===//
// SlotObjectGetOp
//===----------------------------------------------------------------------===//

static ParseResult parseSlotObjectGetOp(OpAsmParser &parser,
                                        OperationState *result) {
  OpAsmParser::OperandType object;
  IntegerAttr indexAttr;
  Type indexType = parser.getBuilder().getIndexType();
  if (parser.parseOperand(object) || parser.parseLSquare() ||
      parser.parseAttribute(indexAttr, indexType, "index",
                            result->attributes) ||
      parser.parseRSquare()) {
    return failure();
  }
  Type objectType;
  if (parser.parseColonType(objectType) ||
      parser.resolveOperand(object, objectType, result->operands)) {
    return failure();
  }

  auto castObjectType = objectType.dyn_cast<SlotObjectType>();
  if (!castObjectType) {
    return parser.emitError(parser.getNameLoc(),
                            "illegal object type on custom assembly form");
  }
  auto index = indexAttr.getValue().getZExtValue();
  auto slotTypes = castObjectType.getSlotTypes();
  if (index >= slotTypes.size()) {
    return parser.emitError(parser.getNameLoc(),
                            "out of bound index on custom assembly form");
  }
  result->addTypes({slotTypes[index]});
  return success();
}

static void printSlotObjectGetOp(OpAsmPrinter &p, SlotObjectGetOp op) {
  // If the argument types do not match the result type slots, then
  // print the generic form.
  auto canCustomPrint = ([&]() -> bool {
    auto type = op.object().getType().dyn_cast<SlotObjectType>();
    if (!type)
      return false;
    auto index = op.index().getZExtValue();
    if (index >= type.getSlotCount())
      return false;
    if (op.result().getType() != type.getSlotTypes()[index])
      return false;
    return true;
  })();
  if (!canCustomPrint) {
    p.printGenericOp(op);
    return;
  }

  p << op.getOperationName() << " ";
  p.printOperand(op.object());
  p << "[" << op.index() << "]";
  p.printOptionalAttrDict(op.getAttrs(), {"index"});
  p << " : ";
  p.printType(op.object().getType());
}

//===----------------------------------------------------------------------===//
// SingletonOp
//===----------------------------------------------------------------------===//

OpFoldResult SingletonOp::fold(ArrayRef<Attribute> operands) {
  auto resultType = getResult().getType();
  return TypeAttr::get(resultType);
}

//===----------------------------------------------------------------------===//
// StrConstantOp
//===----------------------------------------------------------------------===//

OpFoldResult StrConstantOp::fold(ArrayRef<Attribute> operands) {
  return valueAttr();
}

//===----------------------------------------------------------------------===//
// UnknownCastOp
//===----------------------------------------------------------------------===//

namespace {

class ElideIdentityUnknownCast : public OpRewritePattern<UnknownCastOp> {
public:
  using OpRewritePattern::OpRewritePattern;
  LogicalResult matchAndRewrite(UnknownCastOp op,
                                PatternRewriter &rewriter) const {
    if (op.operand().getType() != op.result().getType())
      return failure();
    rewriter.replaceOp(op, op.operand());
    return success();
  }
};

} // namespace

void UnknownCastOp::getCanonicalizationPatterns(
    OwningRewritePatternList &patterns, MLIRContext *context) {
  patterns.insert<ElideIdentityUnknownCast>(context);
}

} // namespace Basicpy
} // namespace NPCOMP
} // namespace mlir

#define GET_OP_CLASSES
#include "npcomp/Dialect/Basicpy/IR/BasicpyOps.cpp.inc"
