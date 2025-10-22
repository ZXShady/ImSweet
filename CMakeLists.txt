cmake_minimum_required(VERSION 3.22.0)
project(imsweet
VERSION 0.0.1
HOMEPAGE_URL "https://github.com/ZXShady/ImSweet"
DESCRIPTION  "Helper library for ImGui providing utilities"
LANGUAGES CXX)

if(POLICY CMP0128)
    cmake_policy(SET CMP0128 NEW)
endif()

set(INCDIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE INCS "${INCDIR}/*.hpp")

add_library(imsweet INTERFACE ${INCS})
add_library(imsweet::imsweet ALIAS imsweet)
target_compile_features(imsweet INTERFACE cxx_std_20)
 
target_include_directories(imsweet INTERFACE
    $<BUILD_INTERFACE:${INCDIR}>
    $<INSTALL_INTERFACE:include>
)

#option(IMSWEET_BUILD_TESTS "Enable tests for this `imsweet` library" OFF)

#if(IMSWEET_BUILD_TESTS)
#  enable_testing()
#  add_subdirectory(tests)
#endif()

install(TARGETS imsweet
    EXPORT imsweetTargets
)

include(GNUInstallDirs)

install(DIRECTORY ${INCDIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
)

install(EXPORT imsweetTargets
    NAMESPACE imsweet::
    DESTINATION ${CMAKE_INSTALL_DATADIR}/imsweet/cmake
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/imsweetConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/imsweetConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/imsweetConfig.cmake"
    INSTALL_DESTINATION cmake
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/imsweetConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/imsweetConfigVersion.cmake"
    DESTINATION cmake
)

export(
    TARGETS imsweet
    NAMESPACE imsweet::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/imsweetTargets.cmake"
)