//
// Created by salim on 09/01/2022.
//

#ifndef METAFUN_METAINHERITANCESEARCH_HPP
#define METAFUN_METAINHERITANCESEARCH_HPP

#include "metafunctionsPCH.hpp"
#include "metafuncUtils.hpp"

namespace metafun
{
    // check with pointers
    template<typename T>
    static constexpr auto check(TypeIdentity<T> const*)->std::true_type { return {};};

    template<typename T>
    static constexpr auto check(void const*)->std::false_type { return {};};

    template<typename... Ts>
    struct IsInPackImpl:TypeIdentity<Ts>...{};

    template<typename TargetT, typename... Ts>
    using IsInPack_Inherit = decltype(check<TargetT>(static_cast<IsInPackImpl<Ts...>*>(nullptr)));



} // end of namespace

#endif //METAFUN_METAINHERITANCESEARCH_HPP
