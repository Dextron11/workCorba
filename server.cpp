#include <OB/CORBA.h>
#include "upTime_skel.h"
#include <fstream>

#include <iostream>

class upTime_impl : public virtual POA_upTime {
public:
    virtual void getUpTime(CORBA::Float_out systemHasBeenUp,
                           CORBA::Float_out systemHasSpentIdle)
    throw(CORBA::SystemException);
};

void  upTime_impl::getUpTime(CORBA::Float_out systemHasBeenUp,CORBA::Float_out systemHasSpentIdle)
    throw(CORBA::SystemException) {
    std::ifstream uptime ("/proc/uptime");
    if (!uptime) {
        std::cerr << "Unable to open /proc/uptime" <<std::endl;
        throw 0;
    }

    uptime  >> systemHasBeenUp >>  systemHasSpentIdle;
    uptime .close();
}

int main(int argc, char *argv[]) {
    try {

        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);


        CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var poa = PortableServer::POA::_narrow(obj.in());
        PortableServer::POAManager_var mgr = poa->the_POAManager();
        mgr->activate();
        upTime_impl uptime;

        CORBA::uptime_var uptimeRef = uptime._this();


        CORBA::String_var str = orb->object_to_string(uptimeRef.in());

        std::ofstream iorFile("ior.dat");
        if (!iorFile) {
            std::cerr << "Failed to open ior.dat file"
                      << std::endl;
            throw 0;
        }

        iorFile << str.in() << std::endl;
        iorFile.close();

        orb->run();
    }
    catch (const CORBA::Exception &) {
        std::cerr << "Uncaught CORBA exception" << std::endl;
        return 1;
    }
    return 0;
}