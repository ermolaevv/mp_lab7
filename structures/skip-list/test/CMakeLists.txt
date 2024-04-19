file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${test} ${srcs} ${hdrs})
target_link_libraries(${test} ${include} gtest)
set_target_properties(${test} PROPERTIES FOLDER structures/${nameBaseProj})
add_test(${nameBaseProj}_gtest ${CMAKE_BINARY_DIR}/bin/${test})
