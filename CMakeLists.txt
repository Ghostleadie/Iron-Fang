cmake_minimum_required(VERSION 3.0)
project(IFEngine)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(IFEngine/Vendor/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(IFEngine/Vendor/assimp)

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(IFEngine/Vendor/bullet)

option(freetype-gl_BUILD_TESTS OFF)
option(freetype-gl_BUILD_DEMOS OFF)
add_subdirectory(IFEngine/Vendor/freetype)

add_subdirectory(IFEngine/Vendor/spdlog)

OPTION(ALSOFT_TESTS OFF)
Option(ALSOFT_BUILD_ROUTER ON)
add_subdirectory(IFEngine/Vendor/openal)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(IFEngine/src/Headers/
                    IFEngine/Vendor/assimp/include/
                    IFEngine/Vendor/bullet/src/
                    IFEngine/Vendor/glad/include/
                    IFEngine/Vendor/glfw/include/
                    IFEngine/Vendor/glm/
                    IFEngine/Vendor/stb/
					IFEngine/Vendor/openal/include/
					IFEngine/Vendor/freetype/window/freetype/
					IFEngine/Vendor/spdlog/include/)

file(GLOB VENDORS_SOURCES 			 IFEngine/Vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS			 IFEngine/src/Headers/*.h
									 IFEngine/src/Headers/*.hpp)
file(GLOB PROJECT_HEADERS_AUDIO 	 IFEngine/src/Headers/Audio/*.hpp
									 IFEngine/src/Headers/Audio/*.h)
file(GLOB PROJECT_HEADERS_CORE 		 IFEngine/src/Headers/Core/*.hpp
									 IFEngine/src/Headers/Core/*.h)
file(GLOB PROJECT_HEADERS_GUI 		 IFEngine/src/Headers/GUI/*.hpp
									 IFEngine/src/Headers/GUI/*.h)
file(GLOB PROJECT_HEADERS_PHYSICS 	 IFEngine/src/Headers/Physics/*.hpp
									 IFEngine/src/Headers/Physics/*.h)
file(GLOB PROJECT_HEADERS_COMPONENTS IFEngine/src/Headers/Components/*.hpp
									 IFEngine/src/Headers/Components/*.h)
file(GLOB PROJECT_HEADERS_RENDERING  IFEngine/src/Headers/Rendering/*.hpp
									 IFEngine/src/Headers/Rendering/*.h)
file(GLOB PROJECT_HEADERS_SHADERS 	 IFEngine/src/Headers/Shaders/*.hpp
									 IFEngine/src/Headers/Shaders/*.h)
									 
file(GLOB PROJECT_SOURCES 			 IFEngine/src/Sources/*.cpp)
file(GLOB PROJECT_SOURCES_AUDIO 	 IFEngine/src/Sources/Audio/*.cpp)
file(GLOB PROJECT_SOURCES_CORE 		 IFEngine/src/Sources/Core/*.cpp)
file(GLOB PROJECT_SOURCES_GUI 		 IFEngine/src/Sources/GUI/*.cpp)
file(GLOB PROJECT_SOURCES_PHYSICS 	 IFEngine/src/Sources/Physics/*.cpp)
file(GLOB PROJECT_SOURCES_COMPONENTS IFEngine/src/Sources/Components/*.cpp)
file(GLOB PROJECT_SOURCES_RENDERING  IFEngine/src/Sources/Rendering/*.cpp)
file(GLOB PROJECT_SOURCES_SHADERS 	 IFEngine/src/Sources/Shaders/*.cpp)
file(GLOB PROJECT_SHADERS IFEngine/Shaders/*.comp
                          IFEngine/Shaders/*.frag
                          IFEngine/Shaders/*.geom
                          IFEngine/Shaders/*.vert
						  IFEngine/Shaders/*.glsl)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Headers\\Audio" FILES ${PROJECT_HEADERS_AUDIO})
source_group("Headers\\Core" FILES ${PROJECT_HEADERS_CORE})
source_group("Headers\\GUI" FILES ${PROJECT_HEADERS_GUI})
source_group("Headers\\Physics" FILES ${PROJECT_HEADERS_PHYSICS})
source_group("Headers\\Components" FILES ${PROJECT_HEADERS_COMPONENTS})
source_group("Headers\\Rendering" FILES ${PROJECT_HEADERS_RENDERING})
source_group("Headers\\Shaders" FILES ${PROJECT_HEADERS_SHADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Sources\\Audio" FILES ${PROJECT_SOURCES_AUDIO})
source_group("Sources\\Core" FILES ${PROJECT_SOURCES_CORE})
source_group("Sources\\GUI" FILES ${PROJECT_SOURCES_GUI})
source_group("Sources\\Physics" FILES ${PROJECT_SOURCES_PHYSICS})
source_group("Sources\\Components" FILES ${PROJECT_SOURCES_COMPONENTS})
source_group("Sources\\Rendering" FILES ${PROJECT_SOURCES_RENDERING})
source_group("Sources\\Shaders" FILES ${PROJECT_SOURCES_SHADERS})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME}	${PROJECT_SOURCES} 
								${PROJECT_SOURCES_AUDIO}
								${PROJECT_SOURCES_CORE} ${PROJECT_SOURCES_GUI}
								${PROJECT_SOURCES_PHYSICS} ${PROJECT_SOURCES_COMPONENTS}
								${PROJECT_SOURCES_RENDERING} ${PROJECT_SOURCES_SHADERS}
								${PROJECT_HEADERS}
								${PROJECT_HEADERS_AUDIO} ${PROJECT_HEADERS_CORE}
								${PROJECT_HEADERS_GUI} ${PROJECT_HEADERS_PHYSICS}
								${PROJECT_HEADERS_COMPONENTS} ${PROJECT_HEADERS_RENDERING}
								${PROJECT_HEADERS_SHADERS}
								${PROJECT_SHADERS} ${PROJECT_CONFIGS}
								${VENDORS_SOURCES})
	
target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath
					  spdlog freetype-gl OpenAL)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/IFEngine/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS})
