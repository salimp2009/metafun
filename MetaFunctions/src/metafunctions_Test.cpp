#include "MetaFuncUtilities/metafuncUtils.hpp"
#include <asio.hpp>
#include <asio/read.hpp>
#include <fmt/core.h>
#include <fmt/os.h>
#include <format>
#include <range/v3/at.hpp>
#include <range/v3/range/concepts.hpp>
#include <range/v3/range/primitives.hpp>

int main() {
    // range-v3 works
    using namespace ranges;
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
    fmt::print("hello yoow\n");
}
