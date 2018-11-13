#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <functional> //for negation
using namespace std;

int* generate_clauses(int nbvar)
{	//generate a random set of values 
	int* arr = new int[nbvar];
	int negative = 0;
	for (int i = 0; i < nbvar; i++)
	{
		arr[i] = i + 1;
		negative = rand() % 2;
		if (negative == 0)
		{
			arr[i] = arr[i] * (-1);
		}
		cout << arr[i];
	}
	cout << endl;
	return arr;
}

int* check_clause(int** arr, int nbvar, int nbclause)
{
	int* random = generate_clauses(nbvar);
	int* clause_checker = new int[nbclause];

	//compare each individual clause and then recursively check the next clause
	//arr will hold the clauses

	for (int i = 0; i < nbclause; i++)
	{
		for (int j = 0; j < nbvar; j++)
		{
			if (arr[i][j] == random[j])
			{
				clause_checker[i] = 1;
				break;
			}
			else
			{
				if (clause_checker[i] == 1)
				{}
				else
				{
 					clause_checker[i] = 0;
				}
			}
		}
	}

	int sum = 0;
	for (int i = 0; i < nbclause; i++)
	{
		sum += clause_checker[i];
	}

	if (sum == nbclause)
	{
		return random;
	}
	else
	{
		delete[] clause_checker;
		delete[] random;
		return check_clause(arr, nbvar, nbclause);
	}
}

int main()
{
	ifstream dimac("DIMAC.txt");
	
	string p; //ignore variable
	string cnf;
	int nbvar = 0;
	int nbclauses = 0;

	while (p != "p")
	{
		dimac >> p;
		if (p[0] == 'c')
		{
			getline(dimac, p);
			/*cout << "comment line" << endl;
			cout << p << endl;*/
		}
		else
		{
			dimac >> cnf;
			//cout << p << " " << cnf << endl;
		}
	}

	dimac >> nbvar;
	dimac >> nbclauses;	

	cout << nbvar << endl;
	cout << nbclauses << endl;

	//in order to grab the necessary clauses from dimac file
	int** variables = new int*[nbclauses];
	for (int i = 0; i < nbvar; i++)
	{
		variables[i] = new int[nbvar];
		for (int j = 0; j < nbvar; j++) //initialize variables beforehand
		{
			variables[i][j] = NULL;
		}
	}
	
	//storing values into clause array
	int temp = 0;
	for (int i = 0; i < nbclauses; i++)
	{
		for (int j = 0; j < nbvar; j++)
		{
			dimac >> variables[i][j];
			if (abs(variables[i][j]) != j + 1)
			{
				if (variables[i][j] == 0)
				{
					variables[i][j] = NULL;
					break;
				}
				if (variables[i][j] < 0)
				{
					dimac.seekg(-2, dimac.cur);
					variables[i][j] = NULL;
				}
				else
				{
					dimac.seekg(-1, dimac.cur);
					variables[i][j] = NULL;
				}
			}
			if (j == nbvar-1)
			{
				getline(dimac, p);
			}
		}
		if (dimac.peek() == '\n' || dimac.peek() == 0 || dimac.peek() == '0')
		{
			getline(dimac, p);
		}
	}

	int* solution = check_clause(variables, nbvar, nbclauses);
	for (int i = 0; i < nbvar; i++)
	{
		cout << solution[i];
	}
	cout << endl << "Please press any key and then enter ";
	int x; std::cin >> x;
	dimac.close();
	return 0;
}
