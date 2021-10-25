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
     std::vector<std::string> fs = {
        "000096-a2024tsaplev-F-20211019121138.py",
        "000097-a2024tsaplev-F-20211019121149.py",
        "000168-a2024orekhova-F-20211019143007.py",
        "000170-a2024orekhova-F-20211019143047.py",
        "000172-a2024orekhova-F-20211019143116.py",
        "000173-a2024tcoi-F-20211019143128.py",
        "000177-a2024tcoi-F-20211019143202.py",
        "000226-a2024somova-F-20211023161408.py",
        "000227-a2024somova-F-20211023161433.py",
        "000228-a2024pakhomov-F-20211023184417.py",
        "000229-a2024pakhomov-F-20211023184733.py",
        "000230-a2024pakhomov-F-20211023184807.py",
        "000231-a2024pakhomov-F-20211023190851.py",
        "000233-a2024pakhomov-F-20211023193414.py",
        "000245-a2024krasovskaya-F-20211023235440.py",
        "000261-a2024mozer-F-20211024155745.py",
        "000262-a2024mozer-F-20211024155909.py",
        "000263-a2024mozer-F-20211024160105.py",
        "000297-a2024urusov-F-20211024204948.py",
        "000298-a2024urusov-F-20211024205033.py",
        "000299-a2024urusov-F-20211024205155.py",
        "000300-a2024urusov-F-20211024205226.py",
        "000301-a2024urusov-F-20211024205513.py",
        "000302-a2024urusov-F-20211024205803.py",
        "000303-a2024shishov-F-20211024210153.py",
        "000305-a2024shishov-F-20211024210555.py",
        "000306-a2024shishov-F-20211024210628.py",
        "000308-a2024tcoi-F-20211024210722.py",
        "000309-a2024urusov-F-20211024211245.py",
        "000310-a2024tcoi-F-20211024211631.py",
        "000325-a2024lysyi-F-20211024220524.py",
        "000326-a2024lysyi-F-20211024220552.py",
        "000328-a2024lysyi-F-20211024221034.py",
        "000329-a2024lysyi-F-20211024221153.py",
        "000340-a2024razdobarin-F-20211024230226.py",
        "000342-a2024razdobarin-F-20211024232821.py",
        "000343-a2024razdobarin-F-20211024232835.py",
        "000391-a2024baukov-F-20211025194934.py",
        "000392-a2024baukov-F-20211025195031.py",
        "000393-a2024dashevskaya-F-20211025195115.py",
        "000394-a2024baukov-F-20211025195130.py",
        "000402-a2024dashevskaya-F-20211025195734.py",
        "000403-a2024dashevskaya-F-20211025200015.py",
        "000405-a2024dashevskaya-F-20211025200103.py",
        "000428-a2024razdobarin-F-20211025202643.py",
        "000432-a2024razdobarin-F-20211025204024.py",
        "000433-a2024osipov-F-20211025204154.py",
        "000440-a2024osipov-F-20211025205350.py",
        "000445-a2024chutko-F-20211025205735.py",
        "000450-a2024razdobarin-F-20211025205943.py",
        "000457-a2024chutko-F-20211025210232.py",
        "000459-a2024chutko-F-20211025210333.py"
    };

    for (int i = 0; i < fs.size(); i++) {
        for(int j = 0; (j < fs.size()) && (i != j) && (get_name(fs[i]) != get_name(fs[j])); j++) {
            std::string s1 = get_file_string(fs[i]), s2 = get_file_string(fs[j]);
            int ans = edit_dist(s1, s2);
            // std::cout << fs[i] << " " << fs[j] << "\n";
            // std::cout << "Results of compare between " << fs[i] << "(size = " << s1.size() << ")" << " and " <<
            //                                               fs[j] << "(size = " << s2.size() << "): " << ans << "\n";
            d.push_back({ans, (double)ans / std::max(s1.size(), s2.size()),  fs[i], fs[j]});
        }
    }
    sort(d.begin(), d.end());
    for (auto el: d) {
        std::cout << std::setw(45) << el.f1 << " " << std::setw(45) << el.f2 << ": " << std::setprecision(3) << el.rel_diff << "(diff = " << el.diff << ")" << "\n";
    }
}
