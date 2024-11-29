#include <vector>
#include <iostream>

struct Planar {
  virtual int x() const = 0;
  virtual int y() const = 0;
  virtual int abs_sqr() const = 0;
  virtual ~Planar() = default;
};
struct Colored {
  enum class Color {
    RED, GREEN, BLUE,
  };
  virtual Color color() const = 0;
  virtual void color(Color cl) = 0;
};
struct Point: Planar {
  Point(int x, int y):
    x_(x),
    y_(y)
  {}
  int x() const override {
    return x_;
  }
  int y() const override {
    return y_;
  }
  int abs_sqr() const override {
    return x_ * x_ + y_ * y_;
  }
 private:
  int x_;
  int y_;
};
struct Vector: Planar {
  Vector(const Point & a, const Point & b):
    a_(a),
    b_(b)
  {}
  int x() const override {
    return (a_.x() + b_.x()) / 2;
  }
  int y() const override {
    return (a_.y() + b_.y()) / 2;
  }
  int abs_sqr() const override {
    int midx = (a_.x() + b_.x()) / 2;
    int midy = (a_.y() + b_.y()) / 2;
    return midx * midx + midy * midy;
  }
 private:
  Point a_;
  Point b_;
};

struct ColoredPoint: Planar, Colored {
  ColoredPoint(const Point & p, Colored::Color cl):
    p_(p),
    cl_(cl)
  {}
  int x() const override {
    return p_.x();
  }
  int y() const override {
    return p_.y();
  }
  int abs_sqr() const override {
    return p_.abs_sqr();
  }
  Color color() const override {
    return cl_;
  }
  void color(Color cl) override {
    cl_ = cl;
  }
 private:
  Point p_;
  Color cl_;
};

struct Brush: Colored {
  explicit Brush(Color cl):
    cl_(cl)
  {}
  Color color() const override {
    return cl_;
  }
  void color(Color cl) override {
    cl_ = cl;
  }
 private:
  Color cl_;
};

bool is_lefter(const Planar * lhs, const Planar * rhs) {
  return lhs->x() < rhs->x();
}
bool is_botter(const Planar * lhs, const Planar * rhs) {
  return lhs->y() < rhs->y();
}
bool is_lefter_and_botter(const Planar * lhs, const Planar * rhs) {
  return is_lefter(lhs, rhs) ||
    (lhs->x() == rhs->x() && is_botter(lhs, rhs));
}

void sort(std::vector< Planar * > & planars) {
  for (std::size_t i = 0; i < planars.size(); ++i) {
    for (std::size_t j = 1 + (i % 2); j < planars.size(); ++j) {
      if (is_lefter_and_botter(planars[j], planars[j - 1])) {
	std::swap(planars[j], planars[j - 1]);
      }
    }
  }
}
std::ostream & print(std::ostream & out, const Planar & pl) {
  return out << "(" << pl.x() << " " << pl.y() << ")";
}

int main() {
  std::vector< Planar * > pls;
  pls.reserve(10);
  try {
    pls.push_back(new Point(1, 1));

    pls.push_back(new ColoredPoint(Point{0, 1}, Colored::Color::BLUE));

    pls.push_back(new Vector(Point{0, 0}, Point{2, 0}));
    pls.push_back(new Point(0, 0));
  } catch (...) {
    for (auto && p: pls) {
      delete p;
    }
    pls.clear();
  }
  std::cout << "Before:\n";
  for (auto && p: pls) {
    print(std::cout, *p) << "\n";
  }

  sort(pls);

  std::cout << "After:\n";
  for (auto && p: pls) {
    print(std::cout, *p) << "\n";
  }
  for (auto && p: pls) {
    delete p;
  }
}
