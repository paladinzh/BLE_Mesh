cmake_minimum_required(VERSION 3.6)

if (NOT CMAKE_VERSION VERSION_LESS 3.9)
    # Allow user to enable CMAKE_INTERPROCEDURAL_OPTIMIZATION (LTO) if supported for the toolchain.
    # This is supported from CMake version 9 and later.
    cmake_policy(SET CMP0069 NEW)
endif ()

set(VERSION_MAJOR 0)
set(VERSION_MINOR 10)
set(VERSION_BUGFIX 1)
set(VERSION_SUFFIX "-Alpha")
set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_BUGFIX}${VERSION_SUFFIX}" CACHE STRING "" FORCE)

message(STATUS "Configuring CMake for nRF5 SDK for Bluetooth Mesh ${VERSION_STRING}")

option(BUILD_HOST "Build for host (unit test build)" OFF)
option(BUILD_EXAMPLES "Build example applications" ON)

if (NOT BUILD_HOST)
    set(CMAKE_SYSTEM_NAME "Generic")
    set(CMAKE_SYSTEM_PROCESSOR "ARM")
endif (NOT BUILD_HOST)

# We enable the project() here for CMake to initialize variables s.a. "CMAKE_HOST_W32".
# Languages are enabled _after_ the toolchain has been setup.
project(MBTLE
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_BUGFIX}
    LANGUAGES NONE)

set(CMAKE_CONFIG_DIR "${CMAKE_SOURCE_DIR}/CMake")
set(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR} CACHE STRING "" FORCE)

# Needed tools for generating documentation and serial PyACI
find_package(PythonInterp)
find_package(Doxygen)
find_program(DOT_EXECUTABLE "dot" PATHS ENV PATH)
find_program(MSCGEN_EXECUTABLE "mscgen" PATHS ENV PATH)

include("${CMAKE_CONFIG_DIR}/FindDependency.cmake")
include("${CMAKE_CONFIG_DIR}/BuildType.cmake")
include("${CMAKE_CONFIG_DIR}/Toolchain.cmake")
include("${CMAKE_CONFIG_DIR}/FindSDK.cmake")
include("${CMAKE_CONFIG_DIR}/Platform.cmake")
include("${CMAKE_CONFIG_DIR}/SoftDevice.cmake")
include("${CMAKE_CONFIG_DIR}/Board.cmake")
include("${CMAKE_CONFIG_DIR}/PCLint.cmake")
include("${CMAKE_CONFIG_DIR}/GenerateSESProject.cmake")

enable_language(C ASM)

if (NOT BUILD_HOST)
    set(CMAKE_EXECUTABLE_SUFFIX ".elf")
    set(BUILD_SHARED_LIBS OFF)
    set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
else ()
    message(STATUS "Building for HOST")
    include("${CMAKE_CONFIG_DIR}/UnitTest.cmake")
    include("${CMAKE_CONFIG_DIR}/Coverage.cmake")
    include("${CMAKE_CONFIG_DIR}/UBSAN.cmake")
endif ()

# Export compilation commands to .json file (used by clang-complete backends)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("mesh")
add_subdirectory("external")

if (NOT PYTHON_EXECUTABLE)
    message(WARNING "Need python executable to generate serial documentation and PyACI")
elseif (NOT DOXYGEN_EXECUTABLE)
    message(WARNING "Doxygen not found, documentation build is not available")
else ()
    add_subdirectory("tools")
    add_subdirectory("doc")
endif ()

if (BUILD_EXAMPLES AND NOT BUILD_HOST)
    include("${CMAKE_CONFIG_DIR}/Nrfjprog.cmake")
    add_subdirectory("models")
    add_subdirectory("examples")
endif ()
