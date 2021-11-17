#include <boost/test/unit_test.hpp>
#include <iostream>
#include <exception>
#include "task2.hpp"

BOOST_AUTO_TEST_SUITE(task2)

  BOOST_AUTO_TEST_CASE (oneCorrectEntity)
  {
    std::stringstream in("3 (256; 342)  (920; 120)  (21; 30)");
    std::stringstream out;
    BOOST_CHECK_NO_THROW(kosnitskiy::executeSecondTask(in, out));
    BOOST_CHECK_EQUAL(out.str(), "Vertices: 3\n"
                                 "Triangles: 1\n"
                                 "Squares: 0\n"
                                 "Rectangles: 0"
                                 "\nPoints: (256; 342) "
                                 "\nShapes: \n"
                                 "3 (256; 342) (920; 120) (21; 30)");
  }

  BOOST_AUTO_TEST_CASE(multipleUnpleasantCorrectEntities)
  {
    std::stringstream in("4 (-7534; -6622)  (-7800; -6300)  (-7534; -6622)  (-7800; -6300)\n"
                         "\n"
                         "\n"
                         "\n"
                         "\n"
                         "6  (-9385; -9390)          (-8837; -8700)  (-9161; -7880)  (-10032; -7751)  (-10580; -8441)  (-10256; -9261)\n"
                         "5  (-529;           -6334)  (751; -11211)  (5785; -11499)  (7615; -6800)  (3712; -3609)\n"
                         "4  (          757; -330)  (757       ; -1794)  (-4093; -1794)  (-4093; -330)\n"
                         "4  (-7348; -8438)  (-7348; -8670)  (-7580; -8670)  (-7580; -8438)                          \n"
                         "3  (3532; -7573)  (8135        ; -8769)  (9155;        1768)\n"
                         "\n"
                         "\n"
                         "\n"
                         "\n"
                         "");
    std::stringstream out;
    BOOST_CHECK_NO_THROW(kosnitskiy::executeSecondTask(in, out));
    std::string str = out.str();
    BOOST_CHECK_EQUAL(out.str(), "Vertices: 26\n"
                                 "Triangles: 1\n"
                                 "Squares: 1\n"
                                 "Rectangles: 3\n"
                                 "Points: (-7534; -6622) (-9385; -9390) (757; -330) (-7348; -8438) (3532; -7573) \n"
                                 "Shapes: \n"
                                 "3 (3532; -7573) (8135; -8769) (9155; 1768)\n"
                                 "4 (-7348; -8438) (-7348; -8670) (-7580; -8670) (-7580; -8438)\n"
                                 "4 (-7534; -6622) (-7800; -6300) (-7534; -6622) (-7800; -6300)\n"
                                 "4 (757; -330) (757; -1794) (-4093; -1794) (-4093; -330)\n"
                                 "6 (-9385; -9390) (-8837; -8700) (-9161; -7880) (-10032; -7751) (-10580; -8441) (-10256; -9261)");
  }

  BOOST_AUTO_TEST_CASE (Empty)
  {
    std::stringstream in("");
    std::stringstream out;
    BOOST_CHECK_NO_THROW(kosnitskiy::executeSecondTask(in, out));
    BOOST_CHECK_EQUAL(out.str(), "Vertices: 0\n"
                                 "Triangles: 0\n"
                                 "Squares: 0\n"
                                 "Rectangles: 0\n"
                                 "Points: \n"
                                 "Shapes: ");
  }

  BOOST_AUTO_TEST_CASE (incorrectPointsAmountLess)
  {
    std::stringstream in("3 (256; 342)  (920; 120)");
    std::stringstream out;
    BOOST_CHECK_THROW(kosnitskiy::executeSecondTask(in, out), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE (incorrectPointsAmountMore)
  {
    std::stringstream in("3 (256; 342)  (920; 120) (256; 342)  (920; 120)");
    std::stringstream out;
    BOOST_CHECK_THROW(kosnitskiy::executeSecondTask(in, out), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE (invalidInput)
  {
    std::stringstream in("2 (256; 342) \n (920; 120)");
    std::stringstream out;
    BOOST_CHECK_THROW(kosnitskiy::executeSecondTask(in, out), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
