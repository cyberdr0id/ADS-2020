#pragma once

#include "stdafx.h"
									
#define ID_MAXSIZE	15				//макс число символов идентификатора
#define ID_FOR_IT   30              //макс число символов идентификатор + принадлежность ф-ии
#define TI_MAXSIZE	4096			//макс число количество строк в таблице идентификаторов
#define TI_INT_DEFAULT	0			//значение по умолчанию для int
#define TI_STR_DEFAULT	0x00		//значение по умолчанию для sting
#define TI_NULLIDX		0xffffffff	//нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	200
#define INT_MAXSIZE_PARM   20
#define INT_MINUS_MAXSIZE   0

namespace IT
{
	enum IDDATATYPE { INT = 1, STR = 2 };				
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, S = 5 };	
	struct Entry										
	{
		int	idxfirstLE;									
		char		id[ID_FOR_IT];						
		IDDATATYPE	iddatatype;							
		IDTYPE		idtype;								
		int count_parm;									
		char parms[INT_MAXSIZE_PARM];

		struct
		{
			int	vNUM;            						
			struct
			{
				int len;								
				char str[TI_STR_MAXSIZE - 1];			
			}vSTR;										
		}value;											
		Entry()
		{
			this->value.vNUM = TI_INT_DEFAULT;
			this->value.vSTR.len = NULL;
		};
		Entry(char* id, int idxLT, IDDATATYPE datatype, IDTYPE idtype)
		{
			strncpy_s(this->id, id, ' ');
			this->idxfirstLE = idxLT;
			this->iddatatype = datatype;
			this->idtype = idtype;
		};
	};
	struct IdTable								
	{
		int maxsize;							
		int size;								
		Entry* table;							
	};

	IdTable Create(int size = NULL);			

	void Add(									
		IdTable &idtable,						
		Entry entry);							

	int IsId(									
		IdTable &idtable,						
		char id[ID_MAXSIZE]);					

	void SetValue(IdTable &idtable, int, char*);
}