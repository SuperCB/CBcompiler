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

        bool operator!=(const LRToken &r) const {
            return !(*this == r);
        }
    };

    class LRItem {
    public:
        std::string lv;
        std::vector<LRToken> rexprs;
        int ploc;
        bool core;
        bool accept{};
        std::set<std::string> look_forward;
        std::set<std::string> temp;

        uint expression_id;

        std::string to_string() {
            std::string str = lv;
            str.append("→");
            uint i = 0;
            for (; i < rexprs.size(); ++i) {
                if (i == ploc) {
                    str.append("·");
                }
                str.append(rexprs[i].str);
                str.append(" ");
            }
            if (ploc == rexprs.size())
                str.append("·");
            return str;
        }

        [[nodiscard]] const std::string &GetLva() const {
            return lv;
        }

        [[nodiscard]] const std::vector<LRToken> &GetRexprs() const {
            return rexprs;
        }

        int GetPointLoc() const {
            return ploc;
        }

        void PointLocAdd() {
            assert(ploc < rexprs.size());
            ++ploc;
        }

        LRItem(std::string lv_, std::vector<LRToken> rexprs_, int pointloc_, uint expreid) : lv(std::move(lv_)),
                                                                                             rexprs(std::move(rexprs_)),
                                                                                             ploc(pointloc_),
                                                                                             core(false),
                                                                                             look_forward({}), temp({}),
                                                                                             expression_id(expreid) {};


        bool TokenAfterPos(LRToken &lrToken) const {
            assert(ploc <= rexprs.size());
            if (ploc == rexprs.size()) {
                return false;
            }
            lrToken = rexprs[ploc];
            return true;
        }

        bool TokenTwoAfterPos(LRToken &lrToken) const {
            assert(ploc <= rexprs.size());
            if (ploc + 1 >= rexprs.size()) {
                return false;
            }
            lrToken = rexprs[ploc + 1];
            return true;
        }

        bool operator==(const LRItem &r) const;

        bool operator!=(const LRItem &r) const;

        bool operator<(const LRItem &r) const;
    };

}




