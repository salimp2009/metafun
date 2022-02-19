//
// Created by salim on 19/02/2022.
//

#ifndef METAFUN_ENUMERATEPACK_HPP
#define METAFUN_ENUMERATEPACK_HPP

#include "metafunctionsPCH.hpp"

namespace metafun
{


    template<typename Fn>
    constexpr auto enumeratePack(Fn&& f, auto&&...args)
    {
        return [&]<std::size_t...Idxs>(std::index_sequence<Idxs...>)
        {
            (std::invoke(std::forward<Fn>(f), Idxs, std::move(args)), ...);


        }(std::make_index_sequence<sizeof...(args)>{});
    }








} // end of namespace

#endif // METAFUN_ENUMERATEPACK_HPP
