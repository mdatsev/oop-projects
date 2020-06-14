#include "BinaryRelation.hpp"
#include "KnowledgeBase.hpp"
#include "string.hpp"

int main() {
    BinaryRelation<int, string> r1;
    r1.add_pair(1, "I");
    r1.add_pair(2, "II");
    r1.add_pair(3, "III");
    r1.add_pair(4, "IV");
    r1.add_pair(5, "V");

    BinaryRelation<int, string> r2;
    r2.add_pair(1, "I");
    r2.add_pair(2, "II");
    r2.add_pair(3, "III");
    r2.add_pair(4, "IIII");
    r2.add_pair(5, "IIIII");

    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;

    std::cout << r1(1, "I") << std::endl;
    std::cout << r1(4, "IIII") << std::endl;
    std::cout << r2(1, "I") << std::endl;
    std::cout << r1(1, "asd") << std::endl;

    std::cout << !r1 << std::endl;
    std::cout << r1 + r2 << std::endl;
    std::cout << (r1 ^ r2) << std::endl;
    std::cout << (r1 + r2)[4] << std::endl;
    std::cout << (r1 + r2)("III") << std::endl;
    std::cout << r1.dom() << std::endl;
    std::cout << (r1 + r2).ran() << std::endl;


    BinaryRelation<int, string> r3;
    r3.add_pair(1, "one");
    r3.add_pair(2, "two");
    r3.add_pair(3, "three");
    r3.add_pair(4, "four");
    r3.add_pair(5, "five");

    BinaryRelation<string, string> r4;
    r4.add_pair("one", "edno");
    r4.add_pair("two", "dve");
    r4.add_pair("three", "tri");
    r4.add_pair("four", "4etiri");
    // r4.add_pair("five", "pet");
    r4.add_pair("six", "6est");

    std::cout << r3 * r4 << std::endl;
    r3 *= r4;
    std::cout << r3 << std::endl;

    BinaryRelation<int, int> r5;
    r5.add_pair(1, 1);
    r5.add_pair(2, 2);

    std::cout << r5.injection() << std::endl;
    std::cout << r5.function() << std::endl;

    r5.add_pair(3, 2);
    std::cout << r5.injection() << std::endl;
    std::cout << r5.function() << std::endl;
    
    r5.add_pair(1, 3);
    std::cout << r5.injection() << std::endl;
    std::cout << r5.function() << std::endl;



    KnowledgeBase<int, string> kb;
    kb("nameOf").add_pair(4, "four");
    kb("nameOf").add_pair(42, "fourty-two");
    kb("nameOf").add_pair(42, "forty-two");
    kb("nameOf").add_pair(5, "five");
    kb("nameOf").add_pair(4, "vier");
    kb("nameOf").add_pair(99, "neunundneunzig");
    kb("romanNumeral").add_pair(5, "V");
    kb("romanNumeral").add_pair(42, "XLII");
    kb("romanNumeral").add_pair(42, "xlii");
    std::cout << kb << std::endl << std::endl;

    KnowledgeBase<int, string> kb2;
    kb2("nameOf").add_pair(4, "four");
    kb2("nameOf").add_pair(42, "fourty-two");
    kb2("nameOf").add_pair(42, "forty-two");
    kb2("nameOf").add_pair(5, "five");
    kb2("nameOf").add_pair(4, "vier");
    kb2("nameOf").add_pair(99, "neunundneunzig");
    kb2("binaryString").add_pair(4, "100");
    kb2("binaryString").add_pair(5, "101");
    kb2("hexString").add_pair(42, "2A");
    kb2("hexString").add_pair(42, "2a");
    kb2("hexString").add_pair(99, "63");
    kb2("octString").add_pair(51, "63");
    kb2("octString").add_pair(65, "101");
    std::cout << kb2 << std::endl << std::endl;


    std::cout << !kb << std::endl << std::endl;
    std::cout << kb + kb2 << std::endl << std::endl;
    std::cout << (kb ^ kb2) << std::endl << std::endl;
    std::cout << (kb + kb2)["nameOf"] << std::endl << std::endl;
    std::cout << (kb + kb2)("octString") << std::endl << std::endl;
    std::cout << kb.dom() << std::endl << std::endl;
    std::cout << (kb + kb2).ran() << std::endl << std::endl;

    std::cout << "try to type like this: " << std::endl;
    std::cout << r3 << std::endl;
    std::cin >> r3;
    std::cout << r3 << std::endl;

    std::cout << "try to type like this: " << std::endl;
    std::cout << kb2 << std::endl;
    std::cin >> kb2;
    std::cout << kb2 << std::endl;
}