cmake_minimum_required(VERSION 3.10)

project(Fastlim VERSION 2.0)

# set the output destination
set(LHPC_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/external/LesHouchesParserClasses_CPP/LHPC/lib/libLHPC.a)


# create a custom target called build_LHPC that is part of ALL
# and will run each time you type make 
add_custom_target(build_LHPC ALL 
                   COMMAND ${CMAKE_MAKE_PROGRAM}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/LesHouchesParserClasses_CPP/LHPC
                   COMMENT "Building LesHouchesParserClasses library" )


# now create an imported static target
add_library(LHPC STATIC IMPORTED)
# Import target "LHPC" for configuration ""
set_property(TARGET LHPC APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(LHPC PROPERTIES IMPORTED_LOCATION_NOCONFIG "${LHPC_LIBRARY}")

# now you can use LHPC as if it were a regular cmake built target in your project
add_dependencies(LHPC build_LHPC)

add_executable(fastlim++ src/main.cpp )
target_link_libraries(fastlim++ LHPC)

set_property(
        TARGET fastlim++
        APPEND
        PROPERTY ADDITIONAL_CLEAN_FILES ${LHPC_LIBRARY} "${PROJECT_SOURCE_DIR}/bin/fastlim++"
)


configure_file(FastlimConfig.h.in FastlimConfig.h)

target_include_directories(fastlim++ PUBLIC 
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/include"
                           "${PROJECT_SOURCE_DIR}/external/LesHouchesParserClasses_CPP/LHPC/include"
                           )

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# installation procedure
install(TARGETS fastlim++ DESTINATION "${PROJECT_SOURCE_DIR}/bin")
