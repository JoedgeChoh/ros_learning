# README

## description

> 1. ROS中的参数服务器无法在线动态更新，也就是说如果Listener不主动查询参数值，就无法获知Talker是否已经修改了参数。这就对ROS参数服务器的使用造成了很大的局限，很多场景下我们还是需要动态更新参数的机制，例如参数调试、功能切换等，所以ROS提供了另外一个非常有用的功能包 —— dynamic_reconfigure，实现这种动态配置参数的机制。
> 2. 动态重配置的重点是提供一种标准的方法，将节点的一个子集参数公开给外部重配置。使用客户端程序，例如gui，可以向节点查询一组可动态配置的参数，包括它们的名称、类型、范围，并向用户提供一个自定义接口

代码详解参考[链接](https://blog.csdn.net/weixin_43569276/article/details/102928817?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control)



