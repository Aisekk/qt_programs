#include "FileReader_ResMap.h"

FileReaderResMap::FileReaderResMap(){}

void FileReaderResMap::fileReading(QFile &ReadFile)
{
    QFile writeFile;//объект для записи в текст. файл
    QTextStream inData;//создание входного потокового объекта для чтения файла ResMap
    QTextStream outData;//создание выходного потокового объекта для записи в текст. файл

    //установка объекта читаемого файла во входной потоковой объект
    inData.setDevice(&ReadFile);
    writeFile.setFileName("ResMap_statistics.txt");
    //установка объекта записываемого файла в выходной потоковой объект
    outData.setDevice(&writeFile);

    QString line2;
    QString line4;
    //Поиск и запись регулярных выражений: разбор данных в 4082-файле
    if (writeFile.open(QFile::WriteOnly | QFile::Truncate))
    {
        inData.readLine();
        line2 = inData.readLine();
        inData.readLine();
        line4 = inData.readLine();
//        while (!m_inputData.atEnd())
//        {

//            //-----------------------------------------------------------------------------------
//            //ЗАПИСЬ ДАТЫ ИЗМЕРЕНИЯ
//            if(line.contains(m_regDate))
//            {
//            }
//            //-----------------------------------------------------------------------------------
//        }
        //end of while
    }
    //end of if(write.open)

    outData << line2 << "\r\n" << line4 << "\r\n";
}
