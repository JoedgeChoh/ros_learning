/***************************************************************************
 *
 * Copyright (c) 2020 weicahi.com All Rights Reserved
 *
 **************************************************************************/
 
/**
 * @file multi_thread_listener3.cpp
 * @author zhuhe(zhuhe@weichai.com)
 * @date 2020/07/23 17:53:11
 * @version $Revision$
 * @brief
 *
 **/


    #include "ros/ros.h"
    #include "ros/callback_queue.h"
    #include "std_msgs/String.h"
     
    #include <boost/thread.hpp> 
    /**
     * tutorial demonstrates the use of custom separate callback queues that can be processed
     * independently, whether in different threads or just at different times. 
     * 演示了自定义独立回调队列的使用，
     * 这些回调队列可以在不同的线程中独立处理，也可以在不同的时间进行处理。
     */
     
    void chatterCallbackMainQueue(const std_msgs::String::ConstPtr& msg)
    {
      ROS_INFO_STREAM("I heard: [ " << msg->data << "] in thread [" << boost::this_thread::get_id() << "] (Main thread)");
    }
     
    //主线程中的调用
    void chatterCallbackCustomQueue(const std_msgs::String::ConstPtr& msg)
    {
      ROS_INFO_STREAM("I heard: [ " << msg->data << "] in thread [" 
            << boost::this_thread::get_id() << "]");
    }
     
    /** 
     * The custom queue used for one of the subscription callbacks
     */
    ros::CallbackQueue g_queue; //第一步:用于订阅回调的自定义队列   

    void callbackThread()
    {
      ROS_INFO_STREAM("Callback thread id=" << boost::this_thread::get_id());
     
      ros::NodeHandle n;
      while (n.ok())
      {
        //第四步: 执行自定义队列中的回调函数. 
            // CallbackQueue类有两种调用内部回调的方法:callAvailable()和callOne()。
            // callAvailable()将获取队列中当前的所有内容并调用它们。callOne()将简单地调用队列上最古老的回调。
        g_queue.callAvailable(ros::WallDuration(0.5));  
        //g_queue.callOne(ros::WallDuration(0.01));  
      }
    }
     
    int main(int argc, char **argv)
    {
      ros::init(argc, argv, "listener_with_custom_callback_processing");
      ros::NodeHandle n;
     
      /**
       * SubscribeOptions结构允许您指定用于特定订阅的自定义队列
       * 还可以使用NodeHandle::setCallbackQueue()函数在节点句柄上设置默认队列
       *
       * 对于话题发布者, 有 AdvertiseOptions 和 AdvertiseServiceOptions  可以使用
       */
      //第二步: 声明订阅或者发布选项, 然后和订阅器/发布器绑定在一起  
      ros::SubscribeOptions ops = ros::SubscribeOptions::create<std_msgs::String>
            ("chatter1", 1000, chatterCallbackCustomQueue, ros::VoidPtr(), &g_queue);
      ros::Subscriber sub = n.subscribe(ops);   
     
      ros::Subscriber sub2 = n.subscribe("chatter1", 1000, chatterCallbackMainQueue);
     
      //第三步: 声明线程.此时主进程与此进程并行进行
      boost::thread chatter_thread(callbackThread); 
      ROS_INFO_STREAM("Main thread id=" << boost::this_thread::get_id());
      //首先是chatter——thread在触发回调，当运行到此处时，spinOnce锁住进程触发sub2主回调，完成后解锁，并有2s的时间缓冲
      //缓冲期间内chatter——thread再次触发回调，直到spinOnce再次锁住a
      ros::Rate r(0.5);
      while (n.ok())
      {
        ros::spinOnce(); 
        r.sleep();
        
      }
      ROS_INFO_STREAM("passing");    
      chatter_thread.join();//锁住主进程，等待chatter——thread完成后，在释放主进程
     
      return 0;
    }






















/* vim: set et ts=4 sw=4 sts=4 tw=100: */
