#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <typeinfo>
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
	friend std::ostream& operator << (std::ostream & out, const person & p)
	{
		return out << "("<<p.age<<","<<p.name<<")" << std::endl;
	}
};

int main() 
{

        using namespace linq;

	//create a vector of persons and print them
	std::vector<person> persons = { {1, "Aleeza"}, {3, "Nayab"}, {7, "Tufail"}, {8, "Sana"}, {11, "Farah"},
		{13, "Ashraf"}, {13, "Neha"}, {15, "Zeeshan" }, {16, "Adil"}, {17, "Nadim"}, {19, "Nafis"}, 
		{20, "Ahsan"}, {21, "Zartab"}, {23, "Nilufer"}, {24, "Talat"}
	};
	std::cout << persons << std::endl;

	//orderby age and print the result 
	auto v3 = persons | orderby([](const person & p) { return p.age; });
	std::cout << v3 << std::endl;

	//filter using age-range, then orderby name, and print the result
	auto v4 = persons 
		| where([](const person & p) { return p.age >=13 && p.age <= 19 ; }) 
		| orderby([](const person & p) { return p.name; });

	std::cout << v4 << std::endl;

	//orderby age and print the result without saving it
	std::cout << (v4 |  orderby([](const person & p) { return p.age; })) << std::endl ;

	//groupby age%6, and print the result - the type of the result of std::map!
	auto groups = persons | groupby([](const person & p) 
	{  
		if ( p.age < 13 ) return std::string("kids");
		else if ( p.age < 20 ) return std::string("teenagers");
		else return std::string("adults");
	});
	for(auto i = groups.begin(); i != groups.end(); i++ )
	{
		std::cout << i->first << std::endl;
		std::cout << i->second << std::endl;
	}
}
