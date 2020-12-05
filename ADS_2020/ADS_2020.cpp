#include "stdafx.h"


int _tmain(int argc, wchar_t *argv[])
{
	setlocale(LC_CTYPE, "Russian");
	
	Log::LOG log;
	Log::LOG lex;
	Log::LOG sint;

	try
	{

		Parm::PARM parm = Parm::getparm(argc, argv);

		log = Log::getlog(parm.log);

		Log::writeLog(log);
		Log::writeParm(log, parm);

		In::IN in = In::getin(log.stream, parm.in);

		in.words = In::split(in.words, in.text, in.code);

		LA::LEX tables = LA::StartLexAnalyze(in, log, parm);

		MFST::Mfst mfst(tables, GRB::getGreibach());

		Log::writeIn(log, in);
		Log::writeLexTable(log, tables.Lextable);
		Log::writeIDtable(log, tables.IDtable);

		if (parm.blex == true)
		{
			lex = Log::getlog(parm.lex);

			Log::writeLexTable(lex, tables.Lextable);
			Log::writeIDtable(lex, tables.IDtable);  
		}
		else
		{
			Log::writeLexTableConsole(lex, tables.Lextable);
			Log::writeIDTableConsole(log, tables.IDtable);
		}

		Log::WriteCode(log, tables.Lextable);

		MFST_TRACE_START(log); 

		mfst.start(log);
		mfst.savededucation(); 
		mfst.printrules(log);

		if (parm.bsint == true)
		{
			sint = Log::getlog(parm.sint);
			MFST::Mfst mfst(tables, GRB::getGreibach());
			MFST_TRACE_START(sint);
			mfst.start(sint);
			mfst.savededucation();
			mfst.printrules(sint);
		}

		if (!Log::Error)
		{
			Generation(tables.Lextable, tables.IDtable, in.words);
			std::cout << "Код сгенерирован. Результат - ResultPage.html. Исходый код - GenCode.js" << endl;
			PN polishNotation;
			if (polishNotation.CreatePolishNotation(&tables))
			{
				*log.stream << endl << endl << "Polish Notation";
				Log::WriteCode(log, tables.Lextable);
			}
		}
		
		Log::Close(log); 
	}

	catch (Error::ERROR e)
	{
		Log::writeError(log.stream, e);
	}
}
