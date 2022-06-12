#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <sstream>
#include <iomanip>
#include "json11/json11.hpp"
// #include <bits/stdc++.h>
using namespace std;

string url_encode(const string &value) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (auto c : value) {
        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << uppercase;
        escaped << '%' << setw(2) << int((unsigned char) c);
        escaped << nouppercase;
    }

    return escaped.str();
}
// exec cmd via pipe
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}
std::string makeCurlCmd(string src, string target, string text)
{
    // std::string fmt = R"(curl -X POST "{}" -d "sl={}&tl={}&q={}")";
    stringstream ss;
    ss << "curl -sS -X POST \"https://translate.google.com/translate_a/single?client=at&dt=t&dt=ld&dt=qca&dt=rm&dt=bd&dj=1&ie=UTF-8&oe=UTF-8&inputm=2&otf=2&iid=1dd3b944-fa62-4b55-b330-74909a99969e\"";
    ss << " -d \"sl=" << src << "&tl=" << target;
    ss << "&q=" << url_encode(text) << "\"";
    return ss.str();
}
std::string parseTranslation(string& response)
{
    string err;
    auto result = json11::Json::parse(response, err);
    if (err.empty()) {
        auto sentences = result["sentences"].array_items();
        return sentences[0]["trans"].string_value();
    }
    return "error: " + err;
}
// json parse
int main(int argc, char *argv[])
{
    if (argc < 3) {
        cout << "usage: translate.exe <source-language> <target-language> <text-to-translate>\n";
        exit(-1);
    }
    auto cmd = makeCurlCmd(argv[1], argv[2], argv[3]);
    auto out = exec(cmd.c_str());
    cout << parseTranslation(out);
}
