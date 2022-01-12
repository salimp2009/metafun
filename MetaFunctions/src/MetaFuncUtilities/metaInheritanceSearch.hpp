//
// Created by salim on 09/01/2022.
//

#ifndef METAFUN_METAINHERITANCESEARCH_HPP
#define METAFUN_METAINHERITANCESEARCH_HPP

#include "metafunctionsPCH.hpp"
#include "metafuncUtils.hpp"

namespace metafun
{
    // check Inheritance and with pointers
    template<typename T>
    static constexpr auto check(TypeIdentity<T> const*)->std::true_type { return {};};

    template<typename T>
    static constexpr auto check(void const*)->std::false_type { return {};};

    template<typename... Ts>
    struct IsInPackImpl: TypeIdentity<Ts>...{};

    template<typename TargetT, typename... Ts>
    using IsInPack_Inherit = decltype(check<TargetT>(static_cast<IsInPackImpl<Ts...>*>(nullptr)));

// check Inheritance and Instance
// performance: when the pack has more 200~ the performance is not good as the pointer version
    template<typename T>
    static constexpr auto check(TypeIdentity<T>) { return std::true_type{}; }

    template<typename T>
    static constexpr auto check(...) { return std::false_type{} ; }

    template<typename TargetT, typename...Ts>
    using IsInPack_Inherit_Inst = decltype(check<TargetT>(IsInPackImpl<Ts...>{}));




} // end of namespace

#endif //METAFUN_METAINHERITANCESEARCH_HPP
