//
// Created by supercb on 22-4-27.
//

#pragma once

#include <string>
#include <utility>
#include <vector>
#include <set>
#include <cassert>


namespace CBCompiler {
    enum class LRType {
        END, UNEND
    };

    class LRToken {
    public:
        LRType type;
        std::string str;;

        bool operator<(const LRToken &r) const {
            return str < r.str;
        }

        LRToken() = default;

        LRToken(LRType type_, std::string str_) : type(type_), str(std::move(str_)) {}

        inline bool IsEnd() const {
            return type == LRType::END;
        }

        inline bool IsUnend() const {
            return type == LRType::UNEND;
        }

        bool operator==(const LRToken &r) const {
            return (type == r.type) && (str == r.str);
        }
    };

    class LR0Item {
    private:
        std::string lv;
        std::vector<LRToken> rexprs;
        int ploc;
        bool core;
        bool accept{};
    public:

        [[nodiscard]] const std::string &GetLva() const {
            return lv;
        }

        [[nodiscard]] const std::vector<LRToken> &GetRexprs() const {
            return rexprs;
        }

        [[nodiscard]] int GetPointLoc() const {
            return ploc;
        }

        void PointLocAdd() {
            assert(ploc < rexprs.size());
            ++ploc;
        }

        LR0Item(std::string lv_, std::vector<LRToken> rexprs_, int pointloc_) : lv(std::move(lv_)),
                                                                                rexprs(std::move(rexprs_)),
                                                                                ploc(pointloc_), core(false) {};


        bool tokenafterpos(LRToken &lrToken) const {
            assert(ploc <= rexprs.size());
            if (ploc == rexprs.size()) {
                return false;
            }
            lrToken = rexprs[ploc];
            return true;
        }

        bool operator==(const LR0Item &r) const;

        bool operator!=(const LR0Item &r) const;

        bool operator<(const LR0Item &r) const;
    };

}




