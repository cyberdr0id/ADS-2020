#include "stdafx.h"
//синтакс
#define GRB_ERROR_SERIES 50

namespace GRB
{
	Greibach greibach(NS('S'), TS('$'), 8,
		Rule(NS('S'), GRB_ERROR_SERIES, 5,   //programm structure
			Rule::Chain(10, TS('s'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), NS('S')),
			Rule::Chain(10, TS('n'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), NS('S')),
			Rule::Chain(9, TS('s'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), NS('S')),
			Rule::Chain(9, TS('n'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), NS('S')),
			Rule::Chain(4, TS('m'), TS('{'), NS('N'), TS('}'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 1, 4, //function params
			Rule::Chain(4, TS('s'), TS('i'), TS(','), NS('F')),
			Rule::Chain(2, TS('s'), TS('i')),
			Rule::Chain(4, TS('n'), TS('i'), TS(','), NS('F')),
			Rule::Chain(2, TS('n'), TS('i'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 2, 14,  //function body
			Rule::Chain(5, TS('t'), TS('n'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(5, TS('t'), TS('s'), TS('i'), TS(';'), NS('N')),
			\
			Rule::Chain(5, TS('t'), TS('s'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('t'), TS('s'), TS('i'), TS('='), NS('E'), TS(';')),
			\
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('b'), TS(';'), NS('N')),
			Rule::Chain(4, TS('o'), NS('E'), TS(';'), NS('N')),

			Rule::Chain(3, TS('r'), TS('i'), TS(';')),
			Rule::Chain(3, TS('r'), TS('l'), TS(';')),
			Rule::Chain(4, TS('t'), TS('n'), TS('i'), TS(';')),
			Rule::Chain(4, TS('t'), TS('s'), TS('i'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(2, TS('b'), TS(';')),


			Rule::Chain(3, TS('o'), NS('E'), TS(';'))
			
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 3, 18, //expressions	
			Rule::Chain(1, TS('i')),
			Rule::Chain(2, TS('i'), NS('E')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),

			Rule::Chain(3, TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), TS(')'), NS('M')),
	
			Rule::Chain(4, TS('c'), TS('('), NS('W'), TS(')')),
			Rule::Chain(5, TS('c'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('p'), TS('('), NS('W'), TS(')')),
			Rule::Chain(5, TS('p'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('k'), TS('('), NS('W'), TS(')')),
			Rule::Chain(5, TS('k'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('z'), TS('('), NS('W'), TS(')'))
		
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 4, 4, //geting params
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 5, 5, //arithmetic signs
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(2, TS('/'), NS('E')),
			Rule::Chain(2, TS('%'), NS('E'))
		),

		Rule(NS('C'), GRB_ERROR_SERIES + 6, 3, //arithmetic signs
			Rule::Chain(2, TS('>'), NS('E')),
			Rule::Chain(2, TS('<'), NS('E')),
			Rule::Chain(2, TS('~'), NS('E'))
		),

		Rule(NS('A'), GRB_ERROR_SERIES + 7, 2, //arithmetic signs
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l'))
		)
	);

	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{
		nt = new GRBALPHABET[size = psize];    
		int*p = (int*)&s;                      
		for (short i = 0; i < psize; ++i)
			nt[i] = (GRBALPHABET)p[i];
	};

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
	{															
		nn = pnn;    
		iderror = piderror;
		chains = new Chain[size = psize];
		Chain*p = &c;
		for (int i = 0; i < size; i++)
			chains[i] = p[i];
	};

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)
	{
		startN = pstartN;
		stbottomT = pstbottom;
		rules = new Rule[size = psize];
		Rule*p = &r;
		for (int i = 0; i < size; i++) rules[i] = p[i];
	};
	Greibach getGreibach() { return greibach; };

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1;
		short k = 0;
		while (k < size&&rules[k].nn != pnn)
			k++;
		if (k < size)
			prule = rules[rc = k]; 
		return rc;
	};

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < size)rc = rules[n];
		return rc;
	};

	char*Rule::getCRule(char*b, short nchain)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn); b[1] = '-'; b[2] = '>'; b[3] = 0x00;
		chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	};

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)  
	{                                                                
		short rc = -1;
		while (j < size&&chains[j].nt[0] != t)++j;
		rc = (j < size ? j : -1);
		if (rc >= 0)pchain = chains[rc];
		return rc;
	};

	char*Rule::Chain::getCChain(char*b)
	{
		for (int i = 0; i < size; i++)b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	};
};