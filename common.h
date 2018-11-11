#include <iostream>
#include <string>

using namespace std;

#define HR cout << "------------------------------------" << endl;
#define NHR cout << "\n------------------------------------" << endl;

namespace fmt {
    struct format {
        ios_base::fmtflags flag;
        streamsize pr;
    };
    format setfmt(int n = 2) {
        format f;
        f.flag = cout.setf(ios_base::fixed, ios_base::floatfield);
        f.pr = cout.precision(n);
        return f;
    }
    void reset(format& f) {
        cout.setf(f.flag, ios_base::floatfield);
        cout.precision(f.pr);
    }
}

inline void eat_line_rest() {while(cin.get() != '\n') continue;}
