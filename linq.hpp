#include <type_traits>
#include "linq_details.hpp"
#include "traits.hpp"

namespace linq
{
	namespace 
	{
		template<typename Functor>
		struct signature
		{
			typedef typename traits::function_traits<Functor>::template arg<0>::type OriginalA;
			typedef typename std::remove_const<typename std::remove_reference<OriginalA>::type>::type A;

			typedef typename traits::function_traits<Functor>::result_type   OriginalR;
			typedef typename std::remove_const<typename std::remove_reference<OriginalR>::type>::type R;
		};
	}

	template<typename TContainer, typename Functor>
	auto operator | (const TContainer & source, Functor clause) -> decltype(clause(source))
	{
		return clause(source);
	}

	//linq interfaces
	template<typename TPredicate>
	details::where_impl<typename signature<TPredicate>::A> 
	where(TPredicate predicate)
	{
		typedef typename signature<TPredicate>::A source_type;
     		return details::where_impl<source_type>(predicate);
	}
	template<typename TSelector>
	details::select_impl<typename signature<TSelector>::A, typename signature<TSelector>::R> 
	select(TSelector selector)
	{
		typedef typename signature<TSelector>::A source_type;
		typedef typename signature<TSelector>::R result_type;
     		return details::select_impl<source_type, result_type>(selector);
	}

	template<typename TKeySelector>
	details::groupby_impl<typename signature<TKeySelector>::A, typename signature<TKeySelector>::R>
	groupby(TKeySelector keySelector)
	{
		typedef typename signature<TKeySelector>::A source_type;
		typedef typename signature<TKeySelector>::R result_type;
     		return details::groupby_impl<source_type, result_type>(keySelector);
	}
	
	template<typename TKeySelector>
	details::orderby_impl<typename signature<TKeySelector>::A, typename signature<TKeySelector>::R>
	orderby(TKeySelector keySelector)
	{
		typedef typename signature<TKeySelector>::A source_type;
		typedef typename signature<TKeySelector>::R result_type;
     		return details::orderby_impl<source_type, result_type>(keySelector);
	}
}
