//
// Created by Grigory on 02/10/2022.
//

#include "Analyzer.h"

using namespace std;

int main(int argv, char* argc[])
{
    cout<<endl<<"------------------------ ANALYZER ------------------------"<<endl<<endl;
    if(argv>1)
    {
        auto* analyzer = new Analyzer(argc[2], getAlphabetFromString(argc[1]));
        analyzer->processFile();
    }
    else {
        cout << "USAGE:" << endl;
        cout << "--type  <file to analyze>" << endl;
        cout << "AVALIABLE TYPES:" << endl;
        cout << "* byte\n* utf8" << endl;
    }
    cout<<endl<<"----------------------------------------------------------"<<endl<<endl;

}