#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/twist.hpp"
#include "base_interfaces_demo/msg/distence.hpp"
using namespace std::chrono_literals;
using base_interfaces_demo::msg::Distence;

class TurtleFrameListener : public rclcpp::Node {
public:
  TurtleFrameListener():Node("exer03_tf_listener_node_cpp"){
    // 声明并解析参数；
    this->declare_parameter("father_frame","turtle1");
    this->declare_parameter("child_frame","t2");
    father_frame = this->get_parameter("father_frame").as_string();
    child_frame = this->get_parameter("child_frame").as_string();

    // 创建tf缓存对象指针；
    buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
    // 创建tf监听器；
    listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_);
    cmd_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/" + father_frame + "/cmd_vel",100);
    timer_ = this->create_wall_timer(1s, std::bind(&TurtleFrameListener::on_timer,this));
    publisher_ = this->create_publisher<Distence>("chatter_dis",100);
  }

    private:
  void on_timer(){
    // 3-5.生成 turtle1 的速度指令，并发布。
    try
    {
      auto ts = buffer_->lookupTransform(father_frame,child_frame,tf2::TimePointZero);
      geometry_msgs::msg::Twist twist;
      twist.linear.x = 0.5 * sqrt(pow(ts.transform.translation.x,2) + pow(ts.transform.translation.y,2));
      twist.angular.z = 1.0 * atan2(ts.transform.translation.y,ts.transform.translation.x);
      cmd_pub_->publish(twist);
      auto dis = Distence();
      dis.distence = sqrt(pow(ts.transform.translation.x,2) + pow(ts.transform.translation.y,2));
      publisher_->publish(dis);
      
    }
    catch(const tf2::LookupException& e)
    {
      RCLCPP_INFO(this->get_logger(),"坐标变换异常：%s",e.what());
      return;
    }
    
   
  }
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::shared_ptr<tf2_ros::TransformListener> listener_;
  std::shared_ptr<tf2_ros::Buffer> buffer_;
  std::string father_frame;
  std::string child_frame;
  rclcpp::Publisher<Distence>::SharedPtr publisher_;
};

int main(int argc, char const *argv[])
{
  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<TurtleFrameListener>());
  rclcpp::shutdown();
  return 0;
}