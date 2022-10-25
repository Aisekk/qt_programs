#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Document
{
    vector<string> data;
public:
    Document()
    {
        data.reserve(100); // at least for 100 lines
    }

    void Insert(int line, const string & str)
    {
        if (line <= data.size())
            data.insert(data.begin() + line, str);
        else
            cout << "Error!" << endl;
    }

    void Remove(int line)
    {
        if( !(line>data.size()) )
            data.erase(data.begin() + line);
        else
            cout << "Error!" << endl;
    }

    string& operator [] (int x)
    {
        return data[x];
    }

    void Show()
    {
        for(int i = 0; i < data.size(); ++i)
        {
            cout << i + 1 << ". " << data[i] << endl;
        }
    }
};

class Command
{
protected:
    Document * _doc;
public:
    virtual ~Command() {}
    virtual void Execute() = 0;
    virtual void unExecute() = 0;

    void setDocument(Document* doc)
    {
        _doc = doc;
    }
};

class InsertCommand : public Command
{
    int _line;
    string _str;
public:
    InsertCommand(int line, const string& str): _line(line), _str(str) {}

    void Execute()
    {
        _doc->Insert(_line, _str);
    }

    void unExecute()
    {
        _doc->Remove(_line);
    }
};

class Invoker
{
    vector<Command*> _doneCommands;
    Document _doc;
    Command* _command;
public:
    void Insert( int line, string str )
    {
        _command = new InsertCommand( line, str );
        _command->setDocument(&_doc);
        _command->Execute();
        _doneCommands.push_back(_command);
    }

    void Undo()
    {
        if(_doneCommands.size() == 0)
        {
            cout << "There is nothing to undo!" << endl;
        }
        else
        {
            _command = _doneCommands.back();
            _doneCommands.pop_back();
            _command->unExecute();
            // Don't forget to delete command!!!
            delete _command;
        }
    }

    void Show()
    {
        _doc.Show();
    }
};

int main()
{
    char s = '1';
    int line = 10;
    int line_b = 10;
    string str;
    Invoker inv;
    while( s!= 'e' )
    {
        cout << "What to do: \n1.Add a line\n2.Undo last command" << endl;
        cin >> s;
        switch( s )
        {
        case '1':
            cout << "What line to insert: ";
            cin >> line;
            --line;
            cout << "What to insert: ";
            cin >> str;
            inv.Insert( line, str );
            break;
        case '2':
            inv.Undo();
            break;
        }
        cout << "$$$DOCUMENT$$$" << endl;
        inv.Show();
        cout << "$$$DOCUMENT$$$" << endl;
    }
}
