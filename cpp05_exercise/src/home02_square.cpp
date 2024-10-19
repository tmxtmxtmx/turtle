#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/twist.hpp"
using namespace std::chrono_literals;
class TurtleSquare : public rclcpp::Node {
public:
  TurtleSquare():rclcpp::Node("home02_square_node_cpp"){

    cmd_run_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",100);//
    timer_ = this->create_wall_timer(1s, std::bind(&TurtleSquare::run,this));
   
  }
   int a = 0;
private://对a进行累加，到达一定程度直角转弯
  void run(){
      geometry_msgs::msg::Twist twist;
      twist.linear.x = 0.5;
        a++; 
        if(a==6){
            a=0;
      twist.linear.x =0;
      twist.angular.z = 1.5707963;
        }
         cmd_run_->publish(twist);
  }
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_run_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char const *argv[])
{
  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<TurtleSquare>());
  rclcpp::shutdown();
  return 0;
}


















