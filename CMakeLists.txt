cmake_minimum_required(VERSION 2.8...3.13)
set (CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME Pascal--)
project(${PROJECT_NAME})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
set_target_properties(gtest PROPERTIES FOLDER 3rdparty/${nameBaseProj})
set_target_properties(gtest_main PROPERTIES FOLDER 3rdparty/${nameBaseProj})
set_target_properties(gmock PROPERTIES FOLDER 3rdparty/${nameBaseProj})
set_target_properties(gmock_main PROPERTIES FOLDER 3rdparty/${nameBaseProj})

add_subdirectory(past-labs)
add_subdirectory(structures)
add_subdirectory(pascal--)
add_subdirectory(ide)
