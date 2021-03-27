#ifndef DUCK_H
#define DUCK_H

#include<string>
namespace learning_plugin {
  class Duck {
  public:
    virtual void initialize(std::string const &name)=0;//声明纯虚函数，表示此函数一定未被实现，其派生类继承时一定要重新定义
    virtual std::string const & get_name(void) const { return mName; }
    virtual std::string const & get_type(void) const { return mType; }
    virtual ~Duck() {}
  protected:
    Duck() {}
  protected:
    std::string mName;
    std::string mType;
  };
};
#endif
