cmake_minimum_required( VERSION 3.5 )

project( thp )

SET( CMAKE_BUILD_TYPE "Debug" )

set( tools /usr/local/bin )
set( CMAKE_C_COMPILER ${tools}/gcc-12 )
set( CMAKE_CXX_COMPILER ${tools}/g++-12 )

set( CMAKE_C_COMPILER g++ )

SET( CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -pthread -march=native -Wno-unused-variable -Wno-sign-compare -Wno-return-type" )

SET( CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++11 -O3 -Wall -pthread -march=native -Wno-unused-variable -Wno-sign-compare -Wno-return-type" )

add_compile_options( -std=c++11 -lpthread -march=native -Wno-unused-variable -Wno-sign-compare -Wno-return-type )


set( SOURCES
    # src/Hello.cpp
    src/main.cpp
)

#Generate the static library from the library sources
add_library( thp_library STATIC 
    src/Fivecards.cpp
    src/Poker.cpp
)

target_include_directories( thp_library
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)


############################################################
# Create an executable
############################################################

# Add an executable with the above sources
add_executable( thp_binary 
    src/main.cpp
)

# link the new hello_library target with the hello_binary target
target_link_libraries( thp_binary
    PRIVATE 
        thp_library
)
