#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;

template<typename Head, typename Tail, typename TargetType>
struct IndexOf <TypeList<Head, Tail>, TargetType>
{
    enum { another_pos = IndexOf<Tail, TargetType>::pos };
    enum { pos = (another_pos == -1) ? -1 : 1 + another_pos };
};

template<typename Tail, typename TargetType>
struct IndexOf <TypeList<TargetType, Tail>, TargetType>
{
    enum { pos = 0 };
};

template<typename TargetType>
struct IndexOf <NullType, TargetType>
{
    enum { pos = -1 };
};