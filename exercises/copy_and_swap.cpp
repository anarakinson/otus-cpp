#include <iostream>
#include <string>
#include <algorithm>


class Person {
public:
  Person(std::string first_name, std::string last_name)
      : m_first_name{std::move(first_name)},
        m_last_name{std::move(last_name)} {}

  Person(const Person &) = default;
  Person(Person &&) = default;

  Person &operator=(Person &other) {
    // Copy and swap idiom.
    swap(other);

    return *this;
  }

  Person &operator=(Person &&) = default;

  ~Person() = default;

  // Implement swap method
  void swap(Person &other) noexcept;


private:
  std::string m_first_name;
  std::string m_last_name;

  friend std::ostream &operator<<(std::ostream &, const Person &);
  friend void swap(Person& lhs, Person& rhs) {
     std::swap(lhs.m_first_name, rhs.m_first_name);
     std::swap(lhs.m_last_name, rhs.m_last_name);
  }

};

void Person::swap(Person &other) noexcept {
  std::swap(m_first_name, other.m_first_name);
  std::swap(m_last_name, other.m_last_name);
}


std::ostream &operator << (std::ostream &os, const Person &person) {
  os << "first_name: " << person.m_first_name << " last_name: " << person.m_last_name;
  return os;
}


int main() {
  Person john{"John", "Smith"};
  Person mary{"Mary", "Jane"};

  john = mary;
  // swap(john, mary);

  std::cout << john << std::endl;
  std::cout << mary << std::endl;

}