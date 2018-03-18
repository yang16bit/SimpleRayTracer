#include <catch.hpp>
#include <limits>

#include "../Matrix2.hpp"
TEST_CASE("Matrix operators", "[Matrix2]") {
  Matrix2 A{Vector2{1, 0}, Vector2{0, 1}};
  Matrix2 A2{Vector2{2, 0}, Vector2{0, 2}};
  SECTION("Matrix2::GetDet()") {
    REQUIRE(A.GetDet() == 1.0f);
    REQUIRE(A2.GetDet() == 4.0f);
  }
  SECTION("Matrix*Matrix") { REQUIRE(A * A2 == A2); }
  SECTION("Matrix::SolveLinearEquasSys()") {
    // [A][x] = [v]
    Matrix2 M{Vector2{2, -1}, Vector2{1, 4}};
    Vector2 v{4, 14};
    Vector2 x = M.SolveLinearEquasSys(v);
    Vector2 v_ = M * x;
    REQUIRE(M.GetDet() != 0.f);
    REQUIRE(v_.x == Approx(v.x));
    REQUIRE(v_.y == Approx(v.y));
  }
}