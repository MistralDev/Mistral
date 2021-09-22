file(GLOB_RECURSE files ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

target_sources(Mistral PRIVATE ${files})
