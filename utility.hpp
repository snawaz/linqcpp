
namespace utility
{
	//function traits
	template <typename T>
	struct function_traits : public function_traits<decltype(&T::operator())>
	{};
	
	template <typename C, typename R, typename... A>
	struct function_traits<R(C::*)(A...) const>
	{
		enum { arity = sizeof...(A) };
		
		typedef R result_type;

		template <size_t i>
		struct arg
		{
			typedef typename std::tuple_element<i, std::tuple<A...>>::type type;
		};
	};

	//extract
	template<typename Functor>
	struct extract
	{
		typedef typename function_traits<Functor>::template arg<0>::type OriginalA;
		typedef typename std::remove_const<typename std::remove_reference<OriginalA>::type>::type A;

		typedef typename function_traits<Functor>::result_type   OriginalR;
		typedef typename std::remove_const<typename std::remove_reference<OriginalR>::type>::type R;
	};

	//rebind 
	template<typename TContainer, typename TNew>
	struct rebind;

	template<template<typename, typename...> class TContainer, typename TOld, typename TNew>
	struct rebind<TContainer<TOld>, TNew>
	{
		typedef TContainer<TNew> type;
	};
}
