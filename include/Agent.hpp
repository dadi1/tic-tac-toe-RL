#include <vector>
#include <string>

class Agent {
public:
    virtual ~Agent() = default;

    virtual int choose_action(const std::string& state, const std::vector<int>& legal_moves) = 0;
};