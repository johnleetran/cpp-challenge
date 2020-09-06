# Automatically generated by boost-vcpkg-helpers/generate-ports.ps1

include(vcpkg_common_functions)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/container_hash
    REF boost-1.72.0
    SHA512 8e739b2876488a081774a6b70c82430bb5949d5c6f4c6e2c05964adfcebf848f56da007d64fc13189a0e6ef6305d2e50d702f4d87d7908fb0e2c6feccba85c1b
    HEAD_REF master
)

include(${CURRENT_INSTALLED_DIR}/share/boost-vcpkg-helpers/boost-modular-headers.cmake)
boost_modular_headers(SOURCE_PATH ${SOURCE_PATH})
