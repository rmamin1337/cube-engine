file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/usr/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/usr/lib)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/usr/share/icons/hicolor/256x256)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/usr/share/applications)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/usr/share/CubeCore)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/usr/share/CubeCore)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dev/CubeCore.png DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/usr/share/icons/hicolor/256x256)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dev/CubeCore.png DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/AppDir)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dev/CubeCore.png DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/.dirIcon)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dev/CubeCore.desktop DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/usr/share/applications)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dev/CubeCore.desktop DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/usr/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/usr/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/usr/bin)
install(TARGETS CubeEngine DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/AppDir/usr/bin)
