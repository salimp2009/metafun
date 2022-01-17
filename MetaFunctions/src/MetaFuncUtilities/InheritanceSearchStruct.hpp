//
// Created by salim on 17/01/2022.
//

#ifndef METAFUN_INHERITANCESEARCHSTRUCT_HPP
#define METAFUN_INHERITANCESEARCHSTRUCT_HPP

#include "metafunctionsPCH.hpp"
#include "metafuncUtils.hpp"

namespace  metafun
{

    template<typename...Ts>
    struct IsInPackImpl2:TypeIdentity<Ts>...
    {
        template<typename  T>
        static constexpr auto check(TypeIdentity<T>) { return std::true_type{}; }

        template<typename  T>
        static constexpr auto check(...) { return std::false_type{}; }
    };

    template<typename TargetT, typename...Ts>
    using IsInPack_Inherit_Struct = decltype(IsInPackImpl2<Ts...>::template check<TargetT>(IsInPackImpl2<Ts...>{}));

    template<typename TargetT, typename... Ts>
    using IsInPack_IsBaseof = std::is_base_of<TypeIdentity<TargetT>, IsInPackImpl2<Ts...>>;


} // end of namespace



#endif //METAFUN_INHERITANCESEARCHSTRUCT_HPP
