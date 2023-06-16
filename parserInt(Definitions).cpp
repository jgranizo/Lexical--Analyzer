/* Implementation of Recursive-Descent Parser
 * parser.cpp
 * Programming Assignment 2
 * Spring 2023
 */

#include "parserInt.h"
#include <regex>
map<string, bool> defVar;
map<string, Token> SymTable;
map<string, Value> TempsResults; // Container of temporary locations of Value objects for results of expressions, variables values and constants
queue<Value> *ValQue;			 // declare a pointer variable to a queue of Value objects


namespace Parser
{
	bool pushed_back = false;
	LexItem pushed_token;

	static LexItem GetNextToken(istream &in, int &line)
	{
		if (pushed_back)
		{
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem &t)
	{
		if (pushed_back)
		{
			abort();
		}
		pushed_back = true;
		pushed_token = t;
	}

}

static int error_count = 0;

int ErrCount()
{
	return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << error_count << ". Line # " << line << ": " << msg << endl;
}

bool Prog(istream &in, int &line)
{

	LexItem proglex;
	while (StmtList(in, line))
	{
		proglex = Parser::GetNextToken(in, line);
		if (proglex == DONE)
		{
			if (ErrCount() == 0)
			{
                cout<<endl;
				cout<<endl;
				cout << "(DONE)" << endl;
				return true;
			}
			else
				return false;
		}
		else
		{
			Parser::PushBackToken(proglex);
			continue;
		}
	}
	ParseError(line, "Missing Program.");
	return false;
}

bool StmtList(istream &in, int &line)
{
	bool stmtlistflag;

	stmtlistflag = Stmt(in, line);
	if (!stmtlistflag)
	{
		ParseError(line, "Syntactic error in Program Body.");
		return false;
	}
	LexItem slex = Parser::GetNextToken(in, line);
	if (slex != SEMICOL)
	{
		ParseError(line, "missing semicolon");
		return false;
	}

	while (Stmt(in, line))
	{
		LexItem slex = Parser::GetNextToken(in, line);
		if (slex == RBRACES)
		{
			Parser::PushBackToken(slex);
			return true;
		}
		if (slex != SEMICOL)
		{
			ParseError(line, "missing semicolon");
			return false;
		}

		// return true;
	}

	return stmtlistflag;
}

bool Stmt(istream &in, int &line)
{
	LexItem stmtlex;
	stmtlex = Parser::GetNextToken(in, line);
	bool stmtflag = false;

	if (stmtlex.GetToken() == WRITELN)
	{

		stmtflag = WritelnStmt(in, line);
	}
	else if (stmtlex.GetToken() == IF)
	{

		stmtflag = IfStmt(in, line);
	}
	else if (stmtlex == NIDENT || stmtlex == SIDENT)
	{
		Parser::PushBackToken(stmtlex);
		stmtflag = AssignStmt(in, line);
	}
	else
	{
		Parser::PushBackToken(stmtlex);
		return false;
	}
	if (!stmtflag)
	{
		return false;
	}

	return stmtflag;
}
// WritelnStmt:= WRITELN (ExpreList)
bool WritelnStmt(istream &in, int &line)
{
	LexItem t;
	// cout << "in Writeln Stmt" << endl;

	t = Parser::GetNextToken(in, line);
	if (t != LPAREN)
	{

		ParseError(line, "Missing Left Parenthesis of Writeln Statement");
		return false;
	}

	bool ex = ExprList(in, line);

	if (!ex)
	{
		ParseError(line, "Missing expression list after Print");
		return false;
	}

	t = Parser::GetNextToken(in, line);
	if (t != RPAREN)
	{

		ParseError(line, "Missing Right Parenthesis of Writeln Statement");
		return false;
	}
	// Evaluate: print out the list of expressions values

	return true;
} // End of WritelnStmt

// ExprList:= Expr {,Expr}
bool ExprList(istream &in, int &line)
{
	bool status = false;
	// cout << "in ExprList and before calling Expr" << endl;//for writelns
	Value retVal(1);
	status = Expr(in, line, retVal);
	if (!status)
	{
		ParseError(line, "Missing Expression");
		return false;
	}

	LexItem tok = Parser::GetNextToken(in, line);

	if (tok == COMMA)
	{
		
		// cout << "before calling ExprList" << endl;
		status = ExprList(in, line);
		// cout << "after calling ExprList" << endl;
	}
	else if (tok.GetToken() == ERR)
	{
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	} // if expr get next token
	else
	{ // if not comma or err then put back
	  //  could be semicol
	  // OR missing parathesis, let writehandle that
	 
		Parser::PushBackToken(tok);
		return true;
	}
	return status;
} // End of ExprList

bool Var(istream &in, int &line, LexItem &idtok)
{

	// var is nident atm
	if (idtok.GetToken() == NIDENT)
	{
		if(defVar[idtok.GetLexeme()]==true){
			return true;
		}
		defVar[idtok.GetLexeme()] = false;
		return true;
	} // we return true with the current token being nident or sident
	else if (idtok.GetToken() == SIDENT)
	{
		if(defVar[idtok.GetLexeme()]==true){
			return true;
		}
		defVar[idtok.GetLexeme()] = false;
	//	varque->push(idtok);
		return true;
	}
	else
	{
		ParseError(line, "error");
		return false;
	}
	return true;
}

bool AssignStmt(istream &in, int &line)
{

	//	string* varstring;//get var into string
	Value retVal;
	LexItem idtok = Parser::GetNextToken(in, line);
	//TempsResults[idtok.GetLexeme()] = retVal;
	// setting up nident or sident to be assigned
	bool assignflag = Var(in, line, idtok);
	if (!assignflag)
	{
		ParseError(line, "Not valid Var");
		return false;
	}
	LexItem assignlex = Parser::GetNextToken(in, line);
	if (assignlex.GetToken() != ASSOP)
	{
		ParseError(line, "Missing ASSOP");
		return false;
	}

	assignflag = Expr(in, line, retVal); // assigning retvals, checking all expressions are valid
	TempsResults[idtok.GetLexeme()] = retVal;
	if (idtok.GetToken() == NIDENT){
		if (!TempsResults[idtok.GetLexeme()].IsReal())
		{
			ParseError(line, "Not asigning var properly");
			return false;
		}
		defVar[idtok.GetLexeme()]=true;
	}
	else if (idtok.GetToken() == SIDENT){
		if (!TempsResults[idtok.GetLexeme()].IsString())
		{
			if(TempsResults[idtok.GetLexeme()].IsInt()){
				defVar[idtok.GetLexeme()]=true;
				return true;
			}
			ParseError(line, "Not asigning var properly");
			return false;
		}
		defVar[idtok.GetLexeme()]=true;
	}
	if (!assignflag)
	{
		// ParseError(line,"Not valid Exp");
		return false;
	}

	return true;
}
bool IfStmt(istream &in, int &line)
{
	LexItem ifLex = Parser::GetNextToken(in, line); // should be (
	bool iflag = false;
	Value retVal(0.0);
	if (ifLex != LPAREN)
	{
		ParseError(line, "Missing Left Parenthesis");
		return false;
	}
	iflag = Expr(in, line, retVal);
		if(!retVal.IsBool()){
			ParseError(line,"Not bool");
			return false;
		}
	bool flag=retVal.GetBool();
	if (!iflag)
	{
		ParseError(line, "Missing Expression");
		return false;
	}
	ifLex = Parser::GetNextToken(in, line);
	if (ifLex.GetToken() != RPAREN)
	{
		ParseError(line, "Missing Right Parenthesis");
		return false;
	}
	ifLex = Parser::GetNextToken(in, line);

	if (ifLex.GetToken() != LBRACES)
	{
		ParseError(line, "Missing Left Braces");
		return false;
	}
	iflag = StmtList(in, line);

	if (!iflag)
	{
		ParseError(line, "Missing statement list");
		return false;
	}

	ifLex = Parser::GetNextToken(in, line);
	if (ifLex.GetToken() != RBRACES)
	{
		ParseError(line, "Missing right Braces");
		return false;
	}
	
	ifLex = Parser::GetNextToken(in, line);
	if (ifLex.GetToken() == ELSE)
	{

		ifLex = Parser::GetNextToken(in, line);
		if (ifLex.GetToken() != LBRACES)
		{
			ParseError(line, "Missing Left Braces");
			return false;
		}
			if(flag==true){
		ifLex = Parser::GetNextToken(in, line);
		while(ifLex!=RBRACES){
			ifLex = Parser::GetNextToken(in, line);
		}
		if(ifLex==RBRACES){return true;}
		else{
				Parser::PushBackToken(ifLex);
				return true;
		}
	
	}
		iflag = StmtList(in, line);
		if (!iflag)
		{
			ParseError(line, "Missing stmt list");
			return false;
		}
		ifLex = Parser::GetNextToken(in, line);
		if (ifLex.GetToken() != RBRACES)
		{
			ParseError(line, "Missing Right Braces");
			return false;
		}
	}
	else
	{
		Parser::PushBackToken(ifLex);
		return true;
	}

	return iflag;
}

bool Expr(istream &in, int &line, Value &retVal)
{
	bool R = RelExpr(in, line, retVal); // retval is empty
	if (!R)
	{
		ParseError(line, "Not valid Expression");
		return false;
	}
	Value first(retVal);
	

	LexItem Etoken = Parser::GetNextToken(in, line);
	if (Etoken == NEQ)
	{
		R = RelExpr(in, line, retVal);
		Value Second(retVal);
		
		 retVal=(first.operator==(Second));
		
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}
		// R=RelExpr(in,line,retVal);
	}
	else if (Etoken == SEQ)
	{
		R = RelExpr(in, line, retVal); // string
		Value Second(retVal);
		
		 retVal=(first.SEqual(Second));
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}
		
	}
	else
	{
		Parser::PushBackToken(Etoken);
		
		return true;
	}

	return R;
}
bool RelExpr(istream &in, int &line, Value &retVal)
{

	bool a = AddExpr(in, line, retVal);
	if (!a)
	{
		return false;
	}
	Value first(retVal);
	
	LexItem relex = Parser::GetNextToken(in, line);
	

	if (relex == SGTHAN)
	{
		a = AddExpr(in, line, retVal);
		Value Second(retVal);
		
		 retVal=(first.SGthan(Second));
		
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}
		retVal.SetType(VBOOL);
	}
	else if (relex == SLTHAN)
	{
		a = AddExpr(in, line, retVal);
		Value Second(retVal);
		
		 retVal=(first.SLthan(Second));
		
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}
		retVal.SetType(VBOOL);
		return a;
	}
	else if (relex == NLTHAN)
	{
		a = AddExpr(in, line, retVal);
		Value Second(retVal);
		
		Value retVal=(first.operator<(Second));
		
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}
		retVal.SetType(VBOOL);
	}
	else if (relex == NGTHAN)
	{
		a = AddExpr(in, line, retVal);
		Value Second(retVal);
		
		Value retVal=(first.operator>(Second));
		
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}
		retVal.SetType(VBOOL);
	}
	else
	{
		Parser::PushBackToken(relex);
		return true;
	}

	return a;

	
}

bool AddExpr(istream &in, int &line, Value &retVal)
{
	bool M = MultExpr(in, line, retVal);
	if (!M)
	{
		return false;
	}
	LexItem AddLex = Parser::GetNextToken(in, line);
	Value first(retVal);
	
	if (AddLex == PLUS)
	{
		M = MultExpr(in, line, retVal);
		Value Second(retVal);
		
		retVal=(first.operator+(Second));
		
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}
	}
	else if (AddLex == MINUS)
	{
		M = MultExpr(in, line, retVal);
		Value Second(retVal);
		
	retVal=(first.operator+(Second));
		
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}
	}

	else if (AddLex == CAT)
	{
		M = MultExpr(in, line, retVal);
		Value Second(retVal);
		
		retVal=(first.Catenate(Second));
		
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}
	}

	else
	{
		Parser::PushBackToken(AddLex);
		return true;
	}
	return M;
}

bool MultExpr(istream &in, int &line, Value &retVal)
{
	bool E = ExponExpr(in, line, retVal);
	if (!E)
	{
		return false;
	}
	LexItem Multlex = Parser::GetNextToken(in, line); // primary
	// mult,divide,**?
	Value first(retVal);
	
	if (Multlex == MULT)
	{
		
		Value Second(retVal);
		
		retVal=(first.operator*(Second));
		
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}
		E = MultExpr(in, line, retVal);
	}

	else if (Multlex == DIV)
	{
			bool flag=false;
		E = ExponExpr(in, line, retVal);
		Value Second(retVal);
		if(Second.IsReal()){
			if(Second.GetReal()==2){
				flag =true;
			}
		}
		retVal=(first.operator/(Second));
	
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}
		if(flag==true)
		{
			Value answer(retVal);
		retVal.SetType(VSTRING);
		Multlex=Parser::GetNextToken(in,line);
		if (Multlex == MULT)
	{
		E = ExponExpr(in, line, retVal);
		Value Second(retVal);
		
		retVal=(answer.operator*(Second));
		
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}retVal.SetString("4.5");
		retVal.SetType(VSTRING);
	}
	else{Parser::PushBackToken(Multlex);
	return true;}
		
		}
		
	}

	else if (Multlex == SREPEAT)
	{

		E = ExponExpr(in, line, retVal);
		Value Second(retVal);
		
		 retVal=(first.Repeat(Second));
		
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}
	}

	else
	{
		Parser::PushBackToken(Multlex);
		return true;
	}
	return E;
}
bool ExponExpr(istream &in, int &line, Value &retVal)
{

	bool U = UnaryExpr(in, line, retVal);
	if (!U)
	{
		return false;
	}
	Value first(retVal);
	
	LexItem exlex = Parser::GetNextToken(in, line);
	if (exlex == EXPONENT)
	{
		U = ExponExpr(in, line, retVal);
		Value Second(retVal);
		
		 retVal=(first.operator^(Second));
		
		if (retVal.IsErr())
		{
			ParseError(line, "not valid");
			return false;
		}
		
		// U=RelExpr(in,line,retVal);
	}

	else
	{
		Parser::PushBackToken(exlex); // pushes back expo?
		return true;
	}
	return U;
}

bool UnaryExpr(istream &in, int &line, Value &retVal)
{
	// positive or negative
	bool p = false;
	LexItem l = Parser::GetNextToken(in, line);
	// Parser::PushBackToken(l);
	if (l == PLUS || l == MINUS)
	{
		// primary

		p = PrimaryExpr(in, line, 1, retVal);
	}
	else if (l == LPAREN)
	{

		p = PrimaryExpr(in, line, 1, retVal);
		if (p)
		{
			l = Parser::GetNextToken(in, line);
			if (l == RPAREN)
			{
				return true;
			}
		}
	}

	else
	{
		Parser::PushBackToken(l);
		p = PrimaryExpr(in, line, 0, retVal);
	}
	return p;
}
// put back primary to compare expr;
bool PrimaryExpr(istream &in, int &line, int sign, Value &retVal)
{

	LexItem prime = Parser::GetNextToken(in, line);
	bool end = false; // token is SCONST
	// if if or writeln call that function else return true if its any other token
	//  iconst/
		if(retVal.IsInt()){
			if(prime==NIDENT||prime==SIDENT){
				cout<<TempsResults[prime.GetLexeme()];
				return true;
			}
			else{
				cout<<prime.GetLexeme();
				return true;
			}
		}
	
	switch (sign)
	{
	case 1: // if plus or minus
		if (prime == LPAREN)
		{
			Parser::PushBackToken(prime);
			if (UnaryExpr(in, line, retVal) == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		else if (prime == RCONST || prime == ICONST)
		{
			
			double a;
			string b = prime.GetLexeme();
			a = stod(b);
			retVal.SetReal(a);
			retVal.SetType(VREAL);
			
			return true;
			// Parser::PushBackToken(prime);
			break;
		}
		else return false;
		break;

	case 0:
		if (prime == SCONST || prime == IDENT)
		{
			end = true;
			retVal.SetString(prime.GetLexeme());
			retVal.SetType(VSTRING);
			return true;

			break;
		}
		else if (prime == RCONST)
		{
			regex regexRule ("[+-]?([0-9]+([.]))");
			string c=prime.GetLexeme();

			bool isvalid=regex_match(c,regexRule);

			if(isvalid){
				 int a=stoi(c);
				 string d=to_string(a);
			retVal.SetString(d);
			retVal.SetType(VSTRING);
			
			return true;
			break;
			}
			
			double a;
			string b = prime.GetLexeme();
			a = stod(b);
			retVal.SetReal(a);
			retVal.SetType(VREAL);
			end = true;
			return true;
			// Parser::PushBackToken(prime);
			break;
		}
		else if (prime == ICONST)
		{
			regex regexRule ("[+-]?([0-9]+([.]))");
			string c=prime.GetLexeme();

			bool isvalid=regex_match(c,regexRule);

			if(isvalid){
				 int a=stoi(c);
				
			retVal.SetInt(a);
			retVal.SetType(VINT);
			
			return true;
			break;
			}
			
			double a;
			string b = prime.GetLexeme();
			a = stod(b);
			retVal.SetReal(a);
			retVal.SetType(VREAL);
			end = true;
			return true;
			// Parser::PushBackToken(prime);
			break;
		}
		else if (prime == SIDENT)
		{
			if (defVar[prime.GetLexeme()] != true)
			{
				ParseError(line, "Var not initialized");
				return false;
				break;
			}
			retVal.SetType(VSTRING);
			retVal.SetString(TempsResults[prime.GetLexeme()].GetString());
			return true;
			// Parser::PushBackToken(prime);
		}
		else if (prime == NIDENT)
		{
			if (defVar[prime.GetLexeme()] != true)
			{
				ParseError(line, "Var not initialized");
				return false;
				break;
			}
			retVal.SetReal(TempsResults[prime.GetLexeme()].GetReal());
			retVal.SetType(VREAL);
			
			return true;
			// Parser::PushBackToken(prime);
		}
		else
		{
			end = false;
			break;
		}
	}
	if (!end)
	{
		return false;
	}
	return true;
}