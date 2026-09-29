#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

void printHelp(const std::string& progName) {
    std::cout << "Использование: " << progName << " -o <операция> <операнд1> <операнд2> ... <операндN>\n";
    std::cout << "\nОперации:\n";
    std::cout << "  multiply  - умножение всех операндов (от 3 до 5 операндов)\n";
    std::cout << "  divide    - деление первого операнда на все остальные (от 3 до 5 операндов)\n";
    std::cout << "\nПримеры:\n";
    std::cout << "  " << progName << " -o multiply 2 3 4\n";
    std::cout << "  " << progName << " --operation divide 100 2 5\n";
    std::cout << "\nБез параметров выводится эта справка.\n";
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printHelp(argv[0]);
        return 0;
    }

    std::string operation;
    std::vector<double> operands;
    bool operationFound = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-o" || arg == "--operation") {
            if (i + 1 >= argc) {
                std::cerr << "Ошибка: после " << arg << " не указана операция.\n";
                printHelp(argv[0]);
                return 1;
            }
            operation = argv[++i];
            operationFound = true;
        } else if (arg == "-h" || arg == "--help") {
            printHelp(argv[0]);
            return 0;
        } else {
            try {
                size_t pos;
                double value = std::stod(arg, &pos);
                if (pos != arg.size()) throw std::invalid_argument("bad");
                operands.push_back(value);
            } catch (...) {
                std::cerr << "Ошибка: '" << arg << "' не является числом.\n";
                return 1;
            }
        }
    }

    if (!operationFound) {
        std::cerr << "Ошибка: не задана операция. Используйте -o или --operation.\n";
        printHelp(argv[0]);
        return 1;
    }

    if (operands.size() < 3 || operands.size() > 5) {
        std::cerr << "Ошибка: количество операндов должно быть от 3 до 5. Получено: "
                  << operands.size() << "\n";
        printHelp(argv[0]);
        return 1;
    }

    double result = 0.0;

    if (operation == "multiply") {
        result = operands[0];
        for (size_t i = 1; i < operands.size(); ++i) {
            result *= operands[i];
        }
        std::cout << result << std::endl;
    } else if (operation == "divide") {
        result = operands[0];
        for (size_t i = 1; i < operands.size(); ++i) {
            if (operands[i] == 0.0) {
                std::cerr << "Ошибка: деление на ноль (операнд №" << i + 1 << ").\n";
                return 1;
            }
            result /= operands[i];
        }
        std::cout << result << std::endl;
    } else {
        std::cerr << "Ошибка: неизвестная операция '" << operation << "'.\n";
        std::cerr << "Доступные операции: multiply, divide.\n";
        return 1;
    }

    return 0;
}
