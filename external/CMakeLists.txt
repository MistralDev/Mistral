target_sources(Mistral PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/MicroPather/micropather.cpp")

if(EnableClip AND EnableVisuals)
    target_sources(Mistral PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/clip/src/clip.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/clip/src/image.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/clip/src/clip_x11.cpp")
endif()

target_include_directories(Mistral PRIVATE "${CMAKE_CURRENT_LIST_DIR}/MicroPather")
target_include_directories(Mistral PRIVATE "${CMAKE_CURRENT_LIST_DIR}/TF2_NavFile_Reader")
target_include_directories(Mistral PRIVATE "${CMAKE_CURRENT_LIST_DIR}/clip/includes")
