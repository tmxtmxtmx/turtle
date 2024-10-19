cmake_minimum_required(VERSION 3.8)
project(cpp05_exercise)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(base_interfaces_demo REQUIRED)
find_package(std_srvs REQUIRED)

add_executable(exer01_spawn src/exer01_spawn.cpp)
add_executable(exer02_tf_broadcaster src/exer02_tf_broadcaster.cpp)
add_executable(exer03_tf_listener src/exer03_tf_listener.cpp)
add_executable(exer04_run src/exer04_run.cpp)
add_executable(exer05_reset src/exer05_reset.cpp)
add_executable(home01_circle src/home01_circle.cpp)
add_executable(home02_square src/home02_square.cpp)
target_include_directories(exer01_spawn PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>)
target_compile_features(exer01_spawn PUBLIC c_std_99 cxx_std_17)





ament_target_dependencies(
exer01_spawn
"rclcpp"
"tf2"
"tf2_ros"
"geometry_msgs"
"turtlesim"
)

ament_target_dependencies(
exer02_tf_broadcaster
"rclcpp"
"tf2"
"tf2_ros"
"geometry_msgs"
"turtlesim"
)

ament_target_dependencies(
exer03_tf_listener
"rclcpp"
"tf2"
"tf2_ros"
"geometry_msgs"
"turtlesim"
"base_interfaces_demo"
)

ament_target_dependencies(
exer04_run
"rclcpp"
"tf2"
"tf2_ros"
"geometry_msgs"
"turtlesim"
)
ament_target_dependencies(
exer05_reset
"rclcpp"
"tf2"
"tf2_ros"
"geometry_msgs"
"turtlesim"
"base_interfaces_demo"
std_srvs
)
ament_target_dependencies(
home01_circle
"rclcpp"
"tf2"
"tf2_ros"
"geometry_msgs"
"turtlesim"
)
ament_target_dependencies(
home02_square
"rclcpp"
"tf2"
"tf2_ros"
"geometry_msgs"
"turtlesim"
)

install(TARGETS
exer01_spawn
exer02_tf_broadcaster
exer03_tf_listener
exer04_run
exer05_reset
home01_circle
home02_square
DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
