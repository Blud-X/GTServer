project(GrowtopiaServer LANGUAGES CXX)

file(GLOB INCLUDE_FILES
    *.h
    **/*.h
    **/**/*.h
    **/**/**/*.h
    **/**/**/**/*.h)
file(GLOB SOURCE_FILES
    *.cpp
    **/*.cpp
    **/**/*.cpp
    **/**/**/*.cpp
    **/**/**/**/*.cpp)
add_executable(${PROJECT_NAME}
    ${INCLUDE_FILES}
    ${SOURCE_FILES}
)

if (MSVC)
    add_definitions(/EHsc)
else ()
    add_definitions(-fexceptions)
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 11
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    FMT_HEADER_ONLY
    WIN32_LEAN_AND_MEAN
    _WINSOCK_DEPRECATED_NO_WARNINGS
    CPPHTTPLIB_OPENSSL_SUPPORT
)
set(CMAKE_BUILD_TYPE Debug)

if (CONAN_EXPORTED)
    include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else ()
    include(${CMAKE_CURRENT_SOURCE_DIR}/conan.cmake)
    conan_cmake_configure(REQUIRES
            fmt/10.1.0
            magic_enum/0.8.1
            cpp-httplib/0.18.1
        GENERATORS CMakeDeps CMakeToolchain
        IMPORTS "bin, *.dll -> ./bin"
        OPTIONS
            fmt/*:shared=True)

    conan_cmake_autodetect(settings)
    conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conancenter)
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")
set(DEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../bin")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}" ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_BINARY_DIR}" ${CMAKE_PREFIX_PATH})
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

find_package(fmt REQUIRED)
if (fmt_FOUND)
    message(STATUS "Found fmt: ${fmt_VERSION}, at ${fmt_INCLUDE_DIRS}, ${fmt_LIBRARIES}")
    target_include_directories(${PROJECT_NAME} PUBLIC ${fmt_INCLUDE_DIRS})
else ()
    message(FATAL_ERROR "Could not find fmt")
endif ()

find_package(httplib REQUIRED)
if (httplib_FOUND)
    message(STATUS "Found httplib: ${httplib_VERSION}, at ${httplib_INCLUDE_DIRS}, ${httplib_LIBRARIES}")
    target_include_directories(${PROJECT_NAME} PUBLIC ${httplib_INCLUDE_DIRS})
else ()
    message(FATAL_ERROR "Could not find fmt")
endif ()

find_package(magic_enum REQUIRED)
if (magic_enum_FOUND)
    message(STATUS "Found magic_enum: ${magic_enum_VERSION}, at ${magic_enum_INCLUDE_DIRS}, ${magic_enum_LIBRARIES}")
    target_include_directories(${PROJECT_NAME} PUBLIC ${magic_enum_INCLUDE_DIRS})
else ()
    message(FATAL_ERROR "Could not find magic_enum")
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/enet/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    enet
    fmt::fmt
    magic_enum::magic_enum
    httplib::httplib
)

