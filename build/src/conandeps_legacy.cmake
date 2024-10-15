message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(fmt)
find_package(magic_enum)

set(CONANDEPS_LEGACY  fmt::fmt  magic_enum::magic_enum )