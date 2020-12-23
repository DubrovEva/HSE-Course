#pragma once

#include "typelist.h"

template<typename TList> 
struct Length;

template<typename Head, typename Tail>
struct Length < TypeList<Head, Tail> >
{
    enum{ length = 1 + Length<Tail>::length };
};

template<typename Head>
struct Length<TypeList<Head, NullType>>
{
    enum{ length = 1 };
};

template<>
struct Length<NullType>
{
    enum{ length = 0 };
};
