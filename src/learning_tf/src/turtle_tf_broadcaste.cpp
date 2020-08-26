#include<ros/ros.h>
#include<turtlesim/Pose.h>
#include<tf/transform_broadcaster.h>

std::string turtle_name;
void poseCallback(const turtlesim::PoseConstPtr& msg) {
    static tf::TransformBroadcaster br;  // 创建tf广播器

    // 初始化tf数据
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(msg->x,msg->y,0.0));
    tf::Quaternion q;
    q.setRPY(0,0,msg->theta);
    transform.setRotation(q);

    //广播world和turtle坐标系之间的TF数据
    br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"world",turtle_name));

}
int main(int argc,char** argv) {
    ros::init(argc,argv,"my_tf_broadcaster");
    if(argc != 2) {
        ROS_INFO("need a turtle_name as argument ");
        return -1;
    }
    turtle_name = argv[1];
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe(turtle_name+"/pose",10,&poseCallback);
    
    ros::spin();
    return 0;

}
