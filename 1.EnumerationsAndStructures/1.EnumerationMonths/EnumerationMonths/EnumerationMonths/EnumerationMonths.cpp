#include <iostream>


enum class months
{
	Exit,
	January,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	
	months month = months::January;
	int mnth = static_cast<int>(month);

	while (mnth != 0)
	{
		std::cout << "Введите номер месяца от 1 до 12 или 0 для выхода" << std::endl;
		std::cin >> mnth;
		if (mnth < 0 || mnth > 12)
		{
			std::cout << "Введён некорректный номер месяца!!! " << std::endl;
		}
		months month = static_cast<months> (mnth);
		switch (month)
		{
			case (months::Exit): std::cout << "Выход" << std::endl; break;
			case (months::January): std::cout << "Ваш месяц Январь " << std::endl; break;
			case (months::February): std::cout << "Ваш месяц Февраль " << std::endl; break;
			case (months::March): std::cout << "Ваш месяц Март " << std::endl; break;
			case (months::April): std::cout << "Ваш месяц Апрель " << std::endl; break;
			case (months::May): std::cout << "Ваш месяц Май " << std::endl; break;
			case (months::June): std::cout << "Ваш месяц Июнь " << std::endl; break;
			case (months::July): std::cout << "Ваш месяц Июль " << std::endl; break;
			case (months::August): std::cout << "Ваш месяц Август " << std::endl; break;
			case (months::September): std::cout << "Ваш месяц Сентябрь " << std::endl; break;
			case (months::October): std::cout << "Ваш месяц Октябрь " << std::endl; break;
			case (months::November): std::cout << "Ваш месяц Ноябрь " << std::endl; break;
			case (months::December): std::cout << "Ваш месяц Декабрь " << std::endl; break;
		}	
	}
	return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
