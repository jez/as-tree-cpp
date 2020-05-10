#include <filesystem>
// TODO(jez) absl::flat_hash_map
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "spdlog/spdlog.h"

using namespace std;
namespace fs = std::filesystem;

struct PathTrie {
    map<fs::path, PathTrie> trie;

    void insert(fs::path path) {
        auto current = &this->trie;
        for (const auto &component : path) {
            if (current->find(component) != current->end()) {
                current = &current->at(component).trie;
            } else {
                (*current)[component] = {};
                current = &(*current)[component].trie;
            }
        }
    }

    string show() {
        fmt::memory_buffer result;
        this->_show(result, "");
        return to_string(result);
    }

private:
    void _show(fmt::memory_buffer &result, string_view outerPrefix) const {
        // TODO(jez) Handle non-UTF-8 output
        const auto normalPrefix = fmt::format("{}│   ", outerPrefix);
        const auto lastPrefix = fmt::format("{}    ", outerPrefix);

        size_t idx = 0;
        for (const auto &[path, it] : this->trie) {
            ++idx;

            if (idx != this->trie.size()) {
                fmt::format_to(result, "{}├── {}\n", outerPrefix, path.string());
                it._show(result, normalPrefix);
            } else {
                fmt::format_to(result, "{}└── {}\n", outerPrefix, path.string());
                it._show(result, lastPrefix);
            }
        }
    }
};

int main(int argc, char *argv[]) {
    auto trie = PathTrie{};

    for (string line; getline(cin, line);) {
        trie.insert(line);
    }

    // TODO(jez) Handle absolute paths
    fmt::print(".\n{}", trie.show());

    return 0;
}
