
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <functional>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Triad {
protected:
    double a, b, c;
public:
    Triad() : a(0), b(0), c(0) {
        cout << "[Triad] Default constructor: (" << a << ", " << b << ", " << c << ")\n";
    }
    Triad(double x, double y, double z) : a(x), b(y), c(z) {
        cout << "[Triad] Constructor(" << a << ", " << b << ", " << c << ")\n";
    }
    Triad(const Triad& t) : a(t.a), b(t.b), c(t.c) {
        cout << "[Triad] Copy constructor\n";
    }
    virtual ~Triad() {
        cout << "[Triad] Destructor\n";
    }

    void setA(double x) { a = x; }
    void setB(double y) { b = y; }
    void setC(double z) { c = z; }
    void setAll(double x, double y, double z) { a = x; b = y; c = z; }

    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }

    double sum() const { return a + b + c; }

    virtual string toString() const {
        return "Triad(" + to_string(a) + ", " + to_string(b) + ", " + to_string(c) +
            ") | sum=" + to_string(sum());
    }
    virtual void print() const { cout << toString() << endl; }

    friend ostream& operator<<(ostream& os, const Triad& t) {
        os << t.a << " " << t.b << " " << t.c;
        return os;
    }
    friend istream& operator>>(istream& is, Triad& t) {
        is >> t.a >> t.b >> t.c;
        return is;
    }
};

class Triangle : public Triad {
public:
    Triangle() : Triad() {
        cout << "[Triangle] Default constructor\n";
    }
    Triangle(double x, double y, double z) : Triad(x, y, z) {
        cout << "[Triangle] Constructor(" << x << ", " << y << ", " << z << ")\n";
    }
    Triangle(const Triangle& t) : Triad(t) {
        cout << "[Triangle] Copy constructor\n";
    }
    ~Triangle() {
        cout << "[Triangle] Destructor\n";
    }

    bool isValid() const {
        return (a > 0 && b > 0 && c > 0) &&
            (a + b > c) && (a + c > b) && (b + c > a);
    }
    double perimeter() const { return a + b + c; }
    double area() const {
        if (!isValid()) return 0.0;
        double s = perimeter() / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    double angleA() const {
        if (!isValid()) return 0.0;
        return acos((b * b + c * c - a * a) / (2 * b * c)) * 180.0 / M_PI;
    }
    double angleB() const {
        if (!isValid()) return 0.0;
        return acos((a * a + c * c - b * b) / (2 * a * c)) * 180.0 / M_PI;
    }
    double angleC() const {
        if (!isValid()) return 0.0;
        return acos((a * a + b * b - c * c) / (2 * a * b)) * 180.0 / M_PI;
    }

    string toString() const override {
        if (!isValid())
            return "Triangle(INVALID sides: " + to_string(a) + ", " + to_string(b) + ", " + to_string(c) + ")";
        return "Triangle(a=" + to_string(a) + ", b=" + to_string(b) + ", c=" + to_string(c) +
            ") | P=" + to_string(perimeter()) +
            ", S=" + to_string(area()) +
            ", A=" + to_string(angleA()) +
            ", B=" + to_string(angleB()) +
            ", C=" + to_string(angleC());
    }
    void print() const override { cout << toString() << endl; }

    friend ostream& operator<<(ostream& os, const Triangle& t) {
        os << t.a << " " << t.b << " " << t.c;
        return os;
    }
    friend istream& operator>>(istream& is, Triangle& t) {
        is >> t.a >> t.b >> t.c;
        return is;
    }
};

//  ЗАДАЧА 2.14 — TitleBar

class TitleBar {
    string text;
    int fontSize;
public:
    TitleBar() : text("Untitled"), fontSize(14) {
        cout << "[TitleBar] Default constructor\n";
    }
    TitleBar(const string& t, int fs = 14) : text(t), fontSize(fs) {
        cout << "[TitleBar] Constructor: \"" << text << "\"\n";
    }
    TitleBar(const TitleBar& o) : text(o.text), fontSize(o.fontSize) {
        cout << "[TitleBar] Copy constructor\n";
    }
    ~TitleBar() {
        cout << "[TitleBar] Destructor: \"" << text << "\"\n";
    }

    void setText(const string& t) { text = t; }
    string getText() const { return text; }
    void setFontSize(int fs) { fontSize = fs; }
    int getFontSize() const { return fontSize; }

    string toString() const {
        return "[TitleBar: \"" + text + "\", font=" + to_string(fontSize) + "]";
    }
    void print() const { cout << toString() << endl; }
};

class Button {
    string label;
    int width, height;
    function<void()> callback;
public:
    Button() : label("OK"), width(80), height(30) {
        cout << "[Button] Default constructor\n";
    }
    Button(const string& lbl, int w = 80, int h = 30) : label(lbl), width(w), height(h) {
        cout << "[Button] Constructor: \"" << label << "\"\n";
    }
    Button(const Button& o) : label(o.label), width(o.width), height(o.height) {
        cout << "[Button] Copy constructor\n";
    }
    ~Button() {
        cout << "[Button] Destructor: \"" << label << "\"\n";
    }

    void setLabel(const string& lbl) { label = lbl; }
    string getLabel() const { return label; }
    void setSize(int w, int h) { width = w; height = h; }
    void setCallback(function<void()> cb) { callback = cb; }

    void press() {
        cout << "[Button] \"" << label << "\" pressed!\n";
        if (callback) callback();
        else cout << "[Button] No callback set.\n";
    }

    string toString() const {
        return "[Button: \"" + label + "\", " + to_string(width) + "x" + to_string(height) + "]";
    }
    void print() const { cout << toString() << endl; }
};

class Window {
protected:
    int x, y, width, height;
    string bgColor;
public:
    Window() : x(0), y(0), width(400), height(300), bgColor("white") {
        cout << "[Window] Default constructor\n";
    }
    Window(int x, int y, int w, int h, const string& bg = "white")
        : x(x), y(y), width(w), height(h), bgColor(bg) {
        cout << "[Window] Constructor at (" << x << "," << y << ") size=" << w << "x" << h << "\n";
    }
    Window(const Window& o)
        : x(o.x), y(o.y), width(o.width), height(o.height), bgColor(o.bgColor) {
        cout << "[Window] Copy constructor\n";
    }
    virtual ~Window() {
        cout << "[Window] Destructor\n";
    }

    void setPosition(int nx, int ny) { x = nx; y = ny; }
    void setSize(int w, int h) { width = w; height = h; }
    void setBgColor(const string& bg) { bgColor = bg; }

    virtual string toString() const {
        return "[Window: pos=(" + to_string(x) + "," + to_string(y) +
            ") size=" + to_string(width) + "x" + to_string(height) +
            " bg=" + bgColor + "]";
    }
    virtual void print() const { cout << toString() << endl; }

    virtual void onButtonClick() {
        cout << "[Window] onButtonClick() — base handler\n";
    }
};

class WindowWithTitleAndButton : public Window {
    TitleBar titleBar;
    Button   button;
public:
    WindowWithTitleAndButton()
        : Window(), titleBar("My Window"), button("Click Me") {
        cout << "[WindowWithTitleAndButton] Default constructor\n";
        button.setCallback([this]() { this->onButtonClick(); });
    }
    WindowWithTitleAndButton(int x, int y, int w, int h,
        const string& title, const string& btnLabel,
        const string& bg = "white")
        : Window(x, y, w, h, bg), titleBar(title), button(btnLabel) {
        cout << "[WindowWithTitleAndButton] Constructor\n";
        button.setCallback([this]() { this->onButtonClick(); });
    }
    WindowWithTitleAndButton(const WindowWithTitleAndButton& o)
        : Window(o), titleBar(o.titleBar), button(o.button) {
        cout << "[WindowWithTitleAndButton] Copy constructor\n";
        button.setCallback([this]() { this->onButtonClick(); });
    }
    ~WindowWithTitleAndButton() {
        cout << "[WindowWithTitleAndButton] Destructor\n";
    }

    void setTitle(const string& t) { titleBar.setText(t); }
    void setButtonLabel(const string& lbl) { button.setLabel(lbl); }

    void onKeyPress(char key) {
        cout << "[WindowWithTitleAndButton] Key pressed: '" << key << "' -> triggering button\n";
        button.press();
    }
    void onButtonClick() override {
        cout << "[WindowWithTitleAndButton] EVENT: Button \"" << button.getLabel()
            << "\" clicked in window \"" << titleBar.getText() << "\"!\n";
    }

    string toString() const override {
        return Window::toString() + "\n  " + titleBar.toString() + "\n  " + button.toString();
    }
    void print() const override { cout << toString() << endl; }
};

// ============================================================
//  ЗАДАЧА 3.14 — MyString + UpperString
// ============================================================

class MyString {
protected:
    char* data;
    int   len;

    void allocCopy(const char* src) {
        if (src) {
            len = (int)strlen(src);
            data = new char[len + 1];
            strcpy(data, src);
        }
        else {
            len = 0;
            data = new char[1];
            data[0] = '\0';
        }
    }
public:
    MyString() : data(nullptr), len(0) {
        data = new char[1];
        data[0] = '\0';
        cout << "[MyString] Default constructor\n";
    }
    explicit MyString(const char* s) {
        allocCopy(s);
        cout << "[MyString] Constructor(\"" << data << "\")\n";
    }
    explicit MyString(const string& s) {
        allocCopy(s.c_str());
        cout << "[MyString] Constructor(string: \"" << data << "\")\n";
    }
    MyString(const MyString& o) {
        allocCopy(o.data);
        cout << "[MyString] Copy constructor: \"" << data << "\"\n";
    }
    MyString(MyString&& o) noexcept : data(o.data), len(o.len) {
        o.data = new char[1];
        o.data[0] = '\0';
        o.len = 0;
        cout << "[MyString] Move constructor\n";
    }
    virtual ~MyString() {
        cout << "[MyString] Destructor: \"" << data << "\"\n";
        delete[] data;
    }

    MyString& operator=(const MyString& o) {
        if (this != &o) {
            delete[] data;
            allocCopy(o.data);
        }
        cout << "[MyString] Copy operator=: \"" << data << "\"\n";
        return *this;
    }
    MyString& operator=(MyString&& o) noexcept {
        if (this != &o) {
            delete[] data;
            data = o.data;
            len = o.len;
            o.data = new char[1];
            o.data[0] = '\0';
            o.len = 0;
        }
        cout << "[MyString] Move operator=\n";
        return *this;
    }

    const char* c_str() const { return data; }
    int length()        const { return len; }

    MyString operator+(const MyString& o) const {
        string tmp = string(data) + string(o.data);
        return MyString(tmp.c_str());
    }
    bool operator==(const MyString& o) const {
        return strcmp(data, o.data) == 0;
    }

    virtual string toString() const {
        return string("[MyString: \"") + data + "\", len=" + to_string(len) + "]";
    }
    virtual void print() const { cout << toString() << endl; }

    friend ostream& operator<<(ostream& os, const MyString& s) {
        os << s.data;
        return os;
    }
    friend istream& operator>>(istream& is, MyString& s) {
        string tmp; is >> tmp;
        delete[] s.data;
        s.allocCopy(tmp.c_str());
        return is;
    }
};

class UpperString : public MyString {
    void toUpper() {
        for (int i = 0; i < len; i++)
            data[i] = (char)toupper((unsigned char)data[i]);
    }
public:
    UpperString() : MyString() {
        cout << "[UpperString] Default constructor\n";
    }
    explicit UpperString(const char* s) : MyString(s) {
        toUpper();
        cout << "[UpperString] Constructor(\"" << data << "\")\n";
    }
    explicit UpperString(const string& s) : MyString(s) {
        toUpper();
        cout << "[UpperString] Constructor(string: \"" << data << "\")\n";
    }
    UpperString(const UpperString& o) : MyString(o) {
        cout << "[UpperString] Copy constructor: \"" << data << "\"\n";
    }
    UpperString(UpperString&& o) noexcept : MyString(move(o)) {
        cout << "[UpperString] Move constructor\n";
    }
    ~UpperString() {
        cout << "[UpperString] Destructor: \"" << data << "\"\n";
    }

    UpperString& operator=(const UpperString& o) {
        MyString::operator=(o);
        cout << "[UpperString] Copy operator=\n";
        return *this;
    }
    UpperString& operator=(UpperString&& o) noexcept {
        MyString::operator=(move(o));
        cout << "[UpperString] Move operator=\n";
        return *this;
    }
    UpperString& operator=(const MyString& o) {
        MyString::operator=(o);
        toUpper();
        cout << "[UpperString] operator=(const MyString&)\n";
        return *this;
    }

    void set(const string& s) {
        delete[] data;
        string up = s;
        transform(up.begin(), up.end(), up.begin(),
            [](unsigned char c) { return toupper(c); });
        len = (int)up.size();
        data = new char[len + 1];
        strcpy(data, up.c_str());
    }

    string toString() const override {
        return string("[UpperString: \"") + data + "\", len=" + to_string(len) + "]";
    }
    void print() const override { cout << toString() << endl; }

    friend ostream& operator<<(ostream& os, const UpperString& s) {
        os << s.data;
        return os;
    }
    friend istream& operator>>(istream& is, UpperString& s) {
        string tmp; is >> tmp;
        s.set(tmp);
        return is;
    }
};

// ============================================================
//  ФУНКЦІЇ ТЕСТУВАННЯ
// ============================================================

void testTask1() {
    cout << "\n========== ЗАДАЧА 1.14: Triad + Triangle ==========\n";

    cout << "\n-- 1. Default constructors --\n";
    Triad tr0;
    Triangle t0;
    tr0.print();
    t0.print();

    cout << "\n-- 2. Parametric constructors --\n";
    Triad tr1(1.0, 2.0, 3.0);
    Triangle t1(3.0, 4.0, 5.0);
    tr1.print();
    t1.print();

    cout << "\n-- 3. Copy constructors --\n";
    Triad tr2(tr1);
    Triangle t2(t1);
    tr2.print();
    t2.print();

    cout << "\n-- 4. setAll / setA / setB / setC --\n";
    Triad tr3;
    tr3.setAll(10, 20, 30);
    tr3.print();
    Triangle t3;
    t3.setA(6); t3.setB(8); t3.setC(10);
    t3.print();

    cout << "\n-- 5. Triad sum --\n";
    cout << "Sum of tr1: " << tr1.sum() << endl;

    cout << "\n-- 6. Triangle isValid / area / perimeter / angles --\n";
    Triangle valid(7, 8, 9);
    Triangle invalid(1, 2, 100);
    cout << "valid:   "; valid.print();
    cout << "invalid: "; invalid.print();

    cout << "\n-- 7. operator>> (keyboard) --\n";
    Triangle tInput;
    cout << "Enter three sides (e.g. 5 6 7): ";
    cin >> tInput;
    tInput.print();

    cout << "\n-- 8. Random generation --\n";
    srand((unsigned)time(nullptr));
    for (int i = 0; i < 3; i++) {
        double x = (rand() % 10) + 1;
        double y = (rand() % 10) + 1;
        double z = (rand() % 10) + 1;
        Triangle tRand(x, y, z);
        tRand.print();
    }

    cout << "\n-- 9. File write / read --\n";
    {
        ofstream fout("triangles.txt");
        Triangle ft1(3, 4, 5), ft2(5, 12, 13);
        fout << 2 << "\n" << ft1 << "\n" << ft2 << "\n";
    }
    {
        ifstream fin("triangles.txt");
        int n; fin >> n;
        for (int i = 0; i < n; i++) {
            Triangle ft;
            fin >> ft;
            cout << "From file: "; ft.print();
        }
    }
}

void testTask2() {
    cout << "\n========== ЗАДАЧА 2.14: Window + TitleBar + Button ==========\n";

    cout << "\n-- 1. Default constructor --\n";
    WindowWithTitleAndButton w0;
    w0.print();

    cout << "\n-- 2. Parametric constructor --\n";
    WindowWithTitleAndButton w1(100, 50, 640, 480, "Hello World", "Submit", "gray");
    w1.print();

    cout << "\n-- 3. Copy constructor --\n";
    WindowWithTitleAndButton w2(w1);
    w2.print();

    cout << "\n-- 4. setTitle / setButtonLabel --\n";
    w2.setTitle("Copied Window");
    w2.setButtonLabel("Close");
    w2.print();

    cout << "\n-- 5. setPosition / setSize / setBgColor --\n";
    w1.setPosition(200, 150);
    w1.setSize(800, 600);
    w1.setBgColor("blue");
    w1.print();

    cout << "\n-- 6. onKeyPress -> callback --\n";
    w1.onKeyPress('A');
    w1.onKeyPress('Z');

    cout << "\n-- 7. Polymorphism via Window* --\n";
    Window* pWin = new WindowWithTitleAndButton(0, 0, 320, 240, "Poly Window", "OK");
    pWin->print();
    pWin->onButtonClick();
    delete pWin;

    cout << "\n-- 8. Standalone TitleBar and Button --\n";
    TitleBar tb("Standalone Title", 18);
    tb.print();
    Button btn("Cancel", 100, 40);
    btn.setCallback([]() { cout << "[Standalone] Cancel callback fired!\n"; });
    btn.press();
}

void testTask3() {
    cout << "\n========== ЗАДАЧА 3.14: MyString + UpperString ==========\n";

    cout << "\n-- 1. Default constructors --\n";
    MyString   ms0;
    UpperString us0;
    ms0.print();
    us0.print();

    cout << "\n-- 2. Parametric constructors --\n";
    MyString   ms1("Hello World");
    UpperString us1("hello world");
    ms1.print();
    us1.print();

    cout << "\n-- 3. Copy constructors --\n";
    MyString   ms2(ms1);
    UpperString us2(us1);
    ms2.print();
    us2.print();

    cout << "\n-- 4. Move constructors --\n";
    MyString   ms3(move(ms2));
    UpperString us3(move(us2));
    ms3.print();
    us3.print();
    cout << "After move — ms2: "; ms2.print();
    cout << "After move — us2: "; us2.print();

    cout << "\n-- 5. Copy operator= --\n";
    MyString   ms4;
    UpperString us4;
    ms4 = ms1;
    us4 = us1;
    ms4.print();
    us4.print();

    cout << "\n-- 6. Move operator= --\n";
    MyString   ms5("Temp");
    UpperString us5("Temp");
    ms4 = move(ms5);
    us4 = move(us5);
    ms4.print();
    us4.print();

    cout << "\n-- 7. UpperString::operator=(const MyString&) — auto-uppercase --\n";
    UpperString us6;
    us6 = ms1;
    us6.print();

    cout << "\n-- 8. operator+ (concatenation) --\n";
    MyString msA("foo"), msB("bar");
    MyString msC = msA + msB;
    msC.print();

    cout << "\n-- 9. operator== --\n";
    MyString msX("test"), msY("test"), msZ("other");
    cout << "\"test\" == \"test\":  " << (msX == msY ? "true" : "false") << endl;
    cout << "\"test\" == \"other\": " << (msX == msZ ? "true" : "false") << endl;

    cout << "\n-- 10. operator>> (keyboard) --\n";
    MyString msIn;
    UpperString usIn;
    cout << "Enter a string for MyString: ";
    cin >> msIn;
    msIn.print();
    cout << "Enter a string for UpperString (will be uppercased): ";
    cin >> usIn;
    usIn.print();

    cout << "\n-- 11. File output / input --\n";
    {
        ofstream fout("strings.txt");
        fout << ms1 << "\n" << us1 << "\n";
    }
    {
        ifstream fin("strings.txt");
        MyString fr1;
        UpperString fr2;
        fin >> fr1 >> fr2;
        cout << "From file: "; fr1.print();
        cout << "From file: "; fr2.print();
    }

    cout << "\n-- 12. UpperString::set() --\n";
    UpperString us7;
    us7.set("mixed Case String");
    us7.print();

    cout << "\n-- 13. Polymorphism via MyString* --\n";
    MyString* p = new UpperString("polymorphic");
    p->print();
    delete p;
}

// ============================================================
//  ГОЛОВНЕ МЕНЮ
// ============================================================

int main() {
    char choice = '0';
    do {
        cout << "\n╔══════════════════════════════════════════════╗\n";
        cout << "║  Лабораторна робота №5 — Варіант 14          ║\n";
        cout << "╠══════════════════════════════════════════════╣\n";
        cout << "║  1 — Задача 1.14: Triad + Triangle           ║\n";
        cout << "║  2 — Задача 2.14: Window + TitleBar + Button ║\n";
        cout << "║  3 — Задача 3.14: MyString + UpperString     ║\n";
        cout << "║  0 — Вихід                                   ║\n";
        cout << "╚══════════════════════════════════════════════╝\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case '1': testTask1(); break;
        case '2': testTask2(); break;
        case '3': testTask3(); break;
        case '0': cout << "До побачення!\n"; break;
        default:  cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != '0');

    return 0;
}