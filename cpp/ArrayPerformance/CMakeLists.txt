cmake_minimum_required(VERSION 3.10)
project(ArrayPerformance)

set(HEADER_FILES sortutils.hpp)
set(SOURCE_FILES sortutils.cpp)
set(UNIT_TEST_FILES TestPerformance.cpp)

add_executable(ArrayPerformance ${HEADER_FILES} ${SOURCE_FILES} main.cpp)
add_executable(UnitTestRunner ${HEADER_FILES} ${SOURCE_FILES} ${UNIT_TEST_FILES})

set_property(TARGET ArrayPerformance PROPERTY CXX_STANDARD 17)
set_property(TARGET UnitTestRunner PROPERTY CXX_STANDARD 17)

find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    message("Clang-Format found at: " ${CLANG_FORMAT})

    unset(SOURCE_FILES_PATHS)
    foreach(SOURCE_FILE ${HEADER_FILES} ${SOURCE_FILES})
        get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
        set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
    endforeach()

    add_custom_target(ClangFormat COMMAND ${CLANG_FORMAT} -i -style=file ${SOURCE_FILES_PATHS})

    add_dependencies(ArrayPerformance ClangFormat)
else()
    message("Unable to find clang-format")
endif()


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(ArrayPerformance PRIVATE /W4 /permissive- -Wl,--stack,10000000)
    set_target_properties(ArrayPerformance PROPERTIES LINK_FLAGS "/STACK:10000000")
    target_compile_options(UnitTestRunner PRIVATE /W4 /permissive- -Wl,--stack,10000000)
    set_target_properties(UnitTestRunner PROPERTIES LINK_FLAGS "/STACK:10000000")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(ArrayPerformance PRIVATE -Wall -Wextra -pedantic -Wl,--stack,10000000)
    target_compile_options(UnitTestRunner PRIVATE -Wall -Wextra -pedantic -Wl,--stack,10000000)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "CLANG")
    target_compile_options(ArrayPerformance PRIVATE -Wall -Wextra -pedantic -Wl,--stack,10000000)
    target_compile_options(UnitTestRunner PRIVATE -Wall -Wextra -pedantic -Wl,--stack,10000000)
endif()



configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Now simply link against gtest or gtest_main as needed. Eg
target_link_libraries(UnitTestRunner gtest_main)
