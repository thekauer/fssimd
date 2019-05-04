//
// Created by thekauer on 2019.05.04..
//

#ifndef SIMD_AST_H
#define SIMD_AST_H
#include "compatibility.h"
#include <iostream>
#include "hashed_string.h"
struct Pos {
    ptr line,col;
    Pos(ptr line,ptr col);
};
struct Ast {
    const enum t_ :u8{
        Op,
        Lit,
        Sep,
        Id,
        Kw,



    }type;

    Ast(t_ type);
};


struct ILit : Ast {
    const enum t_ :u8{
        Int,
        Float,
        Bool,
        Char,
        String,
    }type;
    ILit(t_ type);
};

template<typename T>
struct Lit : ILit {
    Lit(T)=delete;
};

template<>
struct Lit<int> : ILit {
    int val;
    Lit(int n) : val(n),ILit(ILit::Int){};
};
template<>
struct Lit<unsigned int> : ILit {
    unsigned int val;
    Lit(unsigned int n) : val(n),ILit(ILit::Int){};
};

template<>
struct Lit<double> : ILit {
    double val;
    Lit(double n) : val(n),ILit(ILit::Float){};
};
template<>
struct Lit<char> : ILit {
    char val;
    Lit(char n) : val(n),ILit(ILit::Char){};
};
template<>
struct Lit<bool > : ILit {
    bool val;
    Lit(bool n) : val(n),ILit(ILit::Bool){};
};
template<>
struct Lit<std::string> : ILit {
    std::string val;
    Lit(std::string n) : val(n),ILit(ILit::String){};
};

struct Op : Ast {
    const enum t_ :u8{
        Add,
        Sub,
        Mul,
        Div,
        Mod,
        Neg,
        Shl,
        Shr,

        Not,
        And,
        Or,
        Xor,
        Less,
        Greater,
        Eq,

        // +15
                Addeq,
        Subeq,
        Muleq,
        Diveq,
        Modeq,
        Negeq,
        Shleq,
        Shreq,
        Noteq,
        Andeq,
        Oreq,
        Xoreq,
        Lesseq,
        Greatereq,
        Eqeq,

        AndAnd,
        OrOr,
        AddAdd,
        SubSub
    } type;
    Op(t_ type);
};


struct Kw : Ast {
    const enum t_ : u8 {
        As, Asm, Assert, Async, Await, Bool, Break, Catch, Char, Class, Const, Continue, Cte, Cteq /*cte?*/, Delete, Double, Else, Enum, Export, Extern, False, Float, Fn, For, From, If, Import, In, Inline, Int, Match, Mod, Namespace, New, Op, Orderby, Priv, Pub, Return, Select, Self, Sizeof, Static, Struct, This, Throw, Trait, True, Try, Typedef, Typeid, Typename, Typeof, Uint, Unsigned, Using, Void, Where, While, Yield

    }type;
    Kw(t_ type);
};

struct Id : Ast {
    HashedString name;
    Id(std::string);
};


#endif //SIMD_AST_H







