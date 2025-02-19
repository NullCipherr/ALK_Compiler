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
#line 51 "src/bison.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "types.h"
#include "semantic.h"
#include "ast.h"

// Protótipos de funções
void mostrarAnaliseGramatical(const char* regra);
void mostrarAnaliseTipos(const char* operacao, TipoVariavel tipo1, TipoVariavel tipo2, TipoVariavel resultado);
extern void analise_lexica(void);  

extern int linha;
extern int total_tokens;
void yyerror(const char *s);
int yylex(void);

FILE* arvore_arquivo = NULL;
int nivel_arvore = 0;

AnalisadorSemantico* analisador;

int num_argumentos = 0;
int num_parametros = 0;

NoArvore* raiz_ast = NULL;  // Raiz da árvore sintática

void iniciar_arquivo_arvore() {
    if (arvore_arquivo != NULL) {
        fclose(arvore_arquivo);
    }
    arvore_arquivo = fopen("arvore_sintatica.txt", "w");
    if (arvore_arquivo == NULL) {
        fprintf(stderr, "Erro ao criar arquivo da árvore sintática: %s\n", 
                strerror(errno));
        exit(1);
    }
}

void fechar_arquivo_arvore() {
    if (arvore_arquivo != NULL) {
        fclose(arvore_arquivo);
        arvore_arquivo = NULL;  // Reseta ponteiro depois de fechar.
    }
}

// Definindo códigos ANSI para cores
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

// Função para mostrar a análise gramatical
void mostrarAnaliseGramatical(const char* regra) {
    // Null check for input parameter
    if (regra == NULL) {
        fprintf(stderr, RED "Erro: regra é NULL\n" RESET);
        return;
    }

    // Limit string length for safety
    const size_t MAX_REGRA_LEN = 80;
    char regra_safe[MAX_REGRA_LEN + 1];
    strncpy(regra_safe, regra, MAX_REGRA_LEN);
    regra_safe[MAX_REGRA_LEN] = '\0';

    // Console output with length-limited format
    printf(YELLOW "╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(YELLOW "║ Regra: %-80.80s \n" RESET, regra_safe);
    printf(YELLOW "╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n" RESET);

    // File output with safety checks
    if (arvore_arquivo != NULL) {
        // Limit indentation level
        const int MAX_NIVEL = 100;
        int nivel_seguro = (nivel_arvore > MAX_NIVEL) ? MAX_NIVEL : nivel_arvore;
        
        // Write indentation
        for (int i = 0; i < nivel_seguro && !ferror(arvore_arquivo); i++) {
            if (fputs("  ", arvore_arquivo) == EOF) {
                fprintf(stderr, RED "Erro ao escrever indentação no arquivo\n" RESET);
                return;
            }
        }
        
        // Write rule
        if (fprintf(arvore_arquivo, "└─ %s\n", regra_safe) < 0) {
            fprintf(stderr, RED "Erro ao escrever regra no arquivo\n" RESET);
            return;
        }
    }
}

void printar_erro_semantico(const char* erro_titulo, const char* mensagem, const char* identificador) {
    printf(BLUE"\n╔════════════════════════ ERRO SEMÂNTICO ════════════════════════╗\n");
    printf("║ %-51s \n", erro_titulo);
    printf("║ %-51s \n", mensagem);
    if (identificador) {
        printf("║ Variável: '%s'%*s\n", identificador, 34 - (int)strlen(identificador), "");
    }
    printf("╚════════════════════════════════════════════════════════════════╝\n\n"RESET);
}



#line 179 "build/bison.tab.c"

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
  YYSYMBOL_BUILT_IN_PRINT = 42,            /* "print"  */
  YYSYMBOL_BUILT_IN_SCAN = 43,             /* "scan"  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_programa = 45,                  /* programa  */
  YYSYMBOL_46_1 = 46,                      /* $@1  */
  YYSYMBOL_lista_declaracoes = 47,         /* lista_declaracoes  */
  YYSYMBOL_lista_comandos = 48,            /* lista_comandos  */
  YYSYMBOL_declaracao = 49,                /* declaracao  */
  YYSYMBOL_declaracao_variavel = 50,       /* declaracao_variavel  */
  YYSYMBOL_declaracao_funcao = 51,         /* declaracao_funcao  */
  YYSYMBOL_52_2 = 52,                      /* $@2  */
  YYSYMBOL_53_3 = 53,                      /* $@3  */
  YYSYMBOL_parametros = 54,                /* parametros  */
  YYSYMBOL_lista_parametros = 55,          /* lista_parametros  */
  YYSYMBOL_parametro = 56,                 /* parametro  */
  YYSYMBOL_tipo = 57,                      /* tipo  */
  YYSYMBOL_comando = 58,                   /* comando  */
  YYSYMBOL_comando_check = 59,             /* comando_check  */
  YYSYMBOL_comando_repeat = 60,            /* comando_repeat  */
  YYSYMBOL_comando_give = 61,              /* comando_give  */
  YYSYMBOL_bloco = 62,                     /* bloco  */
  YYSYMBOL_atribuicao = 63,                /* atribuicao  */
  YYSYMBOL_expressao = 64,                 /* expressao  */
  YYSYMBOL_termo = 65,                     /* termo  */
  YYSYMBOL_fator = 66,                     /* fator  */
  YYSYMBOL_chamada_funcao = 67,            /* chamada_funcao  */
  YYSYMBOL_acesso_variavel = 68,           /* acesso_variavel  */
  YYSYMBOL_argumentos = 69,                /* argumentos  */
  YYSYMBOL_lista_argumentos = 70           /* lista_argumentos  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   181

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  133

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   215,   215,   215,   242,   243,   260,   261,   277,   279,
     284,   298,   317,   325,   316,   339,   343,   350,   355,   363,
     371,   372,   373,   374,   375,   379,   381,   383,   385,   387,
     389,   394,   398,   405,   412,   429,   448,   455,   475,   502,
     525,   527,   531,   535,   540,   545,   550,   558,   560,   564,
     571,   586,   609,   611,   613,   615,   617,   619,   636,   652,
     657,   675,   688,   712,   716,   723,   728
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
  "LITERAL_STR", "\"print\"", "\"scan\"", "$accept", "programa", "$@1",
  "lista_declaracoes", "lista_comandos", "declaracao",
  "declaracao_variavel", "declaracao_funcao", "$@2", "$@3", "parametros",
  "lista_parametros", "parametro", "tipo", "comando", "comando_check",
  "comando_repeat", "comando_give", "bloco", "atribuicao", "expressao",
  "termo", "fator", "chamada_funcao", "acesso_variavel", "argumentos",
  "lista_argumentos", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-107)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -107,    10,  -107,  -107,     0,   173,   173,    17,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,    14,    31,    12,   -17,
      21,    22,    44,    45,  -107,  -107,  -107,  -107,  -107,    35,
      46,    -8,  -107,    25,    25,    25,    25,    25,    55,    13,
      25,    84,  -107,  -107,    25,    48,    65,    -5,    25,  -107,
    -107,  -107,  -107,   141,     9,  -107,   141,   141,    66,    61,
      63,    93,    25,  -107,    41,   105,    75,    74,    52,    82,
     173,    25,    25,   117,    25,    25,    25,    25,    25,    25,
      25,    25,  -107,    25,    94,   103,   129,  -107,  -107,    25,
    -107,  -107,    98,  -107,    86,  -107,   124,    99,    73,  -107,
       9,     9,     9,     9,     9,     9,  -107,  -107,   141,    25,
      95,    95,    83,   128,   104,   173,  -107,  -107,  -107,   141,
    -107,   113,  -107,  -107,   106,    95,  -107,     5,    95,  -107,
    -107,  -107,  -107
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     4,     1,     6,     0,     0,     3,     5,     8,
       9,    20,    21,    22,    23,    24,     0,     0,     0,     0,
       0,     0,     0,     0,    25,     7,    29,    30,    28,     0,
       0,     0,    12,     0,     0,    63,     0,     0,     0,     0,
       0,     0,    26,    27,     0,     0,     0,    50,     0,    52,
      53,    54,    55,    37,    40,    47,    39,    65,     0,    64,
       0,     0,     0,    35,     0,     0,    61,     0,     0,     0,
      15,    63,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,     0,     0,     0,     0,    34,    59,     0,
      60,    10,     0,    13,    16,    17,     0,     0,     0,    56,
      41,    42,    45,    46,    44,    43,    48,    49,    66,     0,
       0,     0,     0,     0,     0,     0,    19,    57,    51,    38,
       6,    31,    33,    62,     0,     0,    18,     0,     0,    11,
      14,    36,    32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -107,  -107,  -107,  -107,    20,  -107,   137,  -107,  -107,  -107,
    -107,  -107,    32,    40,  -107,  -107,  -107,  -107,  -106,  -107,
     -33,    97,   -23,  -107,  -107,    80,  -107
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     4,     7,     8,    24,    10,    46,   114,
      93,    94,    95,    96,    25,    26,    27,    28,   121,    29,
      57,    54,    55,    30,    67,    58,    59
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      53,    56,    44,    60,    61,   122,    64,    65,    18,     5,
       3,    68,     6,    37,     5,    73,    47,    31,    19,   130,
      18,    20,   132,    21,    45,    71,     5,    72,    47,    86,
      19,    80,    81,    20,    32,    21,    33,    34,    38,    98,
     131,    39,    35,    48,    36,    16,    17,    22,    23,    63,
     108,    49,    50,    51,    52,    48,   112,   106,   107,    22,
      23,    74,    75,    49,    50,    51,    52,    76,    77,    78,
      79,    42,    74,    75,    40,    41,   119,    87,    76,    77,
      78,    79,    43,    74,    75,    62,    69,    66,    91,    76,
      77,    78,    79,    74,    75,    70,    84,    82,    83,    76,
      77,    78,    79,    74,    75,    90,   118,    89,   113,    76,
      77,    78,    79,    74,    75,    92,   123,   110,   109,    76,
      77,    78,    79,   115,    85,    74,    75,   116,   128,   120,
     117,    76,    77,    78,    79,   125,    88,    74,    75,   124,
     127,     9,   129,    76,    77,    78,    79,   126,    99,    74,
      75,    97,     0,     0,     0,    76,    77,    78,    79,     0,
     111,    74,    75,     0,     0,     0,     0,    76,    77,    78,
      79,   100,   101,   102,   103,   104,   105,    11,    12,    13,
      14,    15
};

static const yytype_int16 yycheck[] =
{
      33,    34,    10,    36,    37,   111,    39,    40,     3,     9,
       0,    44,    12,    30,     9,    48,     3,     3,    13,   125,
       3,    16,   128,    18,    32,    30,     9,    32,     3,    62,
      13,    22,    23,    16,     3,    18,    24,    25,    17,    72,
      35,    19,    30,    30,    32,     5,     6,    42,    43,    36,
      83,    38,    39,    40,    41,    30,    89,    80,    81,    42,
      43,    20,    21,    38,    39,    40,    41,    26,    27,    28,
      29,    36,    20,    21,    30,    30,   109,    36,    26,    27,
      28,    29,    36,    20,    21,    30,    38,     3,    36,    26,
      27,    28,    29,    20,    21,    30,    33,    31,    37,    26,
      27,    28,    29,    20,    21,    31,    33,    32,    10,    26,
      27,    28,    29,    20,    21,    33,    33,    14,    24,    26,
      27,    28,    29,    37,    31,    20,    21,     3,    15,    34,
      31,    26,    27,    28,    29,    31,    31,    20,    21,    11,
     120,     4,    36,    26,    27,    28,    29,   115,    31,    20,
      21,    71,    -1,    -1,    -1,    26,    27,    28,    29,    -1,
      31,    20,    21,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    74,    75,    76,    77,    78,    79,     4,     5,     6,
       7,     8
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    45,    46,     0,    47,     9,    12,    48,    49,    50,
      51,     4,     5,     6,     7,     8,    57,    57,     3,    13,
      16,    18,    42,    43,    50,    58,    59,    60,    61,    63,
      67,     3,     3,    24,    25,    30,    32,    30,    17,    19,
      30,    30,    36,    36,    10,    32,    52,     3,    30,    38,
      39,    40,    41,    64,    65,    66,    64,    64,    69,    70,
      64,    64,    30,    36,    64,    64,     3,    68,    64,    38,
      30,    30,    32,    64,    20,    21,    26,    27,    28,    29,
      22,    23,    31,    37,    33,    31,    64,    36,    31,    32,
      31,    36,    33,    54,    55,    56,    57,    69,    64,    31,
      65,    65,    65,    65,    65,    65,    66,    66,    64,    24,
      14,    31,    64,    10,    53,    37,     3,    31,    33,    64,
      34,    62,    62,    33,    11,    31,    56,    48,    15,    36,
      62,    35,    62
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    46,    45,    47,    47,    48,    48,    49,    49,
      50,    50,    52,    53,    51,    54,    54,    55,    55,    56,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    58,
      58,    59,    59,    60,    61,    61,    62,    63,    63,    63,
      64,    64,    64,    64,    64,    64,    64,    65,    65,    65,
      66,    66,    66,    66,    66,    66,    66,    66,    67,    67,
      67,    68,    68,    69,    69,    70,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     0,     2,     0,     2,     1,     1,
       6,     9,     0,     0,     9,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     1,
       1,     6,     8,     6,     4,     3,     3,     3,     6,     3,
       1,     3,     3,     3,     3,     3,     3,     1,     3,     3,
       1,     4,     1,     1,     1,     1,     3,     4,     4,     4,
       4,     1,     4,     0,     1,     1,     3
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
  case 2: /* $@1: %empty  */
#line 215 "src/bison.y"
      { 
        analisador = iniciar_analisador_semantico();
        mudar_escopo(analisador, "global");
      }
#line 1340 "build/bison.tab.c"
    break;

  case 3: /* programa: $@1 lista_declaracoes lista_comandos  */
#line 221 "src/bison.y"
      {
          // Combina declarações e comandos em uma única lista
          NoArvore* lista_completa = (yyvsp[-1].no);
          if (lista_completa != NULL) {
              NoArvore* ultimo = lista_completa;
              while (ultimo->proximo != NULL) {
                  ultimo = ultimo->proximo;
              }
              ultimo->proximo = (yyvsp[0].no);
          } else {
              lista_completa = (yyvsp[0].no);
          }
          raiz_ast = criar_no_programa(lista_completa);
          if (arvore_arquivo != NULL) {
              // imprimir_arvore(raiz_ast, arvore_arquivo, 0);
          }
      }
#line 1362 "build/bison.tab.c"
    break;

  case 4: /* lista_declaracoes: %empty  */
#line 242 "src/bison.y"
        { (yyval.no) = NULL; }
#line 1368 "build/bison.tab.c"
    break;

  case 5: /* lista_declaracoes: lista_declaracoes declaracao  */
#line 244 "src/bison.y"
        { 
            if ((yyvsp[-1].no) == NULL) {
                (yyval.no) = (yyvsp[0].no);
            } else {
                NoArvore* ultimo = (yyvsp[-1].no);
                while (ultimo->proximo != NULL) {
                    ultimo = ultimo->proximo;
                }
                ultimo->proximo = (yyvsp[0].no);
                (yyval.no) = (yyvsp[-1].no);
            }
        }
#line 1385 "build/bison.tab.c"
    break;

  case 6: /* lista_comandos: %empty  */
#line 260 "src/bison.y"
        { (yyval.no) = NULL; }
#line 1391 "build/bison.tab.c"
    break;

  case 7: /* lista_comandos: lista_comandos comando  */
#line 262 "src/bison.y"
        {
            if ((yyvsp[-1].no) == NULL) {
                (yyval.no) = (yyvsp[0].no);
            } else {
                NoArvore* ultimo = (yyvsp[-1].no);
                while (ultimo->proximo != NULL) {
                    ultimo = ultimo->proximo;
                }
                ultimo->proximo = (yyvsp[0].no);
                (yyval.no) = (yyvsp[-1].no);
            }
        }
#line 1408 "build/bison.tab.c"
    break;

  case 8: /* declaracao: declaracao_variavel  */
#line 278 "src/bison.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 1414 "build/bison.tab.c"
    break;

  case 9: /* declaracao: declaracao_funcao  */
#line 280 "src/bison.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 1420 "build/bison.tab.c"
    break;

  case 10: /* declaracao_variavel: DECL_CREATE tipo IDENTIFIER DECL_AS expressao DELIM_END_STATEMENT  */
#line 285 "src/bison.y"
        {
            if (!inserir_simbolo(analisador, (yyvsp[-3].id).nome, (yyvsp[-4].tipo))) {
                printar_erro_semantico("Variável já declarada", "A variável já foi declarada anteriormente", (yyvsp[-3].id).nome);
                YYERROR;
            }
            // Verificar o tipo da expressão através do analisador semântico
            SimboloEntrada* simbolo = buscar_simbolo(analisador, (yyvsp[-3].id).nome);
            if (!verificar_compatibilidade_tipos(analisador, (yyvsp[-4].tipo), simbolo->tipo, (yyvsp[-3].id).nome)) {
                printar_erro_semantico("Tipo incompatível", "Erro ao inicializar a variável com tipo incompatível", (yyvsp[-3].id).nome);
                YYERROR;
            }
            (yyval.no) = criar_no_declaracao_var((yyvsp[-3].id).nome, (yyvsp[-4].tipo), (yyvsp[-1].no));
        }
#line 1438 "build/bison.tab.c"
    break;

  case 11: /* declaracao_variavel: DECL_CREATE tipo IDENTIFIER DELIM_BRACKET_OPEN LITERAL_INT DELIM_BRACKET_CLOSE DECL_AS DECL_ARRAY DELIM_END_STATEMENT  */
#line 300 "src/bison.y"
        {
            int tamanho = atoi((yyvsp[-4].literal).valor);
            if (tamanho <= 0) {
                printar_erro_semantico("Tamanho inválido", "O tamanho do vetor deve ser maior que zero.",(yyvsp[-6].id).nome);
                YYERROR;
            }
            if (!inserir_vetor(analisador, (yyvsp[-6].id).nome, (yyvsp[-7].tipo), tamanho)) {
                printar_erro_semantico("Variável já declarada","A variável já foi declarada anteriormente.",(yyvsp[-6].id).nome);
                YYERROR;
            }
            NoArvore* literal = criar_no_literal((yyvsp[-4].literal).valor, TIPO_INT);
            (yyval.no) = criar_no_declaracao_var((yyvsp[-6].id).nome, TIPO_VETOR, literal);
        }
#line 1456 "build/bison.tab.c"
    break;

  case 12: /* $@2: %empty  */
#line 317 "src/bison.y"
        {
            // Criar novo escopo para a função
            char escopo_funcao[256];
            snprintf(escopo_funcao, sizeof(escopo_funcao), "funcao_%s", (yyvsp[0].id).nome);
            mudar_escopo(analisador, escopo_funcao);
            inserir_funcao(analisador, (yyvsp[0].id).nome, (yyvsp[-1].tipo));
        }
#line 1468 "build/bison.tab.c"
    break;

  case 13: /* $@3: %empty  */
#line 325 "src/bison.y"
        {
            // Registrar o número de parâmetros
            registrar_parametros_funcao(analisador, (yyvsp[-3].id).nome, num_parametros);
        }
#line 1477 "build/bison.tab.c"
    break;

  case 14: /* declaracao_funcao: DECL_FUNCTION tipo IDENTIFIER $@2 DELIM_PAREN_OPEN parametros $@3 DELIM_PAREN_CLOSE bloco  */
#line 330 "src/bison.y"
        {
            // Voltar ao escopo global após a função
            mudar_escopo(analisador, "global");
            (yyval.no) = criar_no_declaracao_func((yyvsp[-6].id).nome, (yyvsp[-7].tipo), (yyvsp[-3].no), (yyvsp[0].no));
        }
#line 1487 "build/bison.tab.c"
    break;

  case 15: /* parametros: %empty  */
#line 339 "src/bison.y"
        { 
            mostrarAnaliseGramatical("Parâmetros → vazio");
            num_parametros = 0;
        }
#line 1496 "build/bison.tab.c"
    break;

  case 16: /* parametros: lista_parametros  */
#line 344 "src/bison.y"
        { 
            mostrarAnaliseGramatical("Parâmetros → Lista Parâmetros");
        }
#line 1504 "build/bison.tab.c"
    break;

  case 17: /* lista_parametros: parametro  */
#line 351 "src/bison.y"
        { 
            mostrarAnaliseGramatical("Lista Parâmetros → Parâmetro");
            num_parametros = 1;
        }
#line 1513 "build/bison.tab.c"
    break;

  case 18: /* lista_parametros: lista_parametros DELIM_SEPARATOR parametro  */
#line 356 "src/bison.y"
        { 
            mostrarAnaliseGramatical("Lista Parâmetros → Lista Parâmetros , Parâmetro");
            num_parametros++;
        }
#line 1522 "build/bison.tab.c"
    break;

  case 19: /* parametro: tipo IDENTIFIER  */
#line 364 "src/bison.y"
        {
            mostrarAnaliseGramatical("Parâmetro → Tipo Identificador");
            inserir_parametro(analisador, (yyvsp[0].id).nome, (yyvsp[-1].tipo));
        }
#line 1531 "build/bison.tab.c"
    break;

  case 20: /* tipo: TYPE_INT  */
#line 371 "src/bison.y"
                 { (yyval.tipo) = TIPO_INT; }
#line 1537 "build/bison.tab.c"
    break;

  case 21: /* tipo: TYPE_FLT  */
#line 372 "src/bison.y"
                 { (yyval.tipo) = TIPO_FLOAT; }
#line 1543 "build/bison.tab.c"
    break;

  case 22: /* tipo: TYPE_CHR  */
#line 373 "src/bison.y"
                 { (yyval.tipo) = TIPO_CHAR; }
#line 1549 "build/bison.tab.c"
    break;

  case 23: /* tipo: TYPE_STR  */
#line 374 "src/bison.y"
                 { (yyval.tipo) = TIPO_STRING; }
#line 1555 "build/bison.tab.c"
    break;

  case 24: /* tipo: TYPE_VOID  */
#line 375 "src/bison.y"
                 { (yyval.tipo) = TIPO_VOID; }
#line 1561 "build/bison.tab.c"
    break;

  case 25: /* comando: declaracao_variavel  */
#line 380 "src/bison.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 1567 "build/bison.tab.c"
    break;

  case 26: /* comando: atribuicao DELIM_END_STATEMENT  */
#line 382 "src/bison.y"
        { (yyval.no) = (yyvsp[-1].no); }
#line 1573 "build/bison.tab.c"
    break;

  case 27: /* comando: chamada_funcao DELIM_END_STATEMENT  */
#line 384 "src/bison.y"
        { (yyval.no) = (yyvsp[-1].no); }
#line 1579 "build/bison.tab.c"
    break;

  case 28: /* comando: comando_give  */
#line 386 "src/bison.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 1585 "build/bison.tab.c"
    break;

  case 29: /* comando: comando_check  */
#line 388 "src/bison.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 1591 "build/bison.tab.c"
    break;

  case 30: /* comando: comando_repeat  */
#line 390 "src/bison.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 1597 "build/bison.tab.c"
    break;

  case 31: /* comando_check: CTRL_CHECK DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE CTRL_THEN bloco  */
#line 395 "src/bison.y"
        {
            (yyval.no) = criar_no_if((yyvsp[-3].no), (yyvsp[0].no), NULL);
        }
#line 1605 "build/bison.tab.c"
    break;

  case 32: /* comando_check: CTRL_CHECK DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE CTRL_THEN bloco CTRL_OTHERWISE bloco  */
#line 399 "src/bison.y"
        {
            (yyval.no) = criar_no_if((yyvsp[-5].no), (yyvsp[-2].no), (yyvsp[0].no));
        }
#line 1613 "build/bison.tab.c"
    break;

  case 33: /* comando_repeat: CTRL_REPEAT CTRL_WHILE DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE bloco  */
#line 406 "src/bison.y"
        {
            (yyval.no) = criar_no_while((yyvsp[-2].no), (yyvsp[0].no));
        }
#line 1621 "build/bison.tab.c"
    break;

  case 34: /* comando_give: CTRL_GIVE CTRL_BACK expressao DELIM_END_STATEMENT  */
#line 413 "src/bison.y"
        {
            mostrarAnaliseGramatical("Give → give back expressão;");
            // Verificar se o tipo de retorno corresponde ao tipo da função
            if (analisador->escopo_atual != NULL && 
                strncmp(analisador->escopo_atual, "funcao_", 7) == 0) {
                SimboloEntrada* func = buscar_simbolo(analisador, analisador->escopo_atual + 7);
                if (func && func->info.funcao.tipo_retorno != (yyvsp[-1].no)->info.literal.tipo) {
                    printar_erro_semantico(
                        "Erro de Tipo de Retorno",
                        "Tipo de retorno incompatível na função",
                        analisador->escopo_atual + 7
                    );
                    analisador->num_erros++;
                }
            }
        }
#line 1642 "build/bison.tab.c"
    break;

  case 35: /* comando_give: CTRL_GIVE CTRL_BACK DELIM_END_STATEMENT  */
#line 430 "src/bison.y"
        {
            mostrarAnaliseGramatical("Give → give back;");
            if (analisador->escopo_atual != NULL && 
                strncmp(analisador->escopo_atual, "funcao_", 7) == 0) {
                SimboloEntrada* func = buscar_simbolo(analisador, analisador->escopo_atual + 7);
                if (func && func->info.funcao.tipo_retorno != TIPO_VOID) {
                     printar_erro_semantico(
                        "Erro de Tipo de Retorno",
                        "Função deve retornar um valor",
                        analisador->escopo_atual + 7
                    );
                    analisador->num_erros++;
                }
            }
        }
#line 1662 "build/bison.tab.c"
    break;

  case 36: /* bloco: DELIM_BLOCK_OPEN lista_comandos DELIM_BLOCK_CLOSE  */
#line 449 "src/bison.y"
        {
            mostrarAnaliseGramatical("Bloco → { Lista Comandos }");
        }
#line 1670 "build/bison.tab.c"
    break;

  case 37: /* atribuicao: IDENTIFIER OP_ASSIGN expressao  */
#line 456 "src/bison.y"
        {
            mostrarAnaliseGramatical("Atribuição → Identificador = Expressão");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, (yyvsp[-2].id).nome);
            if (simbolo == NULL) {
                printar_erro_semantico(
                    "Variável Não Declarada",
                    "Variável não foi declarada antes do uso",
                    (yyvsp[-2].id).nome
                );
                analisador->num_erros++;
            } else if (!verificar_compatibilidade_tipos(analisador, simbolo->tipo, (yyvsp[0].no)->info.literal.tipo, (yyvsp[-2].id).nome)) {
                printar_erro_semantico(
                    "Tipo Incompatível",
                    "Tipo incompatível na atribuição",
                    (yyvsp[-2].id).nome
                );
                analisador->num_erros++;
            }
        }
#line 1694 "build/bison.tab.c"
    break;

  case 38: /* atribuicao: IDENTIFIER DELIM_BRACKET_OPEN expressao DELIM_BRACKET_CLOSE OP_ASSIGN expressao  */
#line 476 "src/bison.y"
        {
            mostrarAnaliseGramatical("Atribuição → Identificador[Expressão] = Expressão");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, (yyvsp[-5].id).nome);
            if (simbolo == NULL) {
                printar_erro_semantico(
                    "Variável Não Declarada",
                    "Variável não foi declarada antes do uso",
                    (yyvsp[-5].id).nome
                );
                analisador->num_erros++;
            } else if (simbolo->tipo != TIPO_VETOR) {
                printar_erro_semantico(
                    "Erro de Tipo",
                    "Variável não é um vetor",
                    (yyvsp[-5].id).nome
                );
                analisador->num_erros++;
            } else if (!verificar_compatibilidade_tipos(analisador, simbolo->info.vetor.tipo_base, (yyvsp[0].no)->info.literal.tipo, (yyvsp[-5].id).nome)) {
                printar_erro_semantico(
                    "Tipo Incompatível",
                    "Tipo incompatível na atribuição",
                    (yyvsp[-5].id).nome
                );
                analisador->num_erros++;
            }
        }
#line 1725 "build/bison.tab.c"
    break;

  case 39: /* atribuicao: IDENTIFIER OP_ADD_ASSIGN expressao  */
#line 503 "src/bison.y"
        {
            mostrarAnaliseGramatical("Atribuição → Identificador += Expressão");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, (yyvsp[-2].id).nome);
            if (simbolo == NULL) {
                printar_erro_semantico(
                    "Variável Não Declarada",
                    "Variável não foi declarada antes do uso",
                    (yyvsp[-2].id).nome
                );
                analisador->num_erros++;
            } else if (!verificar_compatibilidade_tipos(analisador, simbolo->tipo, (yyvsp[0].no)->info.literal.tipo, (yyvsp[-2].id).nome)) {
                printar_erro_semantico(
                    "Tipo Incompatível",
                    "Tipo incompatível na operação '+='",
                    (yyvsp[-2].id).nome
                );
                analisador->num_erros++;
            }
        }
#line 1749 "build/bison.tab.c"
    break;

  case 40: /* expressao: termo  */
#line 526 "src/bison.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 1755 "build/bison.tab.c"
    break;

  case 41: /* expressao: expressao OP_ADD termo  */
#line 528 "src/bison.y"
        { 
            (yyval.no) = criar_no_expressao("plus", (yyvsp[-2].no), (yyvsp[0].no));
        }
#line 1763 "build/bison.tab.c"
    break;

  case 42: /* expressao: expressao OP_SUB termo  */
#line 532 "src/bison.y"
        { 
            (yyval.no) = criar_no_expressao("minus", (yyvsp[-2].no), (yyvsp[0].no));
        }
#line 1771 "build/bison.tab.c"
    break;

  case 43: /* expressao: expressao OP_GT termo  */
#line 536 "src/bison.y"
        { 
            mostrarAnaliseGramatical("Expressão → Expressão is_greater_than Termo");
            (yyval.no) = TIPO_INT;  // Operações relacionais retornam tipo booleano (int)
        }
#line 1780 "build/bison.tab.c"
    break;

  case 44: /* expressao: expressao OP_LT termo  */
#line 541 "src/bison.y"
        { 
            mostrarAnaliseGramatical("Expressão → Expressão is_less_than Termo");
            (yyval.no) = TIPO_INT;
        }
#line 1789 "build/bison.tab.c"
    break;

  case 45: /* expressao: expressao OP_EQ termo  */
#line 546 "src/bison.y"
        { 
            mostrarAnaliseGramatical("Expressão → Expressão equals Termo");
            (yyval.no) = TIPO_INT;
        }
#line 1798 "build/bison.tab.c"
    break;

  case 46: /* expressao: expressao OP_NE termo  */
#line 551 "src/bison.y"
        { 
            mostrarAnaliseGramatical("Expressão → Expressão not_equals Termo");
            (yyval.no) = TIPO_INT;
        }
#line 1807 "build/bison.tab.c"
    break;

  case 47: /* termo: fator  */
#line 559 "src/bison.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 1813 "build/bison.tab.c"
    break;

  case 48: /* termo: termo OP_MUL fator  */
#line 561 "src/bison.y"
        { 
            (yyval.no) = criar_no_expressao("times", (yyvsp[-2].no), (yyvsp[0].no));
        }
#line 1821 "build/bison.tab.c"
    break;

  case 49: /* termo: termo OP_DIV fator  */
#line 565 "src/bison.y"
        { 
            (yyval.no) = criar_no_expressao("divided_by", (yyvsp[-2].no), (yyvsp[0].no));
        }
#line 1829 "build/bison.tab.c"
    break;

  case 50: /* fator: IDENTIFIER  */
#line 572 "src/bison.y"
        { 
            SimboloEntrada* simbolo = buscar_simbolo(analisador, (yyvsp[0].id).nome);
            if (simbolo == NULL) {
                printar_erro_semantico(
                    "Variável Não Declarada",
                    "Variável não foi declarada antes do uso",
                    (yyvsp[0].id).nome
                );
                analisador->num_erros++;
                (yyval.no) = criar_no_identificador((yyvsp[0].id).nome, TIPO_ERRO);
            } else {
                (yyval.no) = criar_no_identificador((yyvsp[0].id).nome, simbolo->tipo);
            }
        }
#line 1848 "build/bison.tab.c"
    break;

  case 51: /* fator: IDENTIFIER DELIM_BRACKET_OPEN expressao DELIM_BRACKET_CLOSE  */
#line 587 "src/bison.y"
        {
            SimboloEntrada* simbolo = buscar_simbolo(analisador, (yyvsp[-3].id).nome);
            if (simbolo == NULL) {
                printar_erro_semantico(
                    "Variável Não Declarada",
                    "Variável não foi declarada antes do uso",
                    (yyvsp[-3].id).nome
                );
                analisador->num_erros++;
                (yyval.no) = criar_no_identificador((yyvsp[-3].id).nome, TIPO_ERRO);
            } else if (simbolo->tipo != TIPO_VETOR) {
                printar_erro_semantico(
                    "Tipo de Variável Inválido",
                    "Variável não é um vetor",
                    (yyvsp[-3].id).nome
                );
                analisador->num_erros++;
                (yyval.no) = criar_no_identificador((yyvsp[-3].id).nome, TIPO_ERRO);
            } else {
                (yyval.no) = criar_no_identificador((yyvsp[-3].id).nome, simbolo->info.vetor.tipo_base);
            }
        }
#line 1875 "build/bison.tab.c"
    break;

  case 52: /* fator: LITERAL_INT  */
#line 610 "src/bison.y"
        { (yyval.no) = criar_no_literal((yyvsp[0].literal).valor, TIPO_INT); }
#line 1881 "build/bison.tab.c"
    break;

  case 53: /* fator: LITERAL_FLT  */
#line 612 "src/bison.y"
        { (yyval.no) = criar_no_literal((yyvsp[0].literal).valor, TIPO_FLOAT); }
#line 1887 "build/bison.tab.c"
    break;

  case 54: /* fator: LITERAL_CHR  */
#line 614 "src/bison.y"
        { (yyval.no) = criar_no_literal((yyvsp[0].literal).valor, TIPO_CHAR); }
#line 1893 "build/bison.tab.c"
    break;

  case 55: /* fator: LITERAL_STR  */
#line 616 "src/bison.y"
        { (yyval.no) = criar_no_literal((yyvsp[0].literal).valor, TIPO_STRING); }
#line 1899 "build/bison.tab.c"
    break;

  case 56: /* fator: DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE  */
#line 618 "src/bison.y"
        { (yyval.no) = (yyvsp[-1].no); }
#line 1905 "build/bison.tab.c"
    break;

  case 57: /* fator: IDENTIFIER DELIM_PAREN_OPEN argumentos DELIM_PAREN_CLOSE  */
#line 620 "src/bison.y"
        {
            SimboloEntrada* func = buscar_simbolo(analisador, (yyvsp[-3].id).nome);
            if (func == NULL || func->tipo != TIPO_FUNCAO) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Função '%s' não declarada                             ║\n", (yyvsp[-3].id).nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
                (yyval.no) = NULL;
            } else {
                verificar_chamada_funcao(analisador, (yyvsp[-3].id).nome, num_argumentos);
                (yyval.no) = criar_no_chamada_func((yyvsp[-3].id).nome, (yyvsp[-1].no));
            }
        }
#line 1923 "build/bison.tab.c"
    break;

  case 58: /* chamada_funcao: IDENTIFIER DELIM_PAREN_OPEN argumentos DELIM_PAREN_CLOSE  */
#line 637 "src/bison.y"
        {
            SimboloEntrada* func = buscar_simbolo(analisador, (yyvsp[-3].id).nome);
            if (func == NULL || func->tipo != TIPO_FUNCAO) {
                printar_erro_semantico(
                    "Função Não Declarada",
                    "Função não foi declarada ou não é do tipo função",
                    (yyvsp[-3].id).nome
                );
                analisador->num_erros++;
                (yyval.no) = NULL;
            } else {
                verificar_chamada_funcao(analisador, (yyvsp[-3].id).nome, num_argumentos);
                (yyval.no) = criar_no_chamada_func((yyvsp[-3].id).nome, (yyvsp[-1].no));
            }
        }
#line 1943 "build/bison.tab.c"
    break;

  case 59: /* chamada_funcao: "print" DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE  */
#line 653 "src/bison.y"
        {
            mostrarAnaliseGramatical("Chamada Função → print ( Expressão )");
            (yyval.no) = criar_no_chamada_func("print", (yyvsp[-1].no));
        }
#line 1952 "build/bison.tab.c"
    break;

  case 60: /* chamada_funcao: "scan" DELIM_PAREN_OPEN acesso_variavel DELIM_PAREN_CLOSE  */
#line 658 "src/bison.y"
        {
            mostrarAnaliseGramatical("Chamada Função → scan ( Acesso Variável )");
            if ((yyvsp[-1].id).tipo == TIPO_INT || (yyvsp[-1].id).tipo == TIPO_FLOAT || (yyvsp[-1].id).tipo == TIPO_CHAR || (yyvsp[-1].id).tipo == TIPO_STRING) {
                (yyval.no) = criar_no_chamada_func("scan", criar_no_identificador((yyvsp[-1].id).nome, (yyvsp[-1].id).tipo));
            } else {
                printar_erro_semantico(
                    "Tipo Inválido para scan",
                    "Tipo inválido para scan. Tipos permitidos: int, float, char, string",
                    tipoParaString((yyvsp[-1].id).tipo)
                );
                analisador->num_erros++;
                (yyval.no) = NULL;
            }
        }
#line 1971 "build/bison.tab.c"
    break;

  case 61: /* acesso_variavel: IDENTIFIER  */
#line 676 "src/bison.y"
        {
            mostrarAnaliseGramatical("Acesso Variável → Identificador");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, (yyvsp[0].id).nome);
            if (simbolo == NULL) {
                printar_erro_semantico(
                    "Variável não declarada",
                    "A variável não foi declarada antes de ser utilizada.",
                    (yyvsp[0].id).nome
                );
                analisador->num_erros++;
            }
        }
#line 1988 "build/bison.tab.c"
    break;

  case 62: /* acesso_variavel: IDENTIFIER DELIM_BRACKET_OPEN expressao DELIM_BRACKET_CLOSE  */
#line 689 "src/bison.y"
        {
            mostrarAnaliseGramatical("Acesso Variável → Identificador [ Expressão ]");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, (yyvsp[-3].id).nome);
            if (simbolo == NULL) {
                printar_erro_semantico(
                    "Variável não declarada",
                    "A variável não foi declarada antes de ser utilizada.",
                    (yyvsp[-3].id).nome
                );
                analisador->num_erros++;
            } else if (simbolo->tipo != TIPO_VETOR) {
                printar_erro_semantico(
                    "Não é um vetor",
                    "A variável acessada não é um vetor.",
                    (yyvsp[-3].id).nome
                );
                analisador->num_erros++;
            }
        }
#line 2012 "build/bison.tab.c"
    break;

  case 63: /* argumentos: %empty  */
#line 712 "src/bison.y"
        { 
            mostrarAnaliseGramatical("Argumentos → vazio");
            num_argumentos = 0;
        }
#line 2021 "build/bison.tab.c"
    break;

  case 64: /* argumentos: lista_argumentos  */
#line 717 "src/bison.y"
        { 
            mostrarAnaliseGramatical("Argumentos → Lista Argumentos");
        }
#line 2029 "build/bison.tab.c"
    break;

  case 65: /* lista_argumentos: expressao  */
#line 724 "src/bison.y"
        { 
            mostrarAnaliseGramatical("Lista Argumentos → Expressão");
            num_argumentos = 1;
        }
#line 2038 "build/bison.tab.c"
    break;

  case 66: /* lista_argumentos: lista_argumentos DELIM_SEPARATOR expressao  */
#line 729 "src/bison.y"
        { 
            mostrarAnaliseGramatical("Lista Argumentos → Lista Argumentos , Expressão");
            num_argumentos++;
        }
#line 2047 "build/bison.tab.c"
    break;


#line 2051 "build/bison.tab.c"

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

#line 735 "src/bison.y"


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
    printf("╚═══════════════════════════════════════════════════════════╝\n\n");
    return TIPO_ERRO;
}

void yyerror(const char *s) {
    printf(RED"\n╔════════════════════════ ERRO SINTÁTICO ════════════════════════╗\n");
    printf("║ Linha: %-51d     ║\n", linha);
    printf("║ Erro:  %-51s     ║\n", s);
    printf("║                                                                ║\n");
    printf("║ Contexto do Erro:                                              ║\n");
    printf("║ - Verificar tipos dos operandos                                ║\n");
    printf("║ - Verificar sintaxe da expressão                               ║\n");
    printf("║ - Verificar declaração de variáveis                            ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝ \n\n"RESET);
}

void exibir_cabecalho() {
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                       COMPILADOR ALK - v1.0                                      ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                       Desenvolvido para a disciplina de Compiladores - UEM                       ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n"RESET);
}

void exibir_rodape() {
    printf("\033[1;34m"); // Define a cor do texto para azul brilhante
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           Obrigado por utilizar o Compilador ALK!                                ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    printf("\033[0m"); // Reseta as cores para o padrão
}

int main(void) 
{
    // Exibe o cabeçalho do compilador
    exibir_cabecalho();
    
    // Inicializa o processo de criação da árvore de sintaxe abstrata 
    iniciar_arquivo_arvore();

    // Realiza a análise léxica primeiro
    // analise_lexica();
    
    // Realiza a análise sintática do código fonte
    int resultado = yyparse();
    
    // Se a árvore de sintaxe abstrata foi criada, realiza o processamento
    if (raiz_ast != NULL) {
        if (arvore_arquivo != NULL) {
            imprimir_arvore(raiz_ast, arvore_arquivo, 0);
        }
        liberar_arvore(raiz_ast);
        raiz_ast = NULL;
    }
    
    // Se o analisador semântico foi inicializado, finaliza o processo
    if (analisador != NULL) {
        finalizar_analisador_semantico(analisador);
        analisador = NULL;
    }
    
    // Fecha o arquivo de saída da árvore
    fechar_arquivo_arvore();
    
    // Exibe o rodapé
    exibir_rodape();
    
    return resultado;
}
