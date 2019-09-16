; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple arm64e-apple-darwin -verify-machineinstrs | FileCheck %s --check-prefixes=ALL

target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"

define i64 @test_sign_ia(i64 %arg, i64 %arg1) {
; ALL-LABEL: test_sign_ia:
; ALL:       ; %bb.0:
; ALL-NEXT:    pacia x0, x1
; ALL-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign.i64(i64 %arg, i32 0, i64 %arg1)
  ret i64 %tmp
}

define i64 @test_sign_ia_zero(i64 %arg) {
; ALL-LABEL: test_sign_ia_zero:
; ALL:       ; %bb.0:
; ALL-NEXT:    paciza x0
; ALL-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign.i64(i64 %arg, i32 0, i64 0)
  ret i64 %tmp
}

define i64 @test_sign_ib(i64 %arg, i64 %arg1) {
; ALL-LABEL: test_sign_ib:
; ALL:       ; %bb.0:
; ALL-NEXT:    pacib x0, x1
; ALL-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign.i64(i64 %arg, i32 1, i64 %arg1)
  ret i64 %tmp
}

define i64 @test_sign_ib_zero(i64 %arg) {
; ALL-LABEL: test_sign_ib_zero:
; ALL:       ; %bb.0:
; ALL-NEXT:    pacizb x0
; ALL-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign.i64(i64 %arg, i32 1, i64 0)
  ret i64 %tmp
}

define i64 @test_sign_da(i64 %arg, i64 %arg1) {
; ALL-LABEL: test_sign_da:
; ALL:       ; %bb.0:
; ALL-NEXT:    pacda x0, x1
; ALL-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign.i64(i64 %arg, i32 2, i64 %arg1)
  ret i64 %tmp
}

define i64 @test_sign_da_zero(i64 %arg) {
; ALL-LABEL: test_sign_da_zero:
; ALL:       ; %bb.0:
; ALL-NEXT:    pacdza x0
; ALL-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign.i64(i64 %arg, i32 2, i64 0)
  ret i64 %tmp
}

define i64 @test_sign_db(i64 %arg, i64 %arg1) {
; ALL-LABEL: test_sign_db:
; ALL:       ; %bb.0:
; ALL-NEXT:    pacdb x0, x1
; ALL-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign.i64(i64 %arg, i32 3, i64 %arg1)
  ret i64 %tmp
}

define i64 @test_sign_db_zero(i64 %arg) {
; ALL-LABEL: test_sign_db_zero:
; ALL:       ; %bb.0:
; ALL-NEXT:    pacdzb x0
; ALL-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign.i64(i64 %arg, i32 3, i64 0)
  ret i64 %tmp
}

define i64 @test_sign_generic(i64 %arg, i64 %arg1) {
; ALL-LABEL: test_sign_generic:
; ALL:       ; %bb.0:
; ALL-NEXT:    pacga x0, x0, x1
; ALL-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign.generic.i64(i64 %arg, i64 %arg1)
  ret i64 %tmp
}

define i64 @test_sign_cse(i64 %arg, i64 %arg1) {
; ALL-LABEL: test_sign_cse:
; ALL:       ; %bb.0:
; ALL-NEXT:    pacia x0, x1
; ALL-NEXT:    add x0, x0, x0
; ALL-NEXT:    ret
  %tmp0 = call i64 @llvm.ptrauth.sign.i64(i64 %arg, i32 0, i64 %arg1)
  %tmp1 = call i64 @llvm.ptrauth.sign.i64(i64 %arg, i32 0, i64 %arg1)
  %tmp2 = add i64 %tmp0, %tmp1
  ret i64 %tmp2
}

declare i64 @llvm.ptrauth.sign.i64(i64, i32, i64)
declare i64 @llvm.ptrauth.sign.generic.i64(i64, i64)
