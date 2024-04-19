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

# set(nameMain "Main")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:${nameMain}")

# file(GLOB hdrs "interface/include/*.h*" "interface/src/*.h*")
# file(GLOB srcs "*.cpp" "interface/src/*.cpp")
# file(GLOB resx "interface/include/*.resx")

# add_executable(${PROJECT_NAME} WIN32 ${srcs} ${hdrs} ${resx})
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     VS_DOTNET_REFERENCES "System;System.Data;System.Drawing;System.Windows.Forms;System.Xml"
#     VS_GLOBAL_ROOTNAMESPACE ${PROJECT_NAME}
#     COMMON_LANGUAGE_RUNTIME ""
#     CMAKE_VS_TARGET_FRAMEWORK_VERSION "v4.7.2"
# )
# target_include_directories(${PROJECT_NAME} PRIVATE

# )
