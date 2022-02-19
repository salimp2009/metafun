//
// Created by salim on 19/02/2022.
//

#ifndef METAFUN_APPLY_TO_INDEX_HPP
#define METAFUN_APPLY_TO_INDEX_HPP

#include "metafunctionsPCH.hpp"


namespace metafun
{
    template<std::size_t Id, typename Fn>
    constexpr auto apply_to_Index(Fn&& func, auto&&... args)
    {
        const auto Index =std::min(Id, sizeof...(args))-1;

        [&]<std::size_t...Idx>( std::index_sequence<Idx...>)
         {
            ([&]()
             {
                 if constexpr (Idx==Index)
                 {
                     std::invoke(std::forward<Fn>(func), std::move(args));
                 }
             }(),...);

         }(std::make_index_sequence<sizeof...(args)>{});

    }





}

#endif//METAFUN_APPLY_TO_INDEX_HPP
