#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define ff first
#define ss second

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

class user {
        public:
                string uname, pass, fname, lname, bday;
};

class book {
        public:
                string title, SN, author, edition, publisher, pyear, ISBN, L, subjects;
};

void log_in();
void srch();
void take();
void give();
bool avail(string s);

user x;

int main() {
	ios_base::sync_with_stdio(false), cin.tie(NULL);

        log_in();
        while (true) {
                cout << "You can either search for a book [search], take a book [take] or give a book back [give] by using the keywords.";
                cout << "If you are done write [Done]" << endl;
                string s;
                getline(cin, s);
                if (s == "done")
                        break;
                if (s == "search")
                        srch();
                if (s == "take")
                        take();
                if (s == "give")
                        give();
        }

	return 0;
}

void give() {
        cout << "Enter the book title:" << endl;
        string s;
        getline(cin, s);

        ifstream in("taken_books.txt");
        ofstream out("tmp.txt");

        string a, b;
        while (getline(in, a)) {
                getline(in, b);
                if (a == s)
                        continue;
                out << a << endl;
                out << b << endl;
        }
        in.close();
        out.close();
        remove("taken_books.txt");
        rename("tmp.txt", "taken_books.txt");
        cout << "Book has been succesfully taken back to the libary" << endl;
}

void take() {
        cout << "Enter the book title:" << endl;
        string s;
        getline(cin, s);
        bool flag1 = false, flag2 = false;

        fstream books;
        books.open("all_books.txt");


        string a[10];
        while (getline(books, a[0])) {
                for (int i = 1; i < 9; i++)
                        getline(books, a[i]);
                if (a[0] == s)
                        flag1 = true;
        }
        
        books.close();

        fstream tbooks;
        tbooks.open("taken_books.txt");

        int cnt = 0;
        while (getline(tbooks, a[0])) {
                getline(tbooks, a[1]);
                if (a[1] == x.uname)
                        cnt++;
                if (a[0] == s)
                        flag2 = true;
        }
        if (cnt > 1)    flag2 = true;
        
        if (!flag1) {
                cout << "The libary does not contain the book you are looking for. Sorry." << endl;
                tbooks.close();
                return;
        }
        if (flag2) {
                cout << "Either the book is already taken or You already have 2 books under your name" << endl;
                tbooks.close();
                return;
        }

        cout << "You succesfuly got the book";
        tbooks << s << endl;
        tbooks << x.uname << endl;
        tbooks.close();
}

bool avail(string s) {
        fstream ttbooks;
        ttbooks.open("taken_books.txt");

        string a, b;
        while (getline(ttbooks, a)) {
                getline(ttbooks, b);
                if (a == s) {
                        ttbooks.close();
                        return false;
                }
        }

        ttbooks.close();
        return true;
}

void srch() {
        cout << "by which of the following do you want to search:" << endl;
        cout << "Title[0], Shelf Number[1], Authors[2], Edition[3], Publisher[4], Published Year[5], ISBN[6], Length[7], Subjects[8]" << endl;
        string s;
        getline(cin, s);
        int tmp = stoi(s);
        cout << "What to search:" << endl;
        getline(cin, s);

        fstream books;
        books.open("all_books.txt");
        
        cout << "Results:" << endl;

        string a[10];
        while (getline(books, a[0])) {
                for (int i = 1; i < 9; i++)
                        getline(books, a[i]);
                if (a[tmp] == s) {
                        for (int i = 0; i < 9; i++)
                                cout << a[i] << endl;
                        if (avail(a[0]))
                                cout << "** available **" << endl;
                        else
                                cout << "** not available **" << endl;
                }
        }
        books.close();
}

void log_in() {
        while (true) {
                fstream users;
                users.open("users.txt");

                cout << "You should Sign Up if you don't have an account" << endl;
                cout << "You can use [Sign Up] for signing up and [Log In] to log in" << endl;
                string s;
                getline(cin, s);
                for (int i = 0; i < s.size(); i++)
                        s[i] = tolower(s[i]);
                if (s == "sign up") {
                        cout << "Please enter each of the following:" << endl;
                        cout << "User Name:" << endl;;
                        getline(cin, s);
                        x.uname = s;
                        users << s << endl;

                        cout << "Password:" << endl;
                        getline(cin, s);
                        x.pass = s;
                        users << s << endl;

                        cout << "Fist Name:" << endl;
                        getline(cin, s);
                        x.fname = s;
                        users << s << endl;

                        cout << "Last Name:" << endl;
                        getline(cin, s);
                        x.lname = s;
                        users << s << endl;

                        cout << "Birthday:" << endl;
                        getline(cin, s);
                        x.bday = s;
                        users << s << endl;
                        cout << "Sign Up Succeded" << endl;
                        break;

                }
                else if (s == "log in") {
                        string u, p;

                        cout << "Please enter each of the following:" << endl;
                        cout << "User Name:" << endl;
                        getline(cin, u);

                        cout << "Password:" << endl;
                        getline(cin, p);

                        string a[6];
                        while (getline(users, a[0])) {
                                for (int i = 1; i < 5; i++)
                                        getline(users, a[i]);
                                if (a[0] == u && a[1] == p)
                                        break;
                        }
                        if (a[0] != u)
                                cout << "either user or password is wrong, proceed from the start" << endl;
                        else {
                                cout << "Log In Succeded";
                                x.uname = a[0];
                                x.pass = a[1];
                                x.fname = a[2];
                                x.lname = a[3];
                                x.bday = a[4];
                                break;
                        }
                }
                else
                        cout << "Wrong input. Please try again." << endl;
                users.close();
        }
}
