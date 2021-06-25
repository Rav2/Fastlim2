#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include<string>
#include<vector>
#include<iostream>
#include "FastlimConfig.h"

class InputParser{
    public:
        InputParser (int &argc, char **argv)
        {
            this->programName = argv[0];
            if(programName[0] == '.' and programName[1] == '/');
                programName = programName.substr(2);
            for (int i=1; i < argc; ++i)
                this->tokens.push_back(std::string(argv[i]));
        }
        const std::string& getCmdOption(const std::string &option) const
        {
            std::vector<std::string>::const_iterator itr;
            itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
        }
        bool cmdOptionExists(const std::string &option) const
        {
            return std::find(this->tokens.begin(), this->tokens.end(), option)
                   != this->tokens.end();
        }
        void printHelp() const
        {
            printVersion();
            std::cout << "Usage: ./" << programName << " [-hv] input.slha" << std::endl;
            std::cout
            << "-h --help\t\tprint help" << std::endl 
            << "   --verbose\t\ttprint more output" << std::endl
            << "-v --version\t\tprint version" << std::endl;
        }
        void printVersion() const
        {
            std::cout << "FASTLIM" << " Version " 
            << Fastlim_VERSION_MAJOR << "."
            << Fastlim_VERSION_MINOR << std::endl;

        }
    private:
        std::vector <std::string> tokens;
        std::string programName;
};

#endif