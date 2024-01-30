add_executable(DesktopExample Desk.cpp)
target_link_directories(DesktopExample PRIVATE ${SDK_LIBRARY_DIR})
target_link_libraries(DesktopExample PRIVATE ${SDK_LIBRARIES} X11)
