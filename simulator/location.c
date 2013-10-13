#ifndef location_c
#define location_c
#include "location.h"

void location_save(location *l, FILE *file) {
 int k;
 fprintf(file,"%f,%f,",l->p,l->f);
 for(k = 0; k < AG_SIGNAL_NUMB; k++) {
  fprintf(file,"%f,",l->s[k]);
 } 
 fprintf(file," ");
}

#endif
