// runner_traces.cc  — LOCAL TEST ONLY (do not submit)
// Reads a trace file in the lab's config format and prints a checksum
// for each `isValidScan` command:   VALID_MOVES=<count>

#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

using Student::ChessBoard;

// --- helpers ---
static inline bool starts_with(const std::string &s, const char *pfx) {
    return s.rfind(pfx, 0) == 0;
}

static inline void trim_inline_comment(std::string &line) {
    auto pos = line.find("//");
    if (pos != std::string::npos) line.erase(pos);
}

static inline void trim(std::string &s) {
    size_t i = 0;
    while (i < s.size() && std::isspace((unsigned char)s[i])) ++i;
    size_t j = s.size();
    while (j > i && std::isspace((unsigned char)s[j-1])) --j;
    if (i == 0 && j == s.size()) return;
    s = s.substr(i, j - i);
}

static Type parseTypeToken(const std::string &tok) {
    // supports r/p/b/k (case-insensitive)
    if (tok.empty()) return Rook; // fallback, shouldn't happen
    char t = std::tolower((unsigned char)tok[0]);
    if (t == 'p') return Pawn;
    if (t == 'r') return Rook;
    if (t == 'b') return Bishop;
    return King;
}

static Color parseColorToken(const std::string &tok) {
    // supports w/b (case-insensitive)
    if (!tok.empty() && (tok[0] == 'w' || tok[0] == 'W')) return White;
    return Black;
}

static int isValidScanCount(ChessBoard &board) {
    int count = 0;
    for (int fr = 0; fr < board.getNumRows(); ++fr) {
        for (int fc = 0; fc < board.getNumCols(); ++fc) {
            for (int tr = 0; tr < board.getNumRows(); ++tr) {
                for (int tc = 0; tc < board.getNumCols(); ++tc) {
                    if (board.isValidMove(fr, fc, tr, tc)) ++count;
                }
            }
        }
    }
    return count;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " <trace-file>\n";
        return 1;
    }
    std::ifstream fin(argv[1]);
    if (!fin) {
        std::cerr << "cannot open file: " << argv[1] << "\n";
        return 1;
    }

    // 1) points (ignored)
    int points = 0;
    if (!(fin >> points)) {
        std::cerr << "bad trace: missing points header\n";
        return 1;
    }

    // 2) rows cols
    int rows = 0, cols = 0;
    if (!(fin >> rows >> cols)) {
        std::cerr << "bad trace: missing rows/cols\n";
        return 1;
    }
    ChessBoard board(rows, cols);

    // 3) piece lines until '~'
    while (true) {
        std::string a;
        if (!(fin >> a)) {
            std::cerr << "bad trace: unexpected EOF before '~'\n";
            return 1;
        }
        if (a == "~") break;

        std::string b; int r, c;
        if (!(fin >> b >> r >> c)) {
            std::cerr << "bad trace: malformed piece line\n";
            return 1;
        }
        Color col = parseColorToken(a);
        Type  ty  = parseTypeToken(b);
        board.createChessPiece(col, ty, r, c);
    }

    // consume endline after '~'
    std::string line;
    std::getline(fin, line);

    // 4) commands
    int scan_idx = 0;
    while (std::getline(fin, line)) {
        trim_inline_comment(line);
        trim(line);
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "isValidScan") {
            int total = isValidScanCount(board);
            std::cout << "VALID_MOVES";
            if (scan_idx > 0) std::cout << "[" << scan_idx << "]";
            std::cout << "=" << total << "\n";
            ++scan_idx;
        } else if (cmd == "movePiece") {
            // Part 1 movePiece is a no-op stub (always false), but parsing gracefully:
            int fr, fc, tr, tc;
            if (iss >> fr >> fc >> tr >> tc) {
                (void)board.movePiece(fr, fc, tr, tc);
            }
        } else if (cmd == "underThreatScan") {
            // Not used in part1 traces; ignore safely
            // (Would require part2 implementation to be meaningful)
        } else if (starts_with(cmd, "//")) {
            // comment; ignore
        } else {
            // unknown token; ignore
        }
    }
    return 0;
}
