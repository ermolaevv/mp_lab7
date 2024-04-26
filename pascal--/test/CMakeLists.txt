file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

include_directories("../../structures/hierarchical-list/include")
include_directories("../../past-labs/table/table/include")
include_directories("../../past-labs/table/vector-table/include")
include_directories("../../past-labs/table/ordered-table/include")

add_executable(${test} ${srcs} ${hdrs})
target_link_libraries(${test} ${include} gtest)
set_target_properties(${test} PROPERTIES FOLDER ${nameBaseProj})
add_test(${nameBaseProj}_gtest ${CMAKE_BINARY_DIR}/bin/${test})
