# Let the SDK know where it can find our headers.
target_include_directories(SDKlib PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(SDKlib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# The FUSE integration tests include posix-specific impl headers from this root
# (e.g. <mega/fuse/platform/file_descriptor_forward.h>), which are not exported
# to the installed include/ tree. SDKlib consumes this root PRIVATE so it does
# not leak into the export interface, so hand it to the test target directly.
# See the matching note in linux/CMakeLists.txt.
if (TARGET test_integration)
    target_include_directories(test_integration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# Add sources required by libfuse backend.
target_sources(SDKlib PRIVATE
                      constants.cpp
                      directory_context.cpp
                      file_descriptor.cpp
                      inode_invalidator.cpp
                      mount.cpp
                      mount_db.cpp
                      process.cpp
                      request.cpp
                      service.cpp
                      session_base.cpp
                      signal.cpp
                      unmounter.cpp
                      utility.cpp
)

# Add libfuse sources.
add_subdirectory(libfuse)

# Add libfuse headers.
add_subdirectory(mega)

# Add platform-specific sources.
if(APPLE)
    add_subdirectory(darwin)
else()
    add_subdirectory(linux)
endif()

# Add libfuse tests.
add_subdirectory(testing)
