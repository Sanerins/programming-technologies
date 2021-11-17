#include <boost/test/unit_test.hpp>
#include <unordered_set>
#include <iostream>
#include <string>
#include "task1.hpp"

BOOST_AUTO_TEST_SUITE(task1)

  BOOST_AUTO_TEST_CASE (testTask1)
  {
    std::unordered_set<std::string> words;
    std::stringstream in("kldsfjkladsjl\n\n\n\n"
                         "sdlk           jjdslajklsd\n\n\n"
                         "skldjklds jklfds\n\n\n"
                         "dsfklajklsdjklsdj\n\n"
                         "sdlkgjkl\n\n\n"
                         "er;wlekro\n"
                         "sdfl;k;ldfskl;\n");

    BOOST_CHECK_NO_THROW(kosnitskiy::parseWords(words, in));

    std::unordered_set<std::string> correct = {"kldsfjkladsjl", "sdlk", "jjdslajklsd", "skldjklds", "jklfds", "dsfklajklsdjklsdj",
                                               "sdlkgjkl", "er;wlekro", "sdfl;k;ldfskl;"};

    BOOST_CHECK(correct == words);
  }

BOOST_AUTO_TEST_SUITE_END()
