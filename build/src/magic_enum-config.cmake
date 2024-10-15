########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(magic_enum_FIND_QUIETLY)
    set(magic_enum_MESSAGE_MODE VERBOSE)
else()
    set(magic_enum_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/magic_enumTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${magic_enum_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(magic_enum_VERSION_STRING "0.8.1")
set(magic_enum_INCLUDE_DIRS ${magic_enum_INCLUDE_DIRS_RELEASE} )
set(magic_enum_INCLUDE_DIR ${magic_enum_INCLUDE_DIRS_RELEASE} )
set(magic_enum_LIBRARIES ${magic_enum_LIBRARIES_RELEASE} )
set(magic_enum_DEFINITIONS ${magic_enum_DEFINITIONS_RELEASE} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${magic_enum_BUILD_MODULES_PATHS_RELEASE} )
    message(${magic_enum_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


