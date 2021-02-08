#include <ros/ros.h>
#include <ros/param.h>

int main(int argc, char **argv) {
    std::string global_name1("default_global_name"),global_name2("default_global_name"),local_name("default_local_name"), private_name1("default_private_name"),private_name2("default_private_name");

    ros::init(argc, argv, "node_name");
    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");
    if(nh.hasParam("/a_string")) {
      ROS_INFO_STREAM("a_string is in launch");
    }
    /*set local param by nh*/
    nh.setParam("local_nh_set", "local_name");
    if(nh.hasParam("/namespace/local_nh_set")){
        // std::cout << "local_nh_set is ok! " <<std::endl;
        ROS_INFO_STREAM("local_nh_set by nh is ok! ");
        
    }    
    /*set global param by private_nh*/
    nh.setParam("/global_nh_set", "global_name");
    if(nh.hasParam("/global_nh_set")) {
        ROS_INFO_STREAM("/global_nh_set by nh is ok! ");
    }
    
    /* set local param(二者等价) */
    private_nh.setParam("local_pri_nh_set", "pri_local_name");
    if(nh.hasParam("/namespace/node_name/local_pri_nh_set")){
        // std::cout << "local_pri_nh_set is ok! " <<std::endl;
        ROS_INFO_STREAM("local_pri_nh_set by private_nh is ok! ");
    }
    nh.setParam("node_name/local_pri_nh_set", "pri_local_name");
    if(nh.hasParam("/namespace/node_name/local_pri_nh_set")){
        // std::cout << "local_pri_nh_set is ok! " <<std::endl;
        ROS_INFO_STREAM("local_pri_nh_set by nh is ok! ");
    }
    
    
    /*get global param from launch */
    nh.getParam("a_string", global_name1); // global_name="global_value_by_launch"
    nh.getParam("/a_string", global_name2); // global_name="global_value_by_launch"
    
    
    /*get local param from launch */
    std::string local_name_key(nh.getNamespace() + "/node_name" + "/a_string"); // local_name_key="/node_name/a_string"
    nh.param("local_name_key", local_name, local_name); // local_name="default_local_name"
    

    /*get private param from itself*/
    private_nh.param("a_string", private_name1, private_name1); // private_name="local_value_by_launch"
    private_nh.param("/a_string", private_name2, private_name2); // private_name="local_value_by_launch"

    // std::cout << "global_name: " << global_name << std::endl;
    // std::cout << "local_name: " << local_name << std::endl;
    // std::cout << "private_name: " << private_name << std::endl;
    
    ROS_INFO("global_name1(a_string):%s",global_name1.c_str());
    ROS_INFO("global_name2(/a_string):%s",global_name2.c_str());
    ROS_INFO("local_name:%s",local_name.c_str());
    ROS_INFO("private_name1(a_string):%s",private_name1.c_str());
    ROS_INFO("private_name2(/a_string):%s",private_name2.c_str());

    ros::spin();
    return 0;
}
