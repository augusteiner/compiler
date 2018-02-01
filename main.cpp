#include "kaleidoscope.yy.hpp"
#include "driver.hpp"

int main(int argc, char **argv)
{
  driver* context = nullptr;

  if (argc > 1)
    context = new driver(argv[1]);
  else
    context = new driver();

  yy::parser parser(*context);
  context->scan_begin();
  int result = parser.parse();
  context->scan_end();

  delete context;

  return result;
}

