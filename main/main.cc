#include <string>
#include <vector>

#include "spdlog/spdlog.h"

using namespace std;

const vector<string> listing =
  { "Brewfile"
  , "DECISIONS.md"
  , "Makefile"
  , "README.md"
  , "demo.sh"
  , "run-tests.sh"
  , "scaffold"
  , "scaffold/README.md"
  , "scaffold/TARGET.cm"
  , "scaffold/TARGET.mlb"
  , "scaffold/src"
  , "scaffold/src/call-main.sml"
  , "scaffold/src/main.sig"
  , "scaffold/src/main.sml"
  , "scaffold/symbol"
  , "symbol-new"
  , "tests"
  , "tests/logging.sh"
  , "tests/symbol"
  , "tests/symbol/errors.sh"
  , "tests/symbol/errors.sh.exp"
  , "tests/symbol/help.sh"
  , "tests/symbol/help.sh.exp"
  , "tests/symbol/infer-with.sh"
  , "tests/symbol/overwrite-existing.sh"
  , "tests/symbol/with-mlton.sh"
  , "tests/symbol/with-mlton.sh.exp"
  , "tests/symbol/with-smlnj.sh"
  , "tests/symbol/with-smlnj.sh.exp"
  , "tests/symbol-new"
  , "tests/symbol-new/existing-empty-dot.sh"
  , "tests/symbol-new/existing-empty-dot.sh.exp"
  , "tests/symbol-new/existing-empty.sh"
  , "tests/symbol-new/help.sh"
  , "tests/symbol-new/help.sh.exp"
  , "tests/symbol-new/infer-with.sh"
  , "tests/symbol-new/install-with-smlnj.sh"
  , "tests/symbol-new/new-empty.sh"
  , "tests/symbol-new/new-empty.sh.exp"
  , "tests/symbol-new/no-target.sh"
  , "tests/symbol-new/no-target.sh.exp"
  , "tests/symbol-new/version.sh"
  , "tests/symbol-new/version.sh.exp"
  , "tests/travis-install.sh"
  };

int main(int argc, char *argv[]) {
    fmt::print("Hello, world!\n");

    return 0;
}
