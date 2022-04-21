#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

void PrintTree(double **roots, int i, int j, int space_needed);
void PrintTree2(double **roots, int i, int j, int space_needed, ofstream& outfile);

int main() {
	ifstream infile;
	infile.open("input.txt");

	if (!infile) { cout << "Error: The file could not be opened\n"; }
	else { cout << "File opened successfully\n"; }

	int size; infile >> size;
	int probability;

	vector<int> p;
	p.push_back(0);
	for (int i = 0; i < size; i++) {
		infile >> probability; p.push_back(probability);
	}

	int rowCount = size + 2;
	int colCount = size + 1;

	double** S = new double*[rowCount];
	for (int i = 0; i < rowCount; i++) {
		S[i] = new double[colCount];
	}
	double** R = new double*[rowCount];
	for (int i = 0; i < rowCount; i++) {
		R[i] = new double[colCount];
	}

	for (int i = 1; i <= size + 1; ++i) {
		S[i][i - 1] = 0;
	}



	for (int i = 1; i <= size; i++) {
		S[i][i] = p[i]; R[i][i] = i;
	}


	for (int d = 1; d <= (size); d++) {
		for (int i = 1; i <= (size - d); i++) {
			int j = i + d;
			int sum_p = 0; int min_value = INT_MAX; int min_root = 0;

			for (int k = i; k <= j; k++) {
				sum_p += p[k];
				int value = S[i][k - 1] + S[k + 1][j];
				if (value < min_value) {
					min_value = value;
					min_root = k;
				}
			}
			S[i][j] = sum_p + min_value;
			R[i][j] = min_root;
		}
	}


	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			if (S[i][j] < 0) {
				S[i][j] = -1;
			}
		}
	}

	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			if (R[i][j] < 0) {
				R[i][j] = -1;
			}
		}
	}

	ofstream outfile;
	outfile.open("rmk0017.txt");

	outfile << endl << "*********DP Values Table***********" << endl << endl;

	outfile << right;

	for (int i = -1; i < colCount; i++) {
		if (i == -1) { outfile.width(6); outfile << "(i, j)" << "   "; }
		else {
			outfile.width(6);
			outfile << i << "   ";
		}
	}

	outfile << endl;

	for (int i = 1; i < rowCount; i++) {
		outfile.width(6);
		outfile << i << "   ";
		for (int j = 0; j < colCount; j++) {
			outfile.width(6);
			outfile << S[i][j] << "   ";
		}
		outfile << endl;
	}

	outfile << endl << "*********Roots Table***********" << endl << endl;

	for (int i = -1; i < colCount; i++) {
		if (i == -1) { outfile.width(6); outfile << "(i, j)" << " "; }
		else {
			outfile.width(6);
			outfile << i << " ";
		}
	}

	outfile << endl;

	for (int i = 1; i < rowCount; i++) {
		outfile.width(6);
		outfile << i << " ";
		for (int j = 0; j < colCount; j++) {
			outfile.width(6);
			outfile << R[i][j] << " ";
		}
		outfile << endl;
	}

	outfile << endl << endl << "Optimal BST:" << endl;

	PrintTree2(R, 1, size, 0, outfile);

}

void PrintTree(double **roots, int i, int j, int space_needed)
{
	if (i <= j)
	{
		for (int k = 0; k <= space_needed; k++) { cout << " "; }
		cout << roots[i][j] << endl;

		

		PrintTree(roots, i, roots[i][j] - 1, space_needed+3);

		PrintTree(roots, roots[i][j] + 1, j, space_needed+3);
	}
}

void PrintTree2(double **roots, int i, int j, int space_needed, ofstream& outfile)
{
	if (i <= j)
	{
		for (int k = 0; k <= space_needed; k++) { outfile << " "; }
		outfile << roots[i][j] << endl;

		PrintTree2(roots, i, roots[i][j] - 1, space_needed + 3, outfile);

		PrintTree2(roots, roots[i][j] + 1, j, space_needed + 3, outfile);
	}
}