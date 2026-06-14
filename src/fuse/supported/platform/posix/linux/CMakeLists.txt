# Linux definitely has the O_PATH flag.
target_compile_definitions(SDKlib PUBLIC HAS_OPEN_PATH)

# Linux may or may not have the RENAME_(EXCHANGE|NOREPLACE) flags.
try_compile(HAS_RENAME_FLAGS
            "${CMAKE_BINARY_DIR}"
            "${CMAKE_CURRENT_SOURCE_DIR}/checks/has_rename_flags.cpp"
)

if (HAS_RENAME_FLAGS)
    target_compile_definitions(SDKlib PUBLIC HAS_RENAME_FLAGS)
endif()

target_include_directories(SDKlib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# The platform-agnostic FUSE integration tests (e.g. common_tests.cpp) include
# <mega/fuse/platform/platform.h>, which lives in this platform-specific root.
# The darwin/windows roots reach test_integration by being PUBLIC on SDKlib, but
# this one must stay PRIVATE: install(EXPORT sdklibTargets) rejects a bare
# source-tree path in SDKlib's public interface. So hand the root to the test
# target directly instead of leaking it through SDKlib's export interface.
if (TARGET test_integration)
    target_include_directories(test_integration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

target_sources(SDKlib PRIVATE utility.cpp)

add_subdirectory(mega)
#add_subdirectory(testing)
