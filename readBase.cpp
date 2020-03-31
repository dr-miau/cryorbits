#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include "periodicT.h"
#include "readBase.h"

//read the information of the basis set for all atoms.
int readBase(int Natoms, int atomKind, std::vector<int> &atom,std::vector<int> &atomBasis,
		std::vector<int> &totalBase)
{
        std::cout << "Insert file name:";
        std::string cryOut;
        std::getline(std::cin,cryOut);
        std::ifstream ifile(cryOut);

       // std::cout << "Insert number of atoms: ";
       // int Natoms{0};
       // std::cin >> Natoms;

       // std::cout << "Insert number of atoms types: ";
       // int atomKind{0};
       // std::cin >> atomKind;

        std::cout << "Kind of vacancies? (Enter Z): ";
        int zVacancy{0};
        std::cin >> zVacancy;
        //char *atom{ new char[Natoms]{} };
        atom.resize(Natoms);
        totalBase.resize(atomKind*2);
//        torbit{ new int[Natoms]{} };

//iline->input line. basisIn->bool for 'in the basis section'.
//firstAtom->bool for save basis orbitals info.
//atomBasis->big array with info of orbitals of each atom kind.
//      The index hundreds indicate the atom specifier.
        std::string iline{};
        bool basisIn{false};
        int atomId{0};
        int baseId{0};
        int atomFirst{0};
        bool continueBasis{};
        bool firstAtom{false};
        atomBasis.resize(100*atomKind);
        std::string currentAtom{};
        std::string pastAtom{};
        for(int i=0;i<100*atomKind;i++)
                atomBasis[i]=-1;
        for(int i=0;i<2*atomKind;i++)
                totalBase[i]=0;
        while(ifile)
        {
                std::getline(ifile,iline);
                if(iline==" LOCAL ATOMIC FUNCTIONS BASIS SET")
                {
                        basisIn=true;
                        //TITLE skip
                        for(int i=0;i<3;i++)
                                std::getline(ifile,iline);
                }
                while(basisIn)
                {
                        std::getline(ifile,iline);
                        std::stringstream ssin(iline);
                       std::string tline[6];
                        for(int i=0;i<6;i++)
                                ssin >> tline[i];
                        if(tline[0].find("INFO") != std::string::npos)
                        {
                                basisIn=false;
                                continue;
                        }
                        if(tline[0].find("E") == std::string::npos && tline[4] != "")
                        {
                                //currentAtom=tline[1];
                                if(pastAtom!=tline[1])
                                {
                                        pastAtom=tline[1];
                                        firstAtom=true;
                                }
                                if(pastAtom=="XX")
                                        atom[atomId]=zVacancy;
                                else
                                        atom[atomId]=periodicT(tline[1]);
                                //if(atom[atomId]==0)
                                //      atom[atomId]=zVacancy;
                                atomId++;
                                if(continueBasis)
                                        atomFirst++;
                                continueBasis=false;
                       }
                        if(tline[0].find("E") == std::string::npos && tline[4] == "")
                        {
                                //std::cout << atomFirst << '\n';
                                continueBasis=true;
                                std::istringstream signOrb(tline[0]);
                                std::string unsignOrb;
                                int substId{0};
                                while(std::getline(signOrb,unsignOrb,'-'))
                                {
                                        if(substId==1)
                                                tline[2]=tline[1];
                                        //std::cout << unsignOrb << '\n';
                                        tline[substId]=unsignOrb;
                                        substId++;
                                }
                                if(tline[2]=="")
                                        tline[2]="S";
                                //std::cout << "l is " << orbitalL(tline[2]) << '\n';
                                if(firstAtom)
                                {
					baseId=0;
                                        if(pastAtom=="XX")
					{
						atomBasis[baseId+atomFirst*100]=zVacancy;
					        totalBase[atomFirst*2]=zVacancy;
					}
					else
					{
                                                atomBasis[baseId+atomFirst*100]=periodicT(pastAtom);
					        totalBase[atomFirst*2]=periodicT(pastAtom);
					}
					atomBasis[baseId+atomFirst*100+1]=orbitalL(tline[2]);
					//totalBase[atomFirst*2+1]=totalBase[atomFirst*2+1]+l2orbit(orbitalL(tline[2]));
                                        baseId++;
                                        firstAtom=false;
                                }
                                else
                                        atomBasis[baseId+atomFirst*100]=orbitalL(tline[2]);
					totalBase[atomFirst*2+1]=totalBase[atomFirst*2+1]+l2orbit(orbitalL(tline[2]));
                                baseId++;
				//std::cout << totalBase[3] << "Holi \n";
                                //std::cout << tline[0] << "|" << tline[1]
                                //      << "|" << tline [2] << "|"
                                //      << tline[3] << "|" << tline[4] << "\n";
                        }
                }
        }

        return 0;
}
