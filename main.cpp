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
        try{
            auto* analyzer = new Analyzer(argc[2], getAlphabetFromString(argc[1]));
            analyzer->processFile();
            analyzer->makeReportFile();
        }
        catch (invalid_argument& e){
            cout << "ERROR: " << e.what() << endl;
        }

    }
    else {
       printUsage();
    }
    cout<<endl<<"----------------------------------------------------------"<<endl<<endl;

}