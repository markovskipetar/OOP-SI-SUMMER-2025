#include <iostream>

class Expression
{
public:
    virtual double evaluate() const = 0;
    virtual ~Expression() {}
};

class Constant : public Expression
{
private:
    double value;
public:
    Constant(double value) : value(value) {}

    double evaluate() const
    {
        return value;
    }
};

class Negated : public Expression
{
private:
    const Expression* expression;
public:
    Negated(const Expression* expression) : expression(expression) {}

    double evaluate() const
    {
        return -(expression->evaluate());
    }
};

class Exponent : public Expression
{
private:
    const Expression* expression;
    int exponent;
public:
    Exponent(const Expression* expression, int exponent) : expression(expression), exponent(exponent) {}
    double evaluate() const
    {
        return std::pow(expression->evaluate(), exponent);
    }
};

class BinaryOperation : public Expression {
protected:
    const Expression* left;
    const Expression* right;
public:
    BinaryOperation(const Expression* left, const Expression* right) : left(left), right(right) {}
};

class Addition : public BinaryOperation
{
public:
    Addition(const Expression* left, const Expression* right) : BinaryOperation(left, right) {}

    double evaluate() const
    {
        return left->evaluate() + right->evaluate();
    }
};

class Multiplication : public BinaryOperation
{
public:
    Multiplication(const Expression* left, const Expression* right) : BinaryOperation(left, right) {}

    double evaluate() const
    {
        return left->evaluate() * right->evaluate();
    }
};

int main()
{
    Expression* two = new Constant(2);
    Expression* four = new Constant(4);
    Expression* one = new Constant(1);
    Expression* negOne = new Negated(one);
    Expression* sumTwoFour = new Addition(two, four);
    Expression* mult = new Multiplication(sumTwoFour, negOne);
    Expression* exp = new Exponent(mult, 2);
    Expression* res = new Addition(exp, one);

    std::cout << res->evaluate() << "\n";

    delete one;
    delete two;
    delete four;
    delete negOne;
    delete sumTwoFour;
    delete mult;
    delete exp;
    delete res;
}