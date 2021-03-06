#ifndef MTKCONT_H
#define MTKCONT_H

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Rewrite/Core/Rewriter.h"

#include <unordered_set>

/* Upotreba Clangovog imenskog prostora */
using namespace clang;

/* Pomocna natklasa sa bitnim metodama */
class MTKContext {
public:
    /* Konstruktor inicijalizuje posetioca
     * prepisivacem i kontekstom parsiranja */
    MTKContext(Rewriter &R, ASTContext &A)
      : TheRewriter(R), TheASTContext(A) {}

    /* Staticka inicijalizacija posecenih funkcija */
    static void postaviFje(std::unordered_set<std::string> &f);

    /* Staticka inicijalizacija izlazne datoteke */
    static void postaviDat(const std::string &d);

    /* Prijavljivanje greske u radu */
    static int greska(const std::string &poruka, bool fatal = false);

    /* Tekstualna reprezentacija naredbe */
    std::string stampaj(const Stmt *const s) const;

    /* Odredjivanje mesta naredbe u kodu */
    SourceRange odrediMesto(const Stmt *const s,
                            bool dir = false) const;

    /* Tekstualna zamena koda */
    void zameni(const SourceRange &mesto,
                const Stmt *const novi) const;

    /* Tekstualna zamena koda */
    void zameni(const Stmt *const stari,
                const Stmt *const novi,
                bool dir = false) const;

    /* Prednja tekstualna dopuna koda */
    void dodajIspred(const Stmt *const stari,
                     const std::string &novi) const;

    /* Prednja tekstualna dopuna koda */
    void dodajIspred(const Stmt *const stari,
                     const Stmt *const novi = nullptr) const;

    /* Zadnja tekstualna dopuna koda */
    void dodajIza(const Stmt *const stari,
                  const Stmt *const novi = nullptr) const;

    /* Tekstualna dopuna koda funkcijom */
    void dodajFunkciju(const FunctionDecl *const stara,
                       const FunctionDecl *const nova) const;

    /* Pronalazak prvog slobodnog imena */
    std::string nadjiIme(const std::string &pocetno) const;

    /* Pronalazak prvog slobodnog identifikatora */
    IdentifierInfo *nadjiIdent(const std::string &ime) const;

    /* Pravljenje nove promenljive */
    VarDecl *napraviVar(DeclContext *kontekst,
                        const QualType &tip,
                        const std::string &ime) const;

    /* Pravljenje izraza deklaracije */
    DeclRefExpr *napraviDeclExpr(ValueDecl *dekl) const;

    /* Pravljenje izraza deklaracije */
    DeclRefExpr *napraviDeclExpr(DeclStmt *deknar) const;

    /* Pravljenje celobrojne vrednosti */
    IntegerLiteral *napraviInt(unsigned long long val) const;

    /* Pravljenje tacne istinitosne vrednosti */
    IntegerLiteral *napraviTrue() const;

    /* Pravljenje netacne istinitosne vrednosti */
    IntegerLiteral *napraviFalse() const;

    /* Pravljenje naredbe deklaracije */
    DeclStmt *napraviDeclStmt(VarDecl *var) const;

    /* Pravljenje naredbe deklaracije */
    DeclStmt *napraviDeclStmt(Decl *deklaracija,
                              const std::string &ime,
                              const QualType &tip,
                              Expr *pocetna = nullptr) const;

    /* Pravljenje deklaracije uslovne promenljive */
    DeclStmt *napraviUslovnu(Decl *deklaracija,
                             const std::string &ime,
                             const bool pocetna) const;

    /* Pravljenje izraza u zagradi */
    ParenExpr *napraviParen(Expr *izraz) const;

    /* Pravljenje unarnog operatora */
    UnaryOperator *napraviUnarni(Expr *izraz,
                                 const UnaryOperator::Opcode &op,
                                 const QualType &tip) const;

    /* Pravljenje logicke negacije */
    UnaryOperator *napraviNegaciju(Expr *izraz) const;

    /* Pravljenje referenciranja */
    UnaryOperator *napraviRef(DeclRefExpr *var) const;

    /* Pravljenje dereferenciranja */
    ParenExpr *napraviDeref(DeclRefExpr *var) const;

    /* Dohvatanje celobrojne vrednosti */
    Expr *dohvatiCelobrojnu(Expr *izraz) const;

    /* Dohvatanje istinitosne vrednosti */
    Expr *dohvatiIstinitost(Expr *izraz) const;

    /* Pravljenje binarnog operatora */
    BinaryOperator *napraviBinarni(Expr *lhs, Expr *rhs,
                                   const BinaryOperator::Opcode &op,
                                   const QualType &tip) const;

    /* Pravljenje izraza dodele */
    BinaryOperator *napraviDodelu(Expr *lhs, Expr *rhs) const;

    /* Pravljenje izraza jednakosti */
    BinaryOperator *napraviJednakost(Expr *lhs, Expr *rhs) const;

    /* Pravljenje izraza nejednakosti */
    BinaryOperator *napraviNejednakost(Expr *lhs, Expr *rhs) const;

    /* Pravljenje logicke konjunkcije */
    BinaryOperator *napraviKonjunkciju(Expr *lhs, Expr *rhs) const;

    /* Pravljenje logicke disjunkcije */
    BinaryOperator *napraviDisjunkciju(Expr *lhs, Expr *rhs) const;

    /* Pravljenje slozene naredbe */
    CompoundStmt *napraviSlozenu(const std::vector<Stmt *> &naredbe) const;

    /* Pravljenje uslovne naredbe */
    IfStmt *napraviIf(Expr *ako, Stmt *onda, Stmt *inace = nullptr) const;

    /* Pravljenje do petlje */
    DoStmt *napraviDo(Stmt *telo, Expr *uslov) const;

    /* Pravljenje while petlje */
    WhileStmt *napraviWhile(Expr *uslov, Stmt *telo) const;

    /* Pravljenje for petlje */
    ForStmt *napraviFor(Expr *uslov, Stmt *telo, Expr *korak = nullptr) const;

    /* Pravljenje continue naredbe */
    ContinueStmt *napraviCont() const;

    /* Pravljenje break naredbe */
    BreakStmt *napraviBreak() const;

    /* Pravljenje case klauze */
    CaseStmt *napraviCase(Expr *izraz, Stmt *naredba) const;

    /* Pravljenje default klauze */
    DefaultStmt *napraviDefault(Stmt *naredba) const;

    /* Pravljenje switch naredbe */
    SwitchStmt *napraviSwitch(Expr *uslov, Stmt *telo) const;

    /* Pravljenje funkcije */
    FunctionDecl *napraviFunkciju(DeclContext *kontekst,
                                  const QualType &tip,
                                  const std::string &ime) const;

    /* Pravljenje parametra */
    ParmVarDecl *napraviParam(VarDecl *var) const;

    /* Pravljenje funkcije */
    FunctionDecl *napraviFunkciju(DeclContext *kontekst,
                                  const QualType &tipRet,
                                  const std::string &ime,
                                  const std::vector<VarDecl *> &parms,
                                  Stmt *telo = nullptr) const;

    /* Pravljenje ref funkcije */
    FunctionDecl *napraviRefFunkciju(DeclContext *kontekst,
                                     const QualType &tipRet,
                                     const std::string &ime,
                                     const std::vector<VarDecl *> &parms,
                                     Stmt *telo = nullptr) const;

    /* Pravljenje poziva */
    CallExpr *napraviPoziv(FunctionDecl *funkcija,
                           const std::vector<Expr *> &args) const;

    /* Pravljenje ref poziva */
    CallExpr *napraviRefPoziv(FunctionDecl *funkcija,
                              const std::vector<DeclRefExpr *> &args) const;

    /* Pravljenje ref poziva */
    CallExpr *napraviRefPoziv(FunctionDecl *funkcija,
                              const std::vector<VarDecl *> &args) const;

    /* Pravljenje rekurzivnog poziva */
    CallExpr *napraviRekPoziv(FunctionDecl *funkcija) const;

    /* Pravljenje return naredbe */
    ReturnStmt *napraviReturn(Expr *izraz = nullptr) const;

    /* Pravljenje return naredbe */
    ReturnStmt *napraviReturn(bool vrednost) const;

    GotoStmt* napraviGoto(LabelStmt* labelToJumpTo) const;

    LabelStmt* napraviLabelStmt(FunctionDecl *functionDecl, const std::string& naziv) const;
    /* Prebacivanje naredbe na hip */


    LabelStmt *napraviLabelStmt(FunctionDecl* kontekst, const std::string &naziv, Stmt* body) const;
    NullStmt* napraviNullStmt() const;

        template<typename Naredba, typename ...Args>
    Naredba* naHip(Args&& ...args) const {
        auto rezultat = new (TheASTContext)Naredba(std::forward<Args>(args)...);
        return rezultat;
    }

protected:
    /* Zasticeno cuvanje prepisivaca i konteksta */
    Rewriter &TheRewriter;
    ASTContext &TheASTContext;

    /* Staticko cuvanje posecenih funkcija */
    static std::unordered_set<std::string> *fje;

    /* Staticko cuvanje izlazne datoteke */
    static const std::string *dat;

private:
    /* Poruka da nema slobodnog imena */
    static constexpr auto nemaImena = "Nije moguce pronaci slobodno ime!";

};

#endif
