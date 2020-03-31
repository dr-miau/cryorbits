/*************************************************************
*Cryorbits - Reads Crystal14 output and returns the Crystaline
*            Orbitals (CO) ID's desired.
*
*            Documentation in progress.
*            
*  +Compilation: g++ main.cpp periodicT.cpp readBase.cpp
*  +Input: 1) Number of atoms in the system.
*          2) Number of atomic species.
*          3) Name of the Crystal14 output file.
*          4) If a vacancy, the associated Z number.
*          5) Z number of the atom of interest.
*          6) Type of CO of interest, as coded in
*             Crystal14: (0->s,1->sp,2-p,3-d,4-f,5-g)
*          7) Appereance of the CO of interest.
*
*   +Warnings: -Check periodicT for available atoms
*              -For the moment it can't give the orbitals
*               just for the vacancy.
*              -Doesn't work for multiple Zs vacancies.
*              -Academic code, for group use and learning.
*
**************************************************************
*Author - Marcos Rivera-Almazo
*GitHub - dr-miau
*************************************************************/

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include "periodicT.h"
#include "readBase.h"

int main()
{
	std::vector<int> atom;
	std::vector<int> atomBasis;
	std::vector<int> totalBase;
	
	std::cout << "Insert number of atoms: ";
        int Natoms{0};
	std::cin >> Natoms;

	std::cout << "Insert number of atoms types: ";
        int atomKind{0};
        std::cin >> atomKind;

	std::cin.ignore(10000,'\n');

	readBase(Natoms,atomKind,atom,atomBasis,totalBase);

	std::cout << "Which atom will be analysed? (enter Z): ";
	int qAtom;
	std::cin >> qAtom;

	std::cout << "What kind of orbital do you need?: ";
	int qOrbit;
	std::cin >> qOrbit;

	std::cout << "Which apereance of that kind of orbital?: ";
	int nOrbit;
	std::cin >> nOrbit;


	int idAtom[Natoms]{};
	int j{ 0 };
	
	for(int i=0;i<Natoms;i++)
	{
		idAtom[i]=0;
		if(atom[i]==qAtom)
		{
			idAtom[j]=i;
			j++;
		}
	}


	int atomOrbits[20]{0};
	int residualPreOrb{0};
	int residualPostOrb{0};
	bool preBool{false};
	bool noseBool{false};
	int apearOrb{0};
	j = 0;
	for(int i=0;i<atomKind;i++)
	{
		if(atomBasis[i*100]==qAtom)
		{
			j++;
			preBool=true;
			while(atomBasis[i*100+j]!=-1)
			{
				atomOrbits[j-1] = atomBasis[i*100+j];
				std::cout << atomBasis[i*100+j] << '\n';
				noseBool=atomBasis[i*100+j]==qOrbit;
				if(noseBool)
				{
					apearOrb++;
					if(apearOrb==nOrbit)
						preBool=false;
					else if(preBool)
						residualPreOrb=residualPreOrb+l2orbit(atomOrbits[j-1]);
					else
						residualPostOrb=residualPostOrb+l2orbit(atomOrbits[j-1]);		
				}
				else if(preBool)
					residualPreOrb=residualPreOrb+l2orbit(atomOrbits[j-1]);
				else
					residualPostOrb=residualPostOrb+l2orbit(atomOrbits[j-1]);		

				//std::cout << "Pre: " << residualPreOrb << " Post: " << residualPostOrb << '\n';
				j++;
			}
	//		continue;
		}
	}
	
	//std::cout << "pre " << residualPreOrb << " post " << residualPostOrb << '\n';

	std::cout << "Printing the orbitals numbers...\n";

	int counterOrb{0};
	for(int i=0;i<Natoms;i++)
	{
		if(atom[i]==qAtom)
		{
			counterOrb=counterOrb+residualPreOrb;
			for(int i=0;i<l2orbit(qOrbit);i++)
			{
				counterOrb++;
				std::cout << counterOrb << ' ';
			}
			counterOrb=counterOrb+residualPostOrb;
			//std::cout << "Atom " << atom[i] << " in " << i << "position.\n";
		}
		else
		{
			for(int j=0;j<atomKind;j++)
			{
				if(atom[i]==totalBase[j*2])
				{
					counterOrb=counterOrb+totalBase[j*2+1];
					//std::cout << "Atom " << atom[i] << " with " << totalBase[j+1] << "orbits.\n";
				}
			}
		}
			//std::cout << "Atom in " << i << "position.\n";
	}


	//for(int i=0;i<atomKind*2;i++)
	//	std::cout << totalBase[i] << " ";
			

       // for(int i=0;i<100*atomKind;i++)
	//	if(atomBasis[i]!=-1)
	//	{
          //      	std::cout << atomBasis[i] << " index " << i << '\n';
	//	}
        //std::cout << atomBasis[0] << " ";
        //std::cout << atomBasis[101] << " ";
        //std::cout << atomBasis[200] << " ";
//        for(int i=0;i<Natoms;i++)
 //               std::cout << atom[i] << " ";

	return 0;
}
