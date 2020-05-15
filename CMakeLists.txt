cmake_minimum_required(VERSION 3.10...3.16 FATAL_ERROR)
project(sqlearn VERSION 1.0.0 LANGUAGES CXX)

#Make sure that custom modules like FindRapidJSON are found
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

##############################################
# Declare dependencies
#set(MIN_BOOST_VERSION 1.71)
#find_package(boost_headers ${MIN_BOOST_VERSION} REQUIRED CONFIG)
#find_package(boost_regex ${MIN_BOOST_VERSION} REQUIRED CONFIG)

#set(MIN_RapidJSON_VERSION 1.1)
#find_package(RapidJSON ${MIN_RapidJSON_VERSION} REQUIRED MODULE)

##############################################
# Create target and set properties

add_library(sqlearn
    src/sqlearn.cpp
    src/utils.h
    src/headers/memory/buffer_pool_engine.h
    src/headers/memory/disk_interface.h
    src/headers/config.h
    src/memory/buffer_pool_engine.cpp
    src/memory/disk_interface.cpp
)

#Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(SQLearn::sqlearn ALIAS sqlearn)

#Set target properties
target_include_directories(sqlearn
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(sqlearn PRIVATE cxx_auto_type)
target_compile_options(sqlearn PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall -Wextra -Wpedantic>)

target_link_libraries(sqlearn
    PUBLIC
        # future
    PRIVATE
        # future
)

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/SQLearn)

install(TARGETS sqlearn
    EXPORT sqlearn-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#This is required so that the exported target has the name SQLearn and not sqlearn
set_target_properties(sqlearn PROPERTIES EXPORT_NAME SQLearn)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT sqlearn-targets
    FILE
        SQLearnTargets.cmake
    NAMESPACE
        SQLearn::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/SQLearnConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/SQLearnConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/SQLearnConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/SQLearnConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/SQLearnConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
#configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
#    ${CMAKE_CURRENT_BINARY_DIR}/FindRapidJSON.cmake
#    COPYONLY)

export(EXPORT sqlearn-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/SQLearnTargets.cmake
    NAMESPACE SQLearn::)

#Register package in user's package registry
export(PACKAGE SQLearn)

##############################################
## Add test
enable_testing()
add_subdirectory(test)
