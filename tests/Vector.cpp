#include "../Vector.hpp"

#include <catch2/catch.hpp>

TEST_CASE("Vector operators", "[Vector]") {
  Vector v{1, 2, 3};
  Vector w{4, 5, 6};
  const float dot_product{32};
  const Vector cross_product{-3, 6, -3};
  const float scalar{3};
  const Vector scalar_product{3, 6, 9};
  const Vector sum{5, 7, 9};
  const Vector difference{-3, -3, -3};
  auto reset_v_w = [&v, &w]() -> void {
    v = {1, 2, 3};
    w = {4, 5, 6};
  };
  reset_v_w();

  SECTION("test Vector == Vector") {
    REQUIRE((Vector{1, 2, 3}) == (Vector{1, 2, 3}));
    REQUIRE((Vector{1, 2, 0}) != (Vector{1, 2, 3}));
  }
  SECTION("test reset_v_w") {
    REQUIRE(v == (Vector{1, 2, 3}));
    REQUIRE(w == (Vector{4, 5, 6}));
  }
  SECTION("test Vector + Vector") {
    reset_v_w();
    REQUIRE(v + w == sum);
  }
  SECTION("test Vector += Vector") {
    reset_v_w();
    v += w;
    REQUIRE(v == sum);
  }
  SECTION("test Vector - Vector") {
    reset_v_w();
    REQUIRE(v - w == difference);
  }
  SECTION("test Vector -= Vector") {
    reset_v_w();
    v -= w;
    REQUIRE(v == difference);
  }
  SECTION("test Vector * float") {
    reset_v_w();
    REQUIRE(v * scalar == scalar_product);
  }
  SECTION("test Vector *= float") {
    reset_v_w();
    v *= scalar;
    REQUIRE(v == scalar_product);
  }
  SECTION("test Vector.Cross(Vector)") {
    reset_v_w();
    REQUIRE(v.Cross(w) == cross_product);
  }
  SECTION("test Vector.Dot(Vector)") {
    reset_v_w();
    REQUIRE(v.Dot(w) == dot_product);
  }
}
