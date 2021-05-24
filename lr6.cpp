#include <Windows.h>
#include <iostream>

using namespace std;

template <class T>
class Array
{
public:
	Array(int m_countRow, int m_countColumn);
	~Array();

	void sortColumn(int index);
	bool checkSortRow(int Row);
	bool checkSortColumn(int column);

	int getSizeRow() { return m_countRow; }
	int getSizeColumn() { return m_countColumn; }

	template <typename T1> friend ostream& operator<<(ostream& out, const Array<T1>& arr);
	T& operator()(const T row, const T column)
	{
		return elements[row][column];
	}

	const T& operator()(const T row, const T column)const
	{
		return elements[row][column];
	}
private:
	int m_countRow;
	int m_countColumn;
	T** elements;
};


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int row, column;
	cout << "Введіть розмір матриці (рядок/стовпець через пробіл): "; cin >> row >> column;
	Array<int> arr(row, column);

	int answer = -1;
	do
	{
		cout << "1. Заповнити масив випадковими числами. " << endl;
		cout << "2. Перевірити рядок на відсортованність. " << endl;
		cout << "3. Перевірити стовпець на відсортованність. " << endl;
		cout << "4. Відсортувати матрицю за стовпцем. " << endl;
		cout << "5. Вивести матрицю. " << endl;
		cout << "0. Вихід. " << endl;
		cout << "Введіть дію: "; cin >> answer;
		switch (answer)
		{
		case 1:
		{
			for (int i = 0; i < arr.getSizeRow(); i++)
			{
				for (int j = 0; j < arr.getSizeColumn(); j++)
				{
					arr(i, j) = rand() % 21;
				}
			}
		} break;

		case 2:
		{
			int i;
			cout << "Введіть рядок, який потрібно перевірити: "; cin >> i;
			if (arr.checkSortRow(i)) cout << "Рядок відстортованний! " << endl;
			else  cout << "Рядок не відстортованний! " << endl;
		} break;
		case 3:
		{
			int i;
			cout << "Введіть стовпець, який потрібно перевірити: "; cin >> i;
			i--;
			if (arr.checkSortColumn(i)) cout << "Стовпець відстортованний! " << endl;
			else  cout << "Стовпець не відстортованний! " << endl;
		} break;
		case 4:
		{
			int i;
			cout << "Введіть стовпець, за яким потрібно відсортувати: "; cin >> i;
			i--;
			arr.sortColumn(i);
		} break;

		case 5: cout << arr << endl; break;
		default:
			break;
		}
	} while (answer);

	cout << arr << endl;

	arr.sortColumn(6);
	cout << arr;
	return 0;
}


template <class T>
Array<T>::Array(int m_countRow, int m_countColumn) : m_countRow(m_countRow), m_countColumn(m_countColumn), elements{ new T * [m_countRow] }
{
	for (int i = 0; i < m_countRow; i++)
	{
		elements[i] = new T[m_countColumn];
	}
}

template<class T>
Array<T>::~Array()
{
	for (int i = 0; i < m_countRow; i++)
	{
		delete[] elements[i];
	}
	delete[] elements;
}

template<class T>
void Array<T>::sortColumn(int index)
{
	for (int i = 0; i < m_countRow; i++)
	{
		for (int j = i; j < m_countRow; j++)
		{
			if (elements[i][index] > elements[j][index])
			{
				T* temp = elements[i];
				elements[i] = elements[j];
				elements[j] = temp;
			}
		}
	}
}

template<class T>
bool Array<T>::checkSortRow(int Row)
{
	bool sortInc = true;
	bool sortDec = true;
	for (int i = 0; i < m_countColumn - 1; i++)
	{
		if (elements[Row][i] > elements[Row][i + 1])
		{
			sortDec = false;
		}
		else if (elements[Row][i] < elements[Row][i + 1])
		{
			sortInc = false;
		}
	}

	return (sortInc || sortDec);
}

template<class T>
bool Array<T>::checkSortColumn(int column)
{
	bool sortInc = true;
	bool sortDec = true;
	for (int i = 0; i < m_countRow - 1; i++)
	{
		if (elements[i][column] > elements[i + 1][column])
		{
			sortDec = false;
		}
		else if (elements[i][column] < elements[i + 1][column])
		{
			sortInc = false;
		}
	}

	return (sortInc || sortDec);
}



template<class T>
ostream& operator<<(ostream& out, const Array<T>& arr)
{
	for (int i = 0; i < arr.m_countRow; i++)
	{
		for (int j = 0; j < arr.m_countColumn; j++)
		{
			out << arr(i, j) << " ";
		}
		out << endl;
	}

	return out;
}
