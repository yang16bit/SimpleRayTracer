#include "../Matrix.hpp"

#include <catch2/catch.hpp>
#include <limits>
TEST_CASE("Matrix operators", "[Matrix]") {
  Matrix A{Vector{1, 0, 0}, Vector{0, 1, 0}, Vector{0, 0, 1}};
  Matrix A2{Vector{2, 0, 0}, Vector{0, 2, 0}, Vector{0, 0, 2}};
  SECTION("Matrix::GetDet()") {
    REQUIRE(A.GetDet() == 1.0f);
    REQUIRE(A2.GetDet() == 8.0f);
  }
  SECTION("Matrix*Matrix") { REQUIRE(A * A2 == A2); }
  SECTION("Matrix::SolveLinearEquasSys()") {
    // [A][x] = [v]
    Matrix M{Vector{2, -1, 1}, Vector{1, 4, 1}, Vector{1, 1, 5}};
    Vector v{4, 14, 666};
    Vector x = M.SolveLinearEquasSys(v);
    Vector v_ = M * x;
    REQUIRE(M.GetDet() != 0.f);
    REQUIRE(v_.x == Approx(v.x));
    REQUIRE(v_.y == Approx(v.y));
    REQUIRE(v_.z == Approx(v.z));
  }
}
