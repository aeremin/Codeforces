#include <gtest/gtest.h>
#include <vector>
#include <unordered_set>
#include "algo/number_theory/primary_root.h"
#include "algo/number_theory/primes.h"

TEST(PrimaryRootTest, ReturnsPrimaryRoot) {
    auto primes = generatePrimesUntil(1000);
    for (auto p : primes) {   
        auto root = PrimeRoot(p);
        EXPECT_GE(root, 1);
        EXPECT_LE(root, p);
        std::vector<int64_t> rootPowers = { 1, root };
        while (rootPowers.back() != 1)
            rootPowers.push_back((root * rootPowers.back()) % p);

        EXPECT_EQ(p - 1, std::unordered_set<int64_t>(begin(rootPowers), end(rootPowers)).size());
    }
}