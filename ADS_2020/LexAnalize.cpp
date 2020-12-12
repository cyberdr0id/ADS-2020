#include "stdafx.h"	


namespace LA
{
	Graph graph[N_GRAPHS] = 
	{
		{ LEX_SEPARATORS, FST::FST(GRAPH_SEPARATORS) },
		{ LEX_EQUAL, FST::FST(GRAPH_EQUAL) },
		{ LEX_LESS, FST::FST(GRAPH_LESS) },
		{ LEX_MORE, FST::FST(GRAPH_MORE) },
		{ LEX_LEFTSQUAREBRACE, FST::FST(GRAPH_LEFTSQUAREBRACE) },
		{ LEX_RIGTHSQUAREBRACE, FST::FST(GRAPH_RIGHTSQUAREBRACE) },
		{ LEX_DECLARE, FST::FST(GRAPH_DECLARE) },
		{ LEX_LITERAL, FST::FST(GRAPH_NUMBER_LITERAL) },
		{ LEX_LITERAL, FST::FST(GRAPH_STRING_LITERAL) },
		{ LEX_FUNCTION, FST::FST(GRAPH_FUNCTION) },
		{ LEX_RETURN, FST::FST(GRAPH_RETURN) },
		{ LEX_OUTPUT, FST::FST(GRAPH_OUTPUT) },
		{ LEX_MODULE, FST::FST(GRAPH_MODULE) },
		{ LEX_MAIN, FST::FST(GRAPH_MAIN) },
		{ LEX_LIB, FST::FST(GRAPH_USERLIB) },
		{ LEX_DIRSLASH, FST::FST(GRAPH_FORWARD_SLASH) },
		{ LEX_ROOT, FST::FST(GRAPH_ROOT) },
		{ LEX_POWER, FST::FST(GRAPH_POWER) },
		{ LEX_RANDOM, FST::FST(GRAPH_RANDOM) },
		{ LEX_CONCAT, FST::FST(GRAPH_CONCAT) },
		{ LEX_WHILE, FST::FST(GRAPH_WHILE) },
		{ LEX_ID_TYPE_I, FST::FST(GRAPH_INT) },
		{ LEX_ID_TYPE_S, FST::FST(GRAPH_STRING) },
		{ LEX_ID, FST::FST(GRAPH_ID) },
	};
	
	LEX StartLexAnalyze(In::IN &InStruct, Log::LOG &log, Parm::PARM &parm)
	{
		LEX Tables;
		Tables.Lextable = LT::Create(LT_MAXSIZE);
		Tables.IDtable = IT::Create(TI_MAXSIZE); 

		bool FlagEx = false; 
		bool flag1 = false;  
		bool flag2 = false;  
		bool isParam = false;     
		int kol = 0;				
		int MainBody = 0;			
		int MyFunc = 0;				
		int LibBody = 0;			
		char Buffer[255] = "";		
		char PrefixFunc[255] = "";

		IT::IDDATATYPE funcType;
		IT::IDDATATYPE idType;  

		for (int i = 0; i < In::Words::amount; i++)
		{
			FlagEx = false;
			for (int j = 0; j < N_GRAPHS; j++)    
			{
				FST::FST fstex(InStruct.words[i].word, graph[j].graph);
				if (FST::execute(fstex))
				{
					FlagEx = true;
					switch (graph[j].lexema)
					{

					case LEX_MAIN:   
					{
						MainBody++;  
						if (MainBody > 1) 
							Log::writeError(log.stream, Error::GetError(84, InStruct.words[i].line, NULL));

						strcpy_s(PrefixFunc, "m");
						LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line);   
						LT::Add(Tables.Lextable, entrylt); 
						break;
					}
					case LEX_LIB:
					{
						LibBody++;
						if (LibBody > 1)
							Log::writeError(log.stream, Error::GetError(89, InStruct.words[i].line, NULL));

						LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}

					case LEX_ROOT:
					{
						MyFunc++;

						IT::Entry entryit("root", i, IT::INT, IT::S); 
						IT::Add(Tables.IDtable, entryit);				
						LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word)); 
																																		
						LT::Add(Tables.Lextable, entrylt);
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 1;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'n';
						break;
					}
					case LEX_RANDOM:
					{
						MyFunc++;

						IT::Entry entryit("rand", i, IT::INT, IT::S);
						IT::Add(Tables.IDtable, entryit);
						LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word));

						LT::Add(Tables.Lextable, entrylt);
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 2;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'n';
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[1] = 'n';
						break;
					}
					case LEX_POWER:
					{
						MyFunc++;
						IT::Entry entryit("power", i, IT::INT, IT::S); 
						IT::Add(Tables.IDtable, entryit);			
						LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word)); 
																																	
						LT::Add(Tables.Lextable, entrylt);
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 2;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'n';
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[1] = 'n';
						break;
					}
					case LEX_CONCAT:
					{
						MyFunc++;

						IT::Entry entryit("conc", i, IT::STR, IT::S);
						IT::Add(Tables.IDtable, entryit);
						LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word));

						LT::Add(Tables.Lextable, entrylt);
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 1;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 's';
						
						break;
					}
					case LEX_ID:
					{
						if (Tables.Lextable.table[i - 1].lexema != LEX_FUNCTION && IT::IsId(Tables.IDtable, InStruct.words[i].word) == -1)
						{
							strncpy(Buffer, PrefixFunc, ID_MAXSIZE - 1);
							strcat_s(Buffer, InStruct.words[i].word);
							strncpy(InStruct.words[i].word, Buffer, ID_MAXSIZE - 1);
						}

						if (IT::IsId(Tables.IDtable, InStruct.words[i].word) == -1) // если данный идентификатор не найден повторно 
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION) // если предыдущей лексемой была лексема функциии
							{
								strncpy_s(PrefixFunc, InStruct.words[i].word, ID_MAXSIZE - 1);

								funcType = idType; 
								IT::Entry entryit(PrefixFunc, i, idType, IT::F);
								IT::Add(Tables.IDtable, entryit);
								LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word));										 
								LT::Add(Tables.Lextable, entrylt);
								if (InStruct.words[i + 2].word[0] == LEX_RIGHTTHESIS) // если лексема через одну - )  
									isParam = false; // если функция без параметров
								else isParam = true; // наличие параметров
								break;

							}
							else if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE_I) //если предыдущая лесема была лексемой целого типа данных 
							{
								
								if (isParam == false) // если идентификатор типа переменная не является параметром
								{
									if (Tables.Lextable.table[i - 2].lexema != LEX_DECLARE) //если не было предварительного определения словом type
									{
										Log::writeError(log.stream, Error::GetError(82, InStruct.words[i].line, NULL));
										flag1 = true;
									}
									IT::Entry entryit(InStruct.words[i].word, i, idType, IT::V);
									IT::Add(Tables.IDtable, entryit);
								}
								else if (isParam == true)
								{
									int curpos = Tables.IDtable.size;
									while (Tables.IDtable.table[curpos].idtype != IT::F)
										curpos--;
									if (kol > INT_MAXSIZE_PARM)
									{
										Log::writeError(log.stream, Error::GetError(94, InStruct.words[i].line, NULL));
										flag1 = true;
									}
									Tables.IDtable.table[curpos].parms[kol] = 'n';
									kol++;
									IT::Entry entryit(InStruct.words[i].word, i, idType, IT::P);
									IT::Add(Tables.IDtable, entryit);
									if (InStruct.words[i + 1].word[0] == LEX_RIGHTTHESIS)
									{
										isParam = false; // параметры закончились
										int curpos = Tables.IDtable.size;
										while (Tables.IDtable.table[curpos].idtype != IT::F)
											curpos--;
										Tables.IDtable.table[curpos].count_parm = kol;
										kol = 0;
									}
								}

								LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word));
								LT::Add(Tables.Lextable, entrylt);
								break;
							}
							else if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE_S) //если предыдущая лесема была лексемой стокового типа данных
							{
								if (isParam == false) // если идентификатор типа переменная не является параметром
								{
									if (Tables.Lextable.table[i - 2].lexema != LEX_DECLARE) //если не было предварительного определения словом type
									{
										Log::writeError(log.stream, Error::GetError(82, InStruct.words[i].line, NULL));
										flag1 = true;
									}
									IT::Entry entryit(InStruct.words[i].word, i, idType, IT::V);
									IT::Add(Tables.IDtable, entryit);
								}
								else if (isParam == true)
								{
									int curpos = Tables.IDtable.size;																							
									while (Tables.IDtable.table[curpos].idtype != IT::F)
										curpos--;
									Tables.IDtable.table[curpos].parms[kol] = 'w';
									kol++;
									if (kol == INT_MAXSIZE_PARM)
									{
										Log::writeError(log.stream, Error::GetError(80, InStruct.words[i].line, NULL));
										flag1 = true;
									}
									IT::Entry entryit(InStruct.words[i].word, i, idType, IT::P);
									IT::Add(Tables.IDtable, entryit);
																	 
									if (InStruct.words[i + 1].word[0] == LEX_RIGHTTHESIS)
									{
										isParam = false;
										int curpos = Tables.IDtable.size;
										while (Tables.IDtable.table[curpos].idtype != IT::F)
											curpos--;
										Tables.IDtable.table[curpos].count_parm = kol;
										kol = 0;
									}
								}

								LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word));
								LT::Add(Tables.Lextable, entrylt);
								break;
							}
							Log::writeError(log.stream, Error::GetError(82, InStruct.words[i].line, NULL)); // если пред лекс не была ни string, ни int
							flag1 = true;																		
						}
						//проверка на переопределение	
						else
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE_I || Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE_S || Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION) // если предыдущим был тип данных или лексема функции
							{
								Log::writeError(log.stream, Error::GetError(81, InStruct.words[i].line, NULL));
								flag1 = true;
							}
							LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word));
							LT::Add(Tables.Lextable, entrylt);
							break;
						}
						break;
					}
					case LEX_LITERAL:
					{
						if (Tables.Lextable.table[i - 1].lexema == LEX_ASSIGN) // проверим предыдущие лексемы
						{
							
							IT::Entry entryit(LTRL, i, graph[j].graph.type, IT::L);
							IT::Add(Tables.IDtable, entryit);
							IT::SetValue(Tables.IDtable, Tables.IDtable.size - 1, InStruct.words[i].word); 
							LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, Tables.IDtable.size - 1);
							LT::Add(Tables.Lextable, entrylt);
							if (Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.words[i - 2].word)].idtype == IT::F) // если предыдущая была лекс ф-ции
							{
								Log::writeError(log.stream, Error::GetError(86, InStruct.words[i].line, NULL)); //нельзя присваивать значение ф-ции
								flag1 = true;
							}
							if (Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.words[i - 2].word)].idtype == IT::V ||    //если перед = была переменная или параметр
								Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.words[i - 2].word)].idtype == IT::P)
							{
								IT::SetValue(Tables.IDtable, IT::IsId(Tables.IDtable, InStruct.words[i - 2].word), InStruct.words[i].word);
							}
							break;
						}

						else
						{	IT::Entry entryit(LTRL, i, graph[j].graph.type, IT::L);
							IT::Add(Tables.IDtable, entryit); 
							IT::SetValue(Tables.IDtable, Tables.IDtable.size - 1, InStruct.words[i].word); 
							LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, Tables.IDtable.size - 1); 
							LT::Add(Tables.Lextable, entrylt); 
						}
						break;
					}

					case LEX_SEPARATORS: 
					{

						switch (InStruct.words[i].word[0])
						{
						case LEX_SEPARATOR:
						{
							if (Tables.Lextable.table[i - 2].lexema == LEX_RETURN) // 2 лекс назад return
							{
								if (Tables.IDtable.table[Tables.Lextable.table[i - 1].idxTI].iddatatype != funcType) 
								{
									Log::writeError(log.stream, Error::GetError(91, InStruct.words[i].line, NULL));  // возвращаемое значение не совпадает с типом функции
									flag1 = true;
								}
																						
								IT::IDDATATYPE retType; 
								if (Tables.Lextable.table[i - 1].lexema == LEX_LITERAL) // если предыдущая литерал
									retType = Tables.IDtable.table[Tables.IDtable.size - 1].iddatatype;
							}

							LT::Entry entrylt(InStruct.words[i].word[0], InStruct.words[i].line);
							LT::Add(Tables.Lextable, entrylt); 
							break;

						}
						case LEX_PLUS:
						case LEX_ASSIGN:
						case LEX_STAR:
						case LEX_MINUS:
						case LEX_DIRSLASH:
						case LEX_MODULE:
						{
							
							if (Tables.Lextable.table[i - 1].lexema != LEX_ID && Tables.Lextable.table[i - 1].lexema != LEX_RIGHTTHESIS && Tables.Lextable.table[i - 1].lexema != LEX_LEFTTHESIS && Tables.Lextable.table[i - 1].lexema != LEX_LITERAL)
							{   //если прошлым символом был не ID, не скобки, не литерал
								Log::writeError(log.stream, Error::GetError(56, InStruct.words[i].line, NULL)); //два знака операции подряд
								flag1 = true;                           
							}
							LT::Entry entrylt(InStruct.words[i].word[0], InStruct.words[i].line); 
							LT::Add(Tables.Lextable, entrylt); 
							break;
						}

						default:
						{
							LT::Entry entrylt(InStruct.words[i].word[0], InStruct.words[i].line); 
							LT::Add(Tables.Lextable, entrylt); 
						}
						}
						break;
					}
					case LEX_ID_TYPE_S: 
					case LEX_ID_TYPE_I: 
						idType = graph[j].graph.type;
					default:
					{
						LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line); 
						LT::Add(Tables.Lextable, entrylt); 
						break;
					}
					}
					break;
				}
				
			}
			if (FlagEx == false) {
				throw ERROR_THROW_IN(32, InStruct.words[i].line, NULL); //останавливаем работу программы
			}
		}
		if (Tables.Lextable.size == LT_MAXSIZE)
		{
			throw ERROR_THROW(31);
		}
		if (Tables.IDtable.size == TI_MAXSIZE)
		{
			throw ERROR_THROW(30);
		}
		if (!MainBody)
		{
			flag1 = true;
			throw ERROR_THROW(83);
		}
		if (LibBody == 0 && MyFunc>0)
			throw ERROR_THROW(88);
	

		if (flag1 == false && flag2 == false)
		{
			for (int i = 0; i < Tables.Lextable.size; i++) // проверка выражний и не стандратных функций
			{
				if (Tables.Lextable.table[i].lexema == LEX_ID)
				{
					if (Tables.IDtable.table[Tables.Lextable.table[i].idxTI].idtype == IT::F) //если после функции нет открывающейся скобки
					{
						if (Tables.Lextable.table[i + 1].lexema != LEX_LEFTTHESIS)
							throw ERROR_THROW(95);
					}
				}

				if (Tables.Lextable.table[i].lexema == LEX_STAR || Tables.Lextable.table[i].lexema == LEX_DIRSLASH || Tables.Lextable.table[i].lexema == LEX_MINUS || Tables.Lextable.table[i].lexema == LEX_PLUS)
				{   //если вокруг знаков операций что-то помимо ID,литерала и скобок
					if (Tables.Lextable.table[i - 1].lexema != LEX_ID && Tables.Lextable.table[i - 1].lexema != LEX_LEFTTHESIS && Tables.Lextable.table[i - 1].lexema != LEX_RIGHTTHESIS && Tables.Lextable.table[i - 1].lexema != LEX_LITERAL)
						Log::writeError(log.stream, Error::GetError(605, InStruct.words[i + 1].line, NULL)); //ошибка в построении выражения
					if (Tables.Lextable.table[i + 1].lexema != LEX_ID && Tables.Lextable.table[i + 1].lexema != LEX_LEFTTHESIS && Tables.Lextable.table[i + 1].lexema != LEX_RIGHTTHESIS && Tables.Lextable.table[i + 1].lexema != LEX_LITERAL)
						Log::writeError(log.stream, Error::GetError(605, InStruct.words[i + 1].line, NULL)); //ошибка в построении выражения
				}
				if (Tables.Lextable.table[i].lexema == LEX_ASSIGN) //проверка типов в выражении после знака =
				{
					bool mainFunctionFlag = false;
					int pos = i+1;
					idType = Tables.IDtable.table[Tables.Lextable.table[i - 1].idxTI].iddatatype; //тип переменной до =
					if ((Tables.Lextable.table[pos].lexema == LEX_ID && Tables.IDtable.table[Tables.Lextable.table[pos].idxTI].idtype == IT::F) || ((Tables.Lextable.table[pos].lexema == LEX_POWER || Tables.Lextable.table[pos].lexema == LEX_RANDOM)&& Tables.IDtable.table[Tables.Lextable.table[pos].idxTI].idtype == IT::S))
						mainFunctionFlag = true; //чтобы проверка несоответствия типов не распространялась на вызов функции в main
					while (Tables.Lextable.table[pos].lexema != LEX_SEPARATOR)
					{
						if (idType == IT::STR && (Tables.Lextable.table[pos].lexema == LEX_STAR || Tables.Lextable.table[pos].lexema == LEX_DIRSLASH || Tables.Lextable.table[pos].lexema == LEX_MINUS || Tables.Lextable.table[pos].lexema == LEX_PLUS))
							Log::writeError(log.stream, Error::GetError(90, InStruct.words[i].line, NULL));//если переменная строкового типа и мы пытаемся делать с ней какие-то операции

						if (Tables.Lextable.table[pos].lexema == LEX_DIRSLASH && Tables.Lextable.table[pos + 1].lexema == LEX_LITERAL && Tables.IDtable.table[Tables.Lextable.table[pos + 1].idxTI].value.vNUM == 0)
							Log::writeError(log.stream, Error::GetError(87, InStruct.words[pos+1].line+1, NULL)); //попытка разделить на 0

						if ((Tables.Lextable.table[pos].lexema == LEX_ID || Tables.Lextable.table[pos].lexema == LEX_LITERAL) && Tables.IDtable.table[Tables.Lextable.table[pos].idxTI].iddatatype != idType && mainFunctionFlag == false)
							Log::writeError(log.stream, Error::GetError(85, InStruct.words[pos].line+1, NULL)); //несоответствие типов в выражении (если перед и после знаков не скобочки)
						pos++;
					}
					mainFunctionFlag = false;
				}
				
			}
			bool FlagForMain = false; int some_count = 0; char some_buffer[INT_MAXSIZE_PARM];
			for (int i = 0; i < Tables.Lextable.size; i++)
			{
				if (Tables.Lextable.table[i].lexema == LEX_MAIN)
					FlagForMain = true;

				if (FlagForMain == true)
				{
					if ((Tables.Lextable.table[i].lexema == LEX_ID && Tables.IDtable.table[Tables.Lextable.table[i].idxTI].idtype == IT::F) || ((Tables.Lextable.table[i].lexema == LEX_POWER || Tables.Lextable.table[i].lexema == LEX_ROOT || Tables.Lextable.table[i].lexema == LEX_RANDOM) && Tables.IDtable.table[Tables.Lextable.table[i].idxTI].idtype == IT::S))
					{	
							int param = 0;

							if (Tables.Lextable.table[i + 1].lexema == LEX_LEFTTHESIS)
							{
								int k = i + 1;
								while (Tables.Lextable.table[k].lexema != LEX_RIGHTTHESIS)
								{
									if (Tables.Lextable.table[k].lexema == LEX_ID || Tables.Lextable.table[k].lexema == LEX_LITERAL)
									{
										if (Tables.IDtable.table[Tables.Lextable.table[k].idxTI].iddatatype == IT::STR)
											some_buffer[some_count] = 'w';
										if (Tables.IDtable.table[Tables.Lextable.table[k].idxTI].iddatatype == IT::INT)
											some_buffer[some_count] = 'n';
										some_count++;
									}
									k++;
								}
								if (some_count != Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm)
								{
									Log::writeError(log.stream, Error::GetError(92, InStruct.words[i + 1].line, NULL));
								}
								for (int r = 0; r < some_count; r++)
									if (some_buffer[r] != Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[r] && some_count <= Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm)
									{
										Log::writeError(log.stream, Error::GetError(93, InStruct.words[i + 1].line, NULL));
									}
								some_count = 0;
						}
					}
				}
			}
		}
		return Tables;
	}
}