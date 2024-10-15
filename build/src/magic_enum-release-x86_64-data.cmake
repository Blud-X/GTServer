########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(magic_enum_COMPONENT_NAMES "")
if(DEFINED magic_enum_FIND_DEPENDENCY_NAMES)
  list(APPEND magic_enum_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES magic_enum_FIND_DEPENDENCY_NAMES)
else()
  set(magic_enum_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(magic_enum_PACKAGE_FOLDER_RELEASE "C:/Users/agung/.conan2/p/magicf543c72c2856d/p")
set(magic_enum_BUILD_MODULES_PATHS_RELEASE )


set(magic_enum_INCLUDE_DIRS_RELEASE "${magic_enum_PACKAGE_FOLDER_RELEASE}/include")
set(magic_enum_RES_DIRS_RELEASE )
set(magic_enum_DEFINITIONS_RELEASE )
set(magic_enum_SHARED_LINK_FLAGS_RELEASE )
set(magic_enum_EXE_LINK_FLAGS_RELEASE )
set(magic_enum_OBJECTS_RELEASE )
set(magic_enum_COMPILE_DEFINITIONS_RELEASE )
set(magic_enum_COMPILE_OPTIONS_C_RELEASE )
set(magic_enum_COMPILE_OPTIONS_CXX_RELEASE )
set(magic_enum_LIB_DIRS_RELEASE )
set(magic_enum_BIN_DIRS_RELEASE )
set(magic_enum_LIBRARY_TYPE_RELEASE UNKNOWN)
set(magic_enum_IS_HOST_WINDOWS_RELEASE 1)
set(magic_enum_LIBS_RELEASE )
set(magic_enum_SYSTEM_LIBS_RELEASE )
set(magic_enum_FRAMEWORK_DIRS_RELEASE )
set(magic_enum_FRAMEWORKS_RELEASE )
set(magic_enum_BUILD_DIRS_RELEASE )
set(magic_enum_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(magic_enum_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${magic_enum_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${magic_enum_COMPILE_OPTIONS_C_RELEASE}>")
set(magic_enum_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${magic_enum_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${magic_enum_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${magic_enum_EXE_LINK_FLAGS_RELEASE}>")


set(magic_enum_COMPONENTS_RELEASE )