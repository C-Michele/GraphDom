cmake_minimum_required(VERSION 3.20)
project(GraphDom VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

set(GraphDom_SOURCES
        src/utility.cpp
)

add_library(GraphDom_Static STATIC ${GraphDom_SOURCES})

add_library(GraphDom_Shared SHARED ${GraphDom_SOURCES})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

foreach (target GraphDom_Static GraphDom_Shared)
    target_include_directories(
            ${target}
            PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
endforeach ()

set_target_properties(
        GraphDom_Static
        GraphDom_Shared
        PROPERTIES
        OUTPUT_NAME GraphDom
)

install(

        DIRECTORY

        include/

        DESTINATION

        ${CMAKE_INSTALL_INCLUDEDIR}

)

install(
        TARGETS
            GraphDom_Static
        EXPORT
            GraphDomStaticTargets
        ARCHIVE DESTINATION
            ${CMAKE_INSTALL_LIBDIR}
)

install(
        TARGETS
            GraphDom_Shared
        EXPORT
            GraphDomSharedTargets
        ARCHIVE DESTINATION
            ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION
            ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION
            ${CMAKE_INSTALL_BINDIR}
)

install(
        EXPORT
            GraphDomStaticTargets
        FILE
            GraphDomStaticTargets.cmake
        NAMESPACE
            GraphDomInternal::
        DESTINATION
            ${CMAKE_INSTALL_LIBDIR}/cmake/GraphDom
)

install(
        EXPORT
            GraphDomSharedTargets
        FILE
            GraphDomSharedTargets.cmake
        NAMESPACE
            GraphDomInternal::
        DESTINATION
            ${CMAKE_INSTALL_LIBDIR}/cmake/GraphDom
)

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/GraphDomConfig.cmake.in

        ${CMAKE_CURRENT_BINARY_DIR}/GraphDomConfig.cmake

        INSTALL_DESTINATION

        ${CMAKE_INSTALL_LIBDIR}/cmake/GraphDom
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/GraphDomConfigVersion.cmake
        VERSION
        ${PROJECT_VERSION}
        COMPATIBILITY
        SameMajorVersion
)

install(
        FILES
        ${CMAKE_CURRENT_BINARY_DIR}/GraphDomConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/GraphDomConfigVersion.cmake
        DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/GraphDom
)

include(CTest)

if(BUILD_TESTING)
    add_subdirectory(unit_test)
endif()