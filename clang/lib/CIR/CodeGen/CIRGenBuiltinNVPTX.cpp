//===---- CIRGenBuiltinX86.cpp - Emit CIR for X86 builtins ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This contains code to emit x86/x86_64 Builtin calls as CIR or a function
// call to be later resolved.
//
//===----------------------------------------------------------------------===//

#include "CIRGenCXXABI.h"
#include "CIRGenCall.h"
#include "CIRGenFunction.h"
#include "CIRGenModule.h"
#include "TargetInfo.h"
#include "clang/CIR/MissingFeatures.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Value.h"
#include "clang/AST/GlobalDecl.h"
#include "clang/Basic/Builtins.h"
#include "clang/Basic/TargetBuiltins.h"
#include "clang/CIR/Dialect/IR/CIRDialect.h"
#include "clang/CIR/Dialect/IR/CIRTypes.h"
#include "llvm/Support/ErrorHandling.h"

using namespace clang;
using namespace clang::CIRGen;
using namespace cir;

mlir::Value CIRGenFunction::emitNVPTXBuiltinExpr(unsigned BuiltinID,
                                             const CallExpr *E) {
  switch (BuiltinID) {
    case NVPTX::BI__nvvm_read_ptx_sreg_tid_x:
    case NVPTX::BI__nvvm_read_ptx_sreg_tid_y:
    case NVPTX::BI__nvvm_read_ptx_sreg_tid_z: {
        mlir::Type intTy = cir::IntType::get(&getMLIRContext(), 32, false);
        return builder
          .create<cir::LLVMIntrinsicCallOp>(
              getLoc(E->getExprLoc()), builder.getStringAttr("nvvm.read.ptx.sreg.tid.x"),
              intTy)
          .getResult();
      }
    default:
      llvm_unreachable("NYI");
  }
}
