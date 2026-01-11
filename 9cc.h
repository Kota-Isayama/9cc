typedef enum {
    TK_RESERVED,    // 記号
    TK_IDENT,       // 識別子
    TK_NUM,         // 整数トークン
    TK_EOF,         // 入力の終わりを表すトークン
} TokenKind;

typedef struct Token {
    TokenKind kind; // トークンの型
    struct Token *next;    // 次の入力トークン
    int val;        // kindがTK_NUMの場合、その数値
    char *str;      // トークン文字列
    int len;        // トークンの長さ
} Token;

extern Token *token;

void error(char *fmt, ...);

bool consume(char *op);

void expect(char *op);
int expect_number();
bool at_eof();

Token *new_token(TokenKind, Token*, char*, int);
bool startwith(char*, char*);
Token *tokenize(char*);

typedef enum {
    ND_ASSIGN,  // =
    ND_LVAR,    // ローカル変数
    ND_ADD, // +
    ND_SUB, // -
    ND_MUL, // *
    ND_DIV, // /
    ND_EQ,  // ==
    ND_NE,  // !=
    ND_LT,  // <
    ND_LE,  // <=
    ND_NUM, // 整数
} NodeKind;

typedef struct Node {
    NodeKind kind;
    struct Node *lhs;
    struct Node *rhs;
    int val;    // kindがND_NUMの場合のみ使う
    int offset; // kindがND_LVARの場合のみ使う
} Node;

extern Node *code[];

Node *new_node(NodeKind, Node*, Node*);
Node *new_node_num(int);

Node *stmt();
Node *expr();
Node *assign();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

void program();

void gen(Node*);
