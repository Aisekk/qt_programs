#include <iostream>
#include <string>
using namespace std;
//13.1.1 Извлечение имени временного файла

int main(int argc, char* argv[])
{
    string filename, basename, extname, tmpname;
    const string suffix("tmp");

    //для каждого аргумента командной строки, который является обычной С-строкой
    for(int i = 1; i < argc ; ++i)
    {
        filename = argv[i];
        //ищем точку в имени файла
        string::size_type idx = filename.find('.');
        if(idx == string::npos)
        {
            //имя файла не содержит точки
            tmpname = filename + '.' + suffix;
        }
        else{
            //разделяем имя файла на основное имя и расширение
            // - основное имя состоит из сивмолов, предшествующих точке
            // - расширение состоит из символов после точки
            basename = filename.substr(0, idx);
            extname = filename.substr(idx+1);
            if(extname.empty()){
                //содержит точку, но не имеет расширения: добавляем tmp
                tmpname = filename;
                tmpname += suffix;
            }
            else if(extname == suffix)
            {
                //заменяем расширение tmp на xxx
                tmpname = filename;
                tmpname.replace(idx+1, extname.size(), "xxx");
            }
            else{
                //заменяем любое расширение на tmp
                tmpname = filename;
                tmpname.replace(idx+1, string::npos, suffix);
            }
        }
        //выводим имена исходного и временного файлов
        cout << filename << " => " << tmpname << endl;
    }

    system("pause");
    return 0;
}
