#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <typeinfo>
#include <ctime>
#include <cstdlib>
#include "linq.hpp"

//print functions
template<typename T>
std::ostream & operator<<(std::ostream & out, const std::vector<T> & data)
{
	std::copy(data.begin(), data.end(), std::ostream_iterator<T>(out));
	return out;
}
template<typename T>
std::ostream & operator<<(std::ostream & out, const std::list<T> & data)
{
	std::copy(data.begin(), data.end(), std::ostream_iterator<T>(out, "  "));
	return out;
}

struct person
{
	int age;
	std::string name;
	person() : age(std::rand()%100 + 10) 
	{
		std::stringstream ss;
		ss << std::hex << std::rand() * 98789;
		name = ss.str();
	}
	friend std::ostream& operator << (std::ostream & out, const person & p)
	{
		return out << "("<<p.age<<","<<p.name<<")" << std::endl;
	}
};

int main() 
{

        using namespace linq;

	std::srand(std::time(0));

	//create a vector of persons and print them
	std::vector<person> persons;
	persons.reserve(15);
	for(int i = 0 ; i < 15; i++ ) 
		persons.push_back(person());
	std::cout << persons << std::endl;

	//orderby age and print the result 
	auto v3 = persons | orderby([](const person & p) { return p.age; });
	std::cout << v3 << std::endl;

	//filter using age-range, then orderby name, and print the result
	auto v4 = persons 
		| where([](const person & p) { return p.age > 25 && p.age < 50; }) 
		| orderby([](const person & p) { return p.name; });

	std::cout << v4 << std::endl;

	//orderby age and print the result without saving it
	std::cout << (v4 |  orderby([](const person & p) { return p.age; })) << std::endl ;

	//groupby age%6, and print the result - the type of the result of std::map!
	auto groups = persons | groupby([](const person & p) { std::stringstream ss; ss << "key"<< p.age % 6; return ss.str(); });
	for(auto i = groups.begin(); i != groups.end(); i++ )
	{
		std::cout << i->first << std::endl;
		std::cout << i->second << std::endl;
	}
}
