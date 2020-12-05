#include "stdafx.h"


namespace In
{
	IN getin(std::ofstream *stream, wchar_t Infile[])
	{
		std::ifstream txtfile(Infile);
		if (!txtfile.is_open())
			throw ERROR_THROW(20);
		IN InS;
		InS.text = new unsigned char[IN_MAX_LEN_TEXT];
		int pos = 0;
		unsigned char rSymb = IN_CODE_NULL;

		while ((rSymb = txtfile.get()) && (!txtfile.eof()))
		{
			switch (InS.code[rSymb])
			{
			case IN::NS:
			{
				InS.text[InS.size++] = rSymb;
				InS.lines++;
				pos = 0;
				break;
			}
			case IN::PR:
			{
				pos++;
				if (InS.text[InS.size - 1] == IN::PR)
					InS.ignor++;
				else
					InS.text[InS.size++] = rSymb;
				break;
			}
			case IN::SEP:
			{
				pos++;
				if (InS.text[InS.size - 1] == IN_CODE_SPACE)
					InS.text[InS.size - 1] = rSymb; 
				else
					InS.text[InS.size++] = rSymb;
				break;
			}
			case IN::F:
			{
				Log::writeError(stream, Error::GetError(21, InS.lines, InS.size));
				break;
			}
			case IN::I:
			{
				pos++;
				InS.ignor++;
				break;
			}
			case IN::T:
			{
				pos++;
				if (InS.code[InS.text[InS.size - 2]] == IN::SEP && InS.code[InS.text[InS.size - 1]] == IN::PR) 
					InS.text[InS.size - 1] = rSymb;
				else
					InS.text[InS.size++] = rSymb;
				break;
			}
			case IN::L:
			{
				if (InS.text[InS.size - 1] == IN_CODE_SPACE)
					InS.text[InS.size - 1] = rSymb;
				else
					InS.text[InS.size++] = rSymb;
				rSymb = txtfile.get();
				int count = 0;
				while (InS.code[rSymb] != IN::L)
				{
					count++; pos++;
					if (InS.code[rSymb] == IN::NS)
					{
						throw ERROR_THROW_IN(23, InS.lines, pos);
					}
					if (InS.code[rSymb] == IN::F)
					{
						Log::writeError(stream, Error::GetError(21, InS.lines, pos));
					}
					if (count == MAX_STRING - 2)
					{
						Log::writeError(stream, Error::GetError(24, InS.lines, pos));
						while (InS.code[rSymb] != IN::L)
						{
							rSymb = txtfile.get();
						}
						InS.text[InS.size] = rSymb;
						break;
					}
					InS.text[InS.size++] = rSymb;
					rSymb = txtfile.get();
				}
				InS.text[InS.size++] = rSymb;
				break;
			}
			}
		}


		InS.text[InS.size] = IN_CODE_NULL;

		return InS;
	}

	int Words::amount = 0;

	void newWord(Words *words, char* &buf, int &posbuf, int line)
	{
		buf[posbuf++] = IN_CODE_NULL;
		strcpy_s((words[Words::amount].word), posbuf, buf);
		words[Words::amount].line = line; 
		Words::amount++;
		buf[0] = IN_CODE_NULL;
		posbuf = 0;
	}

	Words* split(Words *words, unsigned char *text, int *code)
	{
		words = new Words[IN_MAX_LEN_TEXT];
		char *buf = new char[IN_MAX_STRING_CODE];
		int posBuf = 0;
		int line = 0;

		for (int i = NULL; text[i] != IN_CODE_NULL; i++)
		{
			switch (code[text[i]])
			{
				case IN::NS:
				line++;
				case IN::PR:
				{
					if (buf[0] != IN_CODE_NULL)
						newWord(words, buf, posBuf, line);
					break;
				}
				case IN::SEP:
				{
					if (buf[0] != IN_CODE_NULL)
						newWord(words, buf, posBuf, line);

					buf[posBuf++] = text[i];
					newWord(words, buf, posBuf, line);
					break;
				}
				case IN::T:
				{
					buf[posBuf++] = text[i];
					break;
				}
				case IN::L:
				{
					if (buf[0] != IN_CODE_NULL)
						newWord(words, buf, posBuf, line);
					buf[posBuf++] = text[i];			//первая кавычка
					while (code[text[++i]] != IN::L)
						buf[posBuf++] = text[i];
					buf[posBuf++] = text[i];			//вторая кавычка
					newWord(words, buf, posBuf, line);
					break;
				}
			
			}
		}
		return words;
	}
}
