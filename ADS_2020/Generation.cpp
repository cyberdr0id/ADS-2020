#include "stdafx.h"

ofstream fout("GenCode.js");

void Generation(LT::LexTable &Lextable, IT::IdTable & IDtable, In::Words *words)
{
	for (int i = 0; i < Lextable.size; i++)
	{
		switch (Lextable.table[i].lexema)
		{
		case LEX_PLUS:
		case LEX_STAR:
		case LEX_MINUS:
		case LEX_DIRSLASH:
		case LEX_ASSIGN:
		case LEX_MODULE:
		case LEX_LESS:
		case LEX_MORE:
		case LEX_EQUAL:
		case LEX_NOTEQUAL:
		{
			fout << " " << Lextable.table[i].lexema << " ";
			break;
		}
		case LEX_LEFTSQUAREBRACE:
		{
			fout << "\n{\n";
			break;
		}
		case LEX_RIGHTSQUAREBRACE:
		{
			fout << "}\n";
			break;
		}
		case LEX_COMMA:
		case SPACE:
		{
			fout << Lextable.table[i].lexema << " ";
			break;
		}

		case LEX_RIGHTTHESIS:
		case LEX_LEFTTHESIS:
		{
			fout << Lextable.table[i].lexema;
			break;
		}
		case LEX_LEFTBRACE:
		{

			fout << endl << Lextable.table[i].lexema << endl;
			break;
		}
		case LEX_BRACELET:
		{

			fout << Lextable.table[i].lexema << endl << endl;
			break;
		}
		case LEX_SEPARATOR:
		{
			fout << Lextable.table[i].lexema << endl;
			break;
		}
		case  LEX_DECLARE:
		{
			fout << "var ";
			break;
		}

		case LEX_LITERAL:
		{
			if (IDtable.table[Lextable.table[i].idxTI].iddatatype == IT::INT)
			fout << IDtable.table[Lextable.table[i].idxTI].value.vNUM;
			else fout << IDtable.table[Lextable.table[i].idxTI].value.vSTR.str;
			break;
		}
		case LEX_ID:
		{
			fout << IDtable.table[Lextable.table[i].idxTI].id;
			break;
		}
		case LEX_OUTPUT:
		{
			fout << "document.write('<br>');" << endl;
			fout << "document.write";
			break;
		}
		case LEX_FUNCTION:
		{
			fout << words[i].word << " ";
			break;
		}
		case LEX_RETURN:
		{
			fout << words[i].word << " ";
			break;
		}
		case LEX_LIB:
		{
			fout << "document.write('U can use basic user libs')";
			break;
		}
		case LEX_ROOT:
		{
			fout << "Math.sqrt";
			for (++i; Lextable.table[i].lexema != LEX_RIGHTTHESIS; i++)
				fout << words[i].word;
			fout << words[i].word;
			break;
		}
		case LEX_POWER:
		{
			fout << "Math.pow";
			for (++i; Lextable.table[i].lexema != LEX_RIGHTTHESIS; i++)
				fout << words[i].word;
			fout << words[i].word;
			break;
		}
		case LEX_RANDOM:
		{
			//Math.random() * (max - min) + min
			fout << "Math.floor(Math.random() * " << words[i + 1].word << words[i + 4].word << "-" << words[i + 2].word << words[i + 5].word << "+" << words[i + 2].word << words[i + 5].word;
			i += 5;
			break;
		}
		case LEX_CONCAT:
		{
			fout << words[i + 2].word << ".concat(";
			i += 3;
			break;
		}
		case LEX_CYCLE:
		{
			fout << "while";
			break;
		}
		}
	}
	fout.close();
}
