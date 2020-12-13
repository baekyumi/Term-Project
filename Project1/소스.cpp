#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;

vector<string> vec;
int currentLine = 0, lineNum = 0;
bool flag = false;
string str, instruction, line;
void askInstruction();
void readPage(string s);
void readLine();
void readInstruction(string s);
string sumVec(vector<string> vec);
void makeVec(string);

class TextEditor
{
private:
	TextEditor() {};
	static TextEditor* instance;
public:
	static TextEditor* getInstance()
	{
		if (!instance)
			instance = new TextEditor;
		return instance;
	}
	~TextEditor() { delete instance; };
	void insertStr(int line, int num, string word);
	void deleteStr(int line, int num);
	void searchStr(string word);
	void convertStr(string oldStr, string newStr);
	void saveQuit();
};

TextEditor *TextEditor::instance = 0;

void askInstruction()
{
	while (instruction != "t") {
		for (int i = 0; i < 79; i++)
		{
			cout << "-";
		}
		cout << "\nn:���� ������, p:����������, i:����, d:����, c:����, s:ã��, t:���� �� ����\n";
		for (int i = 0; i < 79; i++)
		{
			cout << "-";
		}
		cout << "\n";
		cin >> instruction;
		for (int i = 0; i < 79; i++)
		{
			cout << "-";
		}
		cout << "\n";
		readInstruction(instruction);
	}
}

void readPage(string s) //������ �б�(n, p)
{
	if (s[0] == 'n')
	{
		if (currentLine == (vec.size()))
		{
			cout << "This is the last page!\n";
			return;
		}
		else
		{
			readLine();
		}
	}
	else if (s[0] == 'p')
	{
		if (currentLine == 20)
		{
			cout << "This is the first page!\n";
			return;
		}
		else
		{
			if (flag)
			{
				currentLine = currentLine - lineNum - 20;
				lineNum = 0;
				flag = false;
			}
			else
			{
				currentLine = currentLine - (20 * 2);
			}
				readLine();

		}
	}
}

void readLine() //�� �پ� �б�
{
	//����ؾ� �ϴ� ���� ���� 20�� �̸��̸� ����ߴ� ���α��� �����Ͽ� 20�� ����ϵ��� currentLine ����
	if (currentLine + 20 > vec.size()) {
		currentLine = vec.size() - 20;
	}
	else if (currentLine < 0) {
		currentLine = 0;
	}
	for (int i = 1; i <= 20; i++)
	{
		cout << i << "| ";
		cout << vec[currentLine++] << "\n";
	}
	cout << "���� �� : " << currentLine << "\n";
}

void TextEditor::insertStr(int line, int num, string word) //����(i)
{
	string str;
	int index = 0, wordNum = 0;
	vector<string> s;

	if (word.size() > 75)
	{
		cout << "75�� �̻� �Է��� �� ����.\n";
		return;
	}
	if ((line > 20) || num < 0)
	{
		cout << "line�� 20 ����, num�� 0 �̻����� �Է��Ͻÿ�.\n";
		return;
	}
	
	if (flag)
	{
		if (line > lineNum)
		{
			cout << "line�� �ٽ� �Է����ּ���.\n";
			return;
		}
		index = currentLine + (line - 1) - lineNum;
		flag = false;
	}
	else
	{
		index = currentLine + (line - 1) - 20; //index�ϱ� 1 �� ��
	}

	str = vec[index];
	istringstream ss(str);
	string stringBuffer, sumStr;


	while (getline(ss, stringBuffer, ' '))
	{
		s.push_back(stringBuffer);
		wordNum++;

	}

	if (wordNum < num)
	{
		cout << "���� : " << num << "��° �ܾ�� �������� ����.\n";
		return;
	}

	for (int i = 0; i < num; i++)
	{
		sumStr += s[i] + ' ';
	}

	if (wordNum == num) //������ �ܾ� �ڿ� �����Ѵٸ�
	{
		if (str[str.size() - 1] == ' ')
		{
			sumStr += word + ' ';
		}
		else
		{
			sumStr += word;
		}
	}
	else
	{
		sumStr += word + ' ';
		for (int i = num; i < wordNum - 1; i++)
		{
			sumStr += s[i] + ' ';
		}
		if (str[str.size() - 1] == ' ')
		{
			sumStr += s[wordNum - 1] + ' ';
		}
		else
		{
			sumStr += s[wordNum - 1];
		}
	}

	vec[index] = sumStr;
	sumVec(vec);
	currentLine -= 20;
	readLine();
	
}

void TextEditor::deleteStr(int line, int num) //����(d)
{
	string str;
	int index = 0, wordNum = 0;
	vector<string> s;

	if ((line > 20) || num < 0)
	{
		cout << "line�� 20 ����, num�� 0 �̻����� �Է��Ͻÿ�.\n";
		return;
	}

	if (flag)
	{
		if (line > lineNum)
		{
			cout << "line�� �ٽ� �Է����ּ���.\n";
			return;
		}
		index = currentLine + (line - 1) - lineNum;
		cout << "currentLine : " << currentLine << endl;
		flag = false;
	}
	else
	{
		index = currentLine + (line - 1) - 20; //index�ϱ� 1 �� ��
	}
	str = vec[index];
	istringstream ss(str);
	string stringBuffer, sumStr;

	while (getline(ss, stringBuffer, ' '))
	{
		s.push_back(stringBuffer);
		wordNum++;

	}

	if (wordNum < num)
	{
		cout << "���� : " << num << "��° �ܾ�� �������� ����.\n";
		return;
	}

	for (int i = 0; i < num - 1; i++)
	{
		sumStr += s[i] + ' ';
	}

	for (int i = num; i < wordNum; i++)
	{
		sumStr += s[i] + ' ';
	}
	if (str[str.size() - 1] == ' ') 
	{
		vec[index] = sumStr;
		sumVec(vec);
		
	}
	else
	{
		sumStr = sumStr.substr(0, sumStr.size() - 1);
		vec[index] = sumStr;
		sumVec(vec);
	}
	currentLine -= 20;
	readLine();

}

void TextEditor::convertStr(string oldStr, string newStr) //����(c)
{
	string s = sumVec(vec);
	string changeStr = "", sumStr = "", last = "";
	int word = s.find(oldStr);
	while (word != -1)
	{
		changeStr = s.substr(0, word);
		changeStr += newStr;
		s = s.substr(word + oldStr.size());
		last = s;
		word = s.find(oldStr);
		sumStr += changeStr;
	}
	sumStr += last;
	makeVec(sumStr);
	currentLine -= 20;
	readLine();
	if (flag)
		flag = false;
}

void TextEditor::searchStr(string findStr) //ã��(s)
{
	int word = 0, index = -1;
	for (int i = 0; i < vec.size(); i++)
	{
		word = vec[i].find(findStr);
		if (word != -1)
		{
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "findStr�� ã�� �� ����.\n";
		return;
	}
	currentLine = index;
	int k = 1;
	if (currentLine + 20 > vec.size())
	{
		flag = true;
		for (int i = currentLine; i < vec.size(); i++)
		{
			cout << k++ << "| ";
			cout << vec[currentLine++] << "\n";
			lineNum++;
		}
	}
	else
		readLine();
}

void TextEditor::saveQuit() //���� �� ����(t)
{
	ofstream writeFile;
	writeFile.open("test.txt");
	string save = sumVec(vec);
	
	if (writeFile.is_open())
	{
		writeFile << save;
	}

	writeFile.close();
}

string sumVec(vector<string> vec)
{
	string s = "";
	for (int i = 0; i < vec.size(); i++)
	{
		s += vec[i];
	}
	makeVec(s);
	return s;
}

void makeVec(string s)
{
	istringstream ss(s);
	string cutStr = "", last = "";
	line = "";
	
	if (!vec.empty())
	{
		while(!vec.empty())
		{		
			vec.pop_back();
		}
	}
	while (getline(ss, cutStr, ' ')) {
		if (line.size() + cutStr.size() + 1 <= 75)
		{
			line += cutStr + " ";
		}
		else
		{
			vec.push_back(line);
			line = cutStr + " ";
		}
	}
	line = line.substr(0, line.size() - 1);
	vec.push_back(line);
	
}

bool isInt(const string& s)
{
	for (const char& c : s)
	{
		if (isdigit(c))
			return true;
	}
	return false;
}

void readInstruction(string instruction)
{
	string stringBuffer, factor, word;
	int line, num;
	int error = 0, find = 0;
	vector<string> s;

	error = instruction.find(' ');
	if (error != string::npos) {
		cout << "���� ���� �ٽ� �Է��ϼ���.\n";
		return;
	}

	if (instruction.size() == 1)
	{
		if (instruction[0] == 'n' || instruction[0] == 'p')
		{
			readPage(instruction);
			return;
		}

		else if (instruction[0] == 't')
		{
			TextEditor::getInstance()->saveQuit();
			return;
		}
		else
		{
			cout << "����. �ٽ� �Է����ּ���.\n";
			return;
		}
	}
	else if (instruction.size() > 1)
	{
		if ((instruction[1] == '(') && (instruction[instruction.size() - 1] == ')'))
		{
			factor = instruction.substr(2, instruction.size() - 3); //��ȣ �ȸ� �ڸ�
			istringstream ss(factor);
			if ((instruction[0] == 'i'))
			{
				while (getline(ss, factor, ','))
				{
					s.push_back(factor);
				}
				if (s.size() != 3)
				{
					cout << "���� : ���� ���� ����. �ٽ� �Է����ּ���.\n";
					return;
				}
				if (!isInt(s[0]) && !isInt(s[1]))
				{
					cout << "���� : ù��° ���ڿ� �ι�° ���ڴ� ���ڷ� �Է��ϼ���.\n";
					return;
				}
				line = atoi(s[0].c_str());
				num = atoi(s[1].c_str());
				word = s[2];
				TextEditor::getInstance()->insertStr(line, num, word);
				return;
			}
			else if ((instruction[0] == 'd'))
			{
				while (getline(ss, factor, ','))
				{
					s.push_back(factor);
				}
				if (s.size() != 2)
				{
					cout << "���� : ���� ���� ����. �ٽ� �Է����ּ���.\n";
					return;
				}
				if (!isInt(s[0]) && !isInt(s[1]))
				{
					cout << "���� : ù��° ���ڿ� �ι�° ���ڴ� ���ڷ� �Է��Ͻÿ�. �ٽ� �Է����ּ���.\n";
					return;
				}
				line = atoi(s[0].c_str());
				num = atoi(s[1].c_str());
				TextEditor::getInstance()->deleteStr(line, num);
				return;
			}
			else if ((instruction[0]) == 's')
			{
				while (getline(ss, factor, ','))
				{
					s.push_back(factor);
				}
				if (s.size() != 1)
				{
					cout << "���� : ���� ���� ����.\n";
					return;
				}
				word = s[0];
				TextEditor::getInstance()->searchStr(word);
				return;
			}
			else if ((instruction[0]) == 'c')
			{
				while (getline(ss, factor, ','))
				{
					s.push_back(factor);
				}
				if (s.size() != 2)
				{
					cout << "���� : ���� ���� ����.\n";
					return;
				}
				TextEditor::getInstance()->convertStr(s[0], s[1]);
				return;
			}
			else
			{
				cout << "����, �ٽ� �Է����ּ���.\n";
				return;
			}
		}
		else 
		{
			cout << "����, �ٽ� �Է����ּ���.\n";
			return;
		}
	}
}

int main()
{
	ifstream readFile;
	readFile.open("test.txt");

	if (readFile.is_open())
	{
		getline(readFile, str);

		makeVec(str);
		readLine();
		askInstruction();
		readFile.close();
	}
	return 0;
}