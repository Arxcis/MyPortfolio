
// @file main.cpp
// @author jonas solsvik
// @date 22.05.17
// @brief exploring possibility of constexpr range() functions.
//           inspired by pythons range()

#include <array>

namespace jet {
    template <typename T>
    constexpr auto abs(T value) -> T
    { return (T{} > value)? -value: value; }

    //
    // @brief calling signature jet::range<END>()
    //
    template <typename T>
    constexpr auto sign(T value) -> T
    { return (T{} > value)? -1: 1; }

    //
    // @brief calling signature jet::range<END>()
    //
    template<int END>
    constexpr auto range () -> std::array<int, jet::abs(END)>
    {
        constexpr int SIZE = jet::abs(END);
        std::array<int, SIZE> arange;
        for (int i = 0; i < SIZE; ++i) {
            arange[i] = i * jet::sign(END);
        }
        return arange;
    }

    //
    // @brief calling signature jet::range<START, END>()
    //
    template<int START, int END>
    constexpr auto range () -> std::array<int, jet::abs(END - START)>
    {
        constexpr int SIZE = jet::abs(END - START);
        std::array<int, SIZE> arange;
        for (int i = 0; i < SIZE; ++i) {
            arange[i] = (i * jet::sign(END-START)) + START;
        }
        return arange;
    }

    //
    // @brief calling signature jet::range<START, END, STEP>()
    //  @TODO NOT STABLE YET, dividing by STEP does not always give the correct SIZE.
    //              Some important information is lost in the division....
    //              This causes the range to be 1 element shorter at the end, than what it should be.
    //              Run testRange3() to see what i mean.
     //                                             hmmmm - Jonas 22.05.17
    //
    template<int START, int END, int STEP>
    constexpr auto range() -> std::array<int, jet::abs(END - START)/STEP>
    {
        constexpr int SIZE = jet::abs(END - START)/STEP;

        std::array<int, SIZE> arange;
        for (int i = 0; i < SIZE; ++i) {
            arange[i] = (i * STEP * jet::sign(END-START)) + START;
        }
        return arange;
    }
}

constexpr char DIVIDER[] = "----------\n";

void testRange1()
{
    for (const auto& i: jet::range<-5>()) { std::cout << i << '\n'; } std::cout << DIVIDER; // Print 0-(-4)
    for (const auto& i: jet::range< 5>()) { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints 0-4
    for (const auto& i: jet::range< 0>()) { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints nothing
    for (const auto& i: jet::range<-1>()) { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints 0
    for (const auto& i: jet::range< 1>()) { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints 0
}

void testRange2()
{
    for (const auto& i: jet::range< 0, -10>()) { std::cout << i << '\n'; } std::cout << DIVIDER; // Print 0->(-9)
    for (const auto& i: jet::range< 0, 10>())  { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints 0->9
    for (const auto& i: jet::range< 0, 0>())   { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints nothing
    for (const auto& i: jet::range<0,-1>())    { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints 0
    for (const auto& i: jet::range<0, 1>())    { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints 0

    for (const auto& i: jet::range<-5, 5>())   { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints (-5)->4
    for (const auto& i: jet::range<5, -5>())   { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints 5->(-4)

    for (const auto& i: jet::range<5, 0>())    { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints 5->1
    for (const auto& i: jet::range<-5, 0>())   { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints (-5)->(-1)
}


void testRange3()
{
    for (const auto& i: jet::range<0, 26, 5>())   { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints (-5)->(-1)
    //for (const auto& i: jet::range< -5, 20, 3>())   { std::cout << i << '\n'; } std::cout << DIVIDER; // Prints (-5)->(-1)
}

int main ()
{
    //testRange1();
    //testRange2();
    testRange3();
}
