//
// Created by supercb on 22-6-20.
//

#include "ir.h"

std::unordered_map<int, ConstValue *>ConstValue::POOL = {};


std::string printvalue(Value *x, IndexMapper<Value> *indexMapper) {
    std::stringstream ss;

    if (auto v = dynamic_cast<ConstValue *>(x)) {
        ss << v->imm;
    } else if (auto v = dynamic_cast<ParamRef *>(x)) {
        ss << "%" << v->decl->name;
    } else if (auto v = dynamic_cast<GlobalRef *>(x)) {
        ss << "@_" << v->decl->name;
    } else {

        ss << "%t" << indexMapper->get(x);
    }
    return ss.str();
}


//void printValue(){
//
//    if (auto x = dyn_cast<ConstValue>(pv.v)) {
//        os << x->imm;
//    } else if (auto x = dyn_cast<GlobalRef>(pv.v)) {
//        os << "%_glob_" << x->decl->name;
//    } else if (auto x = dyn_cast<ParamRef>(pv.v)) {
//        os << "%" << x->decl->name;
//    } else if (isa<UndefValue>(pv.v)) {
//        os << "undef";
//    } else if (isa<MemPhiInst>(pv.v) || isa<MemOpInst>(pv.v)) {
//        os << "mem" << pv.v_index.get(pv.v);
//    } else if (isa<StoreInst>(pv.v)) {
//        dbg("youmother");
//        os << "store" << pv.v_index.get(pv.v);
//    } else {
//        os << "%x" << pv.v_index.get(pv.v);
//    }
//    return os;
//
//
//}
void InstructionVisitor::Visit(LoadInst *x) {
    // temp ptr
    u32 t1 = v_index->alloc();
    os << "%t" << t1 << " = getelementptr inbounds i32, i32";

    os << "*  " <<printvalue(x->arr.value, v_index) << ", ";

    os << "i32 " << printvalue(x->index.value, v_index);
    //pv(v_index, x->index.value);

    os << std::endl;
    u32 t2 = v_index->get(x);

    os << "\t" << "%t" << t2 << " = load i32, i32* %t" << t1 << ", align 4" << std::endl;
}

void InstructionVisitor::Visit(BinaryInst *x) {
    auto op_name = BinaryInst::LLVM_OPS[(int) x->optype];


    if (x->optype >= OpType::Add && x->optype <= OpType::Mod) {

        u32 temp = v_index->get(x);
        os << "%t"
           << temp
           << " = "
           << op_name << " i32 "
           << printvalue(x->lhs.value, v_index)
           << ", "
           << printvalue(x->rhs.value, v_index)
           << std::endl;
    } else {

        u32 temp = v_index->alloc();
        os << "%t"
           << temp
           << " = "
           << op_name
           << " i32 "
           << printvalue(x->lhs.value, v_index)
           << ", "
           << printvalue(x->rhs.value, v_index)
           << std::endl;

        u32 tar = v_index->get(x);
        os << "\t"
           << "%t"
           << tar
           << " = "
           << "zext i1 "
           << "%t" << temp << " to i32"
           << std::endl;
    }


}

void InstructionVisitor::Visit(StoreInst *x) {
//    os << "; store " << v_index.get(x) << endl << "\t";
    // temp ptr
    u32 t1 = v_index->alloc();
    os << "%t" << t1 << " = getelementptr inbounds i32, i32";

    os << "*" << printvalue(x->arr.value, v_index) << ", ";

    os << "i32 " << printvalue(x->index.value, v_index);

//    os << "%t" << temp << " = getelementptr inbounds i32, i32";
//    os << "* " << pv(v_index, x->arr.value) << ", ";
//    os << "i32 " << pv(v_index, x->index.value);

    os << std::endl;
    os << "\t"
       << "store i32 "
       << printvalue(x->data.value, v_index)
       << ", i32* %t"
       << t1
       << ", align 4"
       << std::endl;
}

void InstructionVisitor::Visit(ReturnInst *x) {

    if (x->ret.value) {
        os << "ret i32 "
           << printvalue(x->ret.value, v_index)
           << std::endl;
    } else {
        os << "ret void" << std::endl;
    }
}


void print_dims(std::ostream &os, Expr **dims, Expr **dims_end) {
    if (dims == dims_end) {
        os << "i32 ";
    } else {
        os << "[" << dims[0]->result << " x i32] ";
    }
}

void InstructionVisitor::Visit(AllocaInst *x) {
    u32 temp = v_index->get(x);
    os << "%t" << temp << " = alloca ";
    print_dims(os, x->sym->dims.data(), x->sym->dims.data() + x->sym->dims.size());
    os << ", align 4" << std::endl;

}

void InstructionVisitor::Visit(GetElementPtrInst *x) {

//    os << "; getelementptr " << v_index.get(inst) << endl << "\t";
    u32 temp = v_index->alloc();
    os << "%t" << temp << " = mul i32 " << printvalue(x->index.value, v_index) << ", " << x->multiplier << std::endl;


    u32 tar = v_index->get(x);
    os << "%t"
       << tar
       << " = getelementptr inbounds i32, i32* "
       << printvalue(x->arr.value, v_index)
       << ", i32 "
       << "%t" << temp << std::endl;
}

void InstructionVisitor::Visit(JumpInst *x) {
    os << "br label %_" << bb_index->find(x->next)->second << std::endl;
}

void InstructionVisitor::Visit(BranchInst *x) {
    // add comment
//    os << "; if " << pv(v_index, x->cond.value) << " then _" << bb_index.find(x->left)->second << " else _"
//       << bb_index.find(x->right)->second << endl;
    u32 temp = v_index->alloc();
    os << "%t"
       << temp
       << " = icmp ne i32 "
       << printvalue(x->cond.value, v_index)
       << ", 0"
       << std::endl;


    os << "\tbr i1 %t"
       << temp
       << ", label %_" << bb_index->find(x->left)->second
       << ", label %_" << bb_index->find(x->right)->second
       << std::endl;
}

void InstructionVisitor::Visit(CallInst *x) {
    Func *callee = x->func->func;


    if (callee->is_int) {
        u32 temp = v_index->get(x);
        os << "%t"
           << temp
           << "= call i32";
    } else {
        os << "call void";
    }
    os << " @" << callee->name << "(";
    for (u32 i = 0; i < x->args.size(); i++) {
        // type
        if (callee->params[i].dims.empty()) {
            // simple
            os << "i32 ";
        } else {
            // array param
            os << "i32 * ";
        }
        // arg
        os << printvalue(x->args[i].value, v_index);
        if (i + 1 < x->args.size()) {
            // not last element
            os << ", ";
        }
    }
    os << ")"
       << std::endl;
}

void InstructionVisitor::Visit(PhiInst *x) {
}


void print_flatten_init(std::ostream &os, Expr **dims, Expr **dims_end, Expr **flatten_init, Expr **flatten_init_end) {
    if (dims == dims_end) {
        // last dim
        os << flatten_init[0]->result;
    } else {
        // one or more dims
        os << "[";
        while (flatten_init != flatten_init_end) {
            os << "i32 ";
            os << flatten_init[0]->result;
            if (flatten_init + 1 != flatten_init_end) {
                os << ", ";
            }
            flatten_init++;
        }
        os << "]";
    }
}

std::ostream &operator<<(std::ostream &os, const IrProgram &p) {
    using std::endl;

    for (auto &d: p.glob_decl) {
        os << "@_" << d->name << " = global ";
        // type
        print_dims(os, d->dims.data(), d->dims.data() + d->dims.size());
        if (d->has_init) {
            print_flatten_init(os, d->dims.data(), d->dims.data() + d->dims.size(), d->flatten_init.data(),
                               d->flatten_init.data() + d->flatten_init.size());
        } else {
            // default 0 initialized
            os << "zeroinitializer" << endl;
        }
        os << endl;
    }

    for (auto f = p.func.head; f != nullptr; f = f->next) {
        const char *decl = f->builtin ? "declare" : "define";
        const char *ret = f->func->is_int ? "i32" : "void";
        os << decl << " " << ret << " @";
        os << f->func->name << "(";
        for (auto &p: f->func->params) {
            if (p.dims.size() == 0) {
                // simple case
                os << "i32 ";
            } else {
                // array arg
                os << "i32 * ";
            }

            os << "%" << p.name;
            if (&p != &f->func->params.back()) {
                // not last element
                os << ", ";
            }
        }
        os << ")";
        if (f->builtin) {
            os << endl;
            continue;
        } else {
            os << " {" << endl;
        }

//        os << "_entry:" << endl;
        // bb的标号没有必要用IndexMapper，而且IndexMapper的编号是先到先得，这看着并不是很舒服

        std::map<BasicBlock *, u32> bb_index;
        IndexMapper<Value> v_index;

        InstructionVisitor instructionVisitor(os, &v_index, &bb_index);

        for (auto bb = f->bb.head; bb; bb = bb->next) {
            u32 idx = bb_index.size();
            bb_index.insert({bb, idx});
        }


        for (auto bb = f->bb.head; bb; bb = bb->next) {
            u32 index = bb_index.find(bb)->second;
            os << "_" << index << ":";

            if (bb->pred.size()) {
                os << "                        ; preds = ";
                for (u32 i = 0; i < bb->pred.size(); ++i) {
                    if (i != 0) os << ", ";
                    os << "%_" << bb_index.find(bb->pred[i])->second;
                }
            }

            // 这里原来会输出dom info的，现在不输出了，因为现在所有pass结束后dom info不是有效的
            os << endl;
            for (auto inst = bb->insts.head; inst != nullptr; inst = inst->next) {
                os << "\t";
                inst->Accept(&instructionVisitor);
            }
        }
        os << "}" << endl << endl;
    }
    return os;
}


void PhiInst::Accept(InstructionVisitor *x) {
    x->Visit(this);
}

void AllocaInst::Accept(InstructionVisitor *x) {
    x->Visit(this);
}


void BranchInst::Accept(InstructionVisitor *x) {
    x->Visit(this);
}

void ReturnInst::Accept(InstructionVisitor *x) {
    x->Visit(this);
}

void JumpInst::Accept(InstructionVisitor *x) {
    x->Visit(this);
}

void StoreInst::Accept(InstructionVisitor *x) {
    x->Visit(this);
}

void GetElementPtrInst::Accept(InstructionVisitor *x) {
    x->Visit(this);
}

void CallInst::Accept(InstructionVisitor *x) {
    x->Visit(this);
}


void BinaryInst::Accept(InstructionVisitor *x) {
    x->Visit(this);
}

void LoadInst::Accept(InstructionVisitor *x) {
    x->Visit(this);
}
