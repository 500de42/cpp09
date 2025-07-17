#include "RPN.hpp"


int isOPerator(std::string line)
{
    if (line == "+" || line == "-" || line == "/" || line == "*")
        return 1;
    return 0;
}

int Pars(std::string a)
{
    if (std::isdigit(a) && !isOPerator(a))
        return 0;
    return 1;
}

int RPN::parsing(const char **av)
{
    std::string token;
    std::string a(av[1]);
    std::istringstream ss(a);

    while (ss >> token)
    {
        if (!Pars(token))
        {
            std::cout << "error\n";
            return 1;
        }
        int nb = std::isdigit(std::atoi(token.c_str()));
        if (nb || token == "0")
        {
            if (nb < 0 || nb > 9)
            {
                std::cout << "error\n";
                return 1;
            }
            this->stack.push(nb);
        }
        else if (isOPerator(token))
        {
            if (this->stack.size() >= 2)
            {
                int a = stack.top(); stack.pop();
                int b = stack.top(); stack.pop();
                int nb1;
                if (token == "+")
                    nb1 = b + a;
                else if (token == "-")
                    nb1 = b - a;
                else if (token == "/")
                    nb1 = b / a;
                else if (token == "*")
                    nb1 = b * a;
                this->stack.push(nb1);
            }
        }
        else 
        {
            std::cout << "error\n";
            return 1;
        }
    }
}
