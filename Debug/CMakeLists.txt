# NonogramSolver/Debug

set(TARGET_NAME Debug)

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

file(GLOB_RECURSE HEADER_FILES ${HEADER_DIR}/*.h)
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_DIR}/*.cpp)

set(TARGET_FILES ${HEADER_FILES} ${SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES})

add_executable(${TARGET_NAME})
target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES})
target_include_directories(${TARGET_NAME} PRIVATE ${HEADER_DIR})

target_include_directories(${TARGET_NAME} PRIVATE ${ENGINE_DIR})
target_link_libraries(${TARGET_NAME} PRIVATE Engine)
