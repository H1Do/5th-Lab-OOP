#include <iostream>

class Base {
public:
  Base() { std::cout << "Base()" << std::endl; }
  Base(Base* obj) { std::cout << "Base(Base* obj)" << std::endl; }
  Base(Base& obj) { std::cout << "Base(Base& obj)" << std::endl; }
  virtual ~Base() { std::cout << "~Base()" << std::endl; }
};

class Desc : public Base {
public:
	Desc() { std::cout << "Desc()" << std::endl; }
  Desc(Desc* obj) { std::cout << "Desc(Desc* obj)" << std::endl; }
  Desc(Desc& obj) { std::cout << "Desc(Desc& obj)" << std::endl; }
  ~Desc() { std::cout << "~Desc()" << std::endl; }
};

void func1(Base  obj) { std::cout << "func1(Base obj)" << std::endl; };
void func2(Base *obj) {
  if (dynamic_cast<Desc*>(obj) != NULL)
    Desc* new_obj = dynamic_cast<Desc*>(obj);
  std::cout << "func2(Base *obj)" << std::endl;
};
void func3(Base &obj) { std::cout << "func3(Base &obj)" << std::endl; };

void first_test() {
  std::cout << "Functions that take classes as an argument:" << std::endl;

	{
    std::cout << std::endl << "Constructors:" << std::endl;
		Base obj1;
		Desc obj2;

		std::cout << std::endl << "Passing instances of the class to func1():" << std::endl;
		func1(obj1); // Base(Base& obj) func1(Base obj) ~Base()
		func1(obj2); // Base(Base& obj) func1(Base obj) ~Base()

		std::cout << std::endl << "Passing class references to func3():" << std::endl;
		func3(obj1); // func3(Base &obj)
		func3(obj2); // func3(Base &obj)

    std::cout << std::endl << "Destructors:" << std::endl;
	}

	{
    std::cout << std::endl << "Constructors:" << std::endl;
		Base* obj1 = new Base(); // func2(Base *obj)
		Desc* obj2 = new Desc(); 

		std::cout << std::endl <<  "Passing a pointer to classes in func2():" << std::endl;
		func2(obj1); // func2(Base *obj)
		func2(obj2); // func2(Base *obj)

    std::cout << std::endl << "Destructors:" << std::endl;
    delete obj1; delete obj2;
	}

	{
    std::cout << std::endl << "Passing the reduced class" << std::endl;
    std::cout << std::endl << "Constructors:" << std::endl;
		Base* obj = new Desc();

    std::cout << std::endl << "All functions:" << std::endl;
    func1(*obj);
    func2(obj);
    func3(*obj);

    std::cout << std::endl << "Desctructors:" << std::endl;
    delete obj;
	}
}

Base func1() { 
  std::cout << "Base func1()" << std::endl;
  Base temp;
  // temp.name = "func1() returned Base correct";
  return temp;
};
Base* func2() { 
  std::cout << "Base* func2()" << std::endl; 
  Base temp;
  // temp.name = "func2() returned Base correct";
  return &temp; // Когда мы получим адрес объекта, он уже будет удалён
};
Base& func3() { 
  std::cout << "Base& func3()" << std::endl;
  Base temp;
  // temp.name = "func3() returned Base correct";
  return temp; // Когда мы получим адрес объекта, он уже будет удалён
};
Base func4() { 
  std::cout << "Base func4()" << std::endl; 
  Base* temp = new Base();
  // temp->name = "func4() returned Base correct";
  return *temp; // Здесь мы отдаём копию объекта, а не его адрес, тем самым теряем его. Происходит утечка памяти
};

Base* func5() { 
  std::cout << "Base* func5()" << std::endl;
  Base* temp = new Base();
  // temp->name = "func5() returned Base correct";
  return temp; // Здесь всё пройдет нормально, так как мы отдаём адрес объекта, а значит в будущем можем от него избавится
};

Base& func6() { 
  std::cout << "Base& func6()" << std::endl; 
  Base* temp = new Base();
  // temp->name = "func6() returned Base correct";
  return *temp; // Тоже что и в прошлой функции
};

void second_test() {
  std::cout << std::endl << "Functions that output classes" << std::endl;

  std::cout << std::endl << "Constructor:" << std::endl; 
  Base obj1, * obj2, obj4, * obj5;

  std::cout << std::endl << "Functions that create static objects" << std::endl;
	obj1 = func1(); // Base() ~Base()
	std::cout << std::endl; 
  obj2 = func2(); // Base() ~Base()
	std::cout << std::endl; 
  Base &obj3 = func3(); // Base() ~Base()

  std::cout << std::endl << "Functions that create dynamic objects" << std::endl;
	obj4 = func4(); // Base() Base(Base& obj) ~Base()
	std::cout << std::endl; 
  obj5 = func5(); // Base()
	std::cout << std::endl; 
  Base &obj6 = func6(); // Base()
  
  std::cout << std::endl;
}

int main() {
	first_test();
  second_test();
}