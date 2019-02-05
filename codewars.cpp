#include "pch.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
#include <regex>
#include <numeric>
#include <iterator>
#include <functional>
#include <exception>
#include <string>
#include <unordered_map>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RGB To Hex Conversion
// https://www.codewars.com/kata/513e08acc600c94f01000001
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RGBToHex
{
protected:
    static int rangeCheck(int v)
    {
        return (v < 0) ? 0 : ((v > 255) ? 255 : v);
    }
    static int rangeCheck2(int v)
    {
        return std::max(0, std::min(255, v));
    }
public:
    static std::string rgb(int r, int g, int b)
    {
        std::stringstream ss;
        ss << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << rangeCheck(r);
        ss << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << rangeCheck(g);
        ss << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << rangeCheck(b);
        return ss.str();
    }
    static std::string rgb2(int r, int g, int b)
    {
        std::ostringstream ss;
        ss.flags(std::ios::hex | std::ios::uppercase);
        ss.fill('0');
        ss << std::setw(2) << rangeCheck2(r);
        ss << std::setw(2) << rangeCheck2(g);
        ss << std::setw(2) << rangeCheck2(b);
        return ss.str();
    }
    static void byte2hex(unsigned char b, std::string& s)
    {
        static const char* hex = "0123456789ABCDEF";
        s.push_back(hex[b >> 4]);
        s.push_back(hex[b & 0xf]);
    }
    static std::string rgb3(int r, int g, int b)
    {
        std::string result;
        byte2hex(rangeCheck2(r), result);
        byte2hex(rangeCheck2(g), result);
        byte2hex(rangeCheck2(b), result);
        return result;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Find the odd int
// https://www.codewars.com/kata/54da5a58ea159efa38000836
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int findOdd(const std::vector<int>& numbers)
{
    std::unordered_map<int, int> m;
    for (auto v : numbers)
        m[v]++;
    for (auto v : m)
        if (v.second % 2)
            return v.first;
    return 0;
}
int findOdd2(const std::vector<int>& numbers)
{
    for (auto v : numbers)
        if (std::count(numbers.begin(), numbers.end(), v) % 2)
            return v;
    return 0;
}
int findOdd3(const std::vector<int>& numbers)
{
    return std::accumulate(numbers.begin(), numbers.end(), 0, std::bit_xor<int>());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Valid Braces
// https://www.codewars.com/kata/5277c8a221e209d3f6000b56
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool valid_braces(std::string braces)
{
    std::stack<char> st;
    for (auto ch : braces)
        switch (ch)
        {
        case '(': st.push(')'); break;
        case '[': st.push(']'); break;
        case '{': st.push('}'); break;
        default:
            if (st.empty() || st.top() != ch) return false;
            st.pop();
        }
    return st.empty();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// longest_palindrome
// https://www.codewars.com/kata/54bb6f887e5a80180900046b
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool is_palindrome(const std::string &s)
{
    return s == std::string(s.rbegin(), s.rend());
}

int longest_palindrome(const std::string &s)
{
    size_t max = 0;
    for (size_t offs = 0; offs < s.size() - 1; offs++)
    {
        size_t count = s.size() - offs;
        while (count > max)
        {
            if (is_palindrome(s.substr(offs, count)))
            {
                max = count;
                break;
            }
            count--;
        }
    }
    return max;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Mexican Wave
// https://www.codewars.com/kata/58f5c63f1e26ecda7e000029
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::string> wave(std::string y) 
{
    std::vector<std::string> res;
    for (size_t i = 0; i < y.size(); i++)
    {
        if (isalpha(y[i]))
        {
            res.push_back(y);
            res.back()[i] = toupper(y[i]);
        }
    }
    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Roman Numerals Encoder
// https://www.codewars.com/kata/51b62bf6a9c58071c600001b
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const std::vector<std::pair<int, std::string>> roman = {
  {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
};

std::string RomanNumeralsEncoder(int number) 
{
    std::string res;
    for (const auto p : roman)
        while (number >= p.first)
        {
            res += p.second;
            number -= p.first;
        }
    return res;
}
// Expected: equal to MMMCDLXXII   // 31
// Actual : MMMCCCCLXXII // 3472

int from_roman(std::string s)
{
    int res = 0;
    for (const auto p : roman)
        while (s.find(p.second) == 0)
        {
            s = s.substr(p.second.length());
            res += p.first;
        }
    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Esolang Interpreters #1 - Introduction to Esolangs and My First Interpreter (MiniStringFuck)
// https://www.codewars.com/kata/586dd26a69b6fd46dd0000c0
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string my_first_interpreter(const std::string& code)
{
    char reg = 0;
    std::string res;
    for (auto op : code)
        if (op == '+') 
            reg++;
        else
            if (op == '.') 
                res += reg;
    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fibonacci, Tribonacci and friends
// https://www.codewars.com/kata/556e0fccc392c527f20000c5
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<int> xbonacci(std::vector<int> signature, size_t n)
{
    std::vector<int> res(signature);
    size_t count = res.size();
    if (count > n)
        res.resize(n);
    else
        while (res.size() < n)
            res.push_back(std::accumulate(res.crbegin(), res.crbegin() + count, 0));
    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Find the missing term in an Arithmetic Progression
// https://www.codewars.com/kata/52de553ebb55d1fca3000371
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

static long findMissing(std::vector<long> list) 
{
    long step = (list.back() - list.front()) / (long)list.size();
    long pr = list.front();
    for (auto v : list)
    {
        if (pr != v)
            return pr;
        pr += step;
    }
    return 0;
    /*
     long long expectedSum = (list.front() + list.back()) * (list.size() + 1);
     long long actualSum = std::accumulate(list.begin(), list.end(), 0ll);
     return (expectedSum - 2 * actualSum) / 2;
    */
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Counting Duplicates
// https://www.codewars.com/kata/54bf1c2cd5b56cc47f0007a1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

size_t duplicateCount(const char *in)
{
    std::unordered_map<char, int> m;
    while (char ch = *in++)
        ++m[tolower(ch)];
    return std::count_if(m.cbegin(), m.cend(), [](const auto& v) { return v.second > 1; });
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Which are in?
// https://www.codewars.com/kata/550554fd08b86f84fe000a58
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WhichAreIn
{

public:
    static std::vector<std::string> inArray(std::vector<std::string> &array1, std::vector<std::string> &array2)
    {
        std::vector<std::string> res;
        std::copy_if(array1.begin(), array1.end(), std::back_inserter(res), [&](const std::string& item1) {
            return std::any_of(array2.begin(), array2.end(), [&](const std::string& item2) {
                return item2.find(item1) != std::string::npos;
            });
        });
        return res;
    };
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple Pig Latin
// https://www.codewars.com/kata/520b9d2ad5c005041100000f
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


std::string pig_it(std::string str)
{
    /*
    std::string res;
    bool bFirst = true;
    char chFirst;
    for (auto ch : str)
        if (bFirst)
            if (isalpha(ch))
            {
                bFirst = false;
                chFirst = ch;
            }
            else
                res.push_back(ch);
        else
            if (isalpha(ch))
                res.push_back(ch);
            else
            {
                res.push_back(chFirst);
                res.push_back('a');
                res.push_back('y');
                res.push_back(ch);
                bFirst = true;
            }
    if (!bFirst)
    {
        res.push_back(chFirst);
        res.push_back('a');
        res.push_back('y');
    }
    return res;
    */
    std::regex re("(\\w)(\\w*)(\\s|$)");
    return std::regex_replace(str, re, "$2$1ay$3");
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int32 to IPv4
// https://www.codewars.com/kata/52e88b39ffb6ac53a400022e
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string uint32_to_ip(uint32_t ip)
{
    std::stringstream ss;
    ss << ((ip >> 24) & 0xFF) << '.' << ((ip >> 16) & 0xFF) << '.' << ((ip >> 8) & 0xFF) << '.' << (ip & 0xFF);
    return ss.str();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Esoteric Language: 'Poohbear' Interpreter
// https://www.codewars.com/kata/59a9735a485a4d807f00008a
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string poohbear(const char* sourcecode)
{
    std::string result;
    std::unordered_map<size_t, unsigned char> cells;
    size_t curr_cell = 0;
    unsigned char clipboard;
    const char* p_loop = nullptr;
    while (char code = *sourcecode++)
        switch (code)
        {
        case '+': cells[curr_cell]++; break;
        case '-': cells[curr_cell]--; break;
        case '>': curr_cell++; break;
        case '<': curr_cell--; break;
        case 'c': clipboard = cells[curr_cell]; break;
        case 'p': cells[curr_cell] = clipboard; break;
        case 'W': 
            if (cells[curr_cell])
                p_loop = sourcecode;
            else
                while ('E' != *sourcecode++) ;
            break;
        case 'E': if (cells[curr_cell] && p_loop) sourcecode = p_loop; break;
        case 'P': result += cells[curr_cell]; break;
        case 'N': result += std::to_string((int)cells[curr_cell]); break;
        case 'T': cells[curr_cell] *= 2; break;
        case 'Q': cells[curr_cell] = cells[curr_cell] * cells[curr_cell]; break;
        case 'U': cells[curr_cell] = static_cast<int>(sqrt(cells[curr_cell])); break;
        case 'L': cells[curr_cell] += 2; break;
        case 'I': cells[curr_cell] -= 2; break;
        case 'V': cells[curr_cell] /= 2; break;
        case 'A': cells[curr_cell] += clipboard; break;
        case 'B': cells[curr_cell] -= clipboard; break;
        case 'Y': cells[curr_cell] *= clipboard; break;
        case 'D': cells[curr_cell] /= clipboard; break;
        }
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple assembler interpreter
// https://www.codewars.com/kata/58e24788e24ddee28e000053
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
mov x y - copies y (either a constant value or the content of a register) into register x
inc x - increases the content of register x by one
dec x - decreases the content of register x by one
jnz x y - jumps to an instruction y steps away (positive means forward, negative means backward), but only if x (a constant or a register) is not zero
*/

enum class OP { MOVE, INC, DEC, JNZ };

bool decode(const std::string  &instr, OP &op, std::string &p1, std::string &p2)
{
    static std::regex rMov("(mov)\\s+([[:alpha:]])\\s+([[:alpha:]]|([\\+|-]?[[:digit:]]+))");
    static std::regex rInc("(inc)\\s+([[:alpha:]])");
    static std::regex rDec("(dec)\\s+([[:alpha:]])");
    static std::regex rJnz("(jnz)\\s+([[:alpha:]]|([\\+|-]?[[:digit:]]+))\\s+([\\+|-]?[[:digit:]]+)");
    std::smatch rRes;
    if (std::regex_match(instr, rRes, rMov))
    {
        op = OP::MOVE;
        p1 = rRes[2];
        p2 = rRes[3];
        return true;
    }
    if (std::regex_match(instr, rRes, rInc))
    {
        op = OP::INC;
        p1 = rRes[2];
        return true;
    }
    if (std::regex_match(instr, rRes, rDec))
    {
        op = OP::DEC;
        p1 = rRes[2];
        return true;
    }
    if (std::regex_match(instr, rRes, rJnz))
    {
        op = OP::JNZ;
        p1 = rRes[2];
        p2 = rRes[4];
        return true;
    }
    return false;
}

int getReg(std::unordered_map<std::string, int>& regs, std::string name)
{
    try
    {
        int res = std::stoi(name);
        return res;
    }
    catch (...)
    {
        return regs[name];
    }
}

std::unordered_map<std::string, int> assembler(const std::vector<std::string>& program)
{
    std::unordered_map<std::string, int> regs;
    std::vector<std::pair<OP, std::pair<std::string, std::string> > > prog;
    for (auto line : program)
    {
        OP op;
        std::string p1, p2;
        if (decode(line, op, p1, p2))
            prog.push_back({ op, {p1, p2} });
    }
    for (size_t ip = 0; ip < prog.size(); ip++)
    {
        //if (decode(program[ip], op, p1, p2))
            switch (prog[ip].first)
            {
            case OP::MOVE: regs[prog[ip].second.first] = getReg(regs, prog[ip].second.second); break;
            case OP::INC: ++regs[prog[ip].second.first]; break;
            case OP::DEC: --regs[prog[ip].second.first]; break;
            case OP::JNZ: 
                if (getReg(regs, prog[ip].second.first))
                    ip += getReg(regs, prog[ip].second.second) - 1;
                break;
            }
    }
    return regs;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple Encryption #2 - Index-Difference
// https://www.codewars.com/kata/5782b5ad202c0ef42f0012cb
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::string region = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;-?! '()$%&\"";

class SimpleEncryption
{
    static void check(const std::string &text)
    {
        for (size_t i = 0; i < text.length(); i++)
            if (region.find(text[i]) == region.npos)
                throw std::exception("bad symbol");
    }
    static void changeCase(std::string &text)
    {
        for (size_t i = 1; i < text.length(); i += 2)
            text[i] = isupper(text[i]) ? tolower(text[i]) : toupper(text[i]);
    }
public:
    static std::string encrypt(std::string text)
    {
        if (text.empty()) return text;
        check(text);
        changeCase(text);
        std::string res = text;
        for (size_t i = 1; i < text.length(); i++)
        {
            int idx = region.find(text[i - 1]) - region.find(text[i]);
            if (idx < 0) idx += region.length();
            res[i] = region[idx];
        }
        res[0] = region[region.length() - region.find(res[0]) - 1];
        return res;
    }
    static std::string decrypt(std::string text)
    {
        if (text.empty()) return text;
        check(text);
        text[0] = region[region.length() - region.find(text[0]) - 1];
        for (size_t i = 1; i < text.length(); i++)
        {
            int idx = region.find(text[i - 1]) - region.find(text[i]);
            if (idx < 0) idx += region.length();
            text[i] = region[idx];
        }
        changeCase(text);
        return text;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Square Matrix Multiplication
// https://www.codewars.com/kata/5263a84ffcadb968b6000513
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::vector<int>> matrix_multiplication(std::vector<std::vector<int>> &a, std::vector<std::vector<int>> &b, size_t n)
{
    std::vector<std::vector<int>> result(n, std::vector<int>(n));
    for (size_t row = 0; row < n; row++)
        for (size_t col = 0; col < n; col++)
            for (size_t i = 0; i < n; i++)
                result[row][col] += a[row][i] * b[i][col];
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// My smallest code interpreter (aka Brainf**k)
// https://www.codewars.com/kata/526156943dfe7ce06200063e
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string brainLuck(std::string code, std::string input)
{
    const size_t max_regs = 50;
    std::string result;
    std::vector<unsigned char> regs(max_regs);
    size_t ireg = max_regs / 2;
    auto stream = input.begin();
    for (size_t ip = 0; ip < code.length(); ip++)
        switch (code[ip])
        {
        case '>': ireg++; break;
        case '<': ireg--; break;
        case '+': ++regs[ireg]; break;
        case '-': --regs[ireg]; break;
        case '.': result += regs[ireg]; break;
        case ',': regs[ireg] = *stream++; break;
        case '[': 
            if (regs[ireg] == 0)
            {
                int braces = 1;
                while (braces > 0)
                {
                    ip++;
                    if (code[ip] == '[') braces++;
                    if (code[ip] == ']') braces--;
                }
            }
            break;
        case ']': 
            if (regs[ireg] != 0) 
            {
                    int braces = 1;
                    while (braces > 0) {
                        ip--;
                        if (code[ip] == '[') braces--;
                        if (code[ip] == ']') braces++;
                    }
            }
            break;
        }
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Directions Reduction
// https://www.codewars.com/kata/550f22f4d758534c1100025a
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DirReduction
{
    static bool is_opposite_dir(const std::string& dir1, const std::string& dir2)
    {
        return ((dir1 == "NORTH" && dir2 == "SOUTH") || (dir1 == "SOUTH" && dir2 == "NORTH") ||
                (dir1 == "EAST" && dir2 == "WEST") || (dir1 == "WEST" && dir2 == "EAST"));
    }
public:
    static std::vector<std::string> dirReduc(std::vector<std::string> &arr)
    {
        std::vector<std::string> result;
        for (auto dir : arr)
            if (result.empty() || !is_opposite_dir(result.back(), dir))
                result.push_back(dir);
            else
                result.pop_back();
        return result;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sort - one, three, two
// https://www.codewars.com/kata/56f4ff45af5b1f8cd100067d
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Dinglemouse
{
    static std::string number_to_words(int num)
    {
        static const std::vector<std::string> names = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
        static const std::vector<std::string> tens = { "zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };        
        if (num == 0) return names[0];
        std::string result;
        if ((num / 100) > 0)
        {
            result += number_to_words(num / 100) + " hundred ";
            num %= 100;
        }
        if (num > 0)
        {
            if (num < 20)
                result += names[num];
            else
            {
                result += tens[num / 10];
                if ((num % 10) > 0)
                    result += "-" + names[num % 10];
            }
        }
        return result;
    }
public:
    static std::vector<int> sort(const std::vector<int> &array)
    {
        std::vector<int> result(array);
        std::sort(result.begin(), result.end(), [](const auto &p1, const auto &p2) -> bool
            {
                return number_to_words(p1) < number_to_words(p2);
            });
        return result;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Weight for weight
// https://www.codewars.com/kata/55c6126177c9441a570000cc
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WeightSort
{
public:
    static std::string orderWeight(const std::string &strng)
    {
        std::vector<std::string> arr1;
        std::istringstream iss(strng);
        std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(arr1));
        std::sort(arr1.begin(), arr1.end(), [](const std::string &s1, const std::string &s2)  
        {
            auto fn_weight = [](const int weight, const char ch) -> int { return weight + (ch - '0'); };
            int w1 = std::accumulate(s1.begin(), s1.end(), 0, fn_weight);
            int w2 = std::accumulate(s2.begin(), s2.end(), 0, fn_weight);
            return (w1 == w2) ? s1 < s2 : w1 < w2;
        });
        std::ostringstream oss;
        std::copy(arr1.begin(), arr1.end(), std::ostream_iterator<std::string>(oss, " "));
        std::string result = oss.str();
        return result.substr(0, result.length() - 1);
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A Chain adding function
// https://www.codewars.com/kata/539a0e4d85e3425cb0000a88
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Chain
{
    int _v;
public:
    Chain(int v = 0) : _v(v) { }
    Chain operator()(const int v) const { return Chain(_v + v); }
    operator int() const { return _v; }
};

std::ostream& operator<<(std::ostream &os, Chain const &x)
{
    os << (int)x;
    return os;
}

auto add(int n) 
{ 
    return Chain(n); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Greed is Good
// https://www.codewars.com/kata/5270d0d18625160ada0000e4
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int score(const std::vector<int>& dice)
{        
    int score = 0;
    int count[7] = { 0 };
    for (auto v : dice)
        if (++count[v] == 3)
        {
            score += (v == 1) ? 1000 : v * 100;
            count[v] = 0;
        }
    score += count[1] * 100;
    score += count[5] * 50;
    return score;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Scramblies
// https://www.codewars.com/kata/55c04b4cc56a697bb0000048
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool scramble(const std::string& s1, const std::string& s2) 
{
    int nums['z' - 'a' + 1] = { 0 };
    for (auto c : s1) nums[c - 'a']++;
    for (auto c : s2) if (!nums[c - 'a']--) return false;
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Snail
// https://www.codewars.com/kata/521c2db8ddc89b9b7a0000c1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<int> snail(std::vector<std::vector<int>> &matrix)
{
    std::vector<int> result;
    if (matrix.empty()) return result;
    size_t x = 0, y = 0, x0 = 0, x1 = matrix[0].size() - 1, y0 = 0, y1 = matrix.size() - 1;
    while (y0 <= y1)
    {
        while (x < x1) result.push_back(matrix[y][x++]); y0++;
        while (y < y1) result.push_back(matrix[y++][x]); x1--;
        while (x > x0) result.push_back(matrix[y][x--]); y1--;
        while (y > y0) result.push_back(matrix[y--][x]); x0++;
    }
    result.push_back(matrix[y][x]);
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sudoku Solution Validator
// https://www.codewars.com/kata/529bf0e9bdf7657179000008
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool checkRow(int row, unsigned int board[9][9])
{
    char checks[10] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    for (int c = 0; c < 9; c++)
        if (!checks[board[row][c]]--) return false;
    return true;
}

bool checkCol(int col, unsigned int board[9][9])
{
    char checks[10] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    for (int r = 0; r < 9; r++)
        if (!checks[board[r][col]]--) return false;
    return true;
}

bool checkQuadr(int col, int row, unsigned int board[9][9])
{
    char checks[10] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    for (int r = row; r < row + 3; r++)
        for (int c = col; c < col + 3; c++)
            if (!checks[board[r][c]]--) return false;
    return true;
}

bool validSudoku(unsigned int board[9][9]) 
{
    for (int i = 0; i < 9; i++)
    {
        if (!checkRow(i, board)) return false;
        if (!checkCol(i, board)) return false;
    }
    for (int r = 0; r < 9; r += 3)
        for (int c = 0; c < 9; c += 3)
            if (!checkQuadr(r, c, board)) return false;
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Multiplying numbers as strings
// https://www.codewars.com/kata/55911ef14065454c75000062
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string multiply(std::string a, std::string b) 
{
    if (a.empty() || b.empty()) return "";
    std::vector<std::string> arr;
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    int ten = 0;
    for(auto b1 : b)  //multiplication
    {
        int mem = 0;
        std::string mul;
        for (auto a1 : a)
        {
            int p = (a1 - '0') * (b1 - '0') + mem;
            mem = (p > 9) ? p / 10 : 0;
            p -= mem * 10;
            mul.push_back('0' + p);
        }
        if (mem) mul.push_back('0' + mem);
        arr.push_back(std::string(ten++, '0') + mul);
    }
    std::string res;
    int mem = 0;
    for (size_t i = 0; i < arr[arr.size() - 1].length(); i++) //addition
    {
        int sum = mem;
        for (const auto s : arr)
            if (i < s.length())
                sum += s[i] - '0';
        mem = (sum > 9) ? sum / 10 : 0;
        sum -= mem * 10;
        res.push_back('0' + sum);
    }
    if (mem) res.push_back('0' + mem);
    while (res.back() == '0' && res.length() > 1) res.pop_back();
    std::reverse(res.begin(), res.end());
    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Roman Numerals Helper
// https://www.codewars.com/kata/51b66044bce5799a7f000003
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RomanN
{
public:
    std::string to_roman(int number)
    {
        std::string res;
        for (auto p : roman)
            while (number >= p.first)
            {
                res += p.second;
                number -= p.first;
            }
        return res;
    }

    int from_roman(std::string s)
    {
        int res = 0;
        for (const auto p : roman)
            while (s.find(p.second) == 0)
            {
                s = s.substr(p.second.length());
                res += p.first;
            }
        return res;
    }
} RomanNumerals;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Rotations and reflections I
// https://www.codewars.com/kata/591521e2d64db03a010000fe
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Dih4
{
private:
    int _tr;

public:
    static Dih4 IDENTITY;
    static Dih4 ROTATE_90_ANTICLOCKWISE;
    static Dih4 ROTATE_180;
    static Dih4 ROTATE_90_CLOCKWISE;
    static Dih4 REFLECT_VERTICAL;
    static Dih4 REFLECT_FORWARD_DIAGONAL;
    static Dih4 REFLECT_HORIZONTAL;
    static Dih4 REFLECT_REVERSE_DIAGONAL;

    Dih4(int tr = 0) : _tr(tr) {  }
    bool is_rotation() const { return _tr < 4; }
    bool is_reflection() const { return !is_rotation(); }
    Dih4 inv() const
    {
        if (_tr == 1) return Dih4(3);
        if (_tr == 3) return Dih4(1);
        return Dih4(_tr);
    }
    Dih4 then(Dih4 to) const
    {
        static const int m_tr[8][8] = {
            {0, 1, 2, 3, 4, 5, 6, 7 },
            {1, 2, 3, 0, 5, 6, 7, 4 },
            {2, 3, 0, 1, 6, 7, 4, 5 },
            {3, 0, 1, 2, 7, 4, 5, 6 },
            {4, 7, 6, 5, 0, 3, 2, 1 },
            {5, 4, 7, 6, 1, 0, 3, 2 },
            {6, 5, 4, 7, 2, 1, 0, 3 },
            {7, 6, 5, 4, 3, 2, 1, 0 }
        };
        return Dih4(m_tr[_tr][to._tr]);
    }
    bool operator==(const Dih4 &o) const { return _tr == o._tr; }
    bool operator!=(const Dih4 &o) const { return !(*this == o);  }
};

Dih4 Dih4::IDENTITY(0);
Dih4 Dih4::ROTATE_90_ANTICLOCKWISE(1);
Dih4 Dih4::ROTATE_180(2);
Dih4 Dih4::ROTATE_90_CLOCKWISE(3);
Dih4 Dih4::REFLECT_VERTICAL(4);
Dih4 Dih4::REFLECT_FORWARD_DIAGONAL(5);
Dih4 Dih4::REFLECT_HORIZONTAL(6);
Dih4 Dih4::REFLECT_REVERSE_DIAGONAL(7);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fun with trees : array to tree
// https://www.codewars.com/kata/57e5a6a67fbcc9ba900021cd
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TreeNode
{
public:
    int m_value;
    TreeNode* m_left;
    TreeNode* m_right;
    TreeNode(int value, TreeNode* left, TreeNode* right) : m_value(value), m_left(left), m_right(right) { }
    TreeNode(int value) : m_value(value), m_left(nullptr), m_right(nullptr) { }
};

class Solution
{
public:
    static TreeNode* arrayToTree(const std::vector<int>& arr, size_t i = 0)
    {
        if (i >= arr.size()) return nullptr;
        return new TreeNode(arr[i], arrayToTree(arr, 2 * i + 1), arrayToTree(arr, 2 * i + 2));
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple Encryption #3 - Turn The Bits Around
// https://www.codewars.com/kata/57d0329442e44e65e8000bb5
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::string region3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .";

void to_codes(std::string& text)
{
    for (size_t i = 0; i < text.length(); i++)
    {
        auto code = region3.find(text[i]);
        if (code == region3.npos)
            throw std::exception("unknown symbol");
        else
            text[i] = static_cast<char>(code);
    }
}

void to_chars(std::string& codes)
{
    for (size_t i = 0; i < codes.length(); i++)
        codes[i] = region3[codes[i]];
}

union cOdE {
    struct { 
        char code;
    };
    struct {
        unsigned b6 : 1;
        unsigned b5 : 1;
        unsigned b4 : 1;
        unsigned b3 : 1;
        unsigned b2 : 1;
        unsigned b1 : 1;
    };
    struct {
        unsigned tr1 : 3;
        unsigned tr2 : 3;
    };
    cOdE(char c = 0) : code(c) { };
    void part1(cOdE& from) {
        if (b5 != from.b1) { b5 = ~b5; from.b1 = ~from.b1; }
    }
    void part2() {
        b2 = ~b2;
        b4 = ~b4;
    }
    void part3() {
        char temp = tr1;
        tr1 = tr2;
        tr2 = temp;
    }
    void part4() {
        if (b1 != b2) { b1 = ~b1;  b2 = ~b2; }
        if (b3 != b4) { b3 = ~b3;  b4 = ~b4; }
        if (b5 != b6) { b5 = ~b5;  b6 = ~b6; }
    }
    void part5() {
        if (b1 != b6) { b1 = ~b1;  b6 = ~b6; }
        if (b2 != b5) { b2 = ~b2;  b5 = ~b5; }
        if (b3 != b4) { b3 = ~b3;  b4 = ~b4; }
    }
    void part6() {
        if (b1 != b3) { b1 = ~b1;  b3 = ~b3; }
    }
    char encrypt() {
        part2(); part3(); part4(); part5(); part6();
        return code;
    }
    char decrypt() {
        part6(); part5(); part4(); part3(); part2();
        return code;
    }
};

std::string encrypt3(std::string text)
{
    if (text.empty()) return text;
    to_codes(text);
    for (size_t i = 0; i < text.length(); i++)
    {
        cOdE c1(text[i]);        
        if (i < text.length() - 1)
        {
            cOdE c2(text[i + 1]);
            c1.part1(c2);
            text[i + 1] = c2.code;
        }        
        text[i] = c1.encrypt();
    }
    to_chars(text);
    return text;
}

std::string decrypt3(std::string encryptedText)
{
    if (encryptedText.empty()) return encryptedText;
    to_codes(encryptedText);
    for (size_t i = 0; i < encryptedText.length(); i++)
    {
        cOdE c2(encryptedText[i]);
        c2.decrypt();
        if (i > 0)
        {
            cOdE c1(encryptedText[i - 1]);
            c1.part1(c2);
            encryptedText[i - 1] = c1.code;
        }
        encryptedText[i] = c2.code;
    }
    to_chars(encryptedText);
    return encryptedText;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sum Strings as Numbers
// https://www.codewars.com/kata/sum-strings-as-numbers
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string sum_strings(std::string a, std::string b)
{
    std::string res;
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    size_t n = std::max(a.length(), b.length()) + 1;
    int mem = 0;
    for (size_t i = 0; i < n; i++)
    {
        int sum = mem;
        if (i < a.length()) sum += (a[i] - '0');
        if (i < b.length()) sum += (b[i] - '0');
        mem = (sum > 9) ? sum / 10 : 0;
        sum -= mem * 10;
        res.push_back('0' + sum);
    }
    while (res.back() == '0' && res.length() > 1) res.pop_back();
    std::reverse(res.begin(), res.end());
    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Insane Coloured Triangles
// https://www.codewars.com/kata/insane-coloured-triangles
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 RRGBRGBB
 RBRGBRB
 GGBRGG
 GRGBG
 BBRR
 BGR
 RB
 G
    очень долго...
    нужна математика c теоремой Люка
*/
char triangle(const std::string &row)
{
    std::cout << row << " : ";
    std::string res = row;
    while (res.length() > 1)
    {
        char a = res.at(0);
        for (size_t i = 1; i < res.length(); i++)
        {
            char b = res.at(i);
            if (a != b)
            {
                a = a == 'R' ? (b == 'G' ? 'B' : 'G') : (a == 'G' ? (b == 'B' ? 'R' : 'B') : (b == 'R' ? 'G' : 'R'));
                res[i - 1] = a;
                a = b;
            }
        }
        res.pop_back();
    }
    std::cout << res << std::endl;
    return res.at(0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Assembler interpreter (part II)
// https://www.codewars.com/kata/assembler-interpreter-part-ii
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string trim_left(const std::string& s, const std::string& delimiters = " \t") {  return s.empty() ? s : s.substr(s.find_first_not_of(delimiters)); }
std::string trim_right(const std::string& s, const std::string& delimiters = " \t") {  return s.empty() ? s : s.substr(0, s.find_last_not_of(delimiters) + 1); }
std::string trim(const std::string& s, const std::string& delimiters = " \t") {  return trim_left(trim_right(s, delimiters), delimiters); }

enum class OPER { MOV, INC, DEC, ADD, SUB, MUL, DIV, LABEL, JMP, CMP, JNE, JE, JGE, JG, JLE, JL, CALL, RET, MSG, END };

std::unordered_map<std::string, OPER> keywords = { 
    {"mov", OPER::MOV}, {"inc", OPER::INC}, {"dec", OPER::DEC}, {"add", OPER::ADD}, {"sub", OPER::SUB}, {"mul", OPER::MUL}, {"div", OPER::DIV},
    {"label", OPER::LABEL}, {"jmp", OPER::JMP}, {"cmp", OPER::CMP}, {"jne", OPER::JNE}, {"je", OPER::JE}, {"jge", OPER::JGE}, {"jg", OPER::JG}, {"jle", OPER::JLE}, {"jl", OPER::JL}, 
    {"call", OPER::CALL}, {"ret", OPER::RET}, {"msg", OPER::MSG}, {"end", OPER::END} 
};

using IP = size_t;
using LABELS = std::unordered_map<std::string, IP>;
using OPERANDS = std::vector<std::string>;
using INSTRUCTION = std::pair<OPER, OPERANDS>;
using PROGRAM = std::vector<INSTRUCTION>;
using REGISTERS = std::unordered_map<std::string, int>;
using STACK = std::stack<IP>;

void parse_operands(std::istringstream& ss, OPERANDS& ops)
{
    char ch;
    bool b_string = false;
    std::string s;
    while (ss.get(ch).good())
        switch (ch)
        {
        case '\'':
            if (b_string)
            {
                b_string = false;
                ops.push_back(s);
                s.clear();
            }
            else
            {
                b_string = true;
                s = "'";
            }
            break;
        case ',':
            if (b_string)
                s.push_back(ch);
            else
                if (!s.empty())
                {
                    ops.push_back(trim(s));
                    s.clear();
                }
            break;
        default: s.push_back(ch); break;
        }
    if (!s.empty()) ops.push_back(trim(s));
}

void parse_programm(const std::string& program, PROGRAM& prog, LABELS& labels)
{
    std::istringstream ssprog(program);
    std::string line;
    while (std::getline(ssprog, line))
    {
        line = trim(line.substr(0, line.find(';')));
        if (line.empty()) continue;
        std::istringstream ssline(line);
        std::string instr;
        ssline >> instr;
        if (instr[instr.length() - 1] == ':') 
            labels[instr.substr(0, instr.length() - 1)] = prog.size();
        else
            if (keywords.find(instr) == keywords.end())
                throw std::exception();
            else
            {
                OPERANDS ops;
                parse_operands(ssline, ops);
                prog.push_back({ keywords[instr], ops });
            }
    }
}

std::string assembler_interpreter(std::string program)
{
    PROGRAM prog;
    LABELS lbls;
    parse_programm(program, prog, lbls);
    REGISTERS regs;
    auto getVal = [&](std::string value_or_name) -> int {
        try { return std::stoi(value_or_name); }
        catch (...) { return regs[value_or_name]; }
    };
    STACK stack;
    std::string result;
    bool f_equal, f_less;
    IP ip = 0;
    while (ip < prog.size())
    {
        INSTRUCTION& instruction = prog[ip];  OPERANDS& operands = instruction.second;
        switch (instruction.first)
        {
        case OPER::MOV: regs[operands[0]] = getVal(operands[1]); break;
        case OPER::INC: ++regs[operands[0]]; break;
        case OPER::DEC: --regs[operands[0]]; break;
        case OPER::ADD: regs[operands[0]] += getVal(operands[1]); break;
        case OPER::SUB: regs[operands[0]] -= getVal(operands[1]); break;
        case OPER::MUL: regs[operands[0]] *= getVal(operands[1]); break;
        case OPER::DIV: regs[prog[ip].second[0]] /= getVal(operands[1]); break;
        case OPER::JMP: ip = lbls[operands[0]]; continue;
        case OPER::CMP: 
            f_equal = getVal(operands[0]) == getVal(operands[1]);
            f_less = getVal(operands[0]) < getVal(operands[1]);
            break;
        case OPER::JNE: if (!f_equal) { ip = lbls[operands[0]]; continue; } break;
        case OPER::JE: if (f_equal) { ip = lbls[operands[0]]; continue; } break;
        case OPER::JGE: if (!f_less || f_equal) { ip = lbls[operands[0]]; continue; } break;
        case OPER::JG: if (!f_less && !f_equal) { ip = lbls[operands[0]]; continue; } break;
        case OPER::JLE: if (f_less || f_equal) { ip = lbls[operands[0]]; continue; } break;
        case OPER::JL: if (f_less && !f_equal) { ip = lbls[operands[0]]; continue; } break;
        case OPER::CALL:
            stack.push(ip + 1);
            ip = lbls[operands[0]];
            continue;
        case OPER::MSG: for (auto o : operands) result += (o[0] == '\'') ? o.substr(1) : std::to_string(getVal(o)); break;
        case OPER::RET: 
            if (stack.empty()) return result;
            ip = stack.top();
            stack.pop();
            continue;
        case OPER::END: return result;
        }
        ip++;
    }
    return "-1";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Separate The Wheat From The Chaff
// https://www.codewars.com/kata/separate-the-wheat-from-the-chaff/cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<long long int> wheatFromChaff(std::vector<long long int> values)
{
    size_t i_from = values.size() - 1;
    for (size_t i = 0; i < i_from; i++)
        if (values.at(i) > 0)
            for (size_t j = i_from; j > i; j--) 
                if (values.at(j) < 0) { std::swap(values[i], values[j]); i_from = j - 1;  break; }
    return values;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple Fun #79: Delete a Digit
// https://www.codewars.com/kata/simple-fun-number-79-delete-a-digit/cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int deleteDigit(int n)
{    
    std::string s = std::to_string(n);
    int max = INT_MIN;
    for (size_t i = 0; i < s.length(); i++)
        max = std::max(max, std::stoi(s.substr(0, i) + s.substr(i + 1)));
    return max;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Positions Average
// https://www.codewars.com/kata/positions-average/cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//444996, 699990, 666690, 096904, 600644, 640646, 606469, 409694, 666094, 606490

double posAverage(const std::string &s)
{
    std::vector<std::string> v;
    std::istringstream ss(s);
    while (ss.good())
    {
        std::string sub;
        std::getline(ss, sub, ',');
        v.push_back(sub.substr(sub.find_first_not_of(' '))); //trim
    }
    int found = 0, all = 0;
    size_t digits = v[0].length();    
    for (size_t i = 0; i < v.size() - 1; i++)
        for (size_t j = i + 1; j < v.size(); j++, all += digits)
            for (size_t k = 0; k < digits; k++)
                if (v.at(i)[k] == v.at(j)[k]) found++;
    return found / (double)all * 100.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help the bookseller !
// https://www.codewars.com/kata/help-the-bookseller/cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class StockList
{
public:
    static std::string stockSummary(std::vector<std::string> &lstOfArt, std::vector<std::string> &categories)
    {
        std::ostringstream ss;
        for (const auto& cat : categories)
        {
            int count = std::accumulate(lstOfArt.begin(), lstOfArt.end(), 0, [&](int a, const std::string& book) -> int
            {
                if (book[0] != cat[0]) return a;
                return a + std::stoi(book.substr(book.find_first_of(' ')));
            });
            ss << " - (" << cat << " : " << count << ")";
        }
        return ss.str().substr(3);
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Rectangle into Squares
// https://www.codewars.com/kata/rectangle-into-squares
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SqInRect
{
public:
    static std::vector<int> sqInRect(int lng, int wdth)
    {
        std::vector<int> res;
        if (lng == wdth) return res;
        while (lng > 0)
        {
            if (lng < wdth) std::swap(lng, wdth);
            while (lng >= wdth)
            {
                res.push_back(wdth);
                lng -= wdth;
            }
        }
        return res;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Floating-point Approximation (II)
// https://www.codewars.com/kata/floating-point-approximation-ii/cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace App
{
    template<typename Func>
    std::vector<double> interp(Func f, double l, double u, int n)
    {
        std::vector<double> result(n);
        double d = (u - l) / n;
        for (auto& v : result)
        {
            v = std::floor(f(l) * 100) / 100;
            l += d;
        }
        return result;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Prize Draw
// https://www.codewars.com/kata/prize-draw/cpp
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Rank
{
public:
    static std::string nthRank(const std::string &st, std::vector<int> &we, int n)
    {
        if (st.empty()) return "No participants";
        if (n > we.size()) return "Not enough participants";
        std::vector<std::pair<int, std::string>> result;
        std::istringstream ss(st);
        for (int w : we)
        {
            std::string name;
            std::getline(ss, name, ',');
            int weight = name.length() + std::accumulate(name.begin(), name.end(), 0, [](int a, char ch) -> int {
                return a + (toupper(ch) - 'A' + 1);
            });
            result.push_back(std::make_pair(weight * w, name));
        }
        std::sort(result.begin(), result.end(), [](const auto& p1, const auto& p2) -> bool {
            return p1.first == p2.first ? p1.second < p2.second : p1.first > p2.first;
        });
        return result[n - 1].second;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

long matches = 0;

bool search_word(const std::vector<std::vector<char> > &board, const std::string &word, int row, int col)
{
    matches++;
    if (word.empty()) return true;
    if (row < 0 || col < 0) return false;
    if (row >= static_cast<int>(board.size()) || col >= static_cast<int>(board[0].size())) return false;
    if (board[row][col] != word[0]) return false;
    std::vector<std::vector<char> > new_board = board;
    new_board[row][col] = '\0';
    std::string new_word = word.substr(1);
    if (search_word(new_board, new_word, row, col + 1)) return true;
    if (search_word(new_board, new_word, row + 1, col + 1)) return true;
    if (search_word(new_board, new_word, row + 1, col)) return true;
    if (search_word(new_board, new_word, row + 1, col - 1)) return true;
    if (search_word(new_board, new_word, row, col - 1)) return true;
    if (search_word(new_board, new_word, row - 1, col - 1)) return true;
    if (search_word(new_board, new_word, row - 1, col)) return true;
    if (search_word(new_board, new_word, row - 1, col + 1)) return true;
    return false;
}

bool check_word(const std::vector<std::vector<char> > &board, const std::string &word)
{
    for (int row = 0; row < static_cast<int>(board.size()); row++)
        for (int col = 0; col < static_cast<int>(board[row].size()); col++)
            if (search_word(board, word, row, col))
                return true;
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


long long countOnes(int left, int right)
{
    static const int table[256] = {
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
    };
    long long result = 0;
    while (left <= right)
    {
        unsigned char* p = (unsigned char*)&left;
        result += table[p[0]];
        result += table[p[1]];
        result += table[p[2]];
        result += table[p[3]];
        left++;
    }
    return result;
}

void show_table()
{
    for (int x = 0; x < 256; x++)
    {
        int sum = 0;
        int tmp = x;
        for (int i = 0; i < sizeof(int) * 8; i++, tmp >>= 1)
            sum += (tmp & 1);
        std::cout << sum << ",";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//0   1   1   2   3   5   8   13  21  34   55  89  144   233   377   610   987   1597   2584  4181   6765
//10946 17711 28657 46368 75025 121393 196418 317811 514229 832040 1346269 2178309 3524578 5702887 9227465 14930352 24157817 39088169 63245986 102334155

long long sum_fib(int nFib, long long pp, long long p)
{
    long long res = pp + p;
    return (nFib == 2) ? res : sum_fib(nFib - 1, p, res);
}

long long fib(int nFib)
{
    if (nFib == 0) return 0;
    if (nFib == 1) return 1;
    return sum_fib(nFib, 0, 1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void print_delimiter()
{
    std::cout << std::string(80, '=') << std::endl;
}


int main()
{   
    std::vector<int> we = { 4, 2, 1, 4, 3, 1, 2 };
    std::cout << Rank::nthRank("Addison,Jayden,Sofia,Michael,Andrew,Lily,Benjamin", we, 4) << std::endl; //Benjamin
    we = { 1, 3, 5, 5, 3, 6 };
    std::cout << Rank::nthRank("Elijah,Chloe,Elizabeth,Matthew,Natalie,Jayden", we, 2) << std::endl; //Matthew

    auto lambda = [](double x) { return x; };
    App::interp(lambda, 0.0, 15.0, 9);

    SqInRect::sqInRect(5, 6);

    std::vector<std::string> art = { "BBAR 150", "CDXE 515", "BKWR 250", "BTSQ 890", "DRTY 600" };
    std::vector<std::string> cd = { "A", "B", "C", "D" };
    std::cout << StockList::stockSummary(art, cd) << std::endl;
    print_delimiter();

    posAverage("444996, 699990, 666690, 096904, 600644, 640646, 606469, 409694, 666094, 606490");

    deleteDigit(1001);

    wheatFromChaff({ -7,-35,-46,-22,46,43,-44,-14,34,-5,-26 }); // -7,-35,-46,-22,-26,-5,-44,-14,34,43,46

    std::string
    programm = R"(
mov   a, 5
mov   b, a
mov   c, a
call  proc_fact
call  print
end

proc_fact:
    dec   b
    mul   c, b
    cmp   b, 1
    jne   proc_fact
    ret

print:
    msg   a, '! = ', c ; output text
    ret
)";
    assembler_interpreter(programm);

    if (multiply("0", "30") != "0")
        std::cout << "error mul\n";
    if (multiply("1020303004875647366210", "2774537626200857473632627613") != "2830869077153280552556547081187254342445169156730")
        std::cout << "error mul\n";

    std::vector<std::vector<int>> m = {
        { 0,  1,  2,  3,  4,  5},
        {19, 20, 21, 22, 23,  6},
        {18, 31, 32, 33, 24,  7},
        {17, 30, 35, 34, 25,  8},
        {16, 29, 28, 27, 26,  9},
        {15, 14, 13, 12, 11, 10},
    };
    auto rrr = snail(m);

//    for (int i = 0; i < 100; i++)
        std::cout << fib(65)*fib(66) << std::endl;

    auto vv = add(1)(2)(3);
    std::cout << vv << std::endl;

    print_delimiter();
    std::cout << findOdd2({ 1, 1, 2, 3, 2, 3, 4, 5, 6, 7, 3, 4 , 5, 6, 3 }) << std::endl;
    std::cout << findOdd3({ 1, 1, 2, 3, 2, 3, 4, 5, 6, 7, 3, 4 , 5, 6, 3 }) << std::endl;

    print_delimiter();
    std::cout << RGBToHex::rgb3(255, 100, 0) << std::endl;  //FF6400
    std::cout << RGBToHex::rgb3(-155, 100, 0) << std::endl; //006400
    std::cout << RGBToHex::rgb3(285, 300, 0) << std::endl; //FFFF00
    std::cout << RGBToHex::rgb3(15, 10, 0) << std::endl;   //0F0A00
    std::cout << RGBToHex::rgb3(1, 2, 15) << std::endl;    //01020F 

    print_delimiter();
    std::cout << valid_braces("(){}[]") << std::endl;
    std::cout << valid_braces("([{([{}])}])") << std::endl;
    std::cout << valid_braces("(}") << std::endl;
    std::cout << valid_braces("") << std::endl;
    std::cout << valid_braces("[") << std::endl;
    std::cout << valid_braces("]") << std::endl;

    print_delimiter();
    std::cout << longest_palindrome("a") << std::endl;
    std::cout << longest_palindrome("aa") << std::endl;
    std::cout << longest_palindrome("baa") << std::endl;
    std::cout << longest_palindrome("aab") << std::endl;
    std::cout << longest_palindrome("zyabyz") << std::endl;
    std::cout << longest_palindrome("baabcd") << std::endl;
    std::cout << longest_palindrome("baablkj12345432133d") << std::endl;

    print_delimiter();
    std::vector<std::string> v = wave("hello, world");
    std::copy(std::cbegin(v), std::cend(v), std::ostream_iterator<std::string>(std::cout, "\n"));

    print_delimiter();
    std::cout << RomanNumeralsEncoder(482) << std::endl; //CDLXXXII
    std::cout << RomanNumeralsEncoder(1990) << std::endl;//MCMXC
    std::cout << RomanNumeralsEncoder(1875) << std::endl;//MD
    std::cout << RomanNumeralsEncoder(4472) << std::endl;
    if (from_roman(RomanNumeralsEncoder(333)) != 333)
        std::cout << "from_roman error\n";
    if (from_roman(RomanNumeralsEncoder(1975)) != 1975)
        std::cout << "from_roman error\n";
    if (from_roman(RomanNumeralsEncoder(1010)) != 1010)
        std::cout << "from_roman error\n";
    if (from_roman(RomanNumeralsEncoder(1999)) != 1999)
        std::cout << "from_roman error\n";

    print_delimiter();
    std::cout << my_first_interpreter("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.+++++++++++++++++++++++++++++.+++++++..+++.+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.+++++++++++++++++++++++++++++++++++++++++++++++++++++++.++++++++++++++++++++++++.+++.++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.") << std::endl;
    std::cout << my_first_interpreter("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ + . + . + . + . + . + . + . + . + . + . + . + . + . + . + . + . + . + . + . + . + . + . + . + . + . + .") << std::endl;

    print_delimiter();
    auto v_int = xbonacci({ 0, 1 }, 10); // {0, 1, 1, 2, 3, 5, 8, 13, 21, 34}
    std::copy(v_int.begin(), v_int.end(), std::ostream_iterator<int>(std::cout, " "));  std::cout << std::endl;
    v_int = xbonacci({ 0, 2, 2 }, 8); // {0, 2, 2, 4, 8, 14, 26, 48}
    std::copy(v_int.begin(), v_int.end(), std::ostream_iterator<int>(std::cout, " "));  std::cout << std::endl;

    print_delimiter();
    std::cout << findMissing({ -3, -4, -5, -6, -8, -9, -10, -11, -12 }) << std::endl; //-7

    print_delimiter();
    std::cout << duplicateCount("abcde") << std::endl; //0
    std::cout << duplicateCount("aabBcde") << std::endl; //2
    std::cout << duplicateCount("indivisibility") << std::endl; //1
    std::cout << duplicateCount("aA11") << std::endl; //2

    print_delimiter();

    std::vector<std::vector<char> > test_board = { 
        {'E','A','R','A'},
        {'N','L','E','C'},
        {'I','A','I','S'},
        {'B','Y','O','R'}
    };
    std::cout << check_word(test_board, "RSCAREIOYBAILNEA") << std::endl;
    std::cout << matches << std::endl;

    print_delimiter();
    std::vector<std::string> arr1 = { "arp", "live", "strong" };
    std::vector<std::string> arr2 = { "lively", "alive", "harp", "sharp", "armstrong" };
    auto r = WhichAreIn::inArray(arr1, arr2);
    std::copy(r.begin(), r.end(), std::ostream_iterator<std::string>(std::cout, " "));  std::cout << std::endl;

    print_delimiter();
    std::cout << pig_it("This is my string") << std::endl;
    std::cout << pig_it("Pig latin is cool") << std::endl;
    std::cout << pig_it("Acta est fabula") << std::endl;

    print_delimiter();
    std::cout << uint32_to_ip(2154959208) << std::endl;

    print_delimiter();
    std::cout << poohbear("+LTQIITTIWP-E") << std::endl;

    //print_delimiter();   
    std::vector<std::string> program{ "mov a -5", "mov b 7", "mov c a", "inc a", "inc b", "inc c", "jnz c -3" };
    auto res = assembler(program);

    print_delimiter();
    std::cout << SimpleEncryption::encrypt("Business") << std::endl;
    std::cout << SimpleEncryption::decrypt("&61kujla") << std::endl;


    //print_delimiter();
    std::vector<std::vector<int>> Ma = { {1, 2}, {3, 2} };
    std::vector<std::vector<int>> Mb = { {3, 2}, {1, 1} };
    std::vector<std::vector<int>> Mr = matrix_multiplication(Ma, Mb, 2);

    print_delimiter();
    std::string s_input;
    s_input.append(1, (char)10);
    std::cout << brainLuck(",>+>>>>++++++++++++++++++++++++++++++++++++++++++++>++++++++++++++++++++++++++++++++<<<<<<[>[>>>>>>+>+<<<<<<<-]>>>>>>>[<<<<<<<+>>>>>>>-]<[>++++++++++[-<-[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<[>>>+<<<-]>>[-]]<<]>>>[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<+>>[-]]<<<<<<<]>>>>>[++++++++++++++++++++++++++++++++++++++++++++++++.[-]]++++++++++<[->-<]>++++++++++++++++++++++++++++++++++++++++++++++++.[-]<<<<<<<<<<<<[>>>+>+<<<<-]>>>>[<<<<+>>>>-]<-[>>.>.<<<[-]]<<[>>+>+<<<-]>>>[<<<+>>>-]<<[<+>-]>[<+>-]<<<-]", s_input) << std::endl;

    print_delimiter();
    std::cout << countOnes(4, 7) << std::endl;
    show_table();
 
    print_delimiter();
    arr1 = { "NORTH", "SOUTH", "SOUTH", "EAST", "WEST", "NORTH", "WEST" };
    arr2 = DirReduction::dirReduc(arr1);
    std::copy(arr2.begin(), arr2.end(), std::ostream_iterator<std::string>(std::cout, " "));  std::cout << std::endl;

    std::vector<int> arrInt1 = { 9, 99, 999 };
    std::vector<int> arrInt2 = Dinglemouse::sort(arrInt1);

    print_delimiter();
    std::cout << WeightSort::orderWeight("2000 10003 1234000 44444444 9999 11 11 22 123") << std::endl; // "11 11 2000 10003 22 123 1234000 44444444 9999"

    scramble("rkqodlw", "world");
    scramble("cedewaraaossoqqyt", "codewars");

    unsigned int sudoku1[9][9] = { 
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9} 
    };
    unsigned int sudoku2[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        { 6, 7, 2, 1, 9, 0, 3, 4, 8 },
        { 1, 0, 0, 3, 4, 2, 5, 6, 0 },
        { 8, 5, 9, 7, 6, 1, 0, 2, 0 },
        { 4, 2, 6, 8, 5, 3, 7, 9, 1 },
        { 7, 1, 3, 9, 2, 4, 8, 5, 6 },
        { 9, 0, 1, 5, 3, 7, 2, 1, 4 },
        { 2, 8, 7, 4, 1, 9, 6, 3, 5 },
        { 3, 0, 0, 4, 8, 1, 1, 7, 9 }
    };    
    if (!validSudoku(sudoku1))
        std::cout << "false\n";
    if (!validSudoku(sudoku2))
        std::cout << "false\n";

    TreeNode* node =  Solution::arrayToTree({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
}
