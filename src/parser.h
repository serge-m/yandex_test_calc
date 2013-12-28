#ifndef parser_h__
#define parser_h__

#include <string>
#include <vector>


/// Класс для вычисления выражения
/// Работает только с целыми числами
/// унарный минус не поддерживается
/// Обработка ошибок не полная
/// Главная функция - Parse
/// Оптимизация по скорости/памяти не делалась
/// Обработка проводится в 2 этапа: 1) создается польская обратная запись выражения
/// 2) вычисляется варажение
/// Выражение не должно содержать ничего кроме +-*/, скобок и цифр
/// При желании можно достаточно легко добавить произвольные функции
/// В коде куча ненужных копироавний строк и других операций, которые для быстродействия нужно бы переписать
/// Но в качестве черновика - сойдет
class Parser
{
public:
    Parser();
    virtual ~Parser();
    double Parse( const std::string & s );

private:
    typedef std::string StackElement;
    typedef std::vector<StackElement> Stack;
    typedef std::vector<double> StackForCalculations;

    /// Признак конца строки
    static const std::string eol;
    

    /// Функция для преобразования в польскую инверсную запись
    void CreateReversePolishNotation( std::string s );
    /// Функция для вычисления результата выражения, заданного в польской инверсной записи
    double CalcExpression( Stack st );

    bool IsPositiveInteger(const std::string& s);

    /// приоритет операций
    int Priority( std::string s );
    bool IsOperation( std::string s );

    /// Читаем операцию, скобку или число
    /// числа хранятся в виде строк вплоть до вычисления
    StackElement GetPiece( const std::string & s );
    typedef enum
    {
        CLASS_ALPHA,
        CLASS_NUM,
        CLASS_OPERATION,
        CLASS_SPACE,
        CLASS_UNKNOWN,
    } SymbolClass;
    SymbolClass GetSymbolClass( char symbol );
   
   
    double CalcOperation( StackElement op, StackForCalculations & s );
   
    double GetNumberFromStack( StackForCalculations & s );
    double GetNumberFromString( StackElement se );
private:
    int pos_; /// позиция в исходной строке при разборе /// TODO: сделать локальной переменной
    Stack stackPostfix_; /// Стек для обратной польской записи
    Stack stackOperations_; /// Стек операци. TODO: тоже сделать локальным
};

#endif // parser_h__
