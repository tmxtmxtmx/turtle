#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include "stdlib.h"
#include "time.h"
using namespace std::chrono_literals;
class TurtleRun : public rclcpp::Node {
public:
  TurtleRun():rclcpp::Node("exer04_run_node_cpp"){
    cmd_run_ = this->create_publisher<geometry_msgs::msg::Twist>("/t2/cmd_vel",100);
    timer_ = this->create_wall_timer(1s, std::bind(&TurtleRun::run,this));
   
  }

private:
  // 乌龟2随机运动
  void run(){
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    srand(time(0));
    b=rand()%4;
    a=rand()%4;
    c=b+0.1*a-2;

      geometry_msgs::msg::Twist twist;
      twist.linear.x = 0.5;
      twist.angular.z = c;
      cmd_run_->publish(twist);

  }
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_run_;
  std::string child_frame;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char const *argv[])
{
  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<TurtleRun>());
  rclcpp::shutdown();
  return 0;
}













