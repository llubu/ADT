project (HTable)

include_directories(${PROJECT_SOURCE_DIR}/../include)

# Configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/../include/TutorialConfig.h.in"
#  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
#)

##
# add cpputest library
#add_library(imp_cpputest STATIC IMPORTED)
#set_property(TARGET imp_cpputest PROPERTY
#            IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/lib/libCppUTest.a)

# add cpputestExt library -lCppUTestExt
#add_library(imp_cpputestext STATIC IMPORTED)
#set_property(TARGET imp_cpputestext PROPERTY
#             IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/lib/libCppUTestExt.a)


##
add_library(HashTable ./lru_table.c)
