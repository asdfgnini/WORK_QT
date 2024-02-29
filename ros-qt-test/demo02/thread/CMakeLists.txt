qt_add_library(worker STATIC
    worker.cpp
    worker.h

)

find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)


target_link_libraries(worker PUBLIC Qt6::Core rclcpp::rclcpp)
target_include_directories(worker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} /opt/ros/galactic/include/)
