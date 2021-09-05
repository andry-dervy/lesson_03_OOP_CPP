//============================================================================
// Name        : lesson_03_OOP_CPP.cpp
// Author      : andry antonenko
// IDE         : Qt Creator 4.14.2 based on Qt 5.15.2
// Description : lesson 03 of the object-oriented programming on C++ course
//============================================================================
#include <QCoreApplication>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <cmath>
#include <chrono>
#include <list>
#include <string>
#include <sstream>
using namespace std;
//----------------------------------------------------------------------------
//#define NDEBUG
#include <cassert>
//----------------------------------------------------------------------------
/*
1. Создать абстрактный класс Figure (фигура).
Его наследниками являются классы Parallelogram (параллелограмм) и Circle (круг).
Класс Parallelogram — базовый для классов Rectangle (прямоугольник),
Square (квадрат), Rhombus (ромб).
Для всех классов создать конструкторы.
Для класса Figure добавить чисто виртуальную функцию area() (площадь).
Во всех остальных классах переопределить эту функцию,
исходя из геометрических формул нахождения площади.
//*/

class Figure
{
public:
  Figure(){}
  virtual ~Figure(){}
  virtual double area() = 0;
};

class Parallelogram: public Figure
{
protected:
  double a,b,alpha;
public:
  Parallelogram(double aA = 0,double aB = 0, double aAlpha = 0)
    :a(aA),b(aB),alpha(aAlpha) {}
  double area() override {return a*b*sin(alpha);}
};

class Circle: public Figure
{
  double radius;
public:
  Circle(double aRadius = 0)
    :radius(aRadius){}
  double area() override {return M_PI*radius*radius;}
};

class Rectangle: public Parallelogram
{
public:
  Rectangle(double aA = 0,double aB = 0)
      :Parallelogram(aA,aB,M_PI/2) {}
  double area() override {return a*b;}
};

class Square: public Parallelogram
{
public:
  Square(double aA = 0)
    :Parallelogram(aA,aA,M_PI/2) {}
  double area() override {return a*a;}
};

class Rhombus: public Parallelogram
{
public:
  Rhombus(double aA = 0, double aAlpha = 0)
    :Parallelogram(aA,aA,aAlpha) {}
  double area() override {return a*a*sin(alpha);}
};


//----------------------------------------------------------------------------
/*
2. Создать класс Car (автомобиль) с полями company (компания) и model (модель).
Классы-наследники: PassengerCar (легковой автомобиль) и Bus (автобус).
От этих классов наследует класс Minivan (минивэн).
Создать конструкторы для каждого из классов,
чтобы они выводили данные о классах.
Создать объекты для каждого из классов и посмотреть,
в какой последовательности выполняются конструкторы.
Обратить внимание на проблему «алмаз смерти».

Примечание: если использовать виртуальный базовый класс,
то объект самого "верхнего" базового класса создает самый "дочерний" класс.
//*/

class Car
{
public:
  string company;
  string model;

  Car(string aCompany = "",string aModel = "Car")
    :company(aCompany),model(aModel) {
    cout << model << endl;
  }
  virtual ~Car(){}
};

class PassengerCar: public Car
{
public:
  PassengerCar(string aCompany = "",string aModel = "PassengerCar")
    :Car(aCompany,aModel) {
    cout << model << endl;
  }
  ~PassengerCar() {}
};

class Bus: public Car
{
public:
  Bus(string aCompany = "",string aModel = "Bus")
    :Car(aCompany,aModel) {
    cout << model << endl;
  }
  ~Bus() {}
};

class Minivan: public PassengerCar,Bus
{
public:
  Minivan(string aCompany = "",string aModel = "Minivan")
    :PassengerCar(aCompany,aModel), Bus(aCompany,aModel) {
    cout << PassengerCar::model << " and " << Bus::model << endl;
  }
  ~Minivan() {}
};

//----------------------------------------------------------------------------
/*
3. Создать класс: Fraction (дробь).
Дробь имеет числитель и знаменатель (например, 3/7 или 9/2).
Предусмотреть, чтобы знаменатель не был равен 0.
Перегрузить:
    • математические бинарные операторы (+, -, *, /) для выполнения действий с дробями
    • унарный оператор (-)
    • логические операторы сравнения двух дробей (==, !=, <, >, <=, >=).

Примечание: Поскольку операторы < и >=, > и <= — это логические противоположности,
попробуйте перегрузить один через другой.
Продемонстрировать использование перегруженных операторов.
//*/

class Fraction
{
private:
  int numerator;
  int divider;
public:
  Fraction(int aNumerator = 0, int aDivider = 1)
    :numerator(aNumerator),divider(aDivider) {
    assert(aDivider != 0);
    if(aDivider == 0)
    {
      cout << "ERROR: Divider can't equal zero." << endl;
      divider = 1;
    }
  }
  ~Fraction(){}

  int getNumerator() const {return numerator;}
  int getDivider() const {return divider;}
  void print() const {
    cout << numerator << "/" << divider;
  }

  friend Fraction operator+(const Fraction &f1, const Fraction &f2);
  friend Fraction operator-(const Fraction &f1, const Fraction &f2);
  friend Fraction operator*(const Fraction &f1, const Fraction &f2);
  friend Fraction operator/(const Fraction &f1, const Fraction &f2);

  Fraction operator-() const
  {
    return Fraction(-numerator,divider);
  }

  friend bool operator==(const Fraction &f1, const Fraction &f2);
  friend bool operator!=(const Fraction &f1, const Fraction &f2);

  friend bool operator>(const Fraction &f1, const Fraction &f2);
  friend bool operator<(const Fraction &f1, const Fraction &f2);
  friend bool operator>=(const Fraction &f1, const Fraction &f2);
  friend bool operator<=(const Fraction &f1, const Fraction &f2);
};

Fraction operator+(const Fraction &f1, const Fraction &f2)
{
  if(f1.divider == f2.divider)
    return Fraction(f1.numerator + f2.numerator,f1.divider);

  int num = f1.numerator*f2.divider +
      f2.numerator*f1.divider;

  if(num%f1.divider == 0 && num%f2.divider == 0)
    return Fraction((num/f1.divider)/f2.divider,1);
  if(num%f1.divider == 0)
    return Fraction(num/f1.divider,f2.divider);
  if(num%f2.divider == 0)
    return Fraction(num/f2.divider,f1.divider);

  return Fraction(num,f1.divider*f2.divider);
}

Fraction operator-(const Fraction &f1, const Fraction &f2)
{
  if(f1.divider == f2.divider)
    return Fraction(f1.numerator - f2.numerator,f1.divider);

  int num = f1.numerator*f2.divider -
      f2.numerator*f1.divider;

  if(num%f1.divider == 0 && num%f2.divider == 0)
    return Fraction((num/f1.divider)/f2.divider,1);
  if(num%f1.divider == 0)
    return Fraction(num/f1.divider,f2.divider);
  if(num%f2.divider == 0)
    return Fraction(num/f2.divider,f1.divider);

  return Fraction(num,f1.divider*f2.divider);
}

Fraction operator*(const Fraction &f1, const Fraction &f2)
{
  int num = f1.numerator*f2.numerator;

  if(num%f1.divider == 0)
    return Fraction(num/f1.divider,f2.divider);
  if(num%f2.divider == 0)
    return Fraction(num/f2.divider,f1.divider);

  return Fraction(num,f1.divider*f2.divider);
}

Fraction operator/(const Fraction &f1, const Fraction &f2)
{
  int num = f1.numerator*f2.divider;

  if(num%f1.divider == 0)
    return Fraction(num/f1.divider,f2.numerator);
  if(num%f2.numerator == 0)
    return Fraction(num/f1.divider,f2.divider);

  return Fraction(num,f1.divider*f2.numerator);
}

bool operator==(const Fraction &f1, const Fraction &f2)
{
  int num1 = f1.numerator*f2.divider;
  int num2 = f2.numerator*f1.divider;

  if(num1 == num2)
    return true;

  return false;
}

bool operator!=(const Fraction &f1, const Fraction &f2)
{
  return !(f1 == f2);
}

bool operator>(const Fraction &f1, const Fraction &f2)
{
  int num1 = f1.numerator*f2.divider;
  int num2 = f2.numerator*f1.divider;

  if(num1 > num2)
    return true;

  return false;
}

bool operator<(const Fraction &f1, const Fraction &f2)
{
  return !(f1 > f2);
}

bool operator>=(const Fraction &f1, const Fraction &f2)
{
  int num1 = f1.numerator*f2.divider;
  int num2 = f2.numerator*f1.divider;

  if(num1 >= num2)
    return true;

  return false;
}

bool operator<=(const Fraction &f1, const Fraction &f2)
{
  return !(f1 >= f2);
}

//----------------------------------------------------------------------------
/*
4. Создать класс Card, описывающий карту в игре БлэкДжек.
У этого класса должно быть три поля:
масть, значение карты и положение карты (вверх лицом или рубашкой).
Сделать поля масть и значение карты типом перечисления (enum).
Положение карты - тип bool.
Также в этом классе должно быть два метода:
    • метод Flip(), который переворачивает карту,
т.е. если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
    • метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.
//*/

enum Suit
{
  HEARTS,
  CLUBS,
  DIAMONDS,
  SPADES,
};

enum ValueCard
{
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  LADY,
  KING,
  ACE,
};

class Card
{
private:
  Suit suit;
  ValueCard value;
  bool position;
public:
  Card(Suit aSuit = HEARTS,ValueCard aValue = SIX, bool aPosition = false)
    :suit(aSuit),value(aValue),position(aPosition){}
  ~Card(){}
  void Flip() {
    if(position) position = false;
    else position = true;
  }
  int GetValue() const {
    switch (value) {
    case SIX: return 6;
    case SEVEN: return 7;
    case EIGHT: return 8;
    case NINE: return 9;
    case TEN:
    case JACK:
    case LADY:
    case KING: return 10;
    case ACE: return 1;
    }
  }
};

//----------------------------------------------------------------------------
void task_1()
{
  cout << "Task 1\n" << endl;

  //Test 1
  cout << "Test 1\n" << endl;

  {
    Parallelogram prllgrm(2,3,1);
    cout << "Area of a parallelogram equal " << prllgrm.area() << endl;
    Circle crcl(2);
    cout << "Area of a circle equal " << crcl.area() << endl;
    Rectangle rctngl(2,5);
    cout << "Area of a rectangle equal " << rctngl.area() << endl;
    Square sqr(2);
    cout << "Area of a square equal " << sqr.area() << endl;
    Rhombus rhmbs(2,3);
    cout << "Area of a rhombus equal " << rhmbs.area() << endl;
  }

  //Test 2
  cout << "\nTest 2\n" << endl;

  {
    Figure *p_figure = nullptr;

    Parallelogram prllgrm(2,3,1);
    p_figure = &prllgrm;
    cout << "Area of a parallelogram equal " << p_figure->area() << endl;
    Circle crcl(2);
    p_figure = &crcl;
    cout << "Area of a circle equal " << p_figure->area() << endl;
    Rectangle rctngl(2,5);
    p_figure = &rctngl;
    cout << "Area of a rectangle equal " << p_figure->area() << endl;
    Square sqr(2);
    p_figure = &sqr;
    cout << "Area of a square equal " << p_figure->area() << endl;
    Rhombus rhmbs(2,3);
    p_figure = &rhmbs;
    cout << "Area of a rhombus equal " << p_figure->area() << endl;
  }

  cout << endl;
}
//----------------------------------------------------------------------------
void task_2()
{
  cout << "Task 2\n" << endl;

  Car car;
  PassengerCar passengerCar;
  Bus bus;
  Minivan minivan;

  cout << endl;
}
//----------------------------------------------------------------------------
void task_3()
{
  cout << "Task 3\n" << endl;

  Fraction f1(-1,3);
  Fraction f2(1,6);

  cout << "Test 1" << endl;
  Fraction f3 = f1 + f2;

  f1.print();
  cout << " + ";
  f2.print();
  cout << " = ";
  f3.print();
  cout << endl;

  cout << "Test 2" << endl;
  Fraction f4 = f1 - f2;

  f1.print();
  cout << " - ";
  f2.print();
  cout << " = ";
  f4.print();
  cout << endl;

  cout << "Test 3" << endl;
  Fraction f5 = f1 * f2;

  f1.print();
  cout << " * ";
  f2.print();
  cout << " = ";
  f5.print();
  cout << endl;

  cout << "Test 4" << endl;
  Fraction f6 = f1 / f2;

  f1.print();
  cout << " / ";
  f2.print();
  cout << " = ";
  f6.print();
  cout << endl;

  cout << "Test 5" << endl;
  Fraction f7 = - f1;

  f7.print();
  cout << " = -(";
  f1.print();
  cout << ")" << endl;

  cout << "Test 6" << endl;
  f1.print();
  cout << " == ";
  f2.print();
  if(f1 == f2) cout << " -> true" << endl;
  else cout << " -> false" << endl;

  cout << "Test 7" << endl;
  f1.print();
  cout << " != ";
  f2.print();
  if(f1 != f2) cout << " -> true" << endl;
  else cout << " -> false" << endl;

  cout << "Test 8" << endl;
  f1.print();
  cout << " > ";
  f2.print();
  if(f1 > f2) cout << " -> true" << endl;
  else cout << " -> false" << endl;

  cout << "Test 9" << endl;
  f1.print();
  cout << " < ";
  f2.print();
  if(f1 < f2) cout << " -> true" << endl;
  else cout << " -> false" << endl;

  cout << "Test 10" << endl;
  f1.print();
  cout << " >= ";
  f2.print();
  if(f1 >= f2) cout << " -> true" << endl;
  else cout << " -> false" << endl;

  cout << "Test 11" << endl;
  f1.print();
  cout << " <= ";
  f2.print();
  if(f1 <= f2) cout << " -> true" << endl;
  else cout << " -> false" << endl;

  cout << endl;
}
//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  //----------------------------------------------------------------------------
  // Task 1
  //*
  task_1();
  //*/
  //----------------------------------------------------------------------------
  // Task 2
  //*
  task_2();
  //*/
  //----------------------------------------------------------------------------
  // Task 3
  //*
  task_3();
  //*/
  //----------------------------------------------------------------------------
  return a.exec();
}
//----------------------------------------------------------------------------
