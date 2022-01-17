//
// Created by salim on 06/01/2022.
//

#ifndef METAFUN_METAFUNCUTILS_HPP
#define METAFUN_METAFUNCUTILS_HPP

#include "metafunctionsPCH.hpp"

namespace metafun
{
    void voidTest();
    void voidtCornerCases();
    void recursiveFind_LinearSearch();
    void LinearSearch_UsingFunctionPointers();
    void SearchWithInheritance();
    void SearchWithInheritance_Inst();
    void SearchWithInheritance_Struct();

    template<typename T>
    struct TypeIdentity {using type = T;};

   template<typename TFirst, typename...>
   struct void_t_Helper: TypeIdentity<TFirst> {};

    template<typename...Ts>
    using void_t = typename void_t_Helper<void, Ts...>::type;

    // primary template; if the type is valid then this is selected
    template<typename T, typename=void>
    struct Add_Lvalue_Reference : TypeIdentity<T> {};

    // specialization; if the type is valid but matches with T& then specialization will be selected
    template<typename T>
    struct Add_Lvalue_Reference<T, void_t<T&>> : TypeIdentity<T&> {};


 } // end of namespace metafun
















#endif //METAFUN_METAFUNCUTILS_HPP
