#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/twist.hpp"
using namespace std::chrono_literals;
class TurtleCircle : public rclcpp::Node {
public:
  TurtleCircle():rclcpp::Node("home01_circle_node_cpp"){

    cmd_run_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",100);//
    timer_ = this->create_wall_timer(1s, std::bind(&TurtleCircle::run,this));
   
  }
// 设置定时器，循环执行回调函数
private:
  void run(){

      geometry_msgs::msg::Twist twist;
      twist.linear.x = 1.5;
      twist.angular.z = 1.56;
      cmd_run_->publish(twist);

  }
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_run_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char const *argv[])
{
  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<TurtleCircle>());
  rclcpp::shutdown();
  return 0;
}












