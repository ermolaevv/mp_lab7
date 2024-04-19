set(target ${nameBaseProj})

file(GLOB hdrs "*.h*" "../include/*.h*")
file(GLOB srcs "*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} ${LIBRARY_DEPS})
set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${target} PROPERTIES FOLDER ${proj_folder}/${nameBaseProj})

