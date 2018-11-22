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
    cout << "input number of columns" << endl;
    int col_no;
    cin >> col_no;

    freopen("material.in", "r", stdin);
    freopen("material.tex", "w", stdout);

    vector<string> all;
    string current;
    while(getline(cin, current))
        all.emplace_back(current);
 
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
            fragment += s + '|';
        }

    cout << "\\documentclass{article}\n"
            "\n"
            "% small margin\n"
            "\\usepackage[a4paper, margin=1cm, top=0.1cm, bottom=0.01cm]{geometry}\n"
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
            "\n"
            "\\begin{document}\n"
            "\n"
            "\\setlength{\\tabcolsep}{1pt} % tiny table margins\n"
            "{\\fontsize{4}{5}\\selectfont % tiny font\n"
            "    \\begin{longtabu}{|";

    for(int i = 0; i < col_no; ++i)
        cout << "X[l]|";

    cout << "} % equal-sized columns\n"
            "        \\hline\n"
            "        ";

    for(int i = 0; i < col_no; ++i) {
        cout << fragment;
        if(i != col_no - 1)
            cout << " & ";
    }

    cout << "\\\\ \\hline\n"
            "    \\end{longtabu}\n"
            "    }\n"
            "\n"
            "\\end{document}\n";
}
