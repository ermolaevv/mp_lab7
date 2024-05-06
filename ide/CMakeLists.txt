set(target IDE)
set(nameMain "Main")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:${nameMain}")

file(GLOB hdrs "mainForm/include/*.h*" "mainForm/src/*.h*")
file(GLOB srcs "mainForm/src/*.cpp")
file(GLOB resx "mainForm/include/*.resx")

include_directories("mainForm/include")
add_executable(${target} WIN32 ${srcs} ${hdrs} ${resx})
set_target_properties(${target} PROPERTIES
    VS_DOTNET_REFERENCES "System;System.Data;System.Drawing;System.Windows.Forms;System.Xml"
    VS_GLOBAL_ROOTNAMESPACE ${target}
    COMMON_LANGUAGE_RUNTIME ""
    CMAKE_VS_TARGET_FRAMEWORK_VERSION "v4.7.2"
)
target_include_directories(${target} PRIVATE
)
