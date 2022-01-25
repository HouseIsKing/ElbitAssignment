//Question 5 - Class Inheritance, const correctness and operator overloading

// Task 1 : Add a Circle class that has a center point and radius fields, create a base Shape class that both Circle and Rectangle inherit from, try to move as many common field/functions to the base class

// Task 2: Create an operator overload that will allow us to chain a point instance to a ostream (std::cout), for example:
////Point point1(5,7);
////std::cout << point1;
//The previous line should output "5/7" to the console

// Task 3: Review the const correctness of the Shape/Circle/Rectangle member functions and modify them where it's required

// Do not change the main function body - it should compile and run without any modifications after completion of all tasks  

#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

struct Point {

	Point() :
		x(0),
		y(0)
	{}

	Point(int x_, int y_) :
		x(x_),
		y(y_)
	{}

	int x;
	int y;

};

std::ostream& operator << (std::ostream& os, const Point& point)
{
	os << point.x << "/" << point.y;
	return os;
}

struct Size {

	Size() :
		width(0),
		height(0){}

	Size(int width_, int height_) :
		width(width_),
		height(height_){}

	int width;
	int height;
};

class Shape
{
public:
	const Point& center() const
	{
		return centerPoint;
	}
	const std::string& name() const
	{
		return m_name;
	}
	virtual const double area() const = 0;
protected:
	std::string m_name = "Shape";
	Point centerPoint;
};

class Circle : public Shape
{
public:
	Circle(const Point& center_arg, const double& radius_arg) : radius(radius_arg)
	{
		m_name = "Circle";
		centerPoint = center_arg;
	}
	const double area() const
	{
		return M_PI * radius * radius;
	}
protected:
	double radius;
};


class Rectangle : public Shape {

public:

	Rectangle(const Point& center_arg, const Size& size) :
		m_size(size)
	{
		centerPoint = center_arg;
		m_name = "Rectangle";
	}

	const Size& size() {
		return m_size;
	}

	 const double area() const {
		return m_size.width * m_size.height;
	}

protected:
	Size  m_size;
};


int main(int argc, char** argv)
{
	//Do not change anything in this function body
	Circle circle1(Point(5, 5), 10);
	Rectangle rect1(Point(5, 5), Size(10, 10));
	Circle circle2(Point(8, 8), 4);

	std::vector<Shape*> shapes{&circle1, & rect1, & circle2};
	for (const Shape* shape : shapes) {
		std::cout << "Shape: " << shape->name() << " center: " << shape->center() << " area: " << shape->area() << std::endl;
	}

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}