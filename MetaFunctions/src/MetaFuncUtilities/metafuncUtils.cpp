//
// Created by salim on 06/01/2022.
//
#include "metafuncUtils.hpp"
#include "VoidtCornerCases.hpp"

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
} // end of namespace




