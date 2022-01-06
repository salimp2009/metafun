//
// Created by salim on 06/01/2022.
//

#ifndef METAFUN_METAFUNCUTILS_HPP
#define METAFUN_METAFUNCUTILS_HPP

#include "metafunctionsPCH.hpp"



namespace metafun
{
    void voidTest();

    template<typename...>
    using void_t = void;

    template<typename T>
    struct TypeIdentity {using type = T;};

    // primary template; if the type is valid then this is selected
    template<typename T, typename=void>
    struct Add_Lvalue_Reference : std::type_identity<T> {};

    // specialization; if the type is valid but matches with T& then specialization will be selected
    template<typename T>
    struct Add_Lvalue_Reference<T, void_t<T&>> : std::type_identity<T&> {};


 } // end of namespace metafun
















#endif //METAFUN_METAFUNCUTILS_HPP
