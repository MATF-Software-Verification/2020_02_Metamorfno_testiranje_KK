#ifndef SWITCH2IF_H
#define SWITCH2IF_H

#include "MTKConsumer.hpp"

#include <deque>

/* Posetilac koji swtich pretvara u if */
class Switch2IfVisitor : public MTKVisitor<Switch2IfVisitor> {
public:
    /* Inicijalizacija prepisivaca i konteksta */
    Switch2IfVisitor(Rewriter &R, ASTContext &A)
      : MTKVisitor(R, A) {}

    /* Izracunavanje uslova za default */
    Expr *defUslov(StmtIterator dete,
                   StmtIterator kraj,
                   DeclRefExpr *uslov,
                   std::deque<Expr *> &u) const;

    /* Provera da li je neprazan case */
    bool neprazanSwitchCase(SwitchCase *s) const;

    /* Provera ima li dubokih oznaka */
    bool dubokeOznake(SwitchStmt *s) const;

    /* Pretvaranje switch naredbe u if */
    bool VisitSwitchStmt(SwitchStmt *s) const;

    /* Prekid obilaska kod switch naredbe */
    bool TraverseSwitchStmt(SwitchStmt *s);

    /* Nacin obrade deklaracije */
    bool TraverseDecl(Decl *d);

private:
    /* Privatno cuvanje tekuce deklaracije */
    Decl *tekdek;
};

#endif
