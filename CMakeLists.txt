cmake_minimum_required(VERSION 3.9)
project(holdfastBalance VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE helloworld_SRC
    "src/*.cpp"
    "src/*.hpp"
)

foreach (file ${helloworld_SRC})
    set(MYFILE_DIR)
    if (file MATCHES ".*.hpp")
        get_filename_component(MYFILE_DIR ${file} DIRECTORY)
        include_directories(${MYFILE_DIR})
    endif()
endforeach()

add_executable(holdfastBalance ${helloworld_SRC})

if (WIN32)
    target_link_libraries(holdfastBalance)
else ()
    target_link_libraries(holdfastBalance)
endif ()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

