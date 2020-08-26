/***************************************************************************
 *
 * Copyright (c) 2020 weicahi.com All Rights Reserved
 *
 **************************************************************************/
 
/**
 * @file turtle_tf_listener.cpp
 * @author zhuhe(zhuhe@weichai.com)
 * @date 2020/04/16 22:53:47
 * @version $Revision$
 * @brief 该例程监听tf数据,并计算发布turtle2 的速度数据
 *
 **/

#include<ros/ros.h>
#include<tf/transform_listener.h>
#include<geometry_msgs/Twist.h>
#include<turtlesim/Spawn.h>

int main(int argc,char** argv) {
    ros::init(argc,argv,"my_tf_listener");
    ros::NodeHandle n;

    //请求产生turtle2
    ros::service::waitForService("/Spawn");
    ros::ServiceClient add_turtle = n.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn srv;
   // srv.x = 2.0;
   // srv.y = 2.0;
   // srv.name = "turtle2";
    add_turtle.call(srv);

    // 创建发布器
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle2/cmd_vel",10);
    // 创建tf监听
    tf::TransformListener listener;

    ros::Rate loop_rate(10);

    while(n.ok()) {
        tf::StampedTransform transform;
        try {
            listener.waitForTransform("/turtle2","/turtle1",ros::Time(0),ros::Duration(3.0));
            listener.lookupTransform("/turtle2","/turtle1",ros::Time(0),transform);
        } catch (tf::TransformException& ex) {
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }
        geometry_msgs::Twist vel_msg;
        vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(),2)+pow(transform.getOrigin().y(),2));
        vel_msg.angular.z = 4.0 * atan2(transform.getOrigin().y(),transform.getOrigin().x());
        pub.publish(vel_msg);
        loop_rate.sleep();
    }
    return 0;
}



















/* vim: set et ts=4 sw=4 sts=4 tw=100: */
