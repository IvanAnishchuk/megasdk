add_library(glob OBJECT
    glob.h
    glob.c
)

target_include_directories(glob SYSTEM
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# PIC is needed when this object library is linked into a shared SDKlib,
# not only for the Java bindings.
if(ENABLE_JAVA_BINDINGS OR BUILD_SHARED_LIBS)
    set_target_properties(glob PROPERTIES
        POSITION_INDEPENDENT_CODE ON
    )
endif()
