#include<ros/ros.h>
#include "learning_topic/Person.h"

void personInfoCallback(const learning_topic::Person::ConstPtr& msg) {
    ROS_INFO("person_info: name:%s,age:%d,sex:%d,count:%d",msg->name.c_str(),msg->age,msg->sex,msg->count);
}
int main(int argc, char** argv) {
    ros::init(argc,argv,"person_subsriber");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("person_info",100,personInfoCallback);
    ros::spin();
    return 0;
}
