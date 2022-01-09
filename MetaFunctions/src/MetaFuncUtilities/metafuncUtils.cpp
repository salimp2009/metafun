//
// Created by salim on 06/01/2022.
//
#include "metafunctionsPCH.hpp"
#include "metafuncUtils.hpp"
#include "VoidtCornerCases.hpp"
#include "metaLinearSearch.hpp"


namespace metafun
{

    void voidTest()
    {
        std::puts("--voidTest--");

        /// @ when void_t is given a valid type it return void; this way you can check type
        /// @ also use this as std::enable_if_t
        static_assert(std::is_same_v<void, void_t<void>>);
        static_assert(std::is_same_v<void, void_t<>>);
        static_assert(std::is_same_v<void, void_t<int>>);
        static_assert(std::is_same_v<void, void_t<int, char>>);
        static_assert(std::is_same_v<void, void_t<int&&>>);

        // this is not valid cannot directly refer to void
        // you can add reference std::add_lvalue_reference<void>;
        //static_assert(std::is_same_v<void, void_t<void&>>);

        static_assert(std::is_same_v<void, std::add_lvalue_reference_t<void>>);
        static_assert(std::is_same_v<int&, std::add_lvalue_reference_t<int>>);

        static_assert(std::is_same_v<void, Add_Lvalue_Reference<void>::type>);
        static_assert(std::is_same_v<int&, Add_Lvalue_Reference<int>::type>);

        std::puts("test passed :)");
    }


    void voidtCornerCases()
    {
        std::puts("--voidtCornerCases--");
        func<One>();
        func<Two>();
        std::puts("test passed :)");
    }

    void recursiveFind_LinearSearch()
    {
        std::puts("--recursiveFind_LinearSearch--");

        static_assert(recursive_IsInpack<int, float, double, double, double, int>::value);
        static_assert(! recursive_IsInpack<int, float, double, double, double, std::string>::value);
        auto result = recursive_IsInpack<int, float, double, double, double, int>::value;
        std::printf("result of recursive_pack: %s \n", (result) ? "true": "false");
        std::puts("test passed :)");

      const auto result2 =  []<std::size_t...Idx>(std::index_sequence<Idx...>) consteval
        {
            constexpr auto resultTrue = recursive_IsInpack<int, decltype(Idx)..., int>::value;
            constexpr auto resultFalse = recursive_IsInpack<int, decltype(Idx)...>::value;
            return std::pair{resultTrue, resultFalse};

        }(std::make_index_sequence<200>{});

        std::printf("result of true case: recursive_pack: %s \n", (result2.first) ? "true": "false");
        std::printf("result of false case: recursive_pack: %s \n", (result2.second) ? "true": "false");

        // false case test
        const auto result3 = recursiveFind<int, 200, std::string>();
        std::printf("result of true case: recursive_pack: %s \n", (result3) ? "true": "false");

        // true case test; default value for Sentinel is int
        const auto result4 = recursiveFind<int, 200>();
        std::printf("result of true case: recursive_pack: %s \n", (result4) ? "true": "false");

    }

    void LinearSearch_UsingFunctionPointers()
    {
        std::puts("--------------------------------------");
        std::puts("--LinearSearch_UsingFunctionPointers--");
        IsInPack<int, char, double, float, std::string> typePack{};
        auto result = typePack.contains(nameof<int>);
        std::printf("IsInPack contains int: (expected true): %s \n", result ? "true": "false");
        result = typePack.contains((nameof<unsigned>));
        std::printf("IsInPack contains int: (expected false): %s \n", result ? "true": "false");
        result = typePack.contains((nameof<std::vector<int>>));
        std::printf("IsInPack contains int: (expected false): %s \n", result ? "true": "false");
        std::puts("--------------------------------------");
    }



    } // end of namespace




