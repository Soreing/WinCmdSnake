cmake_minimum_required(VERSION 3.0.0)
project(snake VERSION 0.1.0)

include(CTest)
enable_testing()

set(LEVEL /res/levels/level.bin)
file(GLOB TARGET_SRC "./src/*.cpp" )

add_executable(main ${TARGET_SRC})

add_custom_command(
  TARGET main POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          ${CMAKE_SOURCE_DIR}${LEVEL}
          ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}
          )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
