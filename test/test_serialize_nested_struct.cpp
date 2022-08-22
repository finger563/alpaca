#include <doctest.hpp>
#include <serialize/serialize.h>

using doctest::test_suite;

TEST_CASE("Serialize nested struct (1 level)" * test_suite("struct")) {
  struct my_struct {
    int value;

    struct nested_struct {
      float value;
    };
    nested_struct nested;
  };

  my_struct s;
  s.value = 5;
  s.nested.value = 3.14f;

  auto bytes = serialize(s);
  REQUIRE(bytes.size() == 5);

  REQUIRE(bytes[0] == static_cast<uint8_t>(5));
  // 3.14f
  REQUIRE(bytes[1] == static_cast<uint8_t>(0xc3));
  REQUIRE(bytes[2] == static_cast<uint8_t>(0xf5));
  REQUIRE(bytes[3] == static_cast<uint8_t>(0x48));
  REQUIRE(bytes[4] == static_cast<uint8_t>(0x40));
}

TEST_CASE("Serialize nested struct (2 levels)" * test_suite("struct")) {
  struct my_struct {
    int value;

    struct nested_struct {
      float value;

      struct nested_nested_struct {
        bool value;
      };
      nested_nested_struct nested;
    };
    nested_struct nested;
  };

  my_struct s;
  s.value = 5;
  s.nested.value = 3.14f;
  s.nested.nested.value = true;

  auto bytes = serialize(s);
  REQUIRE(bytes.size() == 6);

  REQUIRE(bytes[0] == static_cast<uint8_t>(5));
  // 3.14f
  REQUIRE(bytes[1] == static_cast<uint8_t>(0xc3));
  REQUIRE(bytes[2] == static_cast<uint8_t>(0xf5));
  REQUIRE(bytes[3] == static_cast<uint8_t>(0x48));
  REQUIRE(bytes[4] == static_cast<uint8_t>(0x40));
  REQUIRE(bytes[5] == static_cast<uint8_t>(true));
}