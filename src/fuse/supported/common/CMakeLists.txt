target_include_directories(SDKlib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# The FUSE integration tests pull in private impl headers from this root (e.g.
# <mega/fuse/common/constants.h>, which is not part of the exported include/
# tree). SDKlib keeps this root PRIVATE so it does not leak into the installed
# export interface, so hand it to the test target directly. See the matching
# note in platform/posix/linux/CMakeLists.txt.
if (TARGET test_integration)
    target_include_directories(test_integration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

target_sources(SDKlib PRIVATE
                      database_builder.cpp
                      directory_inode.cpp
                      file_cache.cpp
                      file_extension_db.cpp
                      file_info.cpp
                      file_inode.cpp
                      file_io_context.cpp
                      inode_cache.cpp
                      inode.cpp
                      inode_db.cpp
                      mount.cpp
                      mount_db.cpp
)

add_subdirectory(mega)
add_subdirectory(testing)
