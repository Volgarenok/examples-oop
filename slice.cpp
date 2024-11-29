#include <iostream>
struct A
{
  virtual void foo() {
    std::cout << "A::foo()\n";
  }
};

struct B: A
{
  void foo() {
    std::cout << "B::foo()\n";
  }
};

void bar1(A a) {
  a.foo();
}
void bar2(A & a) {
  a.foo();
}

int main() {
  B b;
  //A a = b;
  //вызов конструктора копирования (ранее связывание)
  //"срезка" реального объекта во временный объект
  bar1(b);

  //"B является A"
  //Объект типа B подходит
  bar2(b);
}
