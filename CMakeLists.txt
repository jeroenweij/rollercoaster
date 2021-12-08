cmake_minimum_required(VERSION 2.8)

set(TARGET_PLATFORM atmega2560)
#add_compile_definitions(DEBUG)

include(tools/cmake/arduino.cmake)
project(rollercoaster C CXX)

add_subdirectory(node/Software/lib)
add_subdirectory(tools)


add_executable(${CMAKE_PROJECT_NAME}
    src/RollerSketch.cpp
    src/EStatus.h
    src/IBlock.h
    src/Block.h
    src/Block.cpp
    src/Station.h
    src/Station.cpp
    src/Lift.h
    src/Lift.cpp
    src/Transfer.h
    src/Transfer.cpp
    src/BrakeRun.h
    src/BrakeRun.cpp
    src/Rollercoaster.h
    src/Rollercoaster.cpp
    src/IoInput.h
    src/IoInput.cpp
    src/IoOutput.h
    src/IoOutput.cpp
    src/IoConfig.h
    src/IoConfig.cpp
    src/TrackSwitch.h
    src/TrackSwitch.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/rollercoaster
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    NodeLib
    libtools
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SUFFIX ".elf")
