#include "FileReader_4082.h"

FileReader4082::FileReader4082() : m_maxCountTestElem(100)
{}
//-----------------------------------------------------------------------------------
void FileReader4082::fileReading(QFile &ReadFile)
{
    //-----------------------------------------------------------------------
    //регулярные выражения
    QString strRegDate = "SYS_DATE\t[0-9]{1,2}[/][0-9]{1,2}[/][0-9]{1,4}\t";
    QRegExp regDate{};
    regDate.setPattern(strRegDate);
    QString strRegWaferID = "SYS_WAFERID\t[0-9]{1,2}";
    QRegExp regWaferID{};
    regWaferID.setPattern(strRegWaferID);

    QString strDate{};
    QString strWaferID{};
    //------------------------------------------------------------------------
    //запись названий и количества модулей
    int modCountWithDuplicates = 0;//количество модулей
    QString modName = "ModName";//идентификатор
    QVector<QString> vecModsWithDuplicates;//названия модулей с дубликатами в массиве
    vecModsWithDuplicates.reserve(m_maxCountTestElem);
    //------------------------------------------------------------------------
    //запись названий и количества тестовых элементов
    int testCount = 0;//количество тестов
    QString devName = "DevName";//идентификатор
    QVector<int> vecTestCountOneWafer;
    //------------------------------------------------------------------------
    //запись названий и количества алгов
    int algNameCount = 0;//количество алгов
    QString algName = "AlgName";//идентификатор
    QVector<QString> vecAlgNames;//названия алгов в массиве на всех пластинах
    QVector<QString> vecAlgNames_OneWafer;//названия алгов в массиве для одной пластины
    vecAlgNames_OneWafer.reserve(m_maxCountTestElem);
    //------------------------------------------------------------------------
    //запись названий и количества параметров
    int paramCount = 0;//количество параметров
    QString paramName = "ParName";//иденитификатор
    QVector<QString> vecParamNames;//названия параметров в массиве
    QVector<QString> vecParamNames_OneWafer;
    vecParamNames_OneWafer.reserve(m_maxCountTestElem);
    //------------------------------------------------------------------------
    QVector<int> vecID;//подсчет количества пластин
    QVector<int> vecDieCount;//подсчет количества кристаллов на пластинах
    //------------------------------------------------------------------------
    //разрешить запись данных одной пластины в память
    bool waferWritePermit = false;
    //количество кристаллов на всех пластинах
    int dieCountOneWafer = 0;
    //------------------------------------------------------------------------
    //переменные для вывода в текстовый файл (для отладки)
    int numAllValuesOneWafer = 0;
    int numValuesInLine = 0;
    //------------------------------------------------------------------------
    QFile writeFile;//объект для записи в текст. файл
    QTextStream outData;//создание выходного потокового объекта для записи в текст. файл
    QTextStream inData;//создание входного потокового объекта для чтения файла 4082

    writeFile.setFileName("Statistics of wafers.txt");
    //установка объекта записываемого файла в выходной потоковой объект
    outData.setDevice(&writeFile);
    //установка объекта читаемого файла во входной потоковой объект
    inData.setDevice(&ReadFile);
    //------------------------------------------------------------------------
    //СОЗДАНИЕ ПАРТИИ
    m_spLot = make_shared<Lot>();
    //------------------------------------------------------------------------
    //МАССИВ КРИСТАЛЛОВ
    QMultiMap<int, shared_ptr<Die>> mmap_spDies_OneWafer;
    //МАССИВ ИНФО-ТЕСТОВ
    QVector<shared_ptr<TestInfo>> vec_spTestsInfo_OneWafer;
    vec_spTestsInfo_OneWafer.reserve(m_maxCountTestElem);
    //------------------------------------------------------------------------
    //ОБЪЕКТ ПЛАСТИНЫ
    shared_ptr<Wafer> spWafer;
    //------------------------------------------------------------------------
    //разбор данных в 4082-файле
    int slotIndex = -1;
    size_t slotNum = 0;
    bool waferSlotIndexWritten = false;

    if(writeFile.open(QFile::WriteOnly | QFile::Truncate))
    {
        while (!inData.atEnd())
        {
            QString line = inData.readLine();
            //-----------------------------------------------------------------------------------
            //запись даты измерения
            if(line.contains(regDate))
            {
                RegProcess(regDate, strDate);
                strDate = "";
            }
            //-----------------------------------------------------------------------------------
            //запись номеров пластин
            if(line.contains(regWaferID))
            {
                RegProcess(regWaferID, strWaferID);//SYSWAFERID + номер пластины
                QRegExp regWaferID("[0-9]{1,2}");//номер пластины
                if(strWaferID.contains(regWaferID))
                {
                    QString strWaferID;
                    RegProcess(regWaferID, strWaferID);
                    slotNum = strWaferID.toInt();
                    slotIndex++;
                    vecID.push_back(slotNum);
                    waferSlotIndexWritten = true;
                }
                outData << "\r\n" << strWaferID << "\r\n" << "\r\n";
                strWaferID = "";
            }
            //--------------------------------------------------------------------------
            //СОЗДАНИЕ ОБЪЕКТА-ПЛАСТИНЫ
            if(waferSlotIndexWritten)
            {
                spWafer = make_shared<Wafer>(slotIndex, slotNum);
                waferSlotIndexWritten = false;
            }
            //--------------------------------------------------------------------------

            //-----------------------------------------------------------------------------------
            //запись названий и количества модулей
            if(line.contains(modName))
            {
                if(!vecModsWithDuplicates.isEmpty())
                    vecModsWithDuplicates.clear();

                QStringList modListWithDuplicates = line.split("\t");
                if(!modListWithDuplicates.isEmpty())
                {
                    modListWithDuplicates.pop_front();
                    foreach (QString str, modListWithDuplicates)
                        vecModsWithDuplicates.push_back(str);
                }
                modCountWithDuplicates = modListWithDuplicates.size();
                outData << "Modules: ";
                QVector<QString>::const_iterator cit = vecModsWithDuplicates.constBegin();
                for (;cit != vecModsWithDuplicates.constEnd(); ++cit)
                    outData << (*cit) << "\t";
                outData << "\r\n";
                outData << "Modules count: " << modCountWithDuplicates << "\r\n" << "\r\n";
            }
            //--------------------------------------------------------------------------------------
            //запись названий и количества тестовых элементов
            int testIndex = 0;
            if(line.contains(devName))
            {
                QStringList testList = line.split("\t");
                if(!testList.isEmpty())
                {
                    testList.pop_front();
                    foreach(QString testName, testList)
                    {
                        auto spTestInfo = make_shared<TestInfo>(testName, testIndex, slotIndex,
                                                                ValuePrefix::norm);
                        vec_spTestsInfo_OneWafer.push_back(spTestInfo);

                        ++testIndex;
                    }
                }
                testCount = testList.size();
                vecTestCountOneWafer.push_back(testCount);
            }
            //---------------------------------------------------------------------------------------
            //запись названий и количества алгов
            if(line.contains(algName))
            {
                QStringList algNameList = line.split("\t");
                if(!algNameList.isEmpty())
                {
                    algNameList.pop_front();
                    foreach (QString str, algNameList)
                    {
                        vecAlgNames.push_back(str);
                        vecAlgNames_OneWafer.push_back(str);
                    }
                }
                algNameCount = algNameList.size();
                outData << "Alg Names: ";
                QVector<QString>::const_iterator cit = vecAlgNames.constBegin();
                for (;cit != vecAlgNames.constEnd(); ++cit)
                    outData << (*cit) << "\t";
                outData << "\r\n";
                outData << "Alg Names count: " << algNameCount << "\r\n" << "\r\n";
            }
            //----------------------------------------------------------------------------------------
            //запись названий и количества параметров
            if(line.contains(paramName))
            {
                if(!vecParamNames.isEmpty())  vecParamNames.clear();
                QStringList paramList = line.split("\t");
                if(!paramList.isEmpty())
                {
                    paramList.pop_front();
                    foreach (QString str, paramList)
                    {
                        vecParamNames.push_back(str);
                        vecParamNames_OneWafer.push_back(str);
                    }
                }
                paramCount = paramList.size();
                outData << "Parameters: "; //<< strParams << "\r\n";
                QVector<QString>::const_iterator cit = vecParamNames.constBegin();
                for (;cit != vecParamNames.constEnd(); ++cit)
                    outData << (*cit) << "\t";
                outData << "\r\n";
                outData << "Parameters count: " << paramCount << "\r\n" << "\r\n";
            }
            //-----------------------------------------------------------------------------------------
            //ЗАПИСЬ КООРДИНАТ И ЗНАЧЕНИЙ
            //СОЗДАНИЕ ОБЪЕКТОВ-КРИСТАЛЛОВ

            //координаты кристалла
            QString strXY;
            QString strRegXY = "[0-9][,][0-9]|[-][0-9][,][0-9]|[0-9][,][-][0-9]|[-][0-9][,][-][0-9]";
            QRegExp regPos(strRegXY);

            //список строк для двух координат
            QStringList strListCoordinates;

            //значение теста
            QString strRegValue = "[+-][0-9][.][0-9]{1,10}[E][+-][0-9]{1,3}";
            QRegExp regValue(strRegValue);

            //разделитель координат
            char comma = ',';
            //поля кристалла-объекта:
            int X = 0, Y = 0;
            Mask maskState = Mask::no;
            MaskButtonState maskButtonState = MaskButtonState::unmasked;

            if(line.contains(regPos) && line.contains(regValue))
            {
                waferWritePermit = false;
                ++dieCountOneWafer;
                //количество величин в строке = 0 перед каждой новой строкой
                int NumOfValuesInLine = 0;
                int testIndex = 0;
                QStringList valueList = line.split("\t");
                double value = 0.0;
                if(!valueList.isEmpty())
                {
                    //извлечение координат из строки
                    strXY = valueList.takeFirst();
                    //разделение координат
                    strListCoordinates = strXY.split(comma);
                    //приведение координат к целому типу
                    X = strListCoordinates[0].toInt();
                    Y = strListCoordinates[1].toInt();

                    //запись значений всех тестов для одной строки
                    foreach (QString str, valueList)
                    {
                        value = str.toDouble();
                        testIndex = NumOfValuesInLine;
                        //создание объектов-кристаллов
                        auto spDie = make_shared<Die>(X, Y, value, testIndex, slotIndex,
                                                      maskState, maskButtonState);
                        mmap_spDies_OneWafer.insert(testIndex, spDie);
                        //std:
                        //mmap_spDies_OneWafer.insert({testIndex, spDie});
                        //mmap_spDies_OneWafer.insert(make_pair(testIndex, spDie));
                        ++NumOfValuesInLine;
                    }
                }

                //вывод в файл
                strXY = "";

                NumOfValuesInLine = NumOfValuesInLine;//для вывода в файл
                numAllValuesOneWafer += NumOfValuesInLine;//для вывода в файл
            }

            //-------------------------------------------------------------------------------
            //это ветвление срабатывает каждый раз после записи всех данных очередной пластины
            if((dieCountOneWafer != 0 && waferWritePermit == false
                && !line.contains(regPos) && !line.contains(regValue)) || (inData.atEnd()))
            {
                //вставка количества кристаллов на пластине в массив
                vecDieCount.push_back(dieCountOneWafer);

                dieCountOneWafer = 0;
                //для однократного срабатывания ветвления
                waferWritePermit = true;

                //вывод в файл
                //-------------------------------------------------------------------
                if(!vecDieCount.isEmpty())
                    outData << "Num of all values on this wafer: "
                            << numAllValuesOneWafer << " = "
                            << numValuesInLine * vecDieCount[0] << "\r\n\r\n";

                //для вывода в файл:
                numAllValuesOneWafer = 0;
                numValuesInLine = 0;

                //======================================================================
                //СОЗДАНИЕ И ДОБАВЛЕНИЕ ОБЪЕКТОВ-ТЕСТ.ЭЛЕМ. В ОБЪЕКТ-ПЛАСТИНУ
                //к этому моменту записаны данные одной пластины
                int testIndex = 0;
                auto it_testName = vec_spTestsInfo_OneWafer.begin();
                auto it_paramName = vecParamNames_OneWafer.begin();
                auto it_algName = vecAlgNames_OneWafer.begin();
                auto it_modName = vecModsWithDuplicates.begin();

                QString testName{}, paramName{}, algName{}, modName{};
                while(!mmap_spDies_OneWafer.isEmpty())
                {
                    testName = it_testName->get()->getTestName();
                    paramName = *it_paramName;
                    algName = *it_algName;
                    modName = *it_modName;
                    //-----------------------------------------------------------------------------
                    //ЧАСТО ИЗМЕНЯЕМЫЙ КОД (из-за изменения testName и modName)
                    //удаление запрещенных символов, не записываемых в базу данных
                    QString prohibit("[~!@#$%^&*()\'\"-+?<>=]");
                    QRegExp regProhibit(prohibit);
                    QStringList listTestName{};
                    if(testName.contains(regProhibit))
                    {
                        listTestName = testName.split(regProhibit);
                        testName = listTestName.join("");
                    }
                    QStringList listModName{};
                    if(modName.contains(regProhibit))
                    {
                        listModName = modName.split(regProhibit);
                        modName = listModName.join("");
                    }
                    //подгонка под новые правила
                    QString initTestName = testName;
                    if(testName.contains("_") && testName != modName)
                        testName = modName + "_" + testName;
                    QString transistors = "[A-Z]{1,1}[n-p]{1,1}";
                    QRegExp regTr(transistors);
                    if(modName.contains(regTr)) testName = modName + "_" + initTestName;
                    //если testName == modName после удаления '_'
                    //QString _testName = testName;
                    QString newTestName{};
                    for(QChar ch : testName)
                    { if(ch != '_') newTestName.push_back(ch); }
                    size_t length = newTestName.size();
                    QString leftName = newTestName.left(length/2);
                    QString rightName = newTestName.right(length/2);
                    if(leftName == rightName)
                        testName = initTestName;
                    //-----------------------------------------------------------------------------
                    //создание объекта тестового элемента
                    shared_ptr<TestElem> spTestElem =
                            make_shared<TestElem>(testIndex, testName, paramName,
                                                  algName, ValuePrefix::norm);

                    //ключ мультикарты - индекс теста
                    auto it_die = mmap_spDies_OneWafer.find(testIndex);
                    while(it_die != mmap_spDies_OneWafer.end() && it_die.key() == testIndex)
                    {
                        shared_ptr<Die> spDie = it_die.value();
                        size_t slotIndex = spDie->getSlotIndex();
                        //добавление кристаллов в тестовый элемент
                        if(spTestElem)
                        {
                            spTestElem->addDie(spDie);
                            spTestElem->setSlotIndex(slotIndex);
                        }
                        ++it_die;
                    }
                    mmap_spDies_OneWafer.remove(testIndex);
                    if(spWafer)
                        spWafer->addTestElem(spTestElem, testIndex);

                    ++testIndex;
                    ++it_testName;
                    ++it_paramName;
                    ++it_algName;
                    ++it_modName;
                }

                if(!mmap_spDies_OneWafer.empty())  mmap_spDies_OneWafer.clear();

                int testCount{};
                if(spWafer)
                    testCount = spWafer->getTestElemCount();
                //--------------------------------------------------------------------
                //добавление объекта-пластины в объект-партию
                if(spWafer)
                    m_spLot->addWafer(spWafer, slotNum, slotIndex, testCount);
                //--------------------------------------------------------------------
                //удаление объектов-инфотестов
                vec_spTestsInfo_OneWafer.clear();
                //очистка массивов параметров и алгов
                vecParamNames_OneWafer.clear();
                vecAlgNames_OneWafer.clear();
                //======================================================================
            }
            //-----------------------------------------------------------------------------------

        }
        //end of while
    }
    //end of if

    //------------------------------------------------------------------------------
    //запись для проверок:
    //запись количества кристаллов на каждой пластине
    outData << "\r\n" << "Dies quantity on " << "\r\n";
    if(vecID.size() == vecDieCount.size())
    {
        QVector<int>::const_iterator cit1 = vecID.constBegin();
        QVector<int>::const_iterator cit2 = vecDieCount.constBegin();
        for(;cit1 != vecID.constEnd() && cit2 != vecDieCount.constEnd(); ++cit1, ++cit2)
            outData << "wafer " << *cit1 << ": " << *cit2 << "\r\n";
    }
    //------------------------------------------------------------------------------
    int elem = 0;
    outData << "\r\n" << "testCountOneWafer element: " << elem << ", "
            << vecTestCountOneWafer[elem] << "\r\n";
    int selectWafer = 0;
    outData << "\r\n" << "Num values on wafer " << selectWafer << ": "
            << vecTestCountOneWafer[selectWafer] * vecDieCount[selectWafer] << "\r\n";
    //------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------
void FileReader4082::RegProcess(QRegExp& regInput, QString& strReg) const
{
    QStringList list1 = regInput.capturedTexts();
    foreach (QString str, list1) strReg = str;
}
shared_ptr<Lot> FileReader4082::getLot() const{ return m_spLot; }
//------------------------------------------------------------------------------------
