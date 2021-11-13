#include <iostream>
#include <array>

#pragma once
class classes
{
	class Numbers
	{
	public:
		int m_value;
		int m_bombCount = 0;
		bool m_openly = 0;
		bool m_cursored = 0;
		bool m_flaged = 0;

		friend std::ostream& operator<< (std::ostream& out, const Numbers& number);
	};

	/*
	std::ostream& operator<< (std::ostream& out, const Numbers& number)
	{
		out << number.m_value;

		return out;
	}
	*/

	class Array
	{
	public:
		int m_diff = diff;
		m_size = 10;
		//std::array <std::array <Numbers, size>, 10> m_massiv{ 0 };
		int m_massiv[size][size];

		Array() {};

		int getValue(int x, int y)
		{
			return m_massiv[x][y].m_value;
		};

		bool getOpenly(int x, int y)
		{
			return m_massiv[x][y].m_openly;
		};

		int getBombCount(int x, int y)
		{
			return m_massiv[x][y].m_bombCount;
		};

		void setValueToMassiv(int x, int y, int value)
		{
			m_massiv[x][y].m_value = value;
		};

		void setOpenly(int x, int y)
		{
			m_massiv[x][y].m_openly++;
		};

		int randomNumber()
		{
			return rand() % 100;
		};

		void fillField()
		{
			for (int countY = 0; countY <= 9; countY++)
				for (int countX = 0; countX <= 9; countX++)
				{
					setValueToMassiv(countX, countY, randomNumber());

					if (m_massiv[countX][countY].m_value < diff)
					{
						//распределение цифр вокруг бомб
						m_massiv[countX][countY].m_bombCount = 10;
						if (countX > 0 && countY > 0)
							m_massiv[countX - 1][countY - 1].m_bombCount++;
						if (countY > 0)
							m_massiv[countX][countY - 1].m_bombCount++;
						if (countX < 9 && countY > 0)
							m_massiv[countX + 1][countY - 1].m_bombCount++;
						if (countX > 0)
							m_massiv[countX - 1][countY].m_bombCount++;
						if (countX < 9)
							m_massiv[countX + 1][countY].m_bombCount++;
						if (countX > 0 && countY < 9)
							m_massiv[countX - 1][countY + 1].m_bombCount++;
						if (countY < 9)
							m_massiv[countX][countY + 1].m_bombCount++;
						if (countX < 9 && countY < 9)
							m_massiv[countX + 1][countY + 1].m_bombCount++;

					}
				}
		}

		void printField()
		{
			for (int countY = 0; countY <= 9; countY++)
			{
				for (int countX = 0; countX <= 9; countX++)
				{
					std::cout << m_massiv[countX][countY] << '\t';
				}
				std::cout << std::endl;
			}

			std::cout << std::endl;
		}

		void printBombCounts()
		{
			for (int countY = 0; countY <= 9; countY++)
			{
				for (int countX = 0; countX <= 9; countX++)
				{
					std::cout << m_massiv[countX][countY].m_bombCount << '\t';
				}
				std::cout << std::endl;
			}
		}
	};
};

