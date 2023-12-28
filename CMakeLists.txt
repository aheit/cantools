cmake_minimum_required(VERSION 3.10)

project(cantools)
set(PACKAGE_NAME "cantools")
set(PACKAGE_TARNAME ${PACKAGE_NAME})
set(PACKAGE_URL "")

# versions
set(CMAKE_C_STANDARD 99)
set(PROJECT_MAJOR_VERSION 0)
set(PROJECT_MINOR_VERSION 34)
set(PROJECT_PATCH_VERSION 0)
set(PACKAGE_VERSION ${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}.${PROJECT_PATCH_VERSION})
set(VERSION ${PACKAGE_VERSION})
set(PACKAGE_STRING "${PACKAGE_VERSION} ${PACKAGE_VERSION}")

# project specific cmake scripts
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# check for required functions
include(CheckSymbolExists)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckTypeSize)
include(CheckCSourceCompiles)
include(CheckFunctionExists)

# options
option(WITH_DMALLOC "Use dmalloc for memory debugging" OFF)
option(WITH_MATLAB "Build with MATLAB backend (requires MATIO, HDF5, and zlib)" ON)

# Check for headers
check_include_files("stdlib.h;stdarg.h;string.h;float.h" STDC_HEADERS)
check_include_file(inttypes.h  HAVE_INTTYPES_H)
check_include_file(stdint.h    HAVE_STDINT_H)
check_include_file(unistd.h    HAVE_UNISTD_H)

# Check if Dmalloc is requested and available
if(WITH_DMALLOC)
    find_library(DMALLOC_LIBRARY dmalloc)

    if(DMALLOC_LIBRARY)
        message(STATUS "Dmalloc enabled for memory debugging")
        # add_definitions(-DWITH_DMALLOC)
    else()
        message(FATAL_ERROR "Dmalloc library not found. Please install Dmalloc or disable the DMALLOC option.")
    endif()
else()
    message(STATUS "Dmalloc disabled")
endif()
  
check_type_size("unsigned long long int" UNSIGNED_LONG_LONG_INT)

message("Byte order: ${CMAKE_C_BYTE_ORDER}")
if(${CMAKE_C_BYTE_ORDER} MATCHES "BIG_ENDIAN")
  set("WORDS_BIGENDIAN" 1)
endif()

# check availability of arithmetic right shift
check_c_source_compiles(
    "int main() { int dummy[((-1 >> 1) < 0) ? 1 : -1]; return 0; }"
    HAVE_ARITHMETIC_RSHIFT)

# workaround for missing LINE_MAX definition
check_symbol_exists(LINE_MAX limits.h LINE_MAX_DEFINED)
if (NOT LINE_MAX_DEFINED)
    message(STATUS "LINE_MAX not defined in limits.h. Adding -DLINE_MAX=2048 to CFLAGS")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLINE_MAX=2048")
endif()

configure_file(config.h.cmake cantools_config.h)

# find packages
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(ZLIB REQUIRED)
if(WITH_MATLAB)
  find_package(Matio REQUIRED)
  find_package(HDF5 REQUIRED)
endif(WITH_MATLAB)

# libcandbc
set(SOURCES_LIBCANDBC
    src/libcandbc/dbcmodel.c
    src/libcandbc/dbcreader.c
    src/libcandbc/dbcwriter.c)
set(PARSER_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(LEXER_OUT "${PARSER_DIR}/dbclexer.c")
set(PARSER_OUT "${PARSER_DIR}/dbcparser.c")
flex_target(LEXER "src/libcandbc/lexer.l" "${LEXER_OUT}" DEFINES_FILE "${PARSER_DIR}/dbclexer.h")
bison_target(PARSER "src/libcandbc/parser.y" "${PARSER_OUT}" DEFINES_FILE "${PARSER_DIR}/dbcparser.h")
add_flex_bison_dependency(LEXER PARSER)
add_library(candbc STATIC ${SOURCES_LIBCANDBC} "${LEXER_OUT}" "${PARSER_OUT}")
target_include_directories(candbc PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src/libcandbc "${PARSER_DIR}")

# libcanasc
add_library(canasc STATIC
  src/libcanasc/ascreader.c)
target_include_directories(canasc PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src/cantomat
  ${CMAKE_SOURCE_DIR}/src/hashtable
  ${CMAKE_SOURCE_DIR}/src/libcandbc)

# libcanblf
add_library(canblf STATIC
    src/libcanblf/blfreader.c
    src/libcanblf/blfparser.c
    src/libcanblf/blfstream.c
    src/libcanblf/blfapi.c)
target_include_directories(canblf PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src/cantomat
    ${CMAKE_SOURCE_DIR}/src/hashtable
    ${CMAKE_SOURCE_DIR}/src/libcandbc
    ${ZLIB_INCLUDE_DIRS})

# libcanclg
add_library(canclg STATIC src/libcanclg/clgreader.c)
target_include_directories(canclg PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src/cantomat
  ${CMAKE_SOURCE_DIR}/src/hashtable
  ${CMAKE_SOURCE_DIR}/src/libcandbc)
# libcanmdf
add_library(canmdf STATIC
    src/libcanmdf/mdfcg.c
    src/libcanmdf/mdfcn.c
    src/libcanmdf/mdfdg.c
    src/libcanmdf/mdffile.c
    src/libcanmdf/mdffilter.c
    src/libcanmdf/mdfmodel.c
    src/libcanmdf/mdfsg.c)
target_include_directories(canmdf PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src/cantomat
    ${CMAKE_SOURCE_DIR}/src/hashtable
    ${CMAKE_SOURCE_DIR}/src/libcandbc
    ${ZLIB_INCLUDE_DIRS})

# libmatfile
if(WITH_MATLAB)
  add_library(matfile STATIC src/libmatfile/matfile.c)
  target_include_directories(matfile PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src/cantomat
    ${CMAKE_SOURCE_DIR}/src/hashtable
    ${CMAKE_SOURCE_DIR}/src/libcandbc)
endif(WITH_MATLAB)

# libcanvsb
add_library(canvsb STATIC src/libcanvsb/vsbreader.c)
target_include_directories(canvsb PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src/cantomat
  ${CMAKE_SOURCE_DIR}/src/hashtable
  ${CMAKE_SOURCE_DIR}/src/libcandbc)

# hashtable
add_library(hashtable STATIC
  src/hashtable/hashtable.c
  src/hashtable/hashtable_itr.c )
target_include_directories(hashtable PRIVATE ${CMAKE_SOURCE_DIR})

# dbccopy
add_executable(dbccopy src/dbccopy/dbccopy.c)
target_include_directories(dbccopy PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src/libcandbc)
target_link_libraries(dbccopy PRIVATE candbc -lm -ly ${DMALLOC_LIBRARY})

# dbcls
add_executable(dbcls src/dbcls/dbcls.c)
target_include_directories(dbcls PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src/libcandbc)
target_link_libraries(dbcls PRIVATE candbc -lm -ly ${DMALLOC_LIBRARY})

if(WITH_MATLAB)
  # cantomat
  add_executable(cantomat 
    src/cantomat/cantomat.c
    src/cantomat/messagedecoder.c
    src/cantomat/busassignment.c
    src/cantomat/matwrite.c
    src/cantomat/messagehash.c
    src/cantomat/measurement.c
    src/cantomat/signalformat.c )
  target_include_directories(cantomat PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src/libcanasc
    ${CMAKE_SOURCE_DIR}/src/libcanblf
    ${CMAKE_SOURCE_DIR}/src/libcanclg
    ${CMAKE_SOURCE_DIR}/src/libcanvsb
    ${CMAKE_SOURCE_DIR}/src/cantomat
    ${CMAKE_SOURCE_DIR}/src/hashtable
    ${CMAKE_SOURCE_DIR}/src/libcandbc
    ${CMAKE_SOURCE_DIR}/src/libmatfile
    ${Matio_INCLUDE_DIR} )
  target_link_libraries(cantomat PRIVATE
    canasc
    canblf
    candbc
    canvsb
    canclg
    matfile
    hashtable
    ${Matio_LIBRARY}
    ${ZLIB_LIBRARIES}
    ${HDF5_LIBRARIES}
    -lm -ly ${DMALLOC_LIBRARY})

  # mdftomat
  add_executable(mdftomat
    src/mdftomat/mdftomat.c
    src/mdftomat/mdftomat.h )
  target_include_directories(mdftomat PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src/libmatfile
    ${CMAKE_SOURCE_DIR}/src/libcanmdf )
  target_link_libraries(mdftomat PRIVATE
    canmdf
    matfile
    ${Matio_LIBRARY}
    ${ZLIB_LIBRARIES}
    ${HDF5_LIBRARIES}
    ${DMALLOC_LIBRARY})
  
  # matdump
  add_executable(matdump
    src/matdump/matdump.c
    src/matdump/matdump.h
  )
  target_include_directories(matdump PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src/libmatfile
    ${CMAKE_SOURCE_DIR}/src/libcanmdf )
  target_link_libraries(matdump PRIVATE
    canmdf
    matfile
    ${Matio_LIBRARY}
    ${ZLIB_LIBRARIES}
    ${HDF5_LIBRARIES}
    ${DMALLOC_LIBRARY})

endif(WITH_MATLAB)

# Install headers
install(FILES ${HEADERS} DESTINATION include/cantools)

# Install targets
install(TARGETS dbccopy dbcls RUNTIME DESTINATION bin)
if(WITH_MATLAB)
	install(TARGETS cantomat mdftomat matdump RUNTIME DESTINATION bin)
endif(WITH_MATLAB)

