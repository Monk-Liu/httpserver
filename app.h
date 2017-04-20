#include "httprequest.h"
#include "httpresponse.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class Application{

public:
    Application(HttpRequest &, HttpResponse &);

    int handler(HttpRequest &, HttpResponse &);
};

