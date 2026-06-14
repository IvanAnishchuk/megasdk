# PUBLIC so the platform root (holding <mega/fuse/platform/platform.h>) reaches
# in-tree consumers such as test_integration. Wrapped in BUILD_INTERFACE so the
# bare source-tree path stays out of the installed export interface:
# install(EXPORT sdklibTargets) rejects a source path in SDKlib's public usage
# requirements.
target_include_directories(SDKlib PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_sources(SDKlib PRIVATE utility.cpp)

add_subdirectory(mega)
