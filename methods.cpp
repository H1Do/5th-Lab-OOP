#include <iostream>

class A {
public:
  A() { std::cout << "A()" << std::endl; } // Конструктор
  virtual ~A() { std::cout << "~A()" << std::endl; } // Виртуальный деструктор
  void casualMethod() { std::cout << "A::casualMethod()" << std::endl; } // Простой метод
  virtual void virtualMethod() { std::cout << "A::virtualMethod" << std::endl; } // Виртуальный метод
};

class B : public A {
public:
  B() { std::cout << "B()" << std::endl; } // Конструктор
  ~B() { std::cout << "~B()" << std::endl; } // Всё еще виртуальный деструктор
  void casualMethod() { std::cout << "B::casualMethod()" << std::endl; } // Перекрытый метод
  void virtualMethod() override { std::cout << "B::virtualMethod" << std::endl; } // Переопределенный метод
};

int main() {
  std::cout << "Constructors:" << std::endl; // Вызываем конструкторы классов 
  A* first_object = new A(); // A()
  A* second_object = new B(); // A() B()
  B* third_object = new B(); // A() B()

  std::cout << "Common methods:" << std::endl; // Вызываем перекрываемые методы
  first_object->casualMethod(); // A::casualMethod()
  second_object->casualMethod(); // A::casualMethod()
  third_object->casualMethod(); // B::casualMethod()

  std::cout << "Virtual methods:" << std::endl; // Вызываем переопределяемые методы
  first_object->virtualMethod(); // A::virtualMethod()
  second_object->virtualMethod(); // B::virtualMethod()
  third_object->virtualMethod(); // B::virtualMethod()
    
  std::cout << "Destructors:" << std::endl; // Вызываем деструкторы
  delete first_object; // ~A()
  delete second_object; // ~B() ~A()
  delete third_object; // ~B() ~A()

  return 0;
}
