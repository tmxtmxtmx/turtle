#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/twist.hpp"
using namespace std::chrono_literals;
class TurtleFrameBroadcaster : public rclcpp::Node
{
public:
  TurtleFrameBroadcaster(): Node("tf_dyna_broadcaster_node_cpp")
  {
    this->declare_parameter("turtle","turtle1");
    turtle = this->get_parameter("turtle").as_string();
    broadcaster_ =std::make_shared<tf2_ros::TransformBroadcaster>(this);
    pose_sub_ = this->create_subscription<turtlesim::msg::Pose>("/" + turtle + "/pose",10,
    std::bind(&TurtleFrameBroadcaster::do_pose,this,std::placeholders::_1)
    );
      
  }
private:
  std::string turtle;
  // 根据订阅到的乌龟位姿生成坐标帧并广播。
  void do_pose(const turtlesim::msg::Pose & pose)
  {
    // 组织消息
    geometry_msgs::msg::TransformStamped ts;

    ts.header.stamp = this->now();
    ts.header.frame_id = "world";
    ts.child_frame_id = turtle;

    ts.transform.translation.x = pose.x;
    ts.transform.translation.y = pose.y;
    ts.transform.translation.z = 0.0;

    tf2::Quaternion qtn;
    qtn.setRPY(0, 0, pose.theta);
    ts.transform.rotation.x = qtn.x();
    ts.transform.rotation.y = qtn.y();
    ts.transform.rotation.z = qtn.z();
    ts.transform.rotation.w = qtn.w();
    // 发布消息
    broadcaster_->sendTransform(ts);
    //避免撞墙
      if( ts.transform.translation.x < 2 || ts.transform.translation.x > 10 ||   ts.transform.translation.y < 2 || ts.transform.translation.y > 10 )  
        {cmd_run_ = this->create_publisher<geometry_msgs::msg::Twist>("/" + turtle + "/cmd_vel",100);
      geometry_msgs::msg::Twist twist;
      twist.linear.x = -1;
    
      cmd_run_->publish(twist);

      
        }
  }
  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_sub_;
  std::shared_ptr<tf2_ros::TransformBroadcaster> broadcaster_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_run_;
};

int main(int argc, char * argv[])
{
  
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TurtleFrameBroadcaster>());
  rclcpp::shutdown();
  return 0;
}