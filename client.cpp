
#include <string>
#include <fstream>
#include <iostream>
#include "upTime.h"

int main(int argc, char *argv[]) {
    try {

        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

        ifstream iorFile("ior.dat");
        if (!iorFile) {
            std::cerr << "Failed to open ior.dat file" << std::endl;
            throw 0;
        }
        std::string iorString;
        iorFile >> iorString;
        iorFile.close();


        CORBA::Object_var obj = orb->string_to_object(iorString.c_str());
        if (CORBA::is_nil(obj.in())) {
            std::cerr << "Nil server reference" << std::endl;
            throw 0;
        }

        upTime_var uptime = upTime::_narrow(obj.in());
        if (CORBA::is_nil(uptime.in())) {
            std::cerr << "Reference string does not refer to a CPULoad server" <<std:: endl;
            throw 0;
        }


        CORBA::Float systemHasBeenUp;
        CORBA::Float systemHasSpentIdle;
        uptime->getUpTime(systemHasBeenUp, systemHasSpentIdle);


        std::cout << "Time:\n"
                  << "   system has been up: " << systemHasBeenUp
                  << "   system has spent idle: " << systemHasSpentIdle<<std::endl;
    }
    catch (const CORBA::Exception &x) {
        std::cerr << "Uncaught CORBA exception" << std::endl;
        return 1;
    }
    catch (...) {
        return 1;
    }
    return 0;
}
