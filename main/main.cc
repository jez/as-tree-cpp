#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

namespace {

struct PathTrie {
    map<fs::path, PathTrie> trie;

    void insert(fs::path path) {
        auto current = this;
        for (const auto &component : path) {
            // Default constructs element if lookup fails
            current = &current->trie[component];
        }
    }

    string show() {
        ostringstream result;
        this->_show(result, "");
        return result.str();
    }

private:
    void _show(ostringstream &result, string_view outerPrefix) const {
        // TODO(jez) Handle non-UTF-8 output
        const auto normalPrefix = string(outerPrefix) + "│   ";
        const auto lastPrefix = string(outerPrefix) + "    ";

        size_t idx = 0;
        for (const auto &[path, it] : this->trie) {
            ++idx;

            if (idx != this->trie.size()) {
                result << outerPrefix << "├── " << path.string() << "\n";
                it._show(result, normalPrefix);
            } else {
                result << outerPrefix << "└── " << path.string() << "\n";
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
                cerr << "Warning: reading from stdin, which is a tty." << endl;
            }
            drainInputToPathTrie(cin, trie);
            break;
        case 2: {
            //  TODO(jez) Use cxxopt for option parsing?
            if (string("-h") == argv[1] || string("--help") == argv[1]) {
                cerr << usage;
                return 0;
            }
            ifstream in(argv[1]);
            drainInputToPathTrie(in, trie);
            break;
        }
        default:
            cerr << usage;
            return 1;
    }

    // TODO(jez) Handle absolute paths
    cout << ".\n" << trie.show();

    return 0;
}
