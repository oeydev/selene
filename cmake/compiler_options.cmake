if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")

    set(SELENE_COMPILER_OPTIONS -Wall -Wextra -Wpedantic)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(SELENE_IMG_COMPILER_OPTIONS -Wno-clobbered)
        set(SELENE_TEST_COMPILER_OPTIONS -Wno-unused-but-set-variable)
    endif()

    set(SELENE_COMPILER_DEFINITIONS "")

    # This is a bad, but seemingly required hack for GCC (and Clang using libstdc++).
    # See also the discussion here: https://gitlab.kitware.com/cmake/cmake/issues/17834
    # TODO: What to do with Clang/libc++?
    set(SELENE_LINK_LIBRARY_FILESYSTEM "stdc++fs")

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    set(SELENE_COMPILER_OPTIONS /MP /permissive- /wd4324 /wd4611)
    if (NOT "${CMAKE_GENERATOR}" MATCHES "NMake")
        string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
        string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        set(SELENE_COMPILER_OPTIONS ${SELENE_COMPILER_OPTIONS} /W4)
    endif()

    set(SELENE_COMPILER_DEFINITIONS _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE)

    set(SELENE_LINK_LIBRARY_FILESYSTEM "")

endif()