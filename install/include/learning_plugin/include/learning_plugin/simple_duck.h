#ifndef SIMPLE_DUCK_H
#define SIMPLE_DUCK_H
#include<learning_plugin/duck.h>

namespace learning_plugin {
  class SimpleDuck: public Duck {
    public:
      void initialize(std::string const & name) {
        mName=name;
        mType="SimpleDuck";
      }
  };
};
#endif
