//
// Created by salim on 08/01/2022.
//

#ifndef METAFUN_METALINEARSEARCH_HPP
#define METAFUN_METALINEARSEARCH_HPP

#include "../metafunctionsPCH.hpp"

namespace metafun {
    // Recursive Find
    template<typename TargetT, typename... Ts>
    struct recursive_IsInpack : std::false_type {};

    template<typename TargetT, typename... RestTs>
    struct recursive_IsInpack<TargetT, TargetT, RestTs...> : std::true_type {};

    // the main template that checks the First type in pack matches Target if not
    // it passes the Rest of types and Target recursively to the parent version
    template<typename TargetT, typename FirstT, typename... RestT>
    struct recursive_IsInpack<TargetT, FirstT, RestT...> : recursive_IsInpack<TargetT, RestT...> {};

    // test function to generate Num size of size_t
    template<typename TargetT, std::size_t Num, typename SentinelT = int>
    constexpr bool recursiveFind() {
        return []<std::size_t... Idx>(std::index_sequence<Idx...>) {
            return recursive_IsInpack<TargetT, std::integral_constant<char, Idx>..., SentinelT>::value;
        }(std::make_index_sequence<Num>{});
    }

    // 2nd example for Linear search using function pointers for each given type
    template<typename Ts>
    static constexpr std::string_view nameof() {
        return std::string_view(__PRETTY_FUNCTION__);
    }


    template<typename... Ts>
    struct IsInPack {
        using Fn = std::string_view (*)();
        static constexpr Fn typeIDs[] = {nameof<Ts>...};
        static constexpr auto contains(Fn target) {

#if __cplusplus > 201703L
            // if C++20
            if (std::ranges::find(typeIDs, target) != std::ranges::end(typeIDs)) {
                return true;
            }
            return false;
#else
            // if not C++20
            for (auto &&elem: typeIDs) {
                if (elem == target) { return true; }
            }
            return false;
#endif
        }
    };


}// namespace metafun
#endif//METAFUN_METALINEARSEARCH_HPP
