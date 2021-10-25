#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<iomanip>

struct cmp_log {
    int diff;
    double rel_diff;
    std::string f1, f2;
};

bool operator<(const cmp_log &lhs, const cmp_log &rhs) {
    return lhs.rel_diff < rhs.rel_diff;
}

void print(std::vector<std::vector<int>> &x) {
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0;j < x[i].size(); j++) {
            std::cout << x[i][j] << " ";
        }
        std::cout << "\n";
    }
}

std::string clear_spaces(std::string &s) {
    std::string ans = "";
    for (auto ch: s) {
        if (ch != ' ') {
            ans += ch;
        }
    }
    return ans;
}

std::string get_file_string(std::string f) {
    std::ifstream f_in(f);
    std::string s, file_as_string = "";
    while(getline(f_in, s)) {
        file_as_string += clear_spaces(s);
    }
    return file_as_string;
}

int edit_dist(const std::string &s1, const std::string &s2) {
    std::vector<std::vector<int>> d(s1.size() + 1, std::vector<int>(s2.size() + 1, 0));
    for (int i = 0; i < d[0].size(); i++) {
        d[0][i] = i;
    }
    for (int i = 0; i < d.size(); i++) {
        d[i][0] = i;
    }
    for (int i = 1; i < d.size(); i++) {
        for (int j = 1; j < d[0].size(); j++) {
            if (s1[i - 1] == s2[j - 1]) {
                d[i][j] = d[i - 1][j - 1];
            } else {
                d[i][j] = std::min({d[i - 1][j], d[i][j - 1], d[i - 1][j - 1]}) + 1;
            }
        }
    }
    return d[d.size() - 1][d[0].size() - 1];
}

std::string get_name(std::string &fname) {
    int start = fname.find("-", 0);
    int fin = fname.find("-", start + 1);
    return fname.substr(start + 1, fin - start - 1);
}

int main() {
    std::vector<cmp_log> d;
    std::vector<std::string> fs = {"000228-e23leontyeva-M-20200117093645.py", "000280-e23aleksin-M-20200117101314.py", "000517-e23uluntseva-M-20200130215819.py",
                                   "000519-e23kulik-M-20200130220959.py", "000671-e23shakirov-M-20200206210712.py", "000683-e23golovschinsky-M-20200206213117.py",
                                   "000687-e23zarov-M-20200206213538.py", "000762-e23kholodkova-M-20200207000618.py", "000838-e23kotenko-M-20200212210854.py",
                                   "000849-e23meteleva-M-20200213200954.py", "000854-e23shirshova-M-20200213202556.py", "000885-e23korolev-M-20200213235334.py",
                                   "000919-e23pavlovskaya-M-20200220194139.py", "000929-e23divakova-M-20200220224949.py"};

    for (int i = 0; i < fs.size(); i++) {
        for(int j = 0; (j < fs.size()) && (i != j) && (get_name(fs[i]) != get_name(fs[j])); j++) {
            std::string s1 = get_file_string(fs[i]), s2 = get_file_string(fs[j]);
            int ans = edit_dist(s1, s2);
//            std::cout << "Results of compare between " << fs[i] << "(size = " << s1.size() << ")" << " and " <<
//                                                          fs[j] << "(size = " << s2.size() << "): " << ans << "\n";
            d.push_back({ans, (double)ans / std::max(s1.size(), s2.size()),  fs[i], fs[j]});
        }
    }
    sort(d.begin(), d.end());
    for (auto el: d) {
        std::cout << std::setw(45) << el.f1 << " " << std::setw(45) << el.f2 << ": " << std::setprecision(3) << el.rel_diff << "(diff = " << el.diff << ")" << "\n";
    }
}
