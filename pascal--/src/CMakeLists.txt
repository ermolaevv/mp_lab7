set(target ${nameBaseProj})

file(GLOB hdrs "*.h*" "../include/*.h*")
file(GLOB srcs "*.cpp")


include_directories("../../structures/hierarchical-list/include")
include_directories("../../past-labs/table/table/include")
include_directories("../../past-labs/table/vector-table/include")
include_directories("../../past-labs/table/ordered-table/include")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} ${LIBRARY_DEPS})
set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${target} PROPERTIES FOLDER ${nameBaseProj})
