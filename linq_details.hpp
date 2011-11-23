#include <functional>
#include <algorithm>
#include <map>
#include "adaptors.hpp"
#include "utility.hpp"

namespace linq
{
	namespace details
	{
		template<typename TSource>
		struct where_impl
		{
			std::function<bool(const TSource &)> predicate;
			where_impl(std::function<bool(const TSource &)> predicate) : predicate(predicate) {}
			template<typename TContainer>
			typename utility::rebind<TContainer,TSource>::type operator()(const TContainer & source) const
			{ 
				typename utility::rebind<TContainer,TSource>::type result;
	     			for(typename TContainer::const_iterator i = source.begin() ; i != source.end(); i++)
	     			{
		     			if ( predicate(*i) )
			     			result.push_back(*i);
	     			}
		     		return result;
     			}
   		};

   		template<typename TSource, typename TResult>
   		struct select_impl
   		{
     			std::function<TResult(const TSource &)> selector;
     			select_impl(std::function<TResult(const TSource &)> selector) : selector(selector) {}
			template<typename TContainer>
			typename utility::rebind<TContainer,TResult>::type operator()(const TContainer & source) const
     			{ 
	     			typename utility::rebind<TContainer,TResult>::type result;
	     			for(typename TContainer::const_iterator i = source.begin() ; i != source.end(); i++)
	     			{
		     			result.push_back(selector(*i));
	     			}
				return result;
     			}
		};

		template<typename TSource, typename TKey>
		struct groupby_impl
		{
			std::function<TKey(const TSource &)> keySelector;
			groupby_impl(std::function<TKey(const TSource &)> keySelector) : keySelector(keySelector) {}
			template<typename TContainer>
			std::map<TKey, TContainer> operator()(const TContainer & source) const
			{
				std::map<TKey, TContainer> result;
	     			for(typename TContainer::const_iterator i = source.begin() ; i != source.end(); i++)
	     			{
					result[keySelector(*i)].push_back(*i);
	     			}
				return result;
			}
		};
		
		template<typename TSource, typename TKey>
		struct orderby_impl
		{
			std::function<TKey(const TSource&)> keySelector;
			orderby_impl(std::function<TKey(const TSource&)> keySelector) : keySelector(keySelector) {}
			
			template<typename TContainer>
			TContainer operator()(const TContainer & source) const
			{
				TContainer result(source);
				auto cmp = [this](const TSource & a,const TSource & b) { return this->keySelector(a) < this->keySelector(b); };
				adaptors::sort(result, cmp);
				return result;
			}
		};
	}
}
