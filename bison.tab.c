/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 53 "bison.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

// Protótipos de funções
const char* tipoParaString(TipoVariavel tipo);
const char* nomeVariavel(const char* nome);
TipoVariavel verificarTipos(TipoVariavel tipo1, const char* operador, TipoVariavel tipo2);
void mostrarAnaliseGramatical(const char* regra);
void mostrarAnaliseTipos(const char* operacao, TipoVariavel tipo1, TipoVariavel tipo2, TipoVariavel resultado);
extern void analise_lexica(void);  

extern int linha;
extern int total_tokens;
void yyerror(const char *s);
int yylex(void);

FILE* arvore_arquivo = NULL;
int nivel_arvore = 0;

void iniciar_arquivo_arvore() {
    arvore_arquivo = fopen("arvore_sintatica.txt", "w");
    if (arvore_arquivo == NULL) {
        printf("Erro ao criar arquivo da árvore sintática\n");
        exit(1);
    }
}

void fechar_arquivo_arvore() {
    if (arvore_arquivo != NULL) {
        fclose(arvore_arquivo);
    }
}

void mostrarAnaliseGramatical(const char* regra) {
    printf("║ Regra: %-53s ║\n", regra);
    if (arvore_arquivo != NULL) {
        for (int i = 0; i < nivel_arvore; i++) {
            fprintf(arvore_arquivo, "  ");
        }
        fprintf(arvore_arquivo, "└─ %s\n", regra);
    }
}


#line 119 "bison.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "bison.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_TYPE_INT = 4,                   /* TYPE_INT  */
  YYSYMBOL_TYPE_FLT = 5,                   /* TYPE_FLT  */
  YYSYMBOL_TYPE_CHR = 6,                   /* TYPE_CHR  */
  YYSYMBOL_TYPE_STR = 7,                   /* TYPE_STR  */
  YYSYMBOL_TYPE_VOID = 8,                  /* TYPE_VOID  */
  YYSYMBOL_DECL_CREATE = 9,                /* DECL_CREATE  */
  YYSYMBOL_DECL_AS = 10,                   /* DECL_AS  */
  YYSYMBOL_DECL_ARRAY = 11,                /* DECL_ARRAY  */
  YYSYMBOL_DECL_FUNCTION = 12,             /* DECL_FUNCTION  */
  YYSYMBOL_CTRL_CHECK = 13,                /* CTRL_CHECK  */
  YYSYMBOL_CTRL_THEN = 14,                 /* CTRL_THEN  */
  YYSYMBOL_CTRL_OTHERWISE = 15,            /* CTRL_OTHERWISE  */
  YYSYMBOL_CTRL_REPEAT = 16,               /* CTRL_REPEAT  */
  YYSYMBOL_CTRL_WHILE = 17,                /* CTRL_WHILE  */
  YYSYMBOL_CTRL_GIVE = 18,                 /* CTRL_GIVE  */
  YYSYMBOL_CTRL_BACK = 19,                 /* CTRL_BACK  */
  YYSYMBOL_OP_ADD = 20,                    /* OP_ADD  */
  YYSYMBOL_OP_SUB = 21,                    /* OP_SUB  */
  YYSYMBOL_OP_MUL = 22,                    /* OP_MUL  */
  YYSYMBOL_OP_DIV = 23,                    /* OP_DIV  */
  YYSYMBOL_OP_ASSIGN = 24,                 /* OP_ASSIGN  */
  YYSYMBOL_OP_ADD_ASSIGN = 25,             /* OP_ADD_ASSIGN  */
  YYSYMBOL_OP_EQ = 26,                     /* OP_EQ  */
  YYSYMBOL_OP_NE = 27,                     /* OP_NE  */
  YYSYMBOL_OP_LT = 28,                     /* OP_LT  */
  YYSYMBOL_OP_GT = 29,                     /* OP_GT  */
  YYSYMBOL_DELIM_PAREN_OPEN = 30,          /* DELIM_PAREN_OPEN  */
  YYSYMBOL_DELIM_PAREN_CLOSE = 31,         /* DELIM_PAREN_CLOSE  */
  YYSYMBOL_DELIM_BRACKET_OPEN = 32,        /* DELIM_BRACKET_OPEN  */
  YYSYMBOL_DELIM_BRACKET_CLOSE = 33,       /* DELIM_BRACKET_CLOSE  */
  YYSYMBOL_DELIM_BLOCK_OPEN = 34,          /* DELIM_BLOCK_OPEN  */
  YYSYMBOL_DELIM_BLOCK_CLOSE = 35,         /* DELIM_BLOCK_CLOSE  */
  YYSYMBOL_DELIM_END_STATEMENT = 36,       /* DELIM_END_STATEMENT  */
  YYSYMBOL_DELIM_SEPARATOR = 37,           /* DELIM_SEPARATOR  */
  YYSYMBOL_LITERAL_INT = 38,               /* LITERAL_INT  */
  YYSYMBOL_LITERAL_FLT = 39,               /* LITERAL_FLT  */
  YYSYMBOL_LITERAL_CHR = 40,               /* LITERAL_CHR  */
  YYSYMBOL_LITERAL_STR = 41,               /* LITERAL_STR  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_programa = 43,                  /* programa  */
  YYSYMBOL_declaracoes = 44,               /* declaracoes  */
  YYSYMBOL_declaracao = 45,                /* declaracao  */
  YYSYMBOL_declaracao_variavel = 46,       /* declaracao_variavel  */
  YYSYMBOL_declaracao_funcao = 47,         /* declaracao_funcao  */
  YYSYMBOL_parametros = 48,                /* parametros  */
  YYSYMBOL_lista_parametros = 49,          /* lista_parametros  */
  YYSYMBOL_parametro = 50,                 /* parametro  */
  YYSYMBOL_tipo = 51,                      /* tipo  */
  YYSYMBOL_comando = 52,                   /* comando  */
  YYSYMBOL_comando_check = 53,             /* comando_check  */
  YYSYMBOL_comando_repeat = 54,            /* comando_repeat  */
  YYSYMBOL_comando_give = 55,              /* comando_give  */
  YYSYMBOL_bloco = 56,                     /* bloco  */
  YYSYMBOL_comandos = 57,                  /* comandos  */
  YYSYMBOL_atribuicao = 58,                /* atribuicao  */
  YYSYMBOL_expressao = 59,                 /* expressao  */
  YYSYMBOL_termo = 60,                     /* termo  */
  YYSYMBOL_fator = 61,                     /* fator  */
  YYSYMBOL_chamada_funcao = 62,            /* chamada_funcao  */
  YYSYMBOL_argumentos = 63,                /* argumentos  */
  YYSYMBOL_lista_argumentos = 64           /* lista_argumentos  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  31
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   149

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  114

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   128,   128,   132,   133,   137,   138,   139,   143,   157,
     162,   164,   169,   170,   174,   175,   180,   184,   185,   186,
     187,   191,   192,   193,   194,   195,   199,   201,   206,   211,
     213,   218,   223,   224,   228,   230,   235,   240,   245,   250,
     251,   252,   253,   257,   261,   265,   272,   276,   280,   284,
     288,   292,   294,   298,   303,   304,   308,   309
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "TYPE_INT", "TYPE_FLT", "TYPE_CHR", "TYPE_STR", "TYPE_VOID",
  "DECL_CREATE", "DECL_AS", "DECL_ARRAY", "DECL_FUNCTION", "CTRL_CHECK",
  "CTRL_THEN", "CTRL_OTHERWISE", "CTRL_REPEAT", "CTRL_WHILE", "CTRL_GIVE",
  "CTRL_BACK", "OP_ADD", "OP_SUB", "OP_MUL", "OP_DIV", "OP_ASSIGN",
  "OP_ADD_ASSIGN", "OP_EQ", "OP_NE", "OP_LT", "OP_GT", "DELIM_PAREN_OPEN",
  "DELIM_PAREN_CLOSE", "DELIM_BRACKET_OPEN", "DELIM_BRACKET_CLOSE",
  "DELIM_BLOCK_OPEN", "DELIM_BLOCK_CLOSE", "DELIM_END_STATEMENT",
  "DELIM_SEPARATOR", "LITERAL_INT", "LITERAL_FLT", "LITERAL_CHR",
  "LITERAL_STR", "$accept", "programa", "declaracoes", "declaracao",
  "declaracao_variavel", "declaracao_funcao", "parametros",
  "lista_parametros", "parametro", "tipo", "comando", "comando_check",
  "comando_repeat", "comando_give", "bloco", "comandos", "atribuicao",
  "expressao", "termo", "fator", "chamada_funcao", "argumentos",
  "lista_argumentos", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-32)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       2,    -2,   115,   141,   -23,    -4,     5,    43,     2,   -32,
     -32,   -32,   -32,   -32,   -32,   -32,   -32,    -1,     6,     6,
       6,   -32,   -32,   -32,   -32,    45,    50,    51,     6,    36,
       1,   -32,   -32,   -32,    40,     6,   -32,   -32,   -32,   -32,
      31,     4,   -32,   -32,    35,   109,    34,    53,    -7,    55,
      57,    73,     6,   -32,    48,    85,     6,     6,     6,     6,
       6,     6,   -32,     6,     6,   -32,   -32,     6,     6,    44,
     115,   115,    77,    97,   -32,   -32,     4,     4,     4,     4,
       4,     4,   -32,   -32,   109,    52,    59,    64,    60,   -32,
      93,    72,    74,    74,   -32,    99,    74,   115,   -32,    74,
     -32,    95,   -32,   104,   -32,   -32,   -32,     3,    74,    91,
     -32,   -32,   -32,   -32
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     2,     3,
       5,     6,     7,    21,    22,    24,    23,     0,     0,     0,
      54,    17,    18,    19,    20,     0,     0,     0,     0,     0,
       0,     1,     4,    25,    46,     0,    47,    48,    49,    50,
       0,    36,    43,    52,     0,    56,     0,    55,     0,     0,
       0,     0,     0,    30,     0,     0,     0,     0,     0,     0,
       0,     0,    34,     0,     0,    35,    53,     0,     0,     0,
      12,    12,     0,     0,    29,    51,    37,    38,    39,    40,
      41,    42,    44,    45,    57,     0,     0,     0,    13,    14,
       0,     0,     0,     0,     8,     0,     0,     0,    16,     0,
      32,    26,    28,     0,    11,    15,    10,     0,     0,     0,
      31,    33,    27,     9
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -32,   -32,   -32,   123,   -32,   -32,    61,   -32,    37,    27,
      26,   -32,   -32,   -32,   -10,   -32,   -32,   -18,    83,   -31,
       0,   -32,   -32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    11,    87,    88,    89,    90,
      12,    13,    14,    15,   101,   107,    16,    40,    41,    42,
      43,    46,    47
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      17,    44,    45,    68,    34,     1,     1,    28,    17,    34,
      51,     2,    54,    29,     3,     4,     4,    55,     5,     5,
       6,     6,    18,    19,    30,    69,    63,    64,    20,    25,
      27,    35,    82,    83,    73,    33,    35,    53,   110,    36,
      37,    38,    39,    31,    36,    37,    38,    39,    48,    84,
      85,    56,    57,    49,    50,    56,    57,    58,    59,    60,
      61,    58,    59,    60,    61,    66,    52,    62,    56,    57,
      20,    65,    56,    57,    58,    59,    60,    61,    58,    59,
      60,    61,    86,   102,    74,    70,   104,    71,    94,   106,
      67,    92,    95,    56,    57,    96,    98,    97,   112,    58,
      59,    60,    61,    99,    72,    56,    57,    17,   100,   103,
     108,    58,    59,    60,    61,   109,    75,    56,    57,    21,
      22,    23,    24,    58,    59,    60,    61,   113,    93,    56,
      57,    32,    91,   111,   105,    58,    59,    60,    61,    76,
      77,    78,    79,    80,    81,    21,    22,    23,    24,    26
};

static const yytype_int8 yycheck[] =
{
       0,    19,    20,    10,     3,     3,     3,    30,     8,     3,
      28,     9,    30,    17,    12,    13,    13,    35,    16,    16,
      18,    18,    24,    25,    19,    32,    22,    23,    30,     2,
       3,    30,    63,    64,    52,    36,    30,    36,    35,    38,
      39,    40,    41,     0,    38,    39,    40,    41,     3,    67,
      68,    20,    21,     3,     3,    20,    21,    26,    27,    28,
      29,    26,    27,    28,    29,    31,    30,    36,    20,    21,
      30,    36,    20,    21,    26,    27,    28,    29,    26,    27,
      28,    29,    38,    93,    36,    30,    96,    30,    36,    99,
      37,    14,    33,    20,    21,    31,     3,    37,   108,    26,
      27,    28,    29,    31,    31,    20,    21,   107,    34,    10,
      15,    26,    27,    28,    29,    11,    31,    20,    21,     4,
       5,     6,     7,    26,    27,    28,    29,    36,    31,    20,
      21,     8,    71,   107,    97,    26,    27,    28,    29,    56,
      57,    58,    59,    60,    61,     4,     5,     6,     7,     8
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     9,    12,    13,    16,    18,    43,    44,    45,
      46,    47,    52,    53,    54,    55,    58,    62,    24,    25,
      30,     4,     5,     6,     7,    51,     8,    51,    30,    17,
      19,     0,    45,    36,     3,    30,    38,    39,    40,    41,
      59,    60,    61,    62,    59,    59,    63,    64,     3,     3,
       3,    59,    30,    36,    59,    59,    20,    21,    26,    27,
      28,    29,    36,    22,    23,    36,    31,    37,    10,    32,
      30,    30,    31,    59,    36,    31,    60,    60,    60,    60,
      60,    60,    61,    61,    59,    59,    38,    48,    49,    50,
      51,    48,    14,    31,    36,    33,    31,    37,     3,    31,
      34,    56,    56,    10,    56,    50,    56,    57,    15,    11,
      35,    52,    56,    36
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      47,    47,    48,    48,    49,    49,    50,    51,    51,    51,
      51,    52,    52,    52,    52,    52,    53,    53,    54,    55,
      55,    56,    57,    57,    58,    58,    59,    59,    59,    59,
      59,    59,    59,    60,    60,    60,    61,    61,    61,    61,
      61,    61,    61,    62,    63,    63,    64,    64
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     6,     9,
       7,     7,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     6,     8,     6,     4,
       3,     3,     0,     2,     4,     4,     1,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     1,     1,     1,     1,
       1,     3,     1,     4,     0,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: declaracoes  */
#line 128 "bison.y"
                     { mostrarAnaliseGramatical("Programa → Declarações"); }
#line 1253 "bison.tab.c"
    break;

  case 3: /* declaracoes: declaracao  */
#line 132 "bison.y"
                     { mostrarAnaliseGramatical("Declarações → Declaração"); }
#line 1259 "bison.tab.c"
    break;

  case 4: /* declaracoes: declaracoes declaracao  */
#line 133 "bison.y"
                             { mostrarAnaliseGramatical("Declarações → Declarações Declaração"); }
#line 1265 "bison.tab.c"
    break;

  case 5: /* declaracao: declaracao_variavel  */
#line 137 "bison.y"
                          { mostrarAnaliseGramatical("Declaração → Declaração Variável"); }
#line 1271 "bison.tab.c"
    break;

  case 6: /* declaracao: declaracao_funcao  */
#line 138 "bison.y"
                          { mostrarAnaliseGramatical("Declaração → Declaração Função"); }
#line 1277 "bison.tab.c"
    break;

  case 7: /* declaracao: comando  */
#line 139 "bison.y"
                         { mostrarAnaliseGramatical("Declaração → Comando"); }
#line 1283 "bison.tab.c"
    break;

  case 8: /* declaracao_variavel: DECL_CREATE tipo IDENTIFIER DECL_AS expressao DELIM_END_STATEMENT  */
#line 144 "bison.y"
        {
            mostrarAnaliseGramatical("Declaração → create tipo id as expressão");
            printf("\n╔═════════════════ VERIFICAÇÃO DE TIPOS ═════════════════╗\n");
            printf("║ Variável: %-10s  Tipo Declarado: %-15s ║\n", 
                   (yyvsp[-3].id).nome,
                   tipoParaString((yyvsp[-4].tipo)));
            printf("║ Expressão retorna: %-35s ║\n", 
                   tipoParaString((yyvsp[-1].tipo)));
            if ((yyvsp[-4].tipo) != (yyvsp[-1].tipo)) {
                printf("║ AVISO: Possível perda de precisão na atribuição      ║\n");
            }
            printf("╚═══════════════════════════════════════════════════════════╝\n");
        }
#line 1301 "bison.tab.c"
    break;

  case 9: /* declaracao_variavel: DECL_CREATE tipo IDENTIFIER DELIM_BRACKET_OPEN LITERAL_INT DELIM_BRACKET_CLOSE DECL_AS DECL_ARRAY DELIM_END_STATEMENT  */
#line 158 "bison.y"
        { mostrarAnaliseGramatical("Declaração Array → create tipo id[tamanho] as array;"); }
#line 1307 "bison.tab.c"
    break;

  case 10: /* declaracao_funcao: DECL_FUNCTION tipo IDENTIFIER DELIM_PAREN_OPEN parametros DELIM_PAREN_CLOSE bloco  */
#line 163 "bison.y"
        { mostrarAnaliseGramatical("Declaração Função → function tipo id(parâmetros) bloco"); }
#line 1313 "bison.tab.c"
    break;

  case 11: /* declaracao_funcao: DECL_FUNCTION TYPE_VOID IDENTIFIER DELIM_PAREN_OPEN parametros DELIM_PAREN_CLOSE bloco  */
#line 165 "bison.y"
        { mostrarAnaliseGramatical("Declaração Função → function void id(parâmetros) bloco"); }
#line 1319 "bison.tab.c"
    break;

  case 12: /* parametros: %empty  */
#line 169 "bison.y"
                    { mostrarAnaliseGramatical("Parâmetros → vazio"); }
#line 1325 "bison.tab.c"
    break;

  case 13: /* parametros: lista_parametros  */
#line 170 "bison.y"
                       { mostrarAnaliseGramatical("Parâmetros → Lista de Parâmetros"); }
#line 1331 "bison.tab.c"
    break;

  case 14: /* lista_parametros: parametro  */
#line 174 "bison.y"
                    { mostrarAnaliseGramatical("Lista Parâmetros → Parâmetro"); }
#line 1337 "bison.tab.c"
    break;

  case 15: /* lista_parametros: lista_parametros DELIM_SEPARATOR parametro  */
#line 176 "bison.y"
        { mostrarAnaliseGramatical("Lista Parâmetros → Lista Parâmetros, Parâmetro"); }
#line 1343 "bison.tab.c"
    break;

  case 16: /* parametro: tipo IDENTIFIER  */
#line 180 "bison.y"
                      { mostrarAnaliseGramatical("Parâmetro → Tipo Identificador"); }
#line 1349 "bison.tab.c"
    break;

  case 17: /* tipo: TYPE_INT  */
#line 184 "bison.y"
                 { (yyval.tipo) = TIPO_INT; }
#line 1355 "bison.tab.c"
    break;

  case 18: /* tipo: TYPE_FLT  */
#line 185 "bison.y"
                 { (yyval.tipo) = TIPO_FLOAT; }
#line 1361 "bison.tab.c"
    break;

  case 19: /* tipo: TYPE_CHR  */
#line 186 "bison.y"
                 { (yyval.tipo) = TIPO_CHAR; }
#line 1367 "bison.tab.c"
    break;

  case 20: /* tipo: TYPE_STR  */
#line 187 "bison.y"
                 { (yyval.tipo) = TIPO_STRING; }
#line 1373 "bison.tab.c"
    break;

  case 21: /* comando: comando_check  */
#line 191 "bison.y"
                      { mostrarAnaliseGramatical("Comando → Check"); }
#line 1379 "bison.tab.c"
    break;

  case 22: /* comando: comando_repeat  */
#line 192 "bison.y"
                      { mostrarAnaliseGramatical("Comando → Repeat"); }
#line 1385 "bison.tab.c"
    break;

  case 23: /* comando: atribuicao  */
#line 193 "bison.y"
                     { mostrarAnaliseGramatical("Comando → Atribuição"); }
#line 1391 "bison.tab.c"
    break;

  case 24: /* comando: comando_give  */
#line 194 "bison.y"
                     { mostrarAnaliseGramatical("Comando → Give"); }
#line 1397 "bison.tab.c"
    break;

  case 25: /* comando: chamada_funcao DELIM_END_STATEMENT  */
#line 195 "bison.y"
                                         { mostrarAnaliseGramatical("Comando → Chamada Função;"); }
#line 1403 "bison.tab.c"
    break;

  case 26: /* comando_check: CTRL_CHECK DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE CTRL_THEN bloco  */
#line 200 "bison.y"
        { mostrarAnaliseGramatical("Check → check (expressão) then bloco"); }
#line 1409 "bison.tab.c"
    break;

  case 27: /* comando_check: CTRL_CHECK DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE CTRL_THEN bloco CTRL_OTHERWISE bloco  */
#line 202 "bison.y"
        { mostrarAnaliseGramatical("Check → check (expressão) then bloco otherwise bloco"); }
#line 1415 "bison.tab.c"
    break;

  case 28: /* comando_repeat: CTRL_REPEAT CTRL_WHILE DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE bloco  */
#line 207 "bison.y"
        { mostrarAnaliseGramatical("Repeat → repeat while (expressão) bloco"); }
#line 1421 "bison.tab.c"
    break;

  case 29: /* comando_give: CTRL_GIVE CTRL_BACK expressao DELIM_END_STATEMENT  */
#line 212 "bison.y"
        { mostrarAnaliseGramatical("Give → give back expressão;"); }
#line 1427 "bison.tab.c"
    break;

  case 30: /* comando_give: CTRL_GIVE CTRL_BACK DELIM_END_STATEMENT  */
#line 214 "bison.y"
        { mostrarAnaliseGramatical("Give → give back;"); }
#line 1433 "bison.tab.c"
    break;

  case 31: /* bloco: DELIM_BLOCK_OPEN comandos DELIM_BLOCK_CLOSE  */
#line 219 "bison.y"
        { mostrarAnaliseGramatical("Bloco → { comandos }"); }
#line 1439 "bison.tab.c"
    break;

  case 32: /* comandos: %empty  */
#line 223 "bison.y"
                     { mostrarAnaliseGramatical("Comandos → vazio"); }
#line 1445 "bison.tab.c"
    break;

  case 33: /* comandos: comandos comando  */
#line 224 "bison.y"
                       { mostrarAnaliseGramatical("Comandos → Comandos Comando"); }
#line 1451 "bison.tab.c"
    break;

  case 34: /* atribuicao: IDENTIFIER OP_ASSIGN expressao DELIM_END_STATEMENT  */
#line 229 "bison.y"
        { mostrarAnaliseGramatical("Atribuição → id = expressão;"); }
#line 1457 "bison.tab.c"
    break;

  case 35: /* atribuicao: IDENTIFIER OP_ADD_ASSIGN expressao DELIM_END_STATEMENT  */
#line 231 "bison.y"
        { mostrarAnaliseGramatical("Atribuição → id += expressão;"); }
#line 1463 "bison.tab.c"
    break;

  case 36: /* expressao: termo  */
#line 236 "bison.y"
        { 
            mostrarAnaliseGramatical("Expressão → Termo");
            (yyval.tipo) = (yyvsp[0].tipo);
        }
#line 1472 "bison.tab.c"
    break;

  case 37: /* expressao: expressao OP_ADD termo  */
#line 241 "bison.y"
        { 
            mostrarAnaliseGramatical("Expressão → Expressão plus Termo");
            (yyval.tipo) = verificarTipos((yyvsp[-2].tipo), "plus", (yyvsp[0].tipo));
        }
#line 1481 "bison.tab.c"
    break;

  case 38: /* expressao: expressao OP_SUB termo  */
#line 246 "bison.y"
        { 
            mostrarAnaliseGramatical("Expressão → Expressão minus Termo");
            (yyval.tipo) = verificarTipos((yyvsp[-2].tipo), "minus", (yyvsp[0].tipo));
        }
#line 1490 "bison.tab.c"
    break;

  case 39: /* expressao: expressao OP_EQ termo  */
#line 250 "bison.y"
                             { mostrarAnaliseGramatical("Expressão → Expressão equals Termo"); }
#line 1496 "bison.tab.c"
    break;

  case 40: /* expressao: expressao OP_NE termo  */
#line 251 "bison.y"
                             { mostrarAnaliseGramatical("Expressão → Expressão not_equals Termo"); }
#line 1502 "bison.tab.c"
    break;

  case 41: /* expressao: expressao OP_LT termo  */
#line 252 "bison.y"
                             { mostrarAnaliseGramatical("Expressão → Expressão is_less_than Termo"); }
#line 1508 "bison.tab.c"
    break;

  case 42: /* expressao: expressao OP_GT termo  */
#line 253 "bison.y"
                             { mostrarAnaliseGramatical("Expressão → Expressão is_greater_than Termo"); }
#line 1514 "bison.tab.c"
    break;

  case 43: /* termo: fator  */
#line 258 "bison.y"
        { 
            (yyval.tipo) = (yyvsp[0].tipo);
        }
#line 1522 "bison.tab.c"
    break;

  case 44: /* termo: termo OP_MUL fator  */
#line 262 "bison.y"
        { 
            (yyval.tipo) = verificarTipos((yyvsp[-2].tipo), "times", (yyvsp[0].tipo));
        }
#line 1530 "bison.tab.c"
    break;

  case 45: /* termo: termo OP_DIV fator  */
#line 266 "bison.y"
        { 
            (yyval.tipo) = verificarTipos((yyvsp[-2].tipo), "divided_by", (yyvsp[0].tipo));
        }
#line 1538 "bison.tab.c"
    break;

  case 46: /* fator: IDENTIFIER  */
#line 273 "bison.y"
        { 
            (yyval.tipo) = (yyvsp[0].id).tipo;
        }
#line 1546 "bison.tab.c"
    break;

  case 47: /* fator: LITERAL_INT  */
#line 277 "bison.y"
        { 
            (yyval.tipo) = TIPO_INT;
        }
#line 1554 "bison.tab.c"
    break;

  case 48: /* fator: LITERAL_FLT  */
#line 281 "bison.y"
        { 
            (yyval.tipo) = TIPO_FLOAT;
        }
#line 1562 "bison.tab.c"
    break;

  case 49: /* fator: LITERAL_CHR  */
#line 285 "bison.y"
        { 
            (yyval.tipo) = TIPO_CHAR;
        }
#line 1570 "bison.tab.c"
    break;

  case 50: /* fator: LITERAL_STR  */
#line 289 "bison.y"
        { 
            (yyval.tipo) = TIPO_STRING;
        }
#line 1578 "bison.tab.c"
    break;

  case 51: /* fator: DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE  */
#line 293 "bison.y"
        { mostrarAnaliseGramatical("Fator → (Expressão)"); }
#line 1584 "bison.tab.c"
    break;

  case 52: /* fator: chamada_funcao  */
#line 294 "bison.y"
                     { mostrarAnaliseGramatical("Fator → Chamada Função"); }
#line 1590 "bison.tab.c"
    break;

  case 53: /* chamada_funcao: IDENTIFIER DELIM_PAREN_OPEN argumentos DELIM_PAREN_CLOSE  */
#line 299 "bison.y"
        { mostrarAnaliseGramatical("Chamada Função → id(Argumentos)"); }
#line 1596 "bison.tab.c"
    break;

  case 54: /* argumentos: %empty  */
#line 303 "bison.y"
                    { mostrarAnaliseGramatical("Argumentos → vazio"); }
#line 1602 "bison.tab.c"
    break;

  case 55: /* argumentos: lista_argumentos  */
#line 304 "bison.y"
                       { mostrarAnaliseGramatical("Argumentos → Lista de Argumentos"); }
#line 1608 "bison.tab.c"
    break;

  case 56: /* lista_argumentos: expressao  */
#line 308 "bison.y"
                    { mostrarAnaliseGramatical("Lista Argumentos → Expressão"); }
#line 1614 "bison.tab.c"
    break;

  case 57: /* lista_argumentos: lista_argumentos DELIM_SEPARATOR expressao  */
#line 310 "bison.y"
        { mostrarAnaliseGramatical("Lista Argumentos → Lista Argumentos, Expressão"); }
#line 1620 "bison.tab.c"
    break;


#line 1624 "bison.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 313 "bison.y"


// Implementação das funções
const char* tipoParaString(TipoVariavel tipo) {
    switch(tipo) {
        case TIPO_INT: return "int";
        case TIPO_FLOAT: return "float";
        case TIPO_CHAR: return "char";
        case TIPO_STRING: return "string";
        case TIPO_VOID: return "void";
        default: return "erro";
    }
}

void mostrarAnaliseTipos(const char* operacao, TipoVariavel tipo1, TipoVariavel tipo2, TipoVariavel resultado) {
    printf("║ Análise de Tipos: %-15s %-6s %s %-6s = %-6s ║\n",
           operacao,
           tipoParaString(tipo1),
           operacao,
           tipoParaString(tipo2),
           tipoParaString(resultado));
}

const char* nomeVariavel(const char* nome) {
    if (nome == NULL) {
        return "<<sem nome>>";
    }
    return nome;
}

TipoVariavel verificarTipos(TipoVariavel tipo1, const char* operador, TipoVariavel tipo2) {
    printf("\n╔════════════════════ ANÁLISE DE TIPOS ════════════════════╗\n");
    
    if (tipo1 == TIPO_INT && tipo2 == TIPO_INT) {
        if (strcmp(operador, "plus") == 0) {
            mostrarAnaliseTipos("Adição", tipo1, tipo2, TIPO_INT);
            return TIPO_INT;
        }
    }
    else if (tipo1 == TIPO_FLOAT || tipo2 == TIPO_FLOAT) {
        if (strcmp(operador, "plus") == 0) {
            mostrarAnaliseTipos("Adição", tipo1, tipo2, TIPO_FLOAT);
            return TIPO_FLOAT;
        }
    }
    
    printf("║ ERRO: Tipos incompatíveis para operação %-20s ║\n", operador);
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    return TIPO_ERRO;
}

void yyerror(const char *s) {
    printf("\n╔══════════════════════ ERRO SINTÁTICO ══════════════════════╗\n");
    printf("║ Linha: %-52d ║\n", linha);
    printf("║ Erro:  %-52s ║\n", s);
    printf("║                                                             ║\n");
    printf("║ Contexto do Erro:                                          ║\n");
    printf("║ - Verificar tipos dos operandos                           ║\n");
    printf("║ - Verificar sintaxe da expressão                          ║\n");
    printf("║ - Verificar declaração de variáveis                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
}

int main(void) {
    printf("\n╔════════════════════ COMPILADOR C-2024 ════════════════════╗\n");
    printf("║                                                           ║\n");
    
    if (getenv("GERAR_ARVORE")) {
        iniciar_arquivo_arvore();
    }
    
    int resultado;
    if (getenv("ANALISE_LEXICA")) {
        printf("║              Iniciando Análise Léxica                   ║\n");
        printf("║                                                           ║\n");
        printf("╚═══════════════════════════════════════════════════════════╝\n\n");
        analise_lexica();
        resultado = 0;
    } else {
        printf("║              Iniciando Análise Sintática                 ║\n");
        printf("║                                                           ║\n");
        printf("╚═══════════════════════════════════════════════════════════╝\n\n");
        resultado = yyparse();
    }
    
    if (getenv("GERAR_ARVORE")) {
        fechar_arquivo_arvore();
    }
    
    return resultado;
}
