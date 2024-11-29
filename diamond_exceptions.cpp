#include <exception>
#include <iostream>

struct FundamentalArithmetic: public std::exception {
  const char * what() const noexcept override {
    return "arithmetic";
  }
};
struct Signed: public std::exception {
  const char * what() const noexcept override {
    return "signed";
  }
};
struct SignedFundamentalArithmetic: Signed, FundamentalArithmetic {
  const char * what() const noexcept override {
    return "signed arithmetic";
  }
};

int main()
{
  try {

    throw SignedFundamentalArithmetic{};

  } catch (const std::exception & e) {
    std::cout << e.what() << "\n";
  } catch (...) {
    std::cout << "???\n";
  }
}
