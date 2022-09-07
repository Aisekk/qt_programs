#include <iostream>
#include <string>
using namespace std;

int main()
{
    const string delims(" \t,.;");
    string line;

    //для каждой считанной строки
    while(getline(cin,line)){
        string::size_type begIdx, endIdx;
        //поиск начинается с первого слова
        begIdx = line.find_first_not_of(delims);

        //ищем начало первого слова
        while(begIdx != string::npos){
            //ищем конец текущего слова
            endIdx = line.find_first_of(delims, begIdx);
            if(endIdx == string::npos){
                //конец слова - это конец строки
                endIdx = line.length();
            }

            //выводим символы в обратном порядке
            for(int i = endIdx-1; i >= static_cast<int>(begIdx); --i) cout << line[i];
            cout << ' ';

            //ищем начало следующего символа
            begIdx = line.find_first_not_of(delims, endIdx);
        }
        cout << endl;
    }

    system("pause");
    return 0;
}
