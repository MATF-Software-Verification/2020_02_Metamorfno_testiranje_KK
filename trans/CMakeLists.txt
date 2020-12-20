cmake_minimum_required(VERSION 2.8)

project("Clang transformacije")

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_SOURCE_DIR}/cmake/modules"
)

set(CMAKE_C_COMPILER clang-11)
set(CMAKE_CXX_COMPILER clang++-11)

execute_process(
  COMMAND llvm-config-11 --cxxflags
  OUTPUT_VARIABLE LibClang_DEFINITIONS)

set(LibClang_DEFINITIONS ${LibClang_DEFINITIONS} "-fno-rtti")

execute_process(
  COMMAND llvm-config-11 --includedir
  OUTPUT_VARIABLE LibClang_INCLUDE_DIR)

set(LibClang_LIBRARY /usr/lib/llvm-11/lib/libclang.so)
set(LibClang_LINK_PATH /usr/lib/llvm-11/lib)

find_library(LibClang_LIBRARY NAMES clang)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibClang DEFAULT_MSG LibClang_LIBRARY LibClang_INCLUDE_DIR)

mark_as_advanced(LibClang_INCLUDE_DIR LibClang_LIBRARY)

add_definitions(${LibClang_DEFINITIONS})

include_directories(
  ${LibClang_INCLUDE_DIR}
  include
)

link_directories(${LibClang_LINK_PATH})

add_executable(trans source/trans.cpp
                     include/MTKConsumer.hpp
                     include/MTKContext.hpp
                     source/MTKContext.cpp
                     include/MTKTransformer.hpp
                     source/MTKTransformer.cpp
                     include/Do2ForVisitor.hpp
                     source/Do2ForVisitor.cpp
                     include/For2DoVisitor.hpp
                     source/For2DoVisitor.cpp
                     include/For2WhileVisitor.hpp
                     source/For2WhileVisitor.cpp
                     include/While2DoVisitor.hpp
                     source/While2DoVisitor.cpp
                     include/While2ForVisitor.hpp
                     source/While2ForVisitor.cpp
                     include/PrepForVisitor.hpp
                     source/PrepForVisitor.cpp
                     include/PrepIfVisitor.hpp
                     source/PrepIfVisitor.cpp
                     include/PrepSwitchVisitor.hpp
                     source/PrepSwitchVisitor.cpp
                     include/If2SwitchVisitor.hpp
                     source/If2SwitchVisitor.cpp
                     include/Switch2IfVisitor.hpp
                     source/Switch2IfVisitor.cpp
                     include/Rek2IterVisitor.hpp
                     source/Rek2IterVisitor.cpp
                     include/FinIterVisitor.hpp
                     source/FinIterVisitor.cpp
                     include/Iter2RekVisitor.hpp
                     source/Iter2RekVisitor.cpp
                     include/FinRekVisitor.hpp
                     source/FinRekVisitor.cpp)

target_link_libraries(trans libLLVM-11.so
                            libclangTooling.a
                            libclangAnalysis.a
                            libclangAST.a
                            libclangBasic.a
                            libclangDriver.a
                            libclangEdit.a
                            libclangFrontend.a
                            libclangLex.a
                            libclangParse.a
                            libclangRewrite.a
                            libclangSema.a
                            libclangSerialization.a
                            libclangTooling.a)
