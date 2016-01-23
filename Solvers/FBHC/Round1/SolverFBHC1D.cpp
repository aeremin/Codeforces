#include <Solvers/pch.h>

using namespace std;

class SolverFBHC1D
{
public:
    void run();
    void runOneTest();

    int n, k;
    vector<vector<int>> w;
    vector<uint32_t> canBeatMasks;

    int getPlaceByWinnedRounds(int winnedRounds) const
    {
        if (winnedRounds == k)
            return 1;
        else
            return 1 + (1 << (k - 1 - winnedRounds));
    }

    uint32_t getNumBitsSet(uint32_t mask) const { return __popcnt16(mask); }
    
    vector<uint32_t> getAllSubmasks(uint32_t m) const
    {
        if (m == 0)
            return {0};

        uint32_t leastBit = m & ~(m - 1);
        auto res = getAllSubmasks(m ^ leastBit);
        size_t cnt = res.size();
        for (size_t i = 0; i < cnt; ++i)
            res.push_back(res[i] | leastBit);
        return res;
    }

    void addPossibleWinners(const uint32_t mask, vector<uint32_t>& addTo) const
    {
        auto participants = getNumBitsSet(mask);
        auto winners = participants / 2;
        auto maybeWinnersSubmasks = getAllSubmasks(mask);
        for (auto maybeWinners : maybeWinnersSubmasks)
        {
            if (getNumBitsSet(maybeWinners) == winners)
            {
                auto maybeLoosers = mask - maybeWinners;
                bool canWin = true;
                for (auto submask : getAllSubmasks(maybeWinners))
                {
                    if (getNumBitsSet(canBeatMasks[submask] & maybeLoosers) < getNumBitsSet(submask))
                    {
                        canWin = false;
                        break;
                    }
                }
                if (canWin)
                    addTo.push_back(maybeWinners);
            }
        }
    }
};

void SolverFBHC1D::run()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i)
    {
        cout << "Case #" << (i + 1) << ": \n";
        runOneTest();
    }
}

void SolverFBHC1D::runOneTest()
{
    cin >> n;
    for (k = 0; (1 << k) < n; ++k);
    w = vector<vector<int>>(n, vector<int>(n));
    for (auto& r : w)
        for (auto& elt : r)
            cin >> elt;

    uint32_t maxMask = (1 << n) - 1;
    canBeatMasks = vector<uint32_t>(maxMask + 1);
    for (uint32_t j = 0; j < n; ++j)
        for (uint32_t kk = 0; kk < n; ++kk)
            if (w[j][kk] == 1)
                for (uint32_t i = 0; i <= maxMask; ++i)
                    if (i & (1 << j))
                        canBeatMasks[i] |= (1 << kk);

    vector<vector<uint32_t>> possibleWinnersAfterRound = { {maxMask } };
    vector<uint32_t> possibleWinnersMasks = { maxMask };
    for (int iRound = 0; iRound < k; ++iRound)
    {
        possibleWinnersAfterRound.push_back({});
        auto& currRef = possibleWinnersAfterRound.back();
        for (auto w : possibleWinnersAfterRound[iRound])
            addPossibleWinners(w, currRef);

        sort(begin(currRef), end(currRef));
        currRef.erase(unique(begin(currRef), end(currRef)), end(currRef));
        possibleWinnersMasks.push_back(0);
        for (auto w : currRef)
            possibleWinnersMasks.back() |= w;
    }

    for (int iPlayer = 0; iPlayer < n; ++iPlayer)
    {
        bool beatsEveryone = (canBeatMasks[1 << iPlayer] == (maxMask - (1 << iPlayer)));
        if (beatsEveryone)
        {
            cout << "1 1\n";
            continue;
        }
        
        int maxWinnedRounds = 0;
        int minWinnedRounds = 0;
        while (maxWinnedRounds <= k && (possibleWinnersMasks[maxWinnedRounds] & (1 << iPlayer)))
            maxWinnedRounds++;
        --maxWinnedRounds;
        cout << getPlaceByWinnedRounds(maxWinnedRounds) << " " << getPlaceByWinnedRounds(minWinnedRounds) << "\n";
    }
            
}

class SolverFBHC1DTest : public FBHCProblemTest
{
public:
    SolverFBHC1DTest() : FBHCProblemTest("Inputs\\FBHC\\Round1\\D\\") {}
};

TEST_F(SolverFBHC1DTest, Example)
{
    SolverFBHC1D().run();
}