#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
//TutorialsConfig.h为 #3.2 编译过程中自动生成头文件
#include <learning_cfg/TutorialsConfig.h>

  int int_param;
  double double_param;
  const char* str_param,*bool_param;

//定义回调函数，当客户端请求修改参数时，服务端即可跳转到回调函数中进行处理。
//传入值有两个，一个是参数更新的配置值，一个是表示参数修改的掩码
void callback(learning_cfg::TutorialsConfig &config, uint32_t tevel) 
{  
	int_param=config.int_param;
	double_param=config.double_param;
	str_param=config.str_param.c_str();
	bool_param=config.bool_param?"True":"False";

  ROS_INFO("int_param=%d",int_param);
  ROS_INFO("double_param=%f",double_param);
  ROS_INFO("str_param=%s",str_param);
  ROS_INFO("bool_param=%s",bool_param);
  
  // ROS_INFO("Reconfigure Request: %d %f %s %s %d",             
	// 		config.int_param, config.double_param,             
	// 		config.str_param.c_str(),             
	// 		config.bool_param?"True":"False",
	//         config.size);
}

int main(int argc, char **argv)
{  
  	//初始化ROS节点
	ros::init(argc, argv, "dynamic_tutorials");
	//创建了一个参数动态配置的服务端实例，参数配置的类型就是配置文件中描述的类型
	//该服务端实例会监听客户端的参数配置请求。
	dynamic_reconfigure::Server<learning_cfg::TutorialsConfig> server;    
	dynamic_reconfigure::Server<learning_cfg::TutorialsConfig>::CallbackType f;    
	//并将回调函数和服务端绑定
	f = boost::bind(&callback, _1, _2);    
	server.setCallback(f);    
	ROS_INFO("Spinning node");    
	ros::spin();    
	return 0;
}
