#include "student.hpp"

using namespace std;

Student::Student() : key(0), career(" "), average(0.0), name(" ") {}

long int Student::getKey() const {
  return key;
  }

string Student::getCareer() const {
  return career;
  }

float Student::getAverage() const {
  return average;
  }

string Student::getName() const {
  return name;
  }

string Student::toString() const {
  string result;

  result += to_string(key);
  result.resize(9, ' ');
  result += "|";
  result += career;
  result.resize(14, ' ');
  result += "|";
  result += to_string(average);
  result.resize(20, ' ');
  result += "|";
  result += name;

  return result;
  }

void Student::setKey(const long int &c) {
  key = c;
  }

void Student::setCareer(const std::string &c) {
  career = c;
  }

void Student::setAverage(const float &a) {
  average = a;
  }

void Student::setName(const std::string &n) {
  name = n;
  }

bool Student::operator == (const Student& c) const {
  return key == c.key;
  }

bool Student::operator != (const Student& c) const {
  return !(*this == c);
  }

bool Student::operator > (const Student& c) const {
  return !(*this <= c);
  }

bool Student::operator >= (const Student& c) const {
  return !(*this < c);
  }

bool Student::operator < (const Student& c) const {
  return key < c.key;
  }

bool Student::operator <= (const Student& c) const {
  return *this < c or *this == c;
  }

