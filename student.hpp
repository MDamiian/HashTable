#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED

#include <string>

class Student {
  private:
    long int key;
    std::string career;
    float average;
    std::string name;

  public:
    Student();

    long int getKey() const;
    std::string  getCareer() const;
    float getAverage() const;
    std::string getName() const;

    std::string toString() const;

    void setKey(const long int&);
    void setCareer(const std::string&);
    void setAverage(const float&);
    void setName(const std::string&);

    bool operator == (const Student&) const;
    bool operator != (const Student&) const;
    bool operator > (const Student&) const;
    bool operator >= (const Student&) const;
    bool operator < (const Student&) const;
    bool operator <= (const Student&) const;

    friend std::ostream& operator << (std::ostream&, const Student&);
    friend std::istream& operator >> (std::istream&, Student&);
  };

#endif // STUDENT_HPP_INCLUDED
