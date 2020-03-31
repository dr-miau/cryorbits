#include <string>
#include "periodicT.h"

//periodic table
int periodicT(std::string symbol)
{
        int AtomN{0};

        if(symbol=="CA")
                AtomN=20;
        if(symbol=="O")
                AtomN=8;
        if(symbol=="TI")
                AtomN=22;
        return AtomN;
}

//orbital type
int orbitalL(std::string symbol)
{
        int numL{0};
        if(symbol=="S")
                numL=0;
        if(symbol=="SP")
                numL=1;
        if(symbol=="P")
                numL=2;
        if(symbol=="D")
                numL=3;
        if(symbol=="F")
                numL=4;
        if(symbol=="G")
                numL=5;
        return numL;
}

//l to number of orbitals
int l2orbit(int lNumber)
{
	switch (lNumber)
	{
		case 0: return 1;
		case 1: return 4;
		case 2: return 3;
		case 3: return 5;
		case 4: return 7;
	}

	return 0;
}	
