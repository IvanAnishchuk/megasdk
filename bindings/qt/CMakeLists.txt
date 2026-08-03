add_library(SDKQtBindings)
add_library(MEGA::SDKQtBindings ALIAS SDKQtBindings)

set(SDKLIBQT_HEADERS
    QTMegaEvent.h
    QTMegaGlobalListener.h
    QTMegaListener.h
    QTMegaRequestListener.h
    QTMegaTransferListener.h
    QTMegaApiManager.h
)
target_sources(SDKQtBindings
    PRIVATE
    ${SDKLIBQT_HEADERS}
    QTMegaEvent.cpp
    QTMegaGlobalListener.cpp
    QTMegaListener.cpp
    QTMegaRequestListener.cpp
    QTMegaTransferListener.cpp
    QTMegaApiManager.cpp
)

# Activate the meta-object code generator for Qt.
# VERSION matches SDKlib (see sdklib_target.cmake), so this ships a versioned
# SONAME -- libSDKQtBindings.so.<version> plus the bare .so dev symlink. Without
# it a consumer records a bare NEEDED libSDKQtBindings.so, which any
# system-installed copy satisfies equally well, and that copy drags in whatever
# libSDKlib version it was built against. Only search order kept the right one
# winning, so a stripped RUNPATH could put two SDK copies in one address space.
set_target_properties(SDKQtBindings PROPERTIES
    AUTOMOC ON
    VERSION ${PROJECT_VERSION}
)

## Required for the Qt generated files, to be able to include other headers
target_include_directories(SDKQtBindings
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> # For the top level projects.
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> # For the external projects.
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
message(STATUS "Building the SDK Qt Bindings with Qt v${QT_VERSION} from ${Qt${QT_VERSION_MAJOR}_DIR}")

target_link_libraries(SDKQtBindings
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    MEGA::SDKlib
)

## Adjust compilation flags for warnings and errors ##
target_platform_compile_options(
    TARGET SDKQtBindings
    UNIX $<$<CONFIG:Debug>:-ggdb3> -Wall -Wextra -Wconversion
)

if(ENABLE_CHATLIB_WERROR)
    target_platform_compile_options(
        TARGET SDKQtBindings
        UNIX  $<$<CONFIG:Debug>: -Werror
                                 -Wno-error=deprecated-declarations> # Kept as a warning, do not promote to error.
    )
endif()
# In the same export set as SDKlib, so find_package(sdklib) hands consumers a
# real MEGA::SDKQtBindings target instead of them linking it by bare name.
# Qt6::Core and MEGA::SDKlib are both PRIVATE, so with a shared library they do
# not leak into the export interface.
install(TARGETS SDKQtBindings
    EXPORT "sdklibTargets"
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES ${SDKLIBQT_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mega/bindings/qt)
