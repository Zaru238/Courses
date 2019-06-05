#include <gtest/gtest.h>

#include <library/foo.h>

TEST(Foo, DefaultCase) {
  foo();
  ASSERT_TRUE(true);
}
