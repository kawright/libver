/* Project version metadata */

#ifndef VER_H
#define VER_H

#include <core.h>
#include <err.h>

/* ----- CONSTANTS ----- */

#define VER_NO_BUF_SZ               32
#define VER_DATE_BUF_SZ             26
#define VER_PROJ_NAME_BUF_SZ        64
#define VER_PROJ_DESC_BUF_SZ        128

/* ----- FUNCTIONS ----- */

/* Stores all fields in a '.ver' file. */
typedef struct STRUCT_VER {

    /* The version number */
    Ch      ver_no[VER_NO_BUF_SZ];

    /* The date of the last version update */
    Ch      ver_date[VER_DATE_BUF_SZ];

    /* The build number */
    U32     build_no;

    /* The date of the last build */
    Ch      build_date[VER_DATE_BUF_SZ];

    /* The name of the project */
    Ch      proj_name[VER_PROJ_NAME_BUF_SZ];

    /* A description of the project */
    Ch      proj_desc[VER_PROJ_DESC_BUF_SZ];
} Ver;

/* Set a 'Ver' to default values (not the init values, but those that are
assigned when a new '.ver' file is create). */
Void dflt_ver(Ver *ver);

/* Initialize a 'Ver' */
Void init_ver(Ver *ver);

/* Load a 'Ver' from a '.ver' file. Throws IO, DATA. */
Void ld_ver_from_file(Ver *ver, Ch *path, Err *err);

/* Set the 'proj_desc' field of a 'Ver'. */
Void set_ver_proj_desc(Ver *ver, Ch *desc);

/* Set the 'proj_name' field of a 'Ver'. */
Void set_ver_proj_name(Ver *ver, Ch *name);

/* Set the 'ver_no' field of a 'Ver'. */
Void set_ver_no(Ver *ver, Ch *ver_no);

/* Update the 'ver_date' field of a 'Ver'. */
Void touch_ver_date(Ver *ver);

/* Update the 'build_date' field of a 'Ver'. */
Void touch_ver_build_date(Ver *ver);

/* Write a 'Ver' to a '.ver' file. Throws IO. */
Void write_ver_to_file(Ver *ver, Ch *path, Err *err);

#endif
