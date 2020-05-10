#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unistd.h>
#include <vector>

#include "spdlog/spdlog.h"

using namespace std;
namespace fs = std::filesystem;

namespace {

struct PathTrie {
    map<fs::path, PathTrie> trie;

    void insert(fs::path path) {
        auto current = &this->trie;
        for (const auto &component : path) {
            if (current->contains(component)) {
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

const string usage = "Print a list of paths as a tree of paths.\n"
                     "\n"
                     "Usage:\n"
                     "  as-tree [<file>]\n"
                     "\n"
                     "Arguments:\n"
                     "  <file>      The file to read from [default: stdin]\n"
                     "\n";

void drainInputToPathTrie(istream &is, PathTrie &trie) {
    string line;
    while (getline(is, line)) {
        trie.insert(move(line));
    }
}

} // namespace

int main(int argc, char *argv[]) {
    auto trie = PathTrie{};

    switch (argc) {
        case 1:
            if (isatty(STDIN_FILENO)) {
                fmt::print(stderr, "Warning: reading from stdin, which is a tty.\n");
            }
            drainInputToPathTrie(cin, trie);
            break;
        case 2: {
            //  TODO(jez) Use rang for option parsing?
            if (string("-h") == argv[1] || string("--help") == argv[1]) {
                fmt::print(stderr, "{}", usage);
                return 0;
            }
            ifstream in(argv[1]);
            drainInputToPathTrie(in, trie);
            break;
        }
        default:
            fmt::print(stderr, "{}", usage);
            return 1;
    }

    // TODO(jez) Handle absolute paths
    fmt::print(".\n{}", trie.show());

    return 0;
}
