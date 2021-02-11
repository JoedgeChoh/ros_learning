# ros_learning

## description

> ros的学习记录,之后将逐渐完善! [链接](https://blog.csdn.net/allenhsu6/article/list/1  )

## 盲点

###### 加快克隆速度 

git clone -b develop https://github.com.`cnpmjs.org`/JoedgeChoh/ros_learning.git

###### ROS_INFO:  

1. ROS_INFO_STREAM(“Hello ROS”),输出字符串  
2. ROS_INFO(“s%”, msg.data.c_str()),输出一个字符串变量  
3. ROS_INFO(“I heard: [s%]”, msg.data.c_str()),输出一个字符串变量，这里的中括号不是必须的，输出时会直接显示这个中括号  
4. ROS_INFO(“I heard: [s%]”, msg->data.c_str()),输出一个指针变量  
5. ROS_INFO(“Publish Person Info: name:%s age:%d sex:%d”,person_msg.name.c_str(), person_msg.age, person_msg.sex)，按数据类型输出