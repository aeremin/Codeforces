#include "util/lexicographical_compare.h"

#include <set>

#include <gmock/gmock.h>


struct Pair {
  int foo;
  std::string bar;
};

class StringHolder {
public:
  StringHolder(std::string val) : value_(std::move(val)) {}
  const std::string& value() const { return value_; }
private:
  std::string value_;
};

DEFINE_LEXICOGRAPHICAL_COMPARISON_2(Pair, foo, bar);
DEFINE_LEXICOGRAPHICAL_COMPARISON_1(StringHolder, value());


TEST(LexicographicalCompareTest, Pair) {
  std::vector<Pair> v = {{1, ""}, {1, "a"}, {1, "aa"}, {1, "b"}, {2, "a"}};
  EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(LexicographicalCompareTest, Method) {
  std::vector<StringHolder> v = {{"a"}, {"aa"}, {"b"}};
  EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(LexicographicalCompareTest, EnablesStdSet) {
  std::set<Pair> my_set;
  my_set.insert({1, "b"});
  my_set.insert({1, "a"});
  my_set.insert({1, "c"});
  EXPECT_EQ(my_set.begin()->bar, "a");
}
