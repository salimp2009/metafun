//
// Created by salim on 06/01/2022.
//
#include "metafunctionsPCH.hpp"
#include "metafuncUtils.hpp"
#include "VoidtCornerCases.hpp"
#include "metaLinearSearch.hpp"
#include "metaInheritanceSearch.hpp"
#include "InheritanceSearchStruct.hpp"


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

        }(std::make_index_sequence<3>{});

        std::printf("result2 of true case: recursive_pack: %s \n", (result2.first) ? "true": "false");
        std::printf("result2 of false case: recursive_pack: %s \n", (result2.second) ? "true": "false");

        // false case test
        const auto result3 = recursiveFind<int, 5, std::string>();
        std::printf("result3 of false case: recursive_pack: %s \n", (result3) ? "true": "false");

        // true case test; default value for Sentinel is int
        const auto result4 = recursiveFind<int, 3>();
        std::printf("result4 of true case: recursive_pack: %s \n", (result4) ? "true": "false");
    }

    //
    void LinearSearch_UsingFunctionPointers()
    {
        std::puts("--------------------------------------");
        std::puts("--LinearSearch_UsingFunctionPointers--");
        using typePack = IsInPack<int, char, double, float, std::string>;
        auto result = IsInPack<int, char, double, float, std::string>::contains(nameof<int>);
       // auto result = typePack.contains(nameof<int>);
        std::printf("IsInPack contains int: (expected true): %s \n", result ? "true": "false");
        result = typePack::contains((nameof<unsigned>));
        std::printf("IsInPack contains int: (expected false): %s \n", result ? "true": "false");
        result = typePack::contains((nameof<std::vector<int>>));
        std::printf("IsInPack contains int: (expected false): %s \n", result ? "true": "false");
        std::puts("--------------------------------------");
    }

    void SearchWithInheritance()
    {
        std::puts("--------------------------------------");
        std::puts("--SearchWithInheritance--");
        constexpr auto result1 = IsInPack_Inherit<int, char, float, double, int>::value;
        std::printf("IsInPack with Inheritance test: (expected true): %s \n", result1 ? "true": "false");

        constexpr auto result2 = IsInPack_Inherit<int, char, float, double, std::string>::value;
        std::printf("IsInPack with Inheritance test: (expected false): %s \n", result2 ? "true": "false");

        std::puts("--------------------------------------");
    }

    void SearchWithInheritance_Inst()
    {
        std::puts("--------------------------------------");
        std::puts("--SearchWithInheritance_Inst--");
        constexpr auto result1 = IsInPack_Inherit_Inst<int, char, float, double, int>::value;
        std::printf("IsInPack_Inherit_Inst test: (expected true): %s \n", result1 ? "true": "false");

        constexpr auto result2 = IsInPack_Inherit_Inst<int, char, float, double, std::string>::value;
        std::printf("IsInPack_Inherit_Inst test: (expected false): %s \n", result2 ? "true": "false");

        std::puts("--------------------------------------");
    }


    void SearchWithInheritance_Struct()
    {
        std::puts("--------------------------------------");
        std::puts("--SearchWithInheritance_Struct--");

        constexpr auto result1 = IsInPack_Inherit_Struct<int, char, std::byte, float, int>::value;
        std::printf("IsInPack_Inherit_Struct test: (expected true): %s \n", result1 ? "true": "false");

        constexpr auto result2 = IsInPack_Inherit_Struct<int, char, std::byte, float, double>::value;
        std::printf("IsInPack_Inherit_Struct test: (expected false): %s \n", result2 ? "true": "false");

        constexpr auto result3 = IsInPack_IsBaseof<int, char, std::byte, float, double, int>::value;
        std::printf("IsInPack_Inherit_IsBaseof test: (expected true): %s \n", result3 ? "true": "false");

        constexpr auto result4 = IsInPack_IsBaseof<int, char, std::byte, float, double>::value;
        std::printf("IsInPack_Inherit_IsBaseof test: (expected false): %s \n", result4 ? "true": "false");

        std::puts("--------------------------------------");
    }



    } // end of namespace
