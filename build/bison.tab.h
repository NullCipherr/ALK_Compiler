/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_BISON_TAB_H_INCLUDED
# define YY_YY_BUILD_BISON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    TYPE_INT = 259,                /* TYPE_INT  */
    TYPE_FLT = 260,                /* TYPE_FLT  */
    TYPE_CHR = 261,                /* TYPE_CHR  */
    TYPE_STR = 262,                /* TYPE_STR  */
    TYPE_VOID = 263,               /* TYPE_VOID  */
    DECL_CREATE = 264,             /* DECL_CREATE  */
    DECL_AS = 265,                 /* DECL_AS  */
    DECL_ARRAY = 266,              /* DECL_ARRAY  */
    DECL_FUNCTION = 267,           /* DECL_FUNCTION  */
    CTRL_CHECK = 268,              /* CTRL_CHECK  */
    CTRL_THEN = 269,               /* CTRL_THEN  */
    CTRL_OTHERWISE = 270,          /* CTRL_OTHERWISE  */
    CTRL_REPEAT = 271,             /* CTRL_REPEAT  */
    CTRL_WHILE = 272,              /* CTRL_WHILE  */
    CTRL_GIVE = 273,               /* CTRL_GIVE  */
    CTRL_BACK = 274,               /* CTRL_BACK  */
    OP_ADD = 275,                  /* OP_ADD  */
    OP_SUB = 276,                  /* OP_SUB  */
    OP_MUL = 277,                  /* OP_MUL  */
    OP_DIV = 278,                  /* OP_DIV  */
    OP_ASSIGN = 279,               /* OP_ASSIGN  */
    OP_ADD_ASSIGN = 280,           /* OP_ADD_ASSIGN  */
    OP_EQ = 281,                   /* OP_EQ  */
    OP_NE = 282,                   /* OP_NE  */
    OP_LT = 283,                   /* OP_LT  */
    OP_GT = 284,                   /* OP_GT  */
    DELIM_PAREN_OPEN = 285,        /* DELIM_PAREN_OPEN  */
    DELIM_PAREN_CLOSE = 286,       /* DELIM_PAREN_CLOSE  */
    DELIM_BRACKET_OPEN = 287,      /* DELIM_BRACKET_OPEN  */
    DELIM_BRACKET_CLOSE = 288,     /* DELIM_BRACKET_CLOSE  */
    DELIM_BLOCK_OPEN = 289,        /* DELIM_BLOCK_OPEN  */
    DELIM_BLOCK_CLOSE = 290,       /* DELIM_BLOCK_CLOSE  */
    DELIM_END_STATEMENT = 291,     /* DELIM_END_STATEMENT  */
    DELIM_SEPARATOR = 292,         /* DELIM_SEPARATOR  */
    LITERAL_INT = 293,             /* LITERAL_INT  */
    LITERAL_FLT = 294,             /* LITERAL_FLT  */
    LITERAL_CHR = 295,             /* LITERAL_CHR  */
    LITERAL_STR = 296,             /* LITERAL_STR  */
    BUILT_IN_PRINT = 297,          /* "print"  */
    BUILT_IN_SCAN = 298            /* "scan"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 165 "src/bison.y"

    struct {
        char* nome;
        TipoVariavel tipo;
    } id;
    TipoVariavel tipo;
    struct {
        char* valor;
        int num;
    } literal;
    struct NoArvore* no;

#line 120 "build/bison.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_BISON_TAB_H_INCLUDED  */
