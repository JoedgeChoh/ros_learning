# README

> Description: describe the usage of ros plugin 

1. pluginlib 的工作原理：

   把插件比作派生类，则应用程序包含该插件的基类。

   插件通过应用程序暴露的API(特定的函数)访问应用程序的资源(基类)和原生功能(用户编写的程序)，插件的开发需满足应用程序的各项约定。例如，如果应用程序是一个屋子，则插件可以表示为各种电器，用于加载插件的函数(应用程序暴露的API)可以表示为插座，各种电器的功能开发需要满足规定的用电标准(应用程序中基类的派生)。

2. plugin的实现：

   创建基类Duck以及两个派生子类SimpleDuck和HappyDuck。

3. 插件的注册：

   现在需要通过ROS的各种基础设施和pluginlib的框架约定注册插件。首先，我们分别为两个插件创建一个cpp的源文件，命名为simple_duck.cpp和happy_duck.cpp：

   并分别写入如下内容。在第一行中，我们引入了头文件<pluginlib/class_list_macros.h>，这样就可以在文件的最后使用宏PLUGINLIB_EXPORT_CLASS声明。 这个宏有两个参数，第一个是插件的类，第二个则是基类

   ```c++
   #include<pluginlib/class_list_macros.h>
   #include<learning_plugin/simple_duck.h>
   #include<learning_plugin/duck.h>
   
   PLUGINLIB_EXPORT_CLASS(learning_plugin::SimpleDuck,learning_plugin::Duck)
   ```

   修改learning_plugin的CMakeLists.txt文件，添加如下内容告知ROS的编译系统将simple_duck.cpp和happy_duck.cpp编译成为两个动态链接库。

   catkin_make编译插件