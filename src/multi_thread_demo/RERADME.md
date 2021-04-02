ros多线程
1.概念：当一个节点订阅两个话题，并且触发两个不同的回调函数（回调队列）时，只有运行到spine时才可以同时触发两个回调函数，只有当两个回调函数都运行完成时，才会再次运行spine，开启第二次回调，所以当两个话题发布包频率不一致或者一个回调函数时间复杂度太高时，可能会导致其他回调函数出现丢包的现象。
  典型的例子：ROS需要接受相机传来的点云，并且检测平面，得到法向量，显示在RViz上，这样需要订阅sensormsgs::point2消息并且注册点云处理函数foo()，由于点云处理函数需要较长时间执行，所以如果没有多线程（是单线程spin），则在接收到一个点云消息数据后，订阅函数会阻塞，会一直执行处理函数，不会接收到下一个点云消息，此时如果没有定义消息接收队列，则点云数据会被丢弃，在RViz显示上也会很卡顿。

2.spin()用法：
  当调用ros::spin时，会有一把互斥锁，将回调队列枷锁(在此期间(0.1s)只执行一次相应的回调函数)，防止执行混乱，然后检测回调队列不为空,最后当while(n.ok())为true时，调用队列所有函数
  与spinOnce的区别：
  spin多用于listen,创建线程，不停读取接受的话题，spinOnce多用于talk中，只运行一次，接着往下走，保证有需要时发布，没有需要时不发布，可设置发布频率。
  spin读取回调队列参数时会有0.1s的等待调用时间，spinOnce没有，所以一般会设置一个接受频率：
  ros::Rate r(10); // 10 hz
  while (should_continue)
  {
    ... do some work, publish some messages, etc. ...
    ros::spinOnce();
    r.sleep();
  }


3.多线程SPINING
  原理：从多个线程来调用回调函数
        根据是否阻塞主调函数线程分为阻塞型(同步)和非阻塞型(异步)
    ros::MultiThreadedSpinner spinner(4); // Use 4 threads
    spinner.spin(); // spin() will not return until the node has been shutdown
    //or
    ros::AsyncSpinner spinner(4); // Use 4 threads
    spinner.start();
    ros::waitForShutdown();
  使用：非常耗时的运算建议放在主线程中
        回调函数建议放简单函数，最多放数据复制函数

thread_ws工作空间中代码详细测试了来嗯中多线程方法，均可保证一个线程数据处理时，另一线程的话题仍可接受

4. 多线程boost_thread
   #include <boost/thread.hpp> 
   #include <iostream> 

   void wait(int seconds) 
   { 
     boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
   } 

   void thread() 
   { 
      for (int i = 0; i < 5; ++i) 
      { 
          wait(1); 
          std::cout << i << std::endl; 
       } 
   } 

   int main() 
   { 
      boost::thread t(thread); 
      t.join(); 
   }
   一旦上述示例中的变量 t 被创建，该 thread()
    函数就在其所在线程中被立即执行。 同时在 main() 里也并发地执行该 thread() 。
   为了防止程序终止，就需要对新建线程调用 join() 方法。 join()
   方法是一个阻塞调用：它可以暂停当前线程，直到调用 join() 的线程运行结束。
   这就使得 main() 函数一直会等待到 thread() 运行结束。


