from launch import LaunchDescription
from launch_ros.actions import Node
# 封装终端指令相关类--------------
# from launch.actions import ExecuteProcess
# from launch.substitutions import FindExecutable
# 参数声明与获取-----------------
# from launch.actions import DeclareLaunchArgument
# from launch.substitutions import LaunchConfiguration
# 文件包含相关-------------------
# from launch.actions import IncludeLaunchDescription
# from launch.launch_description_sources import PythonLaunchDescriptionSource
# 分组相关----------------------
# from launch_ros.actions import PushRosNamespace
# from launch.actions import GroupAction
# 事件相关----------------------
# from launch.event_handlers import OnProcessStart, OnProcessExit
# from launch.actions import ExecuteProcess, RegisterEventHandler,LogInfo
# 获取功能包下share目录路径-------
# from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    
    # 启动 turtlesim_node 节点
    turtle = Node(package="turtlesim", executable="turtlesim_node")
    # 生成一只新乌龟
    spawn = Node(package="cpp05_exercise", executable="exer01_spawn",
                parameters=[{"turtle_name":"t2"}]
    )
    # tf 广播
    broadcaster1 = Node(package="cpp05_exercise",executable="exer02_tf_broadcaster",
                            name="broa1")
    broadcaster2 = Node(package="cpp05_exercise",executable="exer02_tf_broadcaster",
                            name="broa2",
                            parameters=[{"turtle":"t2"}]) #广播不起来
    # tf 监听
    listener = Node(package="cpp05_exercise",executable="exer03_tf_listener",
                            parameters=[{"father_frame":"turtle1","child_frame":"t2"}]
                            )
    # 随机乱跑
    run = Node(package="cpp05_exercise",executable="exer04_run",)
    # 重置
    reset = Node(package="cpp05_exercise", executable="exer05_reset")
    return LaunchDescription([turtle,spawn,broadcaster1,broadcaster2,listener,run,reset])
   
