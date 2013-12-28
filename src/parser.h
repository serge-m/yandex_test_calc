#ifndef parser_h__
#define parser_h__

#include <string>
#include <vector>


/// ����� ��� ���������� ���������
/// �������� ������ � ������ �������
/// ������� ����� �� ��������������
/// ��������� ������ �� ������
/// ������� ������� - Parse
/// ����������� �� ��������/������ �� ��������
/// ��������� ���������� � 2 �����: 1) ��������� �������� �������� ������ ���������
/// 2) ����������� ���������
/// ��������� �� ������ ��������� ������ ����� +-*/, ������ � ����
/// ��� ������� ����� ���������� ����� �������� ������������ �������
/// � ���� ���� �������� ����������� ����� � ������ ��������, ������� ��� �������������� ����� �� ����������
/// �� � �������� ��������� - ������
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

    /// ������� ����� ������
    static const std::string eol;
    

    /// ������� ��� �������������� � �������� ��������� ������
    void CreateReversePolishNotation( std::string s );
    /// ������� ��� ���������� ���������� ���������, ��������� � �������� ��������� ������
    double CalcExpression( Stack st );

    bool IsPositiveInteger(const std::string& s);

    /// ��������� ��������
    int Priority( std::string s );
    bool IsOperation( std::string s );

    /// ������ ��������, ������ ��� �����
    /// ����� �������� � ���� ����� ������ �� ����������
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
    int pos_; /// ������� � �������� ������ ��� ������� /// TODO: ������� ��������� ����������
    Stack stackPostfix_; /// ���� ��� �������� �������� ������
    Stack stackOperations_; /// ���� �������. TODO: ���� ������� ���������
};

#endif // parser_h__
