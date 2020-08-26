/***************************************************************************
 *
 * Copyright (c) 2020 weicahi.com All Rights Reserved
 *
 **************************************************************************/
 
/**
 * @file turtle_tf_listener.cpp.cpp
 * @author zhuhe(zhuhe@weichai.com)
 * @date 2020/04/17 22:22:12
 * @version $Revision$
 * @brief
 *
 **/

#include<ros/ros.h>
#include<turtlesim/Spawn.h>
#include<tf/transform_listener.h>
#include<geometry_msgs/Twist.h>

int main(int argc, char** argv) {
    ros::init(argc,argv,"tf_transform_listener");
    ros::NodeHandle n;

    ros::service::waitForService("/spawn");
    ros::ServiceClient add_turtle = n.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn srv;
    add_turtle.call(srv);

    ros::Publish pub = n.advertise<geometry_msgs::Twist>("turtle2/cmd_vel",10);
    ros::Rate rate(10);

    while(n.ok()) {
        tf::StampedTransform transform;
        try {
            listener.waitForTransform("turtle2","turtle1",ros::Time(0),ros::Duration(3.0));
            listener.lookupTransform("turtle2","turtle1",ros::Time(0),transform);
        } catch (tf::TransformException& ex) {
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }
        geometry_msgs::Twist vel_msgs;
        vel_msgs.angular.z = 4.0 * atan2(transform.getOrigin().y(),transform.getOrigin().x());
        vel_msgslinear.x = 0.5 * sqrt(pow(transform.getOrigin.x(),2)+pow(transform.getOrigin.y(),2));
        pub.publish(vel_msgs);
        rate.sleep();
    }
    return 0;
}



















/* vim: set et ts=4 sw=4 sts=4 tw=100: */
