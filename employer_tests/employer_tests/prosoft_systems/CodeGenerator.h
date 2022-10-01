#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <string>
#include <iostream>

//2. Есть класс CodeGenerator, который умеет генерить код на разных языках.
// Предложите рефакторинг с учетом, что количество языков будет расширяться

class CodeGenerator
{
public:
    enum Lang {JAVA, C_PLUS_PLUS, PHP};
    CodeGenerator(Lang language) { _language = language; }
    std::string generateCode()
    {
        std::string code;
        switch(_language) {
        case JAVA: break;       //return generated java code
        case C_PLUS_PLUS:
        {
            code += someCodeRelatedThing();
            code += someCodeRelatedThing();
            break;    //return generated C++ code
        }
        case PHP: break;        //return generated PHP code
        default:
            throw new std::logic_error("Bad language");
        }
        return code;
    }
    std::string someCodeRelatedThing() // used in generateCode()
    {
        std::string someCode;
        switch(_language) {
        case JAVA: break;        //return generated java-related stuff
        case C_PLUS_PLUS:
        {
            someCode = "class Cpp{};";
            break; //return generated C++-related stuff
        }
        case PHP: break;         //return generated PHP-related stuff
        default:
            throw new std::logic_error("Bad language");
        }
        return someCode;
    }

private:
    Lang _language;
};

class AbstractGenerator
{
public:
    virtual std::string someCodeRelatedThing() = 0;
    virtual ~AbstractGenerator() = default;
};

class CppGenerator : public AbstractGenerator
{
public:
    CppGenerator() { std::cout << "CppGenerator()" << std::endl; }
    ~CppGenerator(){ std::cout << "~CppGenerator()" << std::endl; }
    std::string someCodeRelatedThing() override
    {
        // C++ related code
        return std::string("Cpp code");
    }
};

class JavaGenerator : public AbstractGenerator
{
public:
    JavaGenerator() { std::cout << "JavaGenerator()" << std::endl; }
    ~JavaGenerator() { std::cout << "~JavaGenerator()" << std::endl; }
    std::string someCodeRelatedThing() override
    {
        // Java related code
        return std::string("Java code");
    }
};

class PhpGenerator : public AbstractGenerator
{
public:
    PhpGenerator() { std::cout << "PhpGenerator()" << std::endl; }
    ~PhpGenerator() { std::cout << "~PhpGenerator()" << std::endl; }
    std::string someCodeRelatedThing() override
    {
        // PHP related code
        return std::string("Php code");
    }
};

class NewCodeGenerator
{
public:
    enum Lang {JAVA, C_PLUS_PLUS, PHP};
    NewCodeGenerator(Lang language)
    {
        switch(language) {
        case JAVA:
            _generator = std::make_unique<JavaGenerator>();
            break;
        case C_PLUS_PLUS:
            _generator = std::make_unique<CppGenerator>();
            break;
        case PHP:
            _generator = std::make_unique<PhpGenerator>();
            break;
        default:
            throw new std::logic_error("Bad language");
        }
    }
    std::string generateCode()
    {
        std::string someCode = _generator->someCodeRelatedThing();
        return someCode;
    }
private:
    std::unique_ptr<AbstractGenerator> _generator;
};

#endif // CODEGENERATOR_H
