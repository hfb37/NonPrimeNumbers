#include <vector>

namespace Supp {
    bool isPrime(int n);
}

struct Policy {
    virtual int hasNonPrime(const std::vector<int>& numbers) const;
    virtual ~Policy() = default;
};

struct seq_exec : public Policy {
public:
    int hasNonPrime(const std::vector<int> &numbers) const override;
};

struct par_exec : public Policy {
public:
    int hasNonPrime(const std::vector<int>& numbers) const override;
};

int hasNonPrime(const std::vector<int>& numbers, const Policy& policy);

int hasNonPrime(const std::vector<int>& numbers);
