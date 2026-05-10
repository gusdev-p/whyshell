cmake_minimum_required(VERSION 3.10)

project(WhyShell C)
# C set
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# sets
set(NAME "WhyShell" CACHE STRING "name") # Shell name
set(VERSION "1.0.0" CACHE STRING "version") # Shell version
set(DEVS "GusDev" CACHE STRING "devs") # Shell developers
set(PURENAME "whyshell" CACHE STRING "purename") # Shell formatted name

# add the include for headers
include_directories(include)

# the files to be compiled
file(GLOB SOURCES
    src/main.c
    src/modules/*.c
)

# the output
add_executable(whyshell ${SOURCES})

# the flags
target_compile_definitions(whyshell PRIVATE
    __NAME=\"${NAME}\"
    __VERSION=\"${VERSION}\"
    __DEVS=\"${DEVS}\"
    __PURENAME=\"${PURENAME}\"
)

# the linker flags
target_link_libraries(whyshell readline)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(whyshell PRIVATE
        -g
        -fsanitize=address,undefined,leak
    )

    target_link_options(whyshell PRIVATE
        -fsanitize=address,undefined,leak
    )
endif()