MACRO( auto_group ProjectDirectory ProjectSources )
    SET( DirectorySources "${ProjectSources}" )
    FOREACH( Source ${DirectorySources} )
        if ("${Source}" MATCHES "(/)+")
	    STRING( REGEX REPLACE "${ProjectDirectory}" "" RelativePath "${Source}" )
	    STRING( REGEX REPLACE "[\\\\/][^\\\\/]*$" "" RelativePath "${RelativePath}" )
	    STRING( REGEX REPLACE "^[\\\\/]" "" RelativePath "${RelativePath}" )
	    STRING( REGEX REPLACE "/" "\\\\\\\\" RelativePath "${RelativePath}" )
	    SOURCE_GROUP( "${RelativePath}" FILES ${Source} )
	else()
	    SOURCE_GROUP( "" FILES ${Source} )
	endif()
    ENDFOREACH( Source )
ENDMACRO( auto_group )

file(GLOB_RECURSE sources_objects Objects/*.h Objects/*.hpp Objects/*.cpp)
file(GLOB_RECURSE sources_engine Engine/*.h Engine/*.hpp Engine/*.cpp)

set(sources
    ${sources}
    ${sources_utils}
    ${sources_objects}
    ${sources_engine}
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Objects
    ${CMAKE_SOURCE_DIR}/Objects/Enemies
    ${CMAKE_SOURCE_DIR}/Objects/Mario
    ${CMAKE_SOURCE_DIR}/Engine
)

auto_group("${CMAKE_CURRENT_SOURCE_DIR}" "${sources}")

# Define our target executable based on the source files above
add_executable(SuperMario ${sources})

# Link our executable to SFML and its dependencies
target_link_libraries(SuperMario
    sfml-audio
    sfml-graphics
    sfml-window
    sfml-system
)
