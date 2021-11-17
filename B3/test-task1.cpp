#include <boost/test/unit_test.hpp>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "user-interface.hpp"
#include "factorial-container.hpp"

using namespace kosnitskiy;

BOOST_AUTO_TEST_SUITE(task1)

  BOOST_AUTO_TEST_CASE (correctData)
  {
    std::stringstream in;
    std::stringstream out;
    in << "add 731632216946 \"PdgrnCtigapfrGGBERZfrjDlqKdGA,\"\n"
          "add 248338871505 \"tHyXytEeCxQkes\"\n"
          "move current last\n"
          "delete current\n"
          "show current";
    UserInterface(in, out).processCommands();
    BOOST_CHECK_EQUAL(out.str(), "731632216946 PdgrnCtigapfrGGBERZfrjDlqKdGA,\n");
    in.clear();
    out.clear();
  }

  BOOST_AUTO_TEST_CASE(markMovement)
  {
    std::stringstream in;
    std::stringstream out;
    in << "add 581085164436 \"pQi,cZBkBqOQQTDp CiZ\"\n"
          "add 144798680767 \"nAnrQ\\\"XheaAJstbj\"\n"
          "add 131086953465 \"MnSWFuOJV,fL,uObZrPiLpMZ\\\"E\"\n"
          "add 192657725738 \"RwjqsixKDWJSae\\\"\"\n"
          "add 950265531246 \"cbzrSMZzcPmjYM,\"\n"
          "add 482077701345 \"RSNeGrZHQxeSrl\"\n"
          "add 335752908605 \"X ZULyACGT\"\n"
          "add 562953829160 \"ARmh c Dqq,\\\"drYDlA\"\n"
          "add 973481311343 \"bRlwLpxDaNYDiu\"\n"
          "move current 8\n"
          "show current";
    UserInterface(in, out).processCommands();
    BOOST_CHECK_EQUAL(out.str(), "973481311343 bRlwLpxDaNYDiu\n");
    in.clear();
    out.clear();
  }

  BOOST_AUTO_TEST_CASE (invalidCommand)
  {
    std::stringstream in;
    std::stringstream out;
    in << "recall 29";
    UserInterface(in, out).processCommands();
    BOOST_CHECK_EQUAL(out.str(), "<INVALID COMMAND>\n");
  }

  BOOST_AUTO_TEST_CASE (emptyCheck)
  {
    std::stringstream in;
    std::stringstream out;
    in << "show current";
    UserInterface(in, out).processCommands();
    BOOST_CHECK_EQUAL(out.str(), "<EMPTY>\n");
  }

  BOOST_AUTO_TEST_CASE (absentMark)
  {
    std::stringstream in;
    std::stringstream out;
    in << "show curr";
    UserInterface(in, out).processCommands();
    BOOST_CHECK_EQUAL(out.str(), "<INVALID BOOKMARK>\n");
  }

  BOOST_AUTO_TEST_CASE (not_a_number)
  {
    std::stringstream in;
    std::stringstream out;
    in << "add abc \"Georgy\"";
    UserInterface(in, out).processCommands();
    BOOST_CHECK_EQUAL(out.str(), "<INVALID COMMAND>\n");
  }

  BOOST_AUTO_TEST_CASE (wrongMovementStep)
  {
    std::stringstream in;
    std::stringstream out;
    in << "add 7316 \"George\"\n"
          "move current middle";
    UserInterface(in, out).processCommands();
    BOOST_CHECK_EQUAL(out.str(), "<INVALID STEP>\n");
  }

BOOST_AUTO_TEST_SUITE_END()
