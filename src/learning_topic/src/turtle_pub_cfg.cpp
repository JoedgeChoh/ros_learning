#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include <dynamic_reconfigure/server.h>
#include <learning_topic/VelocityConfig.h>
void callback(learning_topic::VelocityConfig &config, uint32_t tevel) 
{  
    ROS_INFO("linea=%f,angle=%f",config.linear,config.angle);
    int linear_old,angle
    ros::NodeHandle n;
    ros::Publisher turtle_vel_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",10);
    
    ros::Rate loop_rate(10);

    while(ros::ok()) {
      geometry_msgs::Twist vel_msg;
      vel_msg.linear.x = config.linear;
      vel_msg.angular.z = config.angle;

      turtle_vel_pub.publish(vel_msg);
      ROS_INFO("Publish turtle velocity command[%0.2f m/s,%0.2f rad/s]",vel_msg.linear.x,vel_msg.angular.z);
      loop_rate.sleep();
    }
}

int main(int argc,char** argv) {
    ros::init(argc,argv,"velocity_publisher");
    // ros::NodeHandle n;
    // ros::Publisher turtle_vel_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",10);
    //创建了一个参数动态配置的服务端实例，参数配置的类型就是配置文件中描述的类型
	//该服务端实例会监听客户端的参数配置请求。
	  dynamic_reconfigure::Server<learning_topic::VelocityConfig> server;
	  dynamic_reconfigure::Server<learning_topic::VelocityConfig>::CallbackType f;
	//并将回调函数和服务端绑定
	  f = boost::bind(&callback, _1, _2);
	  server.setCallback(f);
	  ROS_INFO("Spinning node");
	  ros::spin();



    // ros::Rate loop_rate(0.5);

    // int count = 0;
    // while(ros::ok()) {
    //     geometry_msgs::Twist vel_msg;
    //     vel_msg.linear.x = 0.5;
    //     vel_msg.angular.z = 0.2;

    //     turtle_vel_pub.publish(vel_msg);
    //     ROS_INFO("Publish turtle velocity command[%0.2f m/s,%0.2f rad/s]",vel_msg.linear.x,vel_msg.angular.z);
    //     loop_rate.sleep();
    // }
    return 0;
}
