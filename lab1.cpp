#include <iostream>
#include <string>
#include <Windows.h>

#include "base64.h"

void check()
{
    LPCWSTR ODS = L"This program cannot be run under the debugger\n";
    if (IsDebuggerPresent())::OutputDebugString(ODS);
    if (IsDebuggerPresent()) exit(1);
}

struct Data 
{
    char* data;
    char* crypt;
    bool valid;
    bool changed;
};

std::vector<std::string> VH =
{
    "{hRh'Sgyv2o-n1s;z1Rgn+^^", 
    "(1g7%xs;zyn=(SZ={hf<nb^^"
};

extern int flag_passed = 0;

class Init 
{
private:
    std::uint8_t blocksize; 
    char* msg;
    Data input;

    bool isValid()
    {
        if (this->input.crypt == VH[0] || this->input.crypt == VH[1])
        {
            flag_passed++;
            return true;
        }
        else return false;
    }

    void compress(std::string& s)
    {
        std::string ret = "";
        int counter = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (ret.size() && ret.back() == s[i])
            {
               ++counter;
               if (i == (s.size() - 1))
               {
                   ret += std::to_string(counter + 1);
               }
                continue;
            }
            else if (counter > 0 || i == (s.size() - 1))
            {
                ret += std::to_string(counter + 1);
                counter = 0;
            }
            ret += s[i];
        }
        s = ret;
        this->input.changed = true;
    }

    std::vector<BYTE> string2bytevec(std::string s)
    {
        std::vector<BYTE> returnvec(s.begin(), s.end());
        return returnvec;
    }

    std::string bytevec2string(std::vector<BYTE> vb)
    {
        std::string s(vb.begin(), vb.end());
        return s;
    }

    void complete()
    {
        std::string str = msg;
        std::size_t incompleted = strlen(msg) - int(strlen(msg) / 4) * blocksize;
        for (int i = 0; i < incompleted; i++) { str += "a"; }
        compress(str);
        std::vector<BYTE> data_for_encrypt(str.begin(), str.end());
        if (blocksize == 4) 
        {
            str = base64_encode(&data_for_encrypt[0], data_for_encrypt.size()); 
            data_for_encrypt = string2bytevec(str);
        }
        else 
        {
            for (int i = 0; i < blocksize; i++) 
            {
                str = base64_encode(&data_for_encrypt[0], data_for_encrypt.size());
                data_for_encrypt = string2bytevec(str);
            }
        }
        str = bytevec2string(data_for_encrypt);

        std::string tmp = "";
        for (const auto& item : str) 
        {
            tmp += char(int(item % 93 + 33));
        }
        str = tmp;

        std::copy(str.begin(), str.end(), msg);
        msg[str.size()] = '\0';

        this->input.crypt = msg;

        if (isValid()) 
        {
            std::cout << "Correct!\n";
            if (flag_passed == 2) 
            {
                std::cout << "Login and Password are correct!\n";
            }
        }
        else
        {
            std::cout << "Incorrect login/password\nExit\n";
            exit(-1);
        }
    }

public:
    Init(char par[])
    {
        msg = par;
        input.data = msg;
        input.changed = false;
        strlen(par) / 4.0 - int(strlen(par) / 4) == 0 ? this->blocksize = 4 : this->blocksize = strlen(par) % 4;
        complete();
    }
};

int main()
{
    check();
    char lbuffer[256], pbuffer[256];
    std::cout << "Input for login : ";
    std::cin >> lbuffer;
    Init l(lbuffer);
    std::cout << "Input for password : ";
    std::cin >> pbuffer;
    Init p(pbuffer);

    return 0;
}