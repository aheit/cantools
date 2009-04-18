#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <dbcReader.h>
#include <dbcWriter.h>

int
main(int argc, char **argv)
{
  dbc_t *dbc;
  char *const filename = (argc>1 ? argv[1] : NULL);

  if(NULL != (dbc = dbc_read_file(filename))) {
    FILE *dbcout;

    if(NULL != (dbcout = fopen("copy.dbc","w"))) {
      dbc_write_file(dbcout, dbc);
      fclose(dbcout);
    }
    dbc_free(dbc);
  }

  return 0;
}
