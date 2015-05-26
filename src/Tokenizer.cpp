//============================================================================
// Name        : Tokenizer.cpp
// Author      : Ariel Ancer
// Version     : V.1
// Description : Tokenizer/Lexical Scanner in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

class Token{

	public:
        string type;
		string value;

		void set_values(string t , string v){
			type = t;
			value = v;
		}

};

/** There are three test cases: "test1.txt ( default ) , test2.txt
  * , test3.txt. They may be exchanged in the following ifstream call
  * at your convenience.
  */

	ifstream file("test1.txt",ios::in);
	string tok = "";
	vector<Token> tokens;


    /**
     * The getChar method reads in a single character from
     * the file specified above and returns the character.
     */

char getChar(){
	char myChar = file.get();
	if( (int)(myChar) != -1 ){
		return myChar;
	}else{
		return ' ';
	}
}

/**
 * The nextChar method reads in a single character from
 * the file specified above, saves the character to variable
 * myChar and the character is unread from the file ensuring
 * that it is the next character available from method getChar
 * and myChar is returned.
 */

char nextChar(){
	char myChar = file.get();
	file.unget();
	if( (int)(myChar) != -1 ){
		return myChar;
	}else{
		return ' ';
	}
}

/**
 * The method symbolCheck is called when a potential token does not begin with
 * an alphanumeric character. We classify this character as one of many
 * potential symbols listed in the method's switch statement. The method
 * will add the correct token for the symbol found.
 */

void symbolCheck(char myChar){

	Token tk;
	bool flag = false;

	switch(myChar){
	case ':':
		if( nextChar() == ':' ){
			tk.set_values("SCOPE_RESOLUTION",tok + getChar());
		}else{
			tk.set_values("COLON",tok);
		}
			break;
	case '+':
		if( nextChar() == '+' ){
			tk.set_values("INCREMENT",tok + getChar());
			}else if( nextChar() == '=' ){
			tk.set_values("ASSIGN_SUM",tok + getChar());
			}else{
			tk.set_values("ADD",tok);
			}
			break;
	case '-':
			if( nextChar() == '-' ){
				tk.set_values("DECREMENT",tok + getChar());
				}else if( nextChar() == '=' ){
					tk.set_values("ASSIGN_DIFF",tok + getChar());
				}else if( nextChar() == '>' ){
					tk.set_values("ELEMPOINTER",tok + getChar());

					if( nextChar() == '*' ){
					tk.set_values("POINTERTOMEMB",tok + getChar());
					}

				}else{
				tk.set_values("SUBTRACT",tok);
				}
			break;
	case '(':
			tk.set_values("LPAREN",tok);
			break;
	case ')':
			tk.set_values("RPAREN",tok);
			break;
	case '[':
			tk.set_values("LBPAREN",tok);
			break;
	case ']':
			tk.set_values("RBPAREN",tok);
			break;
	case '{':
			tk.set_values("LSPAREN",tok);
			break;
	case '}':
			tk.set_values("RSPAREN",tok);
			break;
	case '.':
		if( nextChar() == '*' ){
					tk.set_values("POINTERTOMEMBER",tok + getChar());
				}else{
					tk.set_values("ELEMREF",tok);
				}
			break;
	case '!':
		if( nextChar() == '=' ){
			tk.set_values("NOT_EQ",tok + getChar());
		}else{
			tk.set_values("NOT",tok);
		}
			break;
	case '~':
			tk.set_values("BITWISE_NOT",tok);
			break;
	case '*':
		if( nextChar() == '=' ){
					tk.set_values("ASSIGN_PROD",tok + getChar());
		}else{
			tk.set_values("MULT",tok);
		}
			break;
	case '&':
		if( nextChar() == '&' ){
					tk.set_values("LOGICAL_AND",tok + getChar());
				}else if( nextChar() == '=' ){
					tk.set_values("BITWISE_AND_ASSIGN",tok + getChar());
				}else{
					tk.set_values("BITWISE_AND",tok);
				}
			break;
	case '/':
		if( nextChar() == '=' ){
			tk.set_values("ASSIGN_QUOTIENT",tok + getChar());
		}else if( nextChar() == '*' ){
			bool invar = true;

			while( invar ){

				if( nextChar() == '*' ){
					getChar();
					if( nextChar() == '/' ){
						getChar();
						invar = false;
						flag = true;
					}
				}else{
					getChar();
				}
			}

		}else if( nextChar() == '/' ){

			while( nextChar() != '\n' && nextChar() != '\r' ){
					getChar();
			}

			flag = true;

		}else{
			tk.set_values("DIVISION",tok);
		}
			break;
	case '\\':
		if( nextChar() == 'n' ){
			tk.set_values("NEW_LINE",tok + getChar());
		}else if( nextChar() == 't' ){
			tk.set_values("HORZ_TAB",tok + getChar());
		}else if( nextChar() == 'r' ){
			tk.set_values("CARRIAGE_RETURN",tok + getChar());
		}
			break;
	case '%':
		if( nextChar() == '=' ){
			tk.set_values("ASSIGN_REMAINDER",tok + getChar());
		}else{
			tk.set_values("REMAINDER",tok);
		}
			break;
	case '<':
		if( nextChar() == '<' ){
					tk.set_values("LSHIFT",tok + getChar());

					if( nextChar() == '=' ){
					tk.set_values("LSHIFT_ASSIGN",tok + getChar());
					}

				}else if( nextChar() == '=' ){
					tk.set_values("LESS_EQ",tok + getChar());
				}else{
					tk.set_values("LESS",tok);
				}
			break;
	case '>':
		if( nextChar() == '>' ){
					tk.set_values("RSHIFT",tok + getChar());

					if( nextChar() == '=' ){
					tk.set_values("RSHIFT_ASSIGN",tok + getChar());
					}

				}else if( nextChar() == '=' ){
					tk.set_values("GREATER_EQ",tok + getChar());
				}else{
					tk.set_values("GREATER",tok);
				}
			break;
	case '=':
		if( nextChar() == '=' ){
					tk.set_values("EQUIVALENCE",tok + getChar());
				}else{
					tk.set_values("EQUAL",tok);
				}
			break;
	case '^':
		if( nextChar() == '=' ){
			tk.set_values("BITWISE_XOR_ASSIGN",tok + getChar());
		} else {
			tk.set_values("XOR",tok);
		}
			break;
	case '|':
		if( nextChar() == '|' ){
					tk.set_values("LOGICAL_OR",tok + getChar());
				} else if( nextChar() == '=' ){
					tk.set_values("BITWISE_OR_ASSIGN",tok + getChar());
				} else{
					tk.set_values("BITWISE_OR",tok);
				}
			break;
	case '?':
		if( nextChar() == ':' ){
			tk.set_values("TERNARY_COND",tok + getChar());
		}else{
			flag = true;
		}
			break;
	case ',':
		tk.set_values("COMMA",tok);
			break;
	case ';':
		tk.set_values("SEMICOLON",tok);
			break;
	case '\"':
		tk.set_values("DOUBLE_QUOTE",tok);
			break;
	case '\'':
		tk.set_values("SINGLE_QUOTE",tok);
			break;
	default:
		flag = true;
		break;

	}

	if( !flag ){
    tokens.push_back(tk);
	}

}

    /**
     * The checkIdent method is fed the current char built string that has been classified
     * as an IDENT token and checks if that token is rather a keyword, if so the token is
     * added to the ArrayList of tokens.
     *
     * @param tok
     * @return
     */

  bool checkIdent(string tok) {

	  Token tk;

        if(tok.compare("if") == 0){
            	tk.set_values("IF",tok);
        } else if(tok.compare("while") == 0){
        	tk.set_values("WHILE",tok);
        }else if(tok.compare("char") == 0){
        	tk.set_values("CHAR",tok);
        }else if(tok.compare("void") == 0){
        	tk.set_values("VOID",tok);
        }else if(tok.compare("do") == 0){
        	tk.set_values("DO",tok);
        }else if(tok.compare("public") == 0){
        	tk.set_values("PUBLIC",tok);
        }else if(tok.compare("private") == 0){
        	tk.set_values("PRIVATE",tok);
        }else if(tok.compare("protected") == 0){
        	tk.set_values("PROTECTED",tok);
        } else if(tok.compare("alignas") == 0){
        	tk.set_values("ALIGNAS",tok);
        } else if(tok.compare("alignof") == 0){
        	tk.set_values("ALIGNOF",tok);
        } else if(tok.compare("and") == 0){
        	tk.set_values("AND",tok);
        } else if(tok.compare("and_eq") == 0){
        	tk.set_values("AND_EQ",tok);
        } else if(tok.compare("asm") == 0){
        	tk.set_values("ASM",tok);
        } else if(tok.compare("auto") == 0){
        	tk.set_values("AUTO",tok);
        } else if(tok.compare("bitand") == 0){
        	tk.set_values("BITAND",tok);
        } else if(tok.compare("bitor") == 0){
        	tk.set_values("BITOR",tok);
        } else if(tok.compare("bool") == 0){
        	tk.set_values("BOOL",tok);
        } else if(tok.compare("break") == 0){
        	tk.set_values("BREAK",tok);
        } else if(tok.compare("case") == 0){
        	tk.set_values("CASE",tok);
        } else if(tok.compare("char16_t") == 0){
        	tk.set_values("CHAR16_T",tok);
        } else if(tok.compare("char32_t") == 0){
        	tk.set_values("CHAR32_T",tok);
        } else if(tok.compare("class") == 0){
        	tk.set_values("CLASS",tok);
        } else if(tok.compare("compl") == 0){
        	tk.set_values("COMPL",tok);
        } else if(tok.compare("concept") == 0){
        	tk.set_values("CONCEPT",tok);
        } else if(tok.compare("const") == 0){
        	tk.set_values("CONST",tok);
        } else if(tok.compare("constexpr") == 0){
        	tk.set_values("CONSTEXPR",tok);
        } else if(tok.compare("const_cast") == 0){
        	tk.set_values("CONST_CAST",tok);
        } else if(tok.compare("continue") == 0){
        	tk.set_values("CONTINUE",tok);
        } else if(tok.compare("decltype") == 0){
        	tk.set_values("DECLTYPE",tok);
        } else if(tok.compare("default") == 0){
        	tk.set_values("DEFAULT",tok);
        } else if(tok.compare("delete") == 0){
        	tk.set_values("DELETE",tok);
        } else if(tok.compare("double") == 0){
        	tk.set_values("DOUBLE",tok);
        } else if(tok.compare("dynamic_cast") == 0){
        	tk.set_values("DYNAMIC_CAST",tok);
        } else if(tok.compare("else") == 0){
        	tk.set_values("ELSE",tok);
        } else if(tok.compare("enum") == 0){
        	tk.set_values("ENUM",tok);
        } else if(tok.compare("explicit") == 0){
        	tk.set_values("EXPLICIT",tok);
        } else if(tok.compare("export") == 0){
        	tk.set_values("EXPORT",tok);
        } else if(tok.compare("extern") == 0){
        	tk.set_values("EXTERN",tok);
        } else if(tok.compare("false") == 0){
        	tk.set_values("FALSE",tok);
        } else if(tok.compare("float") == 0){
        	tk.set_values("FLOAT",tok);
        } else if(tok.compare("for") == 0){
        	tk.set_values("FOR",tok);
        } else if(tok.compare("friend") == 0){
        	tk.set_values("FRIEND",tok);
        } else if(tok.compare("goto") == 0){
        	tk.set_values("GOTO",tok);
        } else if(tok.compare("inline") == 0){
        	tk.set_values("INLINE",tok);
        } else if(tok.compare("int") == 0){
        	tk.set_values("INT",tok);
        } else if(tok.compare("long") == 0){
        	tk.set_values("LONG",tok);
        } else if(tok.compare("mutable") == 0){
        	tk.set_values("MUTABLE",tok);
        } else if(tok.compare("namespace") == 0){
        	tk.set_values("NAMESPACE",tok);
        } else if(tok.compare("new") == 0){
        	tk.set_values("NEW",tok);
        } else if(tok.compare("noexcept") == 0){
        	tk.set_values("NOEXCEPT",tok);
        } else if(tok.compare("not") == 0){
        	tk.set_values("NOT_EQ",tok);
        } else if(tok.compare("nullptr") == 0){
        	tk.set_values("NULLPTR",tok);
        } else if(tok.compare("operator") == 0){
        	tk.set_values("OPERATOR",tok);
        } else if(tok.compare("or") == 0){
        	tk.set_values("OR",tok);
        } else if(tok.compare("or_eq") == 0){
        	tk.set_values("OR_EQ",tok);
        } else if(tok.compare("register") == 0){
        	tk.set_values("REGISTER",tok);
        } else if(tok.compare("reinterpret_cast") == 0){
        	tk.set_values("REINTERPRET_CAST",tok);
        } else if(tok.compare("requires") == 0){
        	tk.set_values("REQUIRES",tok);
        } else if(tok.compare("return") == 0){
        	tk.set_values("RETURN",tok);
        } else if(tok.compare("short") == 0){
        	tk.set_values("SHORT",tok);
        } else if(tok.compare("signed") == 0){
        	tk.set_values("SIGNED",tok);
        } else if(tok.compare("sizeof") == 0){
        	tk.set_values("SIZEOF",tok);
        } else if(tok.compare("static") == 0){
        	tk.set_values("STATIC",tok);
        } else if(tok.compare("static_assert") == 0){
        	tk.set_values("STATIC_ASSERT",tok);
        } else if(tok.compare("static_cast") == 0){
        	tk.set_values("STATIC_CAST",tok);
        } else if(tok.compare("struct") == 0){
        	tk.set_values("STRUCT",tok);
        } else if(tok.compare("switch") == 0){
        	tk.set_values("SWITCH",tok);
        } else if(tok.compare("template") == 0){
        	tk.set_values("TEMPLATE",tok);
        } else if(tok.compare("this") == 0){
        	tk.set_values("THIS",tok);
        } else if(tok.compare("thread_local") == 0){
        	tk.set_values("THREAD_LOCAL",tok);
        } else if(tok.compare("throw") == 0){
        	tk.set_values("THROW",tok);
        } else if(tok.compare("true") == 0){
        	tk.set_values("TRUE",tok);
        } else if(tok.compare("try") == 0){
        	tk.set_values("TRY",tok);
        } else if(tok.compare("typedef") == 0){
        	tk.set_values("TYPEDEF",tok);
        } else if(tok.compare("typeid") == 0){
        	tk.set_values("TYPEID",tok);
        } else if(tok.compare("typename") == 0){
        	tk.set_values("TYPENAME",tok);
        } else if(tok.compare("union") == 0){
        	tk.set_values("UNION",tok);
        } else if(tok.compare("unsigned") == 0){
        	tk.set_values("UNSIGNED",tok);
        } else if(tok.compare("using") == 0){
        	tk.set_values("USING",tok);
        } else if(tok.compare("virtual") == 0){
        	tk.set_values("VIRTUAL",tok);
        } else if(tok.compare("volatile") == 0){
        	tk.set_values("VOLATILE",tok);
        } else if(tok.compare("wchar_t") == 0){
        	tk.set_values("WCHAR_T",tok);
        } else if(tok.compare("xor") == 0){
        	tk.set_values("XOR",tok);
        } else if(tok.compare("xor_eq") == 0){
        	tk.set_values("XOR_EQ",tok);
        } else if(tok.compare("override") == 0){
        	tk.set_values("OVERRIDE",tok);
        } else if(tok.compare("final") == 0){
        	tk.set_values("FINAL",tok);
        } else if(tok.compare("pragma") == 0){
        	tk.set_values("PRAGMA",tok);
        }  else if(tok.compare("elif") == 0){
        	tk.set_values("ELIF",tok);
        } else if(tok.compare("endif") == 0){
        	tk.set_values("ENDIF",tok);
        } else if(tok.compare("defined") == 0){
        	tk.set_values("DEFINED",tok);
        } else if(tok.compare("ifdef") == 0){
        	tk.set_values("IFDEF",tok);
        } else if(tok.compare("ifndef") == 0){
        	tk.set_values("IFNDEF",tok);
        } else if(tok.compare("define") == 0){
        	tk.set_values("DEFINE",tok);
        } else if(tok.compare("undef") == 0){
        	tk.set_values("UNDEF",tok);
        } else if(tok.compare("#include") == 0){
        	tk.set_values("INCLUDE",tok);
        } else if(tok.compare("line") == 0){
        	tk.set_values("LINE",tok);
        } else if(tok.compare("error") == 0){
        	tk.set_values("ERROR",tok);
        }  else{
        	return false;
        }

        tokens.push_back(tk);
        return true;
    }

  /**
     * Distinguishes between an INTEGER token, INDENT token or a symbol token.
     * THe token is then added to an ArrayList of tokens for further use.
     */

void buildTok( char myChar){

	char nc = (int) nextChar();
	int ic = (int) myChar;

	if(( ( ic >= 32 ) && ( ic <= 47 ) ) ||
		( ( ic >= 58 ) && ( ic <= 64 ) ) ||
		( ( ic >= 91 ) && ( ic <= 94 ) ) ||
		( ( ic >= 123 ) && ( ic <= 126 ) ) ){
		tok += myChar;
		symbolCheck(myChar);
		tok = "";
	} else if( (( nc >= 97) && (nc <= 122) ) ||
			( (nc >= 65) && (nc <= 90) ) ||
			( (nc >= 48) && (nc <= 57) ) ||
			( ic == 95 )){
		tok += myChar;
	}else{ // myChar == ' '
		tok += myChar;
		if( isdigit(tok[0]) ){
			Token t;
			t.set_values("INTEGER",tok);
			tokens.push_back(t);
		}
		else{
			if(!checkIdent(tok)){
				Token t;
				t.set_values("IDENT",tok);
				tokens.push_back(t);}
			}
			tok = "";
	}

}

/**
 * The build method starts the process of retrieving characters
 * from the text file one character at a time. We ensure that the
 * process continues until the end of the file without having the
 * newline, carriage return and horizontal tab characters confuse
 * the process later on.
 */

void build(){

	char myChar;

	while(!file.eof() && (int)(myChar) != -1 ){
		myChar = file.get();
		if((int)(myChar) != -1 && myChar != '\n' && myChar != '\r' && myChar != '\t'){
			buildTok(myChar);
		}
	}
}

/**
 * The method printTokenList iterates through the list of tokens and
 * prints each token with it's position in the ArrayList, it's value and
 * an arrow pointing to the token value.
 *
 */

void printTokenList(){
	cout << "\nTokens:\n\n";
    for(int i = 0; i < tokens.size() ; i++){
    	string num;
    	num = tokens[i].value;
     	cout << tokens[i].value << "\t->\t" << tokens[i].type << "\n";
        }

}

int main() {

	 if (file.is_open())
	  {
	    cout << "\nFile successfully open\n";
	    build();

	    printTokenList();

	  }
	  else
	  {
	    cout << "Error opening file";
	    exit(0);
	  }


	return 0;
}



