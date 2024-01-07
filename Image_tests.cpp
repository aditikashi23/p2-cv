#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

TEST(test_image_init_istringstream) {
  string input = "P3\n5 5\n255\n0 0 0 0 0 0 255 255 250 0 0 0 0 0 0 \n255 255 250 126 66 0 126 66 0 126 66 0 255 255 250 \n126 66 0 0 0 0 255 219 183 0 0 0 126 66 0 \n255 219 183 255 219 183 0 0 0 255 219 183 255 219 183 \n255 219 183 0 0 0 134 0 0 0 0 0 255 219 183 \n";
  istringstream ss_input(input);

  Image *img = new Image;
  Image_init(img, ss_input);

  ostringstream output;
  Image_print(img, output);

  ostringstream expected;
  expected << input;

  ASSERT_EQUAL(output.str(), expected.str());
  delete img;
}

TEST(test_image_fill) {
  Image *img = new Image; //initializing 3x3 image
  Image_init(img, 5, 5);

  Pixel test_color = {100, 100, 100};
  Image_fill(img, test_color);

  for(int r = 0; r < 5; ++r) {
    for(int c = 0; c < 5; ++c) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, r, c), test_color));
    }
  }

  delete img;  
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
