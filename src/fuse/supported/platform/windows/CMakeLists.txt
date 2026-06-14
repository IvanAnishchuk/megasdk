# Let CMake know where it can find our FindWinFsP module.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Make sure WinFSP is present.
find_package(WinFSP REQUIRED)

# Make sure the SDK links against WinFSP.
target_link_libraries(SDKlib PUBLIC WinFSP)

# Let the SDK know where it can find our headers. PUBLIC so the platform root
# reaches in-tree consumers such as test_integration; BUILD_INTERFACE keeps the
# bare source-tree path out of the installed export interface, which
# install(EXPORT sdklibTargets) would otherwise reject.
target_include_directories(SDKlib PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

# Add sources required by WinFSP backend.
target_sources(SDKlib PRIVATE
                      constants.cpp
                      directory_context.cpp
                      dispatcher.cpp
                      file_explorer_setter.cpp
                      local_pointer.cpp
                      mount.cpp
                      mount_db.cpp
                      security_descriptor.cpp
                      security_identifier.cpp
                      service.cpp
                      shell.cpp
                      unmounter.cpp
                      utility.cpp
)

# Add WinFSP backend headers.
add_subdirectory(mega)

# Add WinFSP tests.
add_subdirectory(testing)
