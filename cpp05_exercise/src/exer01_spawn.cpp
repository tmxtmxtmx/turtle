#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "stdlib.h"
#include "time.h"
using namespace std::chrono_literals;


class TurtleSpawnClient: public rclcpp::Node{
  public:
    TurtleSpawnClient():Node("exer01_spawn_node_cpp"){
      // 声明，获取随机参数
      srand(time(0));
      this->declare_parameter("x",rand()%7*0.1+rand()%7+2);
      this->declare_parameter("y",rand()%7*0.1+rand()%7+2);
      this->declare_parameter("theta",0.0);
      this->declare_parameter("turtle_name","turtle2");
      x = this->get_parameter("x").as_double();
      y = this->get_parameter("y").as_double();
      theta = this->get_parameter("theta").as_double();
      turtle_name = this->get_parameter("turtle_name").as_string();
      // 创建客户端；
      spawn_client_ = this->create_client<turtlesim::srv::Spawn>("/spawn");
    }
     // 等待服务连接；
    bool connect_server(){
      while (!spawn_client_->wait_for_service(1s))
      {
        if (!rclcpp::ok())
        {
          RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"客户端退出！");
          return false;
        }

        RCLCPP_INFO(this->get_logger(),"服务连接中，请稍候...");
      }
      return true;
    }
    rclcpp::Client<turtlesim::srv::Spawn>::FutureAndRequestId request(){

        auto req = std::make_shared<turtlesim::srv::Spawn::Request>();
        req->x=x;
        req->y=y;
        req->theta=theta;
        req->name=turtle_name;
        return spawn_client_->async_send_request(req);

    }
   
  private:
    rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spawn_client_;
    double_t x,y,theta;
    std::string turtle_name;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);
  auto client = std::make_shared<TurtleSpawnClient>();
  bool flag = client->connect_server();
  if (!flag)
  {
    RCLCPP_INFO(client->get_logger(),"服务连接失败!");
    return 0;
  }
 
  auto response = client->request();

  // 防止小乌龟重命名
  if (rclcpp::spin_until_future_complete(client,response) == rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(client->get_logger(),"请求正常处理");
    std::string name = response.get()->name;
    if (name.empty())
    {
        RCLCPP_INFO(client->get_logger(),"乌龟重名导致生成失败！");
    } else {
        RCLCPP_INFO(client->get_logger(),"乌龟生成成功！");
    }

  } 
  else {
    RCLCPP_INFO(client->get_logger(),"请求异常");
  }
  rclcpp::shutdown();
  return 0;
}














