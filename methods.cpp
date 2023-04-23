#include <iostream>

class A {
public:
  A() { std::cout << "A()" << std::endl; }
  virtual ~A() { std::cout << "~A()" << std::endl; }
  void casualMethod() { std::cout << "A::casualMethod()" << std::endl; }
  virtual void virtualMethod() { std::cout << "A::virtualMethod" << std::endl; }
};

class B : public A {
public:
  B() { std::cout << "B()" << std::endl; }
  ~B() { std::cout << "~B()" << std::endl; }
  void casualMethod() { std::cout << "B::casualMethod()" << std::endl; }
  void virtualMethod() override { std::cout << "B::virtualMethod" << std::endl; }
};

int main() {
  std::cout << "Constructors:" << std::endl;
  A* first_object = new A();
  A* second_object = new B();
  B* third_object = new B();

  std::cout << "Common methods:" << std::endl;
  first_object->casualMethod();
  second_object->casualMethod();
  third_object->casualMethod();

  std::cout << "Virtual methods:" << std::endl;
  first_object->virtualMethod();
  second_object->virtualMethod();
  third_object->virtualMethod();
    
  std::cout << "Destructors:" << std::endl;
  delete first_object;
  delete second_object;
  delete third_object;

  return 0;
}
