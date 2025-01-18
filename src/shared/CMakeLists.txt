
set(lib_shared_target shared_static)

# Generate header files from dia UML files
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../state.dia")
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../engine.dia")
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../ai.dia")
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../server.dia")

# Find all source files to compile into a library
file(GLOB_RECURSE shared_sources *.cpp)

# Build the "shared" library and add required includes
add_library(${lib_shared_target} STATIC ${shared_sources} ${jsoncpp_sources}
        state/Card.cpp
        state/CardsDeck.cpp
        state/GameBoard.cpp
        state/Player.cpp
        state/State.cpp
        engine/ThrowCard.cpp
        engine/CaptureCard.cpp
        engine/CountScore.cpp
        engine/SetUpGame.cpp
        engine/RoundDistributeCards.cpp
        engine/RoundInitDistributeCards.cpp
        engine/Command.cpp
        engine/Engine.cpp

)
add_dependencies(${lib_shared_target} generate-headers)
target_include_directories(${lib_shared_target} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${jsoncpp_include_dir}
  )

# vim: set sw=2 sts=2 et:

