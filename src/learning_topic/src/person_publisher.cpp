//topic name "/person_info",style:"learning_topic/Person"
#include<ros/ros.h>
#include "learning_topic/Person.h"

int main(int argc,char** argv) {
    ros::init(argc,argv,"person_publisher");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<learning_topic::Person>("/person_info",10);
    ros::Rate loop_rate(10);
    int count = 0;
    while(ros::ok) {
        learning_topic::Person person;
        person.name = "zhuhe";
        person.age = 28;
        person.sex = learning_topic::Person::male;

        pub.publish(person);

        ROS_INFO("publish person info: name:%s,age:%d,sex:%d",
                person.name.c_str(),person.age,person.sex);
        loop_rate.sleep();
    }

    return 0;
} 
