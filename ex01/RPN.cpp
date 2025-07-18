#include "RPN.hpp"


int isOPerator(std::string line)
{
    if (line == "+" || line == "-" || line == "/" || line == "*")
        return 1;
    return 0;
}

int Pars(std::string a)
{
    if (a.size() > 1)
       return 0;
    else if (!std::isdigit(a[0]) && !isOPerator(a))
        return 0;
    return 1;
}

int RPN::algo(char **av)
{
    std::string token;
    std::string a(av[1]);
    std::istringstream ss(a);

    while (ss >> token)
    {
        if (!Pars(token) && token != "0")
        {
            std::cout << "Error\n";
            return 1;
        }
        int nb = std::atoi(token.c_str());
        if (nb || token == "0")
        {
            if (nb < 0 || nb > 9)
            {
                std::cout << "Error\n";
                return 1;
            }
            this->stack.push(nb);
            continue;
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
                continue;
            }
            else 
            {
                std::cout << "Error\n";
                return 1;
            }
        }
        else 
        {
            return 1;
        }
    }
    // std::cout << stack.size() << std::endl;
    // for(size_t i = 0; i < stack.size(); i++)
    // {  
    //     std::cout << stack.top() << std::endl;
    //     stack.pop();
    // }
    std::cout << stack.top() << std::endl;
    return 0;
}
