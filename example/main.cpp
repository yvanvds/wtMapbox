#include "mapboxApplication.h"

using namespace Wt;

WApplication * createApplication(const WEnvironment & env) {
  return new mapboxApplication(env);
}

int main(int argc, char **argv) {
  try {
    WServer server(argc, argv, WTHTTP_CONFIGURATION);
    server.addEntryPoint(Application, createApplication);
    server.run();
  }
  catch (WServer::Exception & e) {
    std::cerr << e.what() << std::endl;
  }
  catch (std::exception & e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}