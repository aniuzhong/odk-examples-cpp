add_executable(UrlResolver UrlResolver.cpp)
target_link_directories(UrlResolver PRIVATE ${SDK_LIBRARY_DIR})
target_link_libraries(UrlResolver PRIVATE ${SDK_LIBRARIES})

