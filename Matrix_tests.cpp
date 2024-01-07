#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <sstream>  

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST(test_get_height_and_width) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  const int width = 10;
  const int height = 20;
  Matrix_init(mat, width, height);

  ASSERT_EQUAL(Matrix_width(mat), width);
  ASSERT_EQUAL(Matrix_height(mat), height);

  delete mat;
}

TEST(test_get_row_and_column_by_pointer) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  const int width = 10;
  const int height = 20;
  Matrix_init(mat, width, height);

  int selected_row = 5; int selected_col = 7; //making pointer to this element of data
  int *ptr = mat->data + ((selected_row * Matrix_width(mat)) + selected_col);

  ASSERT_EQUAL(Matrix_row(mat, ptr), selected_row);
  ASSERT_EQUAL(Matrix_column(mat, ptr), selected_col);

  delete mat;
}

TEST(test_fill_border) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  const int width = 10;
  const int height = 20;
  Matrix_init(mat, width, height);

  Matrix_fill(mat, 0);
  Matrix_fill_border(mat, 1); //sets matrix of 0s, with border of 1

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      if ((r == 0) || (c == 0) || (r == Matrix_height(mat)-1) || (c == Matrix_width(mat)-1)) {ASSERT_EQUAL(*Matrix_at(mat, r, c),1);} //border values
      else {ASSERT_EQUAL(*Matrix_at(mat, r, c),0);} //everything else (inside values)
    }
  }

  delete mat;
}

TEST(test_get_max_element) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  const int width = 10;
  const int height = 20;
  const int value = 5;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);
  *Matrix_at(mat, 7, 2) = 10; //setting a greater value to a random element to retrieve

  ASSERT_EQUAL(Matrix_max(mat), 10);

  delete mat;
}

TEST(test_get_min_element_and_column) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  const int width = 10;
  const int height = 20;
  const int value = 10;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  *Matrix_at(mat, 7, 5) = 7;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 7, 0, width), 5); //edge test
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 7, 0, width), 7);

  *Matrix_at(mat, 7, 2) = 3;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 7, 0, 8), 2); //returns leftmost column 
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 7, 0, width), 3);

  delete mat;
}

TEST(test_print_matrix) {

  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  const int width = 3;
  const int height = 3;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, 0);
  Matrix_fill_border(mat, 1);

  ostringstream expected;
  ostringstream output;

  expected << "3 3\n"
           << "1 1 1 \n"
           << "1 0 1 \n"
           << "1 1 1 \n";
  Matrix_print(mat, output);
  ASSERT_EQUAL(expected.str(), output.str());
  delete mat;

}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
