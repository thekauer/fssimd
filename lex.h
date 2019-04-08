#pragma once
#ifndef __COMPATIBILITY_H__
#define __COMPATIBILITY_H__
#include "compatibility.h"
#include "hashed_string.h"
class Lexem {
public:
	const enum t_ {
		Op,
		Id,
		Kw,
		Lit,
		Sep
	} type;
	Lexem(t_ type);
};


class Op : Lexem {
public:
	const enum t_ {
		Add,
		Sub,
		Mul,
		Div,
		Mod,
		Neg,
		shl,
		shr,

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

	}type;
	Op(t_ type);
};

class Id : Lexem {
public:
	HashedString name;
	Id();
	Id(std::string);
};

class Kw : Lexem {
public:
	const enum t_ {
		As, Asm, Assert, Async, Awit, Bool, Break, Catch, Char, Class, Const, Continue, Cte, Cteq /*cte?*/, Delete, Double, Else, Enum, Export, Extern, False, Float, Fn, For, From, If, Import, In, Inline, Int, Match, Mod, Namespace, New, Op, Orderby, Priv, Pub, Return, Select, Self, Sizeof, Static, Struct, This, Throw, Trait, True, Try, Typedef, Typeid, Typename, Typeof, Uint, Unsigned, Using, Void, Where, While, Yield
	}type;
	Kw(t_ type);
};


class Lex {
	std::string file;
public:
	Lex(std::string);


};


#endif