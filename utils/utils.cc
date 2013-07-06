#include "utils.h"

namespace utils {
    using namespace std;

    void FatalError(string error_message) {
        cerr << error_message << "\n";
        exit(EXIT_FAILURE);
    }
} // namespace utils
