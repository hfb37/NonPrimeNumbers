#include <vector>
#include <thread>

struct Policy {
public:
    virtual int hasNonPrime(const std::vector<int>& numbers) const = 0;
    virtual ~Policy() = default;
protected:
    bool isPrime(int n) const;
    const size_t threads = std::thread::hardware_concurrency();
};

struct seq_exec : public Policy {
public:
    int hasNonPrime(const std::vector<int> &numbers) const override;
};

struct par_exec : public Policy {
public:
    int hasNonPrime(const std::vector<int> &numbers) const override;
};

int hasNonPrime(const std::vector<int>& numbers, const Policy& policy = seq_exec());
