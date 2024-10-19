#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include "tf2_ros/buffer.h"
#include "base_interfaces_demo/msg/distence.hpp"
using namespace std::chrono_literals;
using base_interfaces_demo::msg::Distence;
class TurtleReset: public rclcpp::Node{
  public:
    TurtleReset():Node("exer05_reset_cpp") {
      srand(time(0));
      this->declare_parameter("x",rand()%7*0.1+rand()%7+2);
      this->declare_parameter("y",rand()%7*0.1+rand()%7+2);
      this->declare_parameter("theta",0.0);
      this->declare_parameter("turtle_name","t2");
      x = this->get_parameter("x").as_double();
      y = this->get_parameter("y").as_double();
      theta = this->get_parameter("theta").as_double();
      turtle_name = this->get_parameter("turtle_name").as_string();
      subscription_ = this->create_subscription<Distence>("chatter_dis",100,std::bind(&TurtleReset::do_cb,this,std::placeholders::_1));
    //创建客户端
    kill_client_ = this->create_client<turtlesim::srv::Kill>("/kill");
    spawn_client_ = this->create_client<turtlesim::srv::Spawn>("/spawn");
    setpen_client_ = this->create_client<turtlesim::srv::SetPen>("/t2/set_pen");
    setpen_client_one_= this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
    }
    //乌龟2轨迹清除
    void request_setpen(){
      auto req = std::make_shared<turtlesim::srv::SetPen::Request>();
        req->off=1;
        setpen_client_->async_send_request(req);
       }
    //乌龟1轨迹清除
    void request_setpen_one(){
      auto req = std::make_shared<turtlesim::srv::SetPen::Request>();
        req->off=1;
        setpen_client_one_->async_send_request(req);
       }
    //清除乌龟
    void request_kill(){
      auto req =std::make_shared<turtlesim::srv::Kill::Request>();
        req->name = this->turtle_name;
        kill_client_->async_send_request(req);
       }
    //重置乌龟
    void request_spawn(){
      auto req = std::make_shared<turtlesim::srv::Spawn::Request>();
        req->x=this->x;
        req->y=this->y;
        req->theta=this->theta;
        req->name= this->turtle_name;
        spawn_client_->async_send_request(req);
       }
    private:
    void do_cb(const Distence &dis){
      auto client_=std::make_shared<TurtleReset>();
      //对距离进行判断
      if(dis.distence<1.55){
        client_->request_kill();
        usleep(100000);//感谢学长们帮忙加的延迟器
        client_->request_spawn();
        
      }  
        client_->request_setpen();
        client_->request_setpen_one();
    };
  rclcpp::Subscription<Distence>::SharedPtr subscription_;
  rclcpp::Client<turtlesim::srv::Kill>::SharedPtr kill_client_ ;
  rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr setpen_client_;
  rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr setpen_client_one_;
  rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spawn_client_ ;
   rclcpp::TimerBase::SharedPtr timer_;
  double_t x,y,theta;
  std::string turtle_name;
    };

int main(int argc, char ** argv){
rclcpp::init(argc,argv);
rclcpp::spin(std::make_shared<TurtleReset>());
   rclcpp::shutdown();
  return 0;
}
