#include <algorithm>
#include <list>

namespace adaptors
{
	template<typename TContainer, typename TCmp>
	void sort(TContainer & source, const TCmp & cmp)
	{
		std::sort(source.begin(), source.end(), cmp);
	}
	template<typename T, typename TCmp>
	void sort(std::list<T> & source, const TCmp & cmp)
	{
		source.sort(cmp);
	}
}
