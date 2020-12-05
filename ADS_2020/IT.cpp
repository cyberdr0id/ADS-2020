#include "stdafx.h"

namespace IT
{
	IdTable Create(int size)
	{
		IdTable idtable;
		idtable.table = new Entry[size];
		idtable.size = 0;
		return idtable;
	}

	void Add(IdTable &idtable, Entry entry)
	{
		strncpy_s(idtable.table[idtable.size].id, entry.id, ID_FOR_IT - 1);
		idtable.table[idtable.size].idxfirstLE = entry.idxfirstLE; 
		idtable.table[idtable.size].iddatatype = entry.iddatatype; 
		idtable.table[idtable.size].idtype = entry.idtype;
		if (entry.idtype == IT::F || entry.idtype == IT::S)
		{
			idtable.table[idtable.size].count_parm = 0;
		}
		idtable.table[idtable.size].value.vNUM = TI_INT_DEFAULT;
		idtable.table[idtable.size].value.vSTR.len = 0; 
		idtable.table[idtable.size].value.vSTR.str[0] = TI_STR_DEFAULT; 
		idtable.size++;
	}

	int IsId(IdTable &idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return -1;
	}

	void SetValue(IdTable &idtable, int indTI, char* word)
	{
		if (idtable.table[indTI].iddatatype == INT)
		{
			int tempInt = atoi(word);
			if (tempInt > INT_MAX)
				tempInt = INT_MAX;
			else if (tempInt < INT_MINUS_MAXSIZE)
				tempInt = INT_MINUS_MAXSIZE;
			idtable.table[indTI].value.vNUM = tempInt;
		}
		else
		{
			idtable.table[indTI].value.vSTR.len = strlen(word);
			strcpy_s(idtable.table[indTI].value.vSTR.str, TI_STR_MAXSIZE, word);
		}
	}
}