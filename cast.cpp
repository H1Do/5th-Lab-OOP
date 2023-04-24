#include <iostream>
#include <string>

// Класс сущности (живой или не живой)
class Essence { 
public:
  Essence() { std::cout << "Essence()" << std::endl; }
  ~Essence() { std::cout << "~Essence()" << std::endl; }
  virtual std::string classname() { return "Essence"; }
  virtual bool isA(std::string something) { return something == "Essence"; }
};

// Класс существа (живая сущность)
class Creature : public Essence {
public:
  Creature() { std::cout << "Creature()" << std::endl; }
  ~Creature() { std::cout << "~Creature()" << std::endl; }
  std::string classname() { return "Creature"; }
  bool isA(std::string something) { return something == "Creature" || Essence::isA(something); }
  void breath() { std::cout << "The creature is breathing" << std::endl; }
};

// Класс человека (человеческая живая сущность)
class Human : public Creature {
public:
  Human() { std::cout << "Human()" << std::endl; }
  ~Human() { std::cout << "~Human()" << std::endl; }
  std::string classname() { return "Human"; }
  bool isA(std::string something) { return something == "Human" || Creature::isA(something); }
};

// Класс вещи (не живая сущность)
class Thing : public Essence {
public:
  Thing() { std::cout << "Thing()" << std::endl; }
  ~Thing() { std::cout << "~Thing()" << std::endl; }
  std::string classname() { return "Thing"; }
  bool isA(std::string something) { return something == "isThing" || Essence::isA(something); }
};

int main() {
  Essence* container[9];

  container[0] = new Creature();
  container[3] = new Creature();
  container[6] = new Creature(); std::cout << std::endl;
  container[1] = new Human();
  container[4] = new Human();
  container[7] = new Human(); std::cout << std::endl;
  container[2] = new Thing();
  container[5] = new Thing();
  container[8] = new Thing();

  std::cout << std::endl;
  std::cout << "Unsafe casting:" << std::endl; // Явное приведение типов через указатель на базовый класс - Небезопасно
  std::cout << "classname():" << std::endl; // Проверка на принадлежность с помощью метода classname()

  for (auto i : container)
    if (i->classname() == "Creature")
      ((Creature*)i)->breath(); 

  std::cout << std::endl;
  std::cout << "isA(std::string something):" << std::endl; // Проверка на принадлежность с помощью метода isA()

  for (auto i : container)
    if (i->isA("Creature"))
      ((Creature*)i)->breath(); 

  std::cout << std::endl;
  std::cout << "Safe casting:" << std::endl; // Приведение через dynamic_cast с проверкой на корректность приведения - Безопасно

  for (auto i : container)
    if (dynamic_cast<Creature*>(i) != NULL)
      dynamic_cast<Creature*>(i)->breath();
}