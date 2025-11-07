#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Cover {
	string art;
	string text;
public:
	Cover(string a, string t):art(a),text(t){}
};

class Author {
	string Aname;
public:
	Author(string name) : Aname(name){}
	string getName() const{
		return Aname;
	}
	friend ostream& operator<<(ostream& cout,const Author& au);
};
ostream& operator<<(ostream& cout,const Author& au) {
	cout << au.Aname;
	return cout;
};
vector<Author> Katalog;

class Book {
	string name;
	Author* pauthor;
	int ISBN;
	int year;
	Cover* pcover;
public:
	Book(string n, int I):name(n),ISBN(I) {
		pcover = new Cover("inf art", "inf text");
		year = rand() % 2000 + 1;
	}
	int getYear() const {
		return year;
	};
	string getName() const {
		return name;
	}
	void setAuthor() {
		pauthor = &Katalog[rand() % Katalog.size()];
	}
	Author* getAuthor() {
		return pauthor;
	}
};

class Library {
	vector<Book> Lib;
public:
	void addBook(Book& newbook) {
		Lib.push_back(newbook);
	}
	void printAllBooks() {
		for (auto& elem : Lib) {
			cout << "Название: " << elem.getName()
				<< ", Год: " << elem.getYear();
			if (elem.getAuthor() != nullptr) {
				cout << ", Автор: " << elem.getAuthor()->getName();
			}
			cout << endl;
		}
	}
	void findByAuthor(const string& authorName) {
		for (auto& elem : Lib) {
			if (elem.getAuthor() != nullptr &&
				elem.getAuthor()->getName() == authorName) {
				cout << "Найдено: " << elem.getName()
					<< " (" << elem.getYear() << ")" << endl;
			}
		}
	}
	void findByYear(int year) {
		for (auto& elem : Lib) {
			if (elem.getYear() == year) {
				cout << "Найдено: " << elem.getName();
				if (elem.getAuthor() != nullptr) {
					cout << " by " << elem.getAuthor()->getName();
				}
				cout << endl;
			}
		}
	}
};

void Menu() {
	cout << "1. Вывести все книги библиотеки" << endl;
	cout << "2. Найти по автору" << endl;
	cout << "3. Найти по году" << endl;
	cout << "4. Выйти" << endl;
};

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(0));

	Katalog.push_back(Author("Толстой"));
	Katalog.push_back(Author("Достоевский"));
	Katalog.push_back(Author("Пушкин"));

	Library library;

	Book book1("Война и мир", 111111);
	book1.setAuthor();
	library.addBook(book1);

	Book book2("Преступление и наказание", 222222);
	book2.setAuthor();
	library.addBook(book2);

	Book book3("Евгений Онегин", 333333);
	book3.setAuthor();
	library.addBook(book3);

	int choice;
	do {
		Menu();
		cout << "Выберите пункт: ";
		cin >> choice;

		switch (choice) {
		case 1:
			library.printAllBooks();
			break;
		case 2: {
			string author;
			cout << "Введите имя автора: ";
			cin.ignore();
			getline(cin, author);
			library.findByAuthor(author);
			break;
		}
		case 3: {
			int year;
			cout << "Введите год: ";
			cin >> year;
			library.findByYear(year);
			break;
		}
		case 4:
			cout << "Выход..." << endl;
			break;
		default:
			cout << "Неверный выбор!" << endl;
		}
	} while (choice != 4);

	return 0;
}

