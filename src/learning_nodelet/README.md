# README

> description: nodelet插件教程

## 一. 创建包

```bash
cd src
catkin_create_pkg nodelet_tutorials roscpp nodelet std_msgs
```

这需要依赖nodelet包，这个包提供了编写ROS Nodelet的api。

## 二. 创建nodelet插件文件

```bash
roscd nodelet_tutorials/include/nodelet_tutorials/
touch nodelet_plugins.h
```

将以下内容复制进去：

```bash
#ifndef NODELET_PLUGINS_H_
#define NODELET_PLUGINS_H_

#include <ros/ros.h>
#include <nodelet/nodelet.h>      // 基类Nodelet所在的头文件。
#include <std_msgs/Float64.h>

namespace nodelet_tutorials
{
class nodeletTalker : public nodelet::Nodelet   //任何nodelet plugin都要继承Nodelet类。
{
public:
  nodeletTalker()
  {}

private:
  virtual void onInit()     //此函数声明部分为固定格式，在nodelet加载此plugin会自动执行此函数。
  {
    ros::NodeHandle& private_nh = getPrivateNodeHandle(); //getPrivateNodeHandle()获取plugin节点名。
    pub_ = private_nh.advertise<std_msgs::Float64>("out", 1,true);
    std_msgs::Float64Ptr output(new std_msgs::Float64());
    output->data = 10;
    NODELET_INFO("publish data %f", output->data);
    pub_.publish(output);    
  }

  ros::Publisher pub_;
};

}

#endif
```

nodelet 本身即是基于plugin，所以其写法与plugin非常类似，只是这里的基类变成Nodelet。需要注意的地方有五点。

1. 需要包含#include <nodelet/nodelet.h>头文件。

2. nodelet 插件类需要继承基类Nodelet。

3. 重写虚函数onInit(), 在其中定义ros句柄，此函数类似于普通节点中的main()函数。

4. 使用getPrivateNodeHandle()函数初始化ros句柄，用于命名其话题以及参数命名空间。

5. 在使用nodelet时，打印语句建议使用nodelet自定义的代替原ROS_INFO()系列。

文件链接：

[https://github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/include/nodelet_tutorials/nodelet_plugins.h](https://link.zhihu.com/?target=https%3A//github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/include/nodelet_tutorials/nodelet_plugins.h)[github.com](https://link.zhihu.com/?target=https%3A//github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/include/nodelet_tutorials/nodelet_plugins.h)

## 三. 创建nodelet plugin源文件

```bash
roscd nodelet_tutorials/src/
touch nodelet_plugins.cpp
```

将以下内容复制进去：

```bash
#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>
#include <nodelet_tutorials/nodelet_plugins.h>

//PLUGINLIB_EXPORT_CLASS()将C++类制作为为ros plugin。
PLUGINLIB_EXPORT_CLASS(nodelet_tutorials::nodeletTalker, nodelet::Nodelet)
```

将C++类注册为ros plugin。

文件链接：

[https://github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/src/nodelet_plugins.cpp](https://link.zhihu.com/?target=https%3A//github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/src/nodelet_plugins.cpp)[github.com](https://link.zhihu.com/?target=https%3A//github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/src/nodelet_plugins.cpp)

## 四. 配置CMakeLists.txt

添加如下

```bash
add_library(${PROJECT_NAME} src/nodelet_plugins.cpp)
```

编译插件库文件。

文件链接：

[https://github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/CMakeLists.txt](https://link.zhihu.com/?target=https%3A//github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/CMakeLists.txt)[github.com](https://link.zhihu.com/?target=https%3A//github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/CMakeLists.txt)

## 五. 创建nodelet 插件描述文件

```bash
cd ..
touch nodelet_description.xml
```

将以下内容复制进去：

```bash
<library path="lib/libnodelet_tutorials">
  <class  name="nodelet_tutorials/nodeletTalker" type="nodelet_tutorials::nodeletTalker"  base_class_type="nodelet::Nodelet">
  <description>nodeletTalker</description>
  </class>
</library>
```

基本上与ros plugin一致，需要注意的时name项，推荐使用包名/类名。

文件链接：

[https://github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/nodelet_description.xml](https://link.zhihu.com/?target=https%3A//github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/nodelet_description.xml)[github.com](https://link.zhihu.com/?target=https%3A//github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/nodelet_description.xml)

## 六. 导出插件

导出插件，即是通过包描述文件package.xml，导出插件描述文件，使得其他节点可以使用本包提供的插件，在package.xml中<export>标签添加如下：

```bash
<nodelet plugin="${prefix}/nodelet_description.xml"/>
```

第一项nodelet，是基类所在的包。

文件链接：

[https://github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/package.xml](https://link.zhihu.com/?target=https%3A//github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/package.xml)[github.com](https://link.zhihu.com/?target=https%3A//github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/package.xml)

## 七. 创建launch文件

```bash
mkdir launch
cd launch
touch nodelet_pub.launch
```

将以下内容复制进去：

```bash
<launch>
  <arg name="manager_name" default="nodelet_manager" />

  <node pkg="nodelet" type="nodelet" name="$(arg manager_name)" args="manager" output="screen" />

  <node pkg="nodelet" type="nodelet" name="nodeletTalker"
        args="load nodelet_tutorials/nodeletTalker $(arg manager_name)" >
  </node>      
</launch>
```

文件链接：

[ahuer2435/ros_program](https://link.zhihu.com/?target=https%3A//github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/launch/nodelet_pub.launch)[github.com](https://link.zhihu.com/?target=https%3A//github.com/ahuer2435/ros_program/blob/master/catkin_ws/src/nodelet_tutorials/launch/nodelet_pub.launch)

## 八. 编译

```bash
catkin_make
```

## 九. 运行

```bash
roslaunch nodelet_tutorials nodelet_pub.launch
```

运行效果如图

![img](data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='1052' height='297'></svg>)

我们可以看到有两个节点，/nodelet_manager是nodelet管理器，用于加载ndelet节点的，/nodeletTalker即是我们自己创建的nodelet节点。其启动方式可以参考launch文件，这里不在累赘。