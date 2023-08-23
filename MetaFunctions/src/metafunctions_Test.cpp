#include "MetaFuncUtilities/metafuncUtils.hpp"
// #include <../../build/_deps/asio-src/asio/include/asio.hpp>
// #include <asio.hpp>
#include <fmt/core.h>
#include <fmt/os.h>
#include <format>
int main() {
    metafun::voidTest();
    metafun::voidtCornerCases();
    metafun::recursiveFind_LinearSearch();
    metafun::LinearSearch_UsingFunctionPointers();
    metafun::SearchWithInheritance();
    metafun::SearchWithInheritance_Inst();
    metafun::SearchWithInheritance_Struct();
    metafun::enumeratePack_Test();
    metafun::applyToIndex_Test();
    fmt::print("hello fmt\n");
}
