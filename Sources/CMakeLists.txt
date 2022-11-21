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

file(GLOB_RECURSE sources_utils Utils/*.h Utils/*.hpp Utils/*.cpp)
file(GLOB_RECURSE sources_collision_mgr CollisionMgr/*.h CollisionMgr/*.hpp CollisionMgr/*.cpp)
file(GLOB_RECURSE sources_handlers Handlers/*.h Handlers/*.hpp Handlers/*.cpp)
file(GLOB_RECURSE sources_level_mgr LevelMgr/*.h LevelMgr/*.hpp LevelMgr/*.cpp)
file(GLOB_RECURSE sources_units Units/*.h Units/*.hpp Units/*.cpp)
file(GLOB_RECURSE sources_map Map/*.h Map/*.hpp Map/*.cpp)
file(GLOB_RECURSE sources_engine Engine/*.h Engine/*.hpp Engine/*.cpp)

set(sources
    ${sources}
    ${sources_utils}
    ${sources_collision_mgr}
    ${sources_handlers}
    ${sources_level_mgr}
    ${sources_units}
    ${sources_map}
    ${sources_engine}
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Utils
    ${CMAKE_SOURCE_DIR}/Utils/TinyXML
    ${CMAKE_SOURCE_DIR}/CollisionMgr
    ${CMAKE_SOURCE_DIR}/Handlers
    ${CMAKE_SOURCE_DIR}/Handlers/AnimationHandler
    ${CMAKE_SOURCE_DIR}/LevelMgr
    ${CMAKE_SOURCE_DIR}/Units
    ${CMAKE_SOURCE_DIR}/Units/Mario
    ${CMAKE_SOURCE_DIR}/Units/Enemies
    ${CMAKE_SOURCE_DIR}/Units/Enemies/Goomba
    ${CMAKE_SOURCE_DIR}/Map
    ${CMAKE_SOURCE_DIR}/Engine
)

auto_group("${CMAKE_CURRENT_SOURCE_DIR}" "${sources}")
add_executable(SuperMario ${sources})

target_link_libraries(SuperMario
    sfml-audio
    sfml-graphics
    sfml-window
    sfml-system
)
