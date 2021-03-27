#include<pluginlib/class_loader.h>
#include<learning_plugin/duck.h>

int main(int argc,char** argv) {
  pluginlib::ClassLoader<learning_plugin::Duck> duck_loader("learning_plugin","learning_plugin::Duck");
  try {
    boost::shared_ptr<learning_plugin::Duck> yellow_duck=duck_loader.createInstance("learning_plugin::SimpleDuck");
    yellow_duck->initialize("YellowDuck");
    
    boost::shared_ptr<learning_plugin::Duck> green_duck=duck_loader.createInstance("learning_plugin::HappyDuck");
    green_duck->initialize("GreenDuck");

    ROS_INFO("%s is a %s",yellow_duck->get_name().c_str(),yellow_duck->get_type().c_str());
    ROS_INFO("%s is a %s",green_duck->get_name().c_str(),green_duck->get_type().c_str());

  } catch(pluginlib::PluginlibException &ex) {
    ROS_ERROR("failed to load plugin. Error:%s",ex.what());
  }
  return 0;
}
