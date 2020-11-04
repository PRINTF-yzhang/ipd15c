#include "bst_map_raw.hxx"

#include <catch.hxx>

TEST_CASE("Default construct")
{
    Bst_map map;
    CHECK(map.size() == 0);
    CHECK(map.lookup(5) == nullptr);
}

TEST_CASE("Some insertion")
{
    Bst_map map;

    map.insert(9, 18.0);
    map.insert(2, 4.0);
    map.insert(3, 6.0);
    map.insert(7, 14.0);

    CHECK(map.size() == 4);

    SECTION("lookup missing") {
        CHECK(!map.lookup(1));
        CHECK(!map.lookup(4));
        CHECK(!map.lookup(5));
        CHECK(!map.lookup(8));
        CHECK(!map.lookup(10));
    }

    SECTION("lookup 2") {
        REQUIRE(map.lookup(2));
        CHECK(*map.lookup(2) == 4.0);
    }

    SECTION("lookup 3") {
        REQUIRE(map.lookup(3));
        CHECK(*map.lookup(3) == 6.0);
    }

    SECTION("lookup 7") {
        REQUIRE(map.lookup(7));
        CHECK(*map.lookup(7) == 14.0);
    }

    SECTION("lookup 9") {
        REQUIRE(map.lookup(9));
        CHECK(*map.lookup(9) == 18.0);
    }
}

TEST_CASE("Some removal")
{
    Bst_map map;

    CHECK(map.size() == 0);

    map.insert(9, 18.0);
    map.insert(2, 4.0);
    map.insert(3, 6.0);
    map.insert(7, 14.0);

    CHECK(map.size() == 4);
    CHECK(map.lookup(2));
    CHECK(map.lookup(3));
    CHECK(map.lookup(7));
    CHECK(map.lookup(9));

    map.remove(3);

    CHECK(map.size() == 3);
    CHECK(map.lookup(2));
    CHECK_FALSE(map.lookup(3));
    CHECK(map.lookup(7));
    CHECK(map.lookup(9));

    map.remove(9);

    CHECK(map.size() == 2);
    CHECK(map.lookup(2));
    CHECK_FALSE(map.lookup(3));
    CHECK(map.lookup(7));
    CHECK_FALSE(map.lookup(9));

    map.remove(9);

    CHECK(map.size() == 2);
    CHECK(map.lookup(2));
    CHECK_FALSE(map.lookup(3));
    CHECK(map.lookup(7));
    CHECK_FALSE(map.lookup(9));

    map.remove(7);

    CHECK(map.size() == 1);
    CHECK(map.lookup(2));
    CHECK_FALSE(map.lookup(3));
    CHECK_FALSE(map.lookup(7));
    CHECK_FALSE(map.lookup(9));

    map.remove(0);

    CHECK(map.size() == 1);
    CHECK(map.lookup(2));
    CHECK_FALSE(map.lookup(3));
    CHECK_FALSE(map.lookup(7));
    CHECK_FALSE(map.lookup(9));

    map.remove(2);

    CHECK(map.size() == 0);
    CHECK_FALSE(map.lookup(2));
    CHECK_FALSE(map.lookup(3));
    CHECK_FALSE(map.lookup(7));
    CHECK_FALSE(map.lookup(9));
}

TEST_CASE("Copy constructor")
{
    Bst_map map1;

    map1.insert(5, 50);

     Bst_map map2(map1);

    SECTION("lookup 5") {
        REQUIRE(map2.lookup(5));
        CHECK(*map2.lookup(5) == 50);
    }
}
