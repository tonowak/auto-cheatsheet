#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
void replace_with(string &subject, const string search, const string replace) {
   size_t pos = 0;
   while((pos = subject.find(search, pos)) != string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
   }
}
 
int main() {
    cout << "input number of columns:" << endl;
    int col_no;
    cin >> col_no;

    freopen("input.txt", "r", stdin);
    freopen("converted.tex", "w", stdout);

    vector<string> all;
    string current;
    while(getline(cin, current))
        all.emplace_back(current);
	all.emplace_back("\n");
 
    for(string &s : all)
        while(!s.empty() && (isspace(s.back()) || s.back() == '.' || s.back() == ':' || s.back() == ';' || s.back() == ','))
            s.pop_back();
 
    for(string &s : all) {
        vector<string> vec_polish = {
            "ó", "ą", "ę", "ł", "ć", "ń", "ś", "ż", "ź", // polish characters
            "Ó", "Ą", "Ę", "Ł", "Ć", "Ń", "Ś", "Ż", "Ź",
            "ç" // other stupid special characters
        };
        for(string c : vec_polish)
            replace_with(s, c, "{" + c + "}");
 
        replace_with(s, " -", "-");
        replace_with(s, "- ", "-");
        replace_with(s, " (", "(");
 
        replace_with(s, " ", "\\,");
        replace_with(s, "–", "-");
        replace_with(s, "-", "\\nobreakdash-");
 
        replace_with(s, "”", "``"); // quotation marks
        replace_with(s, "„", "``");
        replace_with(s, "“", "''");
        replace_with(s, "\"", "''");

		replace_with(s, "%", "\\%");
		replace_with(s, "$", "$$");
		bool closing = false;
		for(int i = 0; i < int(s.size()) - 1; ++i)
			if(s[i] == '$' && s[i + 1] == '$') {
				if(closing) {
					s[i + 1] = '|';
					replace_with(s, "|", "\\seqsplit{");
				} else
					s[i] = '}';
				closing = !closing;
				++i;
			}
    }
 
 
    string fragment = "\\seqsplit{";
    bool negated_colors = false, last_negated = false;
    for(string &s : all)
        if(s.empty()) {
            if(last_negated == false) {
                last_negated = true;
                fragment += (string) "}\\color{" + (negated_colors ? "black" : "blue") + '}';
                negated_colors = !negated_colors;
            }
        } else {
            if(last_negated)
                fragment += "\\seqsplit{";
            last_negated = false;
            fragment += s + "$\\|$";
        }

    cout << "\\documentclass{article}\n"
            "\n"
            "% small margin\n"
            "\\usepackage[a4paper, margin=0.7cm, top=0cm, bottom=0cm]{geometry}\n"
            "\n"
            "% fixing polish symbols\n"
            "\\usepackage[polish]{babel}\n"
            "\\usepackage{amsmath} % for non-break dash\n"
            "\\linespread{0.9} % smaller line height\n"
            "\n"
            "% condensed, tiny font\n"
            "\\usepackage{fontspec}\n"
            "\\defaultfontfeatures{Mapping=tex-text,Scale=MatchLowercase}\n"
            "\\setmainfont{Ubuntu Condensed} % \n"
            "\\usepackage{anyfontsize}\n"
            "\\usepackage{seqsplit}\n"
            "\n"
            "\\usepackage{natbib}\n"
            "\\usepackage{graphicx}\n"
            "\\usepackage{xcolor}\n"
            "\n"
            "% big tables\n"
            "\\usepackage{tabu}\n"
            "\\usepackage{longtable}\n"
			"\\usepackage{wrapfig}\n"
            "\n"
            "\\begin{document}\n"
            "\n"
            "\\setlength{\\tabcolsep}{1pt} % tiny table margins\n"
            "{\\fontsize{4}{5}\\selectfont % tiny font\n"
			"    \\begin{wraptable}{r}{19.5cm}\n"
            "        \\begin{longtabu}{|";

    for(int i = 0; i < col_no; ++i)
        cout << "X[l]|";

    cout << "} % equal-sized columns\n"
            "            \\hline\n"
            "            ";

    for(int i = 0; i < col_no; ++i) {
        cout << fragment;
        if(i != col_no - 1)
            cout << " & ";
		else
			cout << "\n";
    }

    cout << "            \\\\ \\hline\n"
            "        \\end{longtabu}\n"
			"    \\end{wraptable}\n"
			"    \n"
			"    \\hfill \\newline\n"
			"    \\begin{tabular}{c}\n"
			"        \\\\ \\\\ \\\\ \\\\ \\\\ \\\\ \\\\ \\\\ \\\\ \\\\\n";
	for(int i = 0; i < 16; ++i)
		cout << "        \\\\ \\_ \\\\ \\\\ \\\\ \\\\ \\\\ \\\\ \\\\ \\\\ \\\\\n";
	cout << "        \\\\ \\_\n"
		    "    \\end{tabular}\n"
			"    \\hfill\\\\\n"
            "}\n"
            "\n"
            "\\end{document}\n";
}
