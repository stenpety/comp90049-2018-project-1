//
// Created by Petr Stenin on 01/04/2018.
//

#include "GlobalConst.h"
namespace gcnst {

    std::string GConst::addr_msspl;
    std::string GConst::addr_crct;
    std::string GConst::addr_dict;

    GConst::GConst() = default;

    void GConst::config(const char *addr_conf) {
        std::ifstream fconfig (addr_conf);

        getline(fconfig, addr_msspl);
        getline(fconfig, addr_crct);
        getline(fconfig, addr_dict);

        std::cout << "Configuration done!" << std::endl;
    }
}

//