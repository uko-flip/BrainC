#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

static char cpu[30000];

int main(int argc, char **argv) {
	if(argc < 2) {
		cerr << "Error: too few arguments" << endl
		     << "Usage: brainc [FILE]" << endl;
	}
    vector<char> acc;
    char ch;
    ifstream infile(argv[1]);
    while (infile) {
        infile.get(ch);
        acc.push_back(ch);
    }
    infile.close();
    unsigned int j = 0;
    int brc = 0;
    for (int i = 0; i < acc.size(); ++i) {
        if (acc[i] == '>')
            j++;
        if (acc[i] == '<')
            j--;
        if (acc[i] == '+')
            cpu[j]++;
        if (acc[i] == '-')
            cpu[j]--;
        if (acc[i] == '.')
            cout << cpu[j];
        if (acc[i] == ',')
            cin >> cpu[j];
        if (acc[i] == '[') {
            if (!cpu[j]) {
                ++brc;
                while (brc) {
                    ++i;
                    if (acc[i] == '[')
                        ++brc;
                    if (acc[i] == ']')
                        --brc;
                }
            } else
                continue;
        } else if (acc[i] == ']') {
            if (!cpu[j])
                continue;
            else {
                if (acc[i] == ']')
                    brc++;
                while (brc) {
                    --i;
                    if (acc[i] == '[')
                        brc--;
                    if (acc[i] == ']')
                        brc++;
                }
                --i;
            }
        }
    }
}
