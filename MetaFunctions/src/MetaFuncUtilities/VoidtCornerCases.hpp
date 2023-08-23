//
// Created by salim on 07/01/2022.
//

#ifndef METAFUN_VOIDTCORNERCASES_HPP
#define METAFUN_VOIDTCORNERCASES_HPP

#include "../metafunctionsPCH.hpp"
#include "metafuncUtils.hpp"


namespace metafun {

    struct One {
        using x = int;
    };
    struct Two {
        using y = int;
    };

    template<typename T, void_t<typename T::x> * = nullptr>
    void func() {}

    // gives a redefinition error if std::void_t is used ; bug in C++ core language
    template<typename T, void_t<typename T::y> * = nullptr>
    void func() {}

}// end of namespace metafun


#endif//METAFUN_VOIDTCORNERCASES_HPP
