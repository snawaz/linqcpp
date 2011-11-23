#include <type_traits>
#include "linq_details.hpp"

namespace linq
{

	template<typename TContainer, typename Functor>
	auto operator | (const TContainer & source, Functor clause) -> decltype(clause(source))
	{
		return clause(source);
	}

	//linq interfaces
	template<typename TPredicate>
	details::where_impl<typename utility::extract<TPredicate>::A> 
	where(TPredicate predicate)
	{
		typedef typename utility::extract<TPredicate>::A source_type;
     		return details::where_impl<source_type>(predicate);
	}
	
	template<typename TSelector>
	details::select_impl<typename utility::extract<TSelector>::A, typename utility::extract<TSelector>::R> 
	select(TSelector selector)
	{
		typedef typename utility::extract<TSelector>::A source_type;
		typedef typename utility::extract<TSelector>::R result_type;
     		return details::select_impl<source_type, result_type>(selector);
	}

	template<typename TKeySelector>
	details::groupby_impl<typename utility::extract<TKeySelector>::A, typename utility::extract<TKeySelector>::R>
	groupby(TKeySelector keySelector)
	{
		typedef typename utility::extract<TKeySelector>::A source_type;
		typedef typename utility::extract<TKeySelector>::R result_type;
     		return details::groupby_impl<source_type, result_type>(keySelector);
	}
	
	template<typename TKeySelector>
	details::orderby_impl<typename utility::extract<TKeySelector>::A, typename utility::extract<TKeySelector>::R>
	orderby(TKeySelector keySelector)
	{
		typedef typename utility::extract<TKeySelector>::A source_type;
		typedef typename utility::extract<TKeySelector>::R result_type;
     		return details::orderby_impl<source_type, result_type>(keySelector);
	}
}
