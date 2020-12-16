#ifndef PREPSWITCH_H
#define PREPSWITCH_H

#include "MTKConsumer.hpp"

#include <unordered_map>

/* Posetilac koji do pretvara u for */
class PrepSwitchVisitor : public MTKVisitor<PrepSwitchVisitor> {
public:
    /* Inicijalizacija prepisivaca i konteksta */
    PrepSwitchVisitor(Rewriter &R, ASTContext &A)
      : MTKVisitor(R, A) {}

    /* Obrada odgovarajuceg switch */
    DeclRefExpr *obradiSwitch(const SwitchStmt *s);

    /* Priprema switch naredbe */
    bool VisitContinueStmt(ContinueStmt *s);

    /* Nacin obrade deklaracije */
    bool TraverseDecl(Decl *d);

private:
    /* Privatno cuvanje tekuce deklaracije */
    Decl *tekdek;

    /* Privatno cuvanje vec pripremljenih naredbi */
    std::unordered_map<const SwitchStmt *, DeclRefExpr *> prip;
};

#endif