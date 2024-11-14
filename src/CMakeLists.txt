project(CubeEngineSrc)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

option(CUBEENGINE_BUILD_WINDOWS_VCPKG ON)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenAL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)

if (NOT APPLE)
    find_package(EnTT REQUIRED)
endif ()

if (WIN32)
    if (CUBEENGINE_BUILD_WINDOWS_VCPKG)
        set(LUA_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/packages/luajit_x64-windows/lib/lua51.lib")
        set(LUA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/packages/luajit_x64-windows/include/luajit")
        find_package(glfw3 REQUIRED)
        find_package(glm REQUIRED)
        find_package(vorbis REQUIRED)
        find_package(yaml-cpp REQUIRED)
        set(YAMLCPPLIB yaml-cpp::yaml-cpp)
        set(VORBISLIB Vorbis::vorbis Vorbis::vorbisfile)
    else ()
        find_package(Lua REQUIRED)
        find_package(yaml-cpp REQUIRED)
        set(YAMLCPPLIB yaml-cpp::yaml-cpp)
        set(VORBISLIB vorbis vorbisfile) # not tested
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw)
    endif ()

elseif (APPLE)
    find_package(PkgConfig)
    find_package(yaml-cpp REQUIRED)
    set(YAMLCPPLIB yaml-cpp::yaml-cpp)
    pkg_check_modules(LUAJIT REQUIRED luajit)
    pkg_check_modules(VORBIS REQUIRED vorbis vorbisfile)

    set(LUA_INCLUDE_DIR "/opt/homebrew/include/luajit-2.1")
    set(LUA_LIBRARIES "/opt/homebrew/lib/libluajit-5.1.a")
    message(STATUS "LUA Libraries: ${LUA_LIBRARIES}")
    message(STATUS "LUA Include Dir: ${LUA_INCLUDE_DIR}")

    set(VORBISLIB ${VORBIS_LDFLAGS})
    message(STATUS "Vorbis Lib: ${VORBIS_LDFLAGS}")

else ()
    find_package(PkgConfig)
    find_package(yaml-cpp)
    set(YAMLCPPLIB yaml-cpp::yaml-cpp)
    pkg_check_modules(LUAJIT REQUIRED luajit)
    pkg_check_modules(VORBIS REQUIRED vorbis vorbisfile)
    set(LUA_LIBRARIES ${LUAJIT_LIBRARIES})
    set(LUA_INCLUDE_DIR ${LUAJIT_INCLUDE_DIRS})
    set(VORBISLIB ${VORBIS_LDFLAGS})
endif ()

set(LIBS "")

if (UNIX)
    find_package(yaml-cpp REQUIRED)
    set(YAMLCPPLIB yaml-cpp::yaml-cpp)
    find_package(glfw3 3.3 REQUIRED)
    find_package(Threads REQUIRED)
    set(LIBS ${LIBS} Threads::Threads)
endif ()

if (UNIX AND NOT APPLE AND NOT WIN32 AND NOT WIN64)
    find_package(yaml-cpp REQUIRED PATHS "/usr/lib/x86_64-linux-gnu/cmake/yaml-cpp")
    set(YAMLCPPLIB yaml-cpp)
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${LUA_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} ${LIBS} glfw OpenGL::GL ${OPENAL_LIBRARY} GLEW::GLEW ZLIB::ZLIB PNG::PNG ${YAMLCPPLIB} ${VORBISLIB} ${LUA_LIBRARIES} ${CMAKE_DL_LIBS})