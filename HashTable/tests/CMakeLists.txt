project (HTable)

#include headers
include_directories(${PROJECT_SOURCE_DIR}/../include)
# include project source
include_directories(${PROJECT_SOURCE_DIR}/../src)

# include mocks only for test code
include_directories(${PROJECT_SOURCE_DIR}/../mocks)

# include CppUTest headers
include_directories($ENV{CPPUTEST_HOME}/include)

set (CMAKE_CXX_FLAGS "-include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h")
set (CMAKE_C_FLAGS "-include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h")
#
# add cpputest library
add_library(imp_cpputest STATIC IMPORTED)
set_property(TARGET imp_cpputest PROPERTY
             IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/lib/libCppUTest.a)

# add cpputestExt library -lCppUTestExt
add_library(imp_cpputestext STATIC IMPORTED)
set_property(TARGET imp_cpputestext PROPERTY
             IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/lib/libCppUTestExt.a)


# build test library for Hash Table
add_library(HashTableTests ./testHT.cpp)

add_executable(RunAllTests RunAllTests.cpp)
target_link_libraries(RunAllTests imp_cpputest imp_cpputestext HashTableTests HashTable)
