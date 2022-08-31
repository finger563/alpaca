#include <alpaca/alpaca.h>
#include <doctest.hpp>
using namespace alpaca;

using doctest::test_suite;

TEST_CASE("Forwards Compatibility (new field added in struct)" *
          test_suite("forward_compatibility")) {

  std::array<uint8_t, 32> bytes = { 0 };
  {
    // client side is using an old structure
    struct my_struct {
      int old_field_1;
      float old_field_2;
    };

    my_struct s{5, 3.14f};
    serialize<my_struct>(s, bytes);
  }

  {
    // server side is updated to use a new structure
    struct my_struct {
      int old_field_1;
      float old_field_2;
      std::string new_field_1;
    };
    std::error_code ec;
    auto s = deserialize<my_struct>(bytes, ec);
    REQUIRE((bool)ec == false);
    REQUIRE(s.old_field_1 == 5);
    REQUIRE(s.old_field_2 == 3.14f);
    REQUIRE(s.new_field_1.empty()); // default initialized
  }

  {
    // server side is updated to use a new structure
    struct my_struct {
      int old_field_1;
      float old_field_2;
      std::string new_field_1;
      std::vector<bool> new_field_2;
    };
    std::error_code ec;
    auto s = deserialize<my_struct>(bytes, ec);
    REQUIRE((bool)ec == false);
    REQUIRE(s.old_field_1 == 5);
    REQUIRE(s.old_field_2 == 3.14f);
    REQUIRE(s.new_field_1.empty());     // default initialized
    REQUIRE(s.new_field_2.size() == 0); // default initialized
  }

  {
    // server side is updated to use a new structure
    struct my_struct {
      int old_field_1;
      float old_field_2;
      std::string new_field_1;
      std::vector<bool> new_field_2;
      int new_field_3;
    };
    std::error_code ec;
    auto s = deserialize<my_struct>(bytes, ec);
    REQUIRE((bool)ec == false);
    REQUIRE(s.old_field_1 == 5);
    REQUIRE(s.old_field_2 == 3.14f);
    REQUIRE(s.new_field_1.empty());     // default initialized
    REQUIRE(s.new_field_2.size() == 0); // default initialized
    REQUIRE(s.new_field_3 == 0);        // default initialized
  }
}