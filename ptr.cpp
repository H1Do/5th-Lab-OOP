#include <memory>
#include <iostream>

class Base {
private:
  int value;
public:
  Base(int value) : value(value) { std::cout << "Base()" << std::endl; }
  Base(Base& obj) { std::cout << "Base(Base& obj)" << std::endl; }
  ~Base() { std::cout << "~Base()" << std::endl; }
};

int main() {
  Base* obj;
  {
    auto smart_obj = std::make_unique<Base>(5);
    Base* common_obj = new Base(5);
    obj = new Base(5);
    
    // auto new_smartl_obj = smart_obj; Ошибка - мы не можем создать новый указатель на тот же объект
  }
  // smart_obj удалится, а common_obj создаст утечку памяти
  delete obj; // Адресс obj мы не потеряли, так что можем удалить вручную

  {
    auto obj1 = std::make_shared<Base>(5);
    std::cout << obj1.use_count() << std::endl; // 1
    {
      auto obj2 = obj1;
      std::cout << obj1.use_count() << std::endl; // 2
      auto obj3 = obj1;
      std::cout << obj1.use_count() << std::endl; // 3
    }
    std::cout << obj1.use_count() << std::endl; // 1
  }
}