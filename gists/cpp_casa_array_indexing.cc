// For testing C array vs CASA array indexing

#include <assert.h>
#include <casacore/casa/Arrays.h>
#include <exception>

static void customPrint(int *ptr, std::string name, int rowSize, int colSize);

int main() {
  int rowSize = 3;
  int colSize = 5;
  std::vector<int> stdVec(rowSize * colSize);

  std::cout << "rowSize: " << rowSize << std::endl
            << "columnSize: " << colSize << std::endl;

  // C array, row major order
  // frequently changing dimension is last
  int array[rowSize][colSize];

  // Fortran / CASA array, column major order
  // frequently changing dimension is first
  casacore::IPosition pos(2, colSize, rowSize);
  casacore::Array<int> casaArray(pos);

  casacore::Matrix<int> casaMatrix(colSize, rowSize);
  assert(casaMatrix.shape().isEqual(pos));

  std::cout << "Expected matrix :" << std::endl;

  // loop remains same for both C style and FORTRAN style
  for (size_t row = 0; row < rowSize; row++) {
    for (size_t col = 0; col < colSize; col++) {
      int pos = row * colSize + col;
      int val = pos + 100;
      std::cout << val << " ";

      stdVec[pos] = val;

      // C style accessing
      array[row][col] = val;

      casacore::IPosition currentPos =
          casacore::toIPositionInArray(pos, casaArray.shape());
      casacore::IPosition currentPos2(2, col, row);
      assert(currentPos.isEqual(currentPos2));

      casaArray(currentPos) = val;

      // FORTRAN style accessing
      casaMatrix(col, row) = val;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  int *ptr;
  std::string name;

  ptr = stdVec.data();
  name = "Standard Vector";
  customPrint(ptr, name, rowSize, colSize);

  ptr = (int *)array;
  name = "C Array";
  customPrint(ptr, name, rowSize, colSize);
  for (size_t row = 0; row < rowSize; row++) {
    for (size_t col = 0; col < colSize; col++) {
      assert(stdVec[row * colSize + col] == *ptr);
      assert(stdVec[row * colSize + col] == array[row][col]);
      ptr++;
    }
  }
  std::cout << "Assertion Passed for vector and C array" << std::endl;

  ptr = casaArray.data();
  name = "Casa Array";
  customPrint(ptr, name, rowSize, colSize);
  for (size_t row = 0; row < rowSize; row++) {
    for (size_t col = 0; col < colSize; col++) {
      assert(stdVec[row * colSize + col] == *ptr);
      casacore::IPosition currentPos(2, col, row);
      assert(stdVec[row * colSize + col] == casaArray(currentPos));
      ptr++;
    }
  }
  std::cout << "Assertion Passed for vector and CasaArray" << std::endl;
  std::cout << "Default print: CasaArray \n" << casaArray << std::endl;

  ptr = casaMatrix.data();
  name = "Casa Matrix";
  customPrint(ptr, name, rowSize, colSize);
  for (size_t row = 0; row < rowSize; row++) {
    for (size_t col = 0; col < colSize; col++) {
      assert(stdVec[row * colSize + col] == *ptr);
      casacore::IPosition currentPos(2, col, row);
      assert(stdVec[row * colSize + col] == casaMatrix(currentPos));
      assert(stdVec[row * colSize + col] == casaMatrix(col, row));
      ptr++;
    }
  }
  std::cout << "Assertion Passed for vector and CasaMatrix" << std::endl;
  std::cout << "Default print: CasaMatrix \n" << casaMatrix << std::endl;
}

static void customPrint(int *ptr, std::string name, int rowSize, int colSize) {

  std::cout << std::endl;
  std::cout << "--------------------------------------------" << std::endl;
  std::cout << name << " : " << std::endl;

  int *movingPtr = ptr;
  // iterating using row and col
  for (size_t row = 0; row < rowSize; row++) {
    for (size_t col = 0; col < colSize; col++) {
      assert(ptr[row * colSize + col] == *movingPtr);
      std::cout << ptr[row * colSize + col] << " ";
      movingPtr++;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Id    Value        Address        Diff" << std::endl;
  for (size_t i = 0; i < colSize * 2; i++) {
    std::string diff;
    if (i == 0)
      diff = "-";
    else
      diff = std::to_string(&ptr[i] - &ptr[i - 1]);
    std::cout << i << "      " << ptr[i] << "        " << &ptr[i] << "       "
              << diff << std::endl;
  }
  std::cout << std::endl;
};