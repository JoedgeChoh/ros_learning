#ifndef HAPPY_DUCH_H
#define HAPPY_DUCH_H
#include<learning_plugin/duck.h>

namespace learning_plugin {
  class HappyDuck:public Duck {
    public:
      void initialize(std::string const & name) {
        mName=name;
        mType="HappyDuck";
      }
  };
};

#endif
