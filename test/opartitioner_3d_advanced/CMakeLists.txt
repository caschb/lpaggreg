cmake_minimum_required(VERSION 3.10)

project(opartitioner_3d_advanced)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers)
file(GLOB HEADER_FILES ${HEADER_DIR}/*.h)

include_directories(${HEADER_DIR} ${lpaggreg_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

add_definitions(-D__BUILD_VERSION__="${LPAGGREG_VERSION}")

target_link_libraries(${PROJECT_NAME} lpaggreg)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${LPAGGREG_VERSION} SOVERSION ${LPAGGREG_VERSION_MAJOR})

add_test(NAME OPartitioner COMMAND ${PROJECT_NAME})
