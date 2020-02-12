// Copyright (c) 2019 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef _BITCOIN_SCRIPT_MINISCRIPT_COMPILER_H_
#define _BITCOIN_SCRIPT_MINISCRIPT_COMPILER_H_

#include <script/miniscript.h>

#include <string>

struct CompilerContext {
    typedef std::string Key;

    bool ToString(const Key& key, std::string& str) const { str = key; return true; }

    template<typename I>
    bool FromString(I first, I last, Key& key) const {
        if (std::distance(first, last) == 0 || std::distance(first, last) > 17) return false;
        key = std::string(first, last);
        return true;
    }

    std::vector<unsigned char> ToPKBytes(const Key& key) const {
        std::vector<unsigned char> ret{2, 'P', 'K', 'b'};
        ret.resize(33, 0);
        std::copy(key.begin(), key.end(), ret.begin() + 4);
        return ret;
    }

    std::vector<unsigned char> ToPKHBytes(const Key& key) const {
        std::vector<unsigned char> ret{'P', 'K', 'h'};
        ret.resize(20, 0);
        std::copy(key.begin(), key.end(), ret.begin() + 3);
        return ret;
    }
};

extern const CompilerContext COMPILER_CTX;

bool Compile(const std::string& policy, miniscript::NodeRef<CompilerContext::Key>& ret, double& avgcost);

std::string Expand(std::string str);
std::string Abbreviate(std::string str);

std::string Disassemble(const CScript& script);

#endif
