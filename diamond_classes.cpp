#include <iostream>
#include <cassert>

struct Shape
{
  virtual ~Shape() = default;
};
struct Curved: virtual Shape
{};
struct Angled: virtual Shape
{};
struct CurvedWithAngles: Curved, Angled
{};

void process(const Shape & shp) {
  //do smth...
}

int main()
{
  CurvedWithAngles cwa = new CurvedWithAngles{};
  process(*cws); //virtual inheritance required

  //Upcast: вверх по иерархии - статический, автоматически выполняется компилятором
  Shape * shp1 = new Curved{};
  Shape * shp2 = new Angled{};
  Shape * shp3 = cwa; //virtual inheritance required

  // Преобразования на этапе выполнения
  // Крайне нежелательны
  // dynamic_cast

  //Downcast (с указателями): вниз по ирерахии (nullptr, если не удалось)
  Angled * an = dynamic_cast< Angled * >(shp1);
  if (!an) {
    std::cout << "Curved is not angled, you know?\n";
  }

  //Downcast (со ссылками): вниз по иерархии (bad_cast, если не удалось)
  try {
    Angled & not_anr = dynamic_cast< Angled & >(*shp1);
  } catch (const std::bad_cast & e) {
    std::cout << "Curved is defenetly not angled!\n";
  }

  //Sidecast (преобразование "поперёк" иерархии)
  Angled * an1 = dynamic_cast< Angled * >(shp3);
  assert(an1 != nullptr);
  Curved * an2 = dynamic_cast< Curved * >(an1);
  assert(an2 != nullptr);
}
