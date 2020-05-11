#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <unistd.h>

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

private:
    friend ostream &operator<<(ostream &result, const PathTrie &trie);

    ostream &fmt(ostream &result, string_view outerPrefix) const {
        const auto normalPrefix = string(outerPrefix) + "│   ";
        const auto lastPrefix = string(outerPrefix) + "    ";

        size_t idx = 0;
        for (const auto &[path, it] : this->trie) {
            ++idx;

            if (idx != this->trie.size()) {
                result << outerPrefix << "├── " << path.string() << "\n";
                it.fmt(result, normalPrefix);
            } else {
                result << outerPrefix << "└── " << path.string() << "\n";
                it.fmt(result, lastPrefix);
            }
        }
        return result;
    }
};

ostream &operator<<(ostream &result, const PathTrie &trie) {
    if (trie.trie.empty()) {
        return result << "\n";
    }

    if (trie.trie.size() == 1) {
        auto [path, it] = *trie.trie.begin();
        if (path.is_absolute() || path == ".") {
            result << path.string() << "\n";
            return it.fmt(result, "");
        }
    }

    result << ".\n";
    return trie.fmt(result, "");
}

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

struct Options {
    optional<string> filename;
};

Options parseOptionsOrDie(int argc, char *argv[]) {
    if (argc == 0) {
        cerr << usage;
        exit(1);
    }

    optional<string> filename;
    for (int argi = 1; argi < argc; argi++) {
        auto arg = string_view(argv[argi]);

        if (arg.size() == 0) {
            cerr << "Unrecognized argument: " << arg << "\n\n" << usage;
            exit(1);
        }

        if (arg == "-h" || arg == "--help") {
            cerr << usage;
            exit(0);
        }

        if (arg[0] == '-') {
            cerr << "Unrecognized option: " << arg << "\n\n" << usage;
            exit(1);
        }

        if (filename.has_value()) {
            cerr << "Extra argument: " << arg << "\n\n" << usage;
            exit(1);
        }

        filename = arg;
    }

    return {{filename}};
}

} // namespace

int main(int argc, char *argv[]) {
    auto options = parseOptionsOrDie(argc, argv);

    auto trie = PathTrie{};
    if (options.filename == nullopt) {
        if (isatty(STDIN_FILENO)) {
            cerr << "Warning: reading from stdin, which is a tty." << endl;
        }
        drainInputToPathTrie(cin, trie);
    } else {
        ifstream in(argv[1]);
        drainInputToPathTrie(in, trie);
    }

    cout << trie;

    return 0;
}
