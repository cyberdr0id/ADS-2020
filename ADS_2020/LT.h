#pragma once
#include "stdafx.h"

#define	LEXEMA_FIXSIZE   1	        
#define	LT_MAXSIZE		 4096	    
#define	LT_TI_NULLDX	 0xffffffff	
#define LEX_SEPARATORS	 'S'
#define	LEX_ID_TYPE_I    'n'
#define	LEX_ID_TYPE_S    's'
#define	LEX_ID			 'i'			
#define	LEX_LITERAL		 'l'	
#define LEX_LIB			 'b'
#define	LEX_FUNCTION     'f'			
#define	LEX_MAIN		 'm'			
#define	LEX_RETURN		 'r'			
#define	LEX_OUTPUT		 'o'	
#define LEX_DECLARE		 't'
#define	LEX_SEPARATOR	 ';'			
#define	LEX_COMMA		 ','			
#define	LEX_LEFTBRACE	 '{'			
#define	LEX_BRACELET	 '}'			
#define	LEX_LEFTTHESIS	 '('			
#define	LEX_RIGHTTHESIS	 ')'			
#define	LEX_PLUS		 '+'	
#define	LEX_MINUS		 '-'
#define LEX_ROOT		 'k'
#define LEX_POWER		 'p'
#define	LEX_STAR		 '*'			
#define	LEX_DIRSLASH	 '/'			
#define	LEX_EQUAL		 '='			
#define	LEX_OPERATION	 'v'
#define	INTEGER			 "int"		
#define	STRING			 "string"
#define	LTRL			 "ltrl"
#define SPACE  ' '
#define DOT '.'
namespace LT	
{
	struct Entry                       
	{
		char lexema;					
		int sn;							
		int idxTI;						

		Entry();
		Entry(char lexema, int snn, int idxti = LT_TI_NULLDX);
	};

	struct LexTable						
	{
		int maxsize;					
		int size;						
		Entry* table;					
	};

	LexTable Create(int size);		            
	void Add(LexTable &lextable, Entry entry);	
}