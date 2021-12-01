#*************************************************************
# Created by J. Weij
#************************************************************/

add_executable(${PROJECT_NAME}
    EStatus.h
    NodeIds.h
    Block.h
    Block.cpp
    Station.h
    Station.cpp
    Lift.h
    Lift.cpp
    Transfer.h
    Transfer.cpp
    StorageTrack.h
    StorageTrack.cpp
    Rollercoaster.h
    Rollercoaster.cpp
    main.cpp
    IoInput.h
    IoInput.cpp
    IoOutput.h
    IoOutput.cpp
    Logger.h
    Logger.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    NodeLib
)
