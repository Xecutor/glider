#include <stdio.h>

#include "Managed.hpp"

using namespace glider;

class Sample : public Managed {
public:
  using Ref = ReferenceTmpl<Sample>;
  Sample() {
    printf("hello!\n");
  }
  void foo() {
    printf("foo!\n");
  }
  ~Sample() {
    printf("bye!\n");
  }
};

class SampleChild : public Sample {
  using Ref = ReferenceTmpl<SampleChild>;
};

class SampleGrandChild : public Sample {
  using Ref = ReferenceTmpl<SampleGrandChild>;
};

void foo(Sample::Ref obj) {
  obj->foo();
}

int main() {
  WeakReferenceTmpl<Sample> wr;
  {
    auto sample = MakeRef<Sample>();
    wr = sample.getWeak();
    sample->foo();
    auto sample2 = wr.lock();
    if (sample2.isAssigned()) {
      printf("ook!\n");
      sample2->foo();
    }
  }
  auto sample3 = wr.lock();
  if (sample3.isAssigned()) {
    printf(":(\n");
  }
  printf("done\n");
  auto obj = MakeRef<SampleGrandChild>();
  foo(obj);
}
