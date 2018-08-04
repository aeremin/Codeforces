#include "container/container_alg.h"
#include "container/container_alg_accumulate.h"
#include "container/container_alg_binop.h"
#include "container/container_alg_binsearch.h"
#include "container/container_alg_filter.h"
#include "container/container_alg_minmax.h"
#include "container/container_alg_permutation.h"
#include "container/container_alg_set.h"


#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::ElementsAre;


TEST(ContainerAlgTest, ForEach) {
  std::vector<int> v = {1, 3, 5, 7};
  c_for_each(v, [](int& a) { ++a; });
  EXPECT_THAT(v, ElementsAre(2, 4, 6, 8));
}

TEST(ContainerAlgTest, RemoveErase) {
  std::vector<int> v = {1, 3, 2, 7, 2, 2, 3, 9, 2};
  c_remove_erase(v, 2);
  EXPECT_THAT(v, ElementsAre(1, 3, 7, 3, 9));
}

TEST(ContainerAlgTest, RemoveEraseIf) {
  std::vector<int> v = {1, 3, 4, 7, 2, 2, 3, 9, 6};
  c_remove_erase_if(v, [](int a){ return a % 2 == 0; });
  EXPECT_THAT(v, ElementsAre(1, 3, 7, 3, 9));
}

TEST(ContainerAlgTest, UniqueErase) {
  std::vector<int> v = {2, 3, 3, 2, 7, 7, 7, 4};
  c_unique_erase(v);
  EXPECT_THAT(v, ElementsAre(2, 3, 2, 7, 4));
}

TEST(ContainerAlgTest, UniqueEraseIf) {
  std::vector<int> v = {2, 3, 33, 2, 7, 77, 7, 4};
  c_unique_erase(v, [](int a, int b){ return a % 2 == b % 2; });
  EXPECT_THAT(v, ElementsAre(2, 3, 2, 7, 4));
}
