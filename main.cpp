//
// Created by Grigory on 02/10/2022.
//

#include "Analyzer.h"

using namespace std;

int main(int argv, char* argc[])
{

    cout  << argc[0] << endl << endl;

    cout<<endl<<"------------------------ ANALYZER ------------------------"<<endl<<endl;
    if(argv>1)
    {
        vector<string> files;  //files from console
        string file = "";  // file
        bool flag_fs = false, flag_path = false;  // flags
        char type[7];              // flag container
        memset(type,0,7);

        auto* analyzer = new Analyzer(file, getAlphabetFromString(type));
        analyzer->processFile();
    }
    else {

        //todo fix
        cout << "USAGE:" << endl;
        cout << "-pack -files <files to compress> -path <folder_to_save_archive_file>" << endl;
        cout << "OR" << endl;
        cout << "-unpack -files <archive_file> -path <path for extracted files>" << endl;
    }
    cout<<endl<<"----------------------------------------------------------"<<endl<<endl;

}