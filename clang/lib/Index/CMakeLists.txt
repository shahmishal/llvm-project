set(LLVM_LINK_COMPONENTS
  BitReader
  Core
  Support
  )

add_clang_library(clangIndex
  ClangIndexRecordWriter.cpp
  CommentToXML.cpp
  FileIndexRecord.cpp
  IndexBody.cpp
  IndexDataStoreUtils.cpp
  IndexDecl.cpp
  IndexingAction.cpp
  IndexingContext.cpp
  IndexRecordHasher.cpp
  IndexRecordReader.cpp
  IndexRecordWriter.cpp
  IndexSymbol.cpp
  IndexTypeSourceInfo.cpp
  IndexUnitReader.cpp
  IndexUnitWriter.cpp
  USRGeneration.cpp

  ADDITIONAL_HEADERS
  IndexingContext.h
  SimpleFormatContext.h

  LINK_LIBS
  clangAST
  clangBasic
  clangFormat
  clangFrontend
  clangLex
  clangRewrite
  clangSerialization
  clangToolingCore
  )
