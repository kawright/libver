#include "ver.h"

#include <cast.h>
#include <calen.h>
#include <chbuf.h>
#include <core.h>
#include <err.h>
#include <fileio.h>
#include <mem.h>

#include <string.h>

Void dflt_ver(Ver *ver) {
    strcpy(ver->ver_no, "1.0");
    ver->build_no = 1;
    touch_ver_date(ver);
    touch_ver_build_date(ver); 
}

Void init_ver(Ver *ver) {
    ver->ver_no[0]          = '\0';
    ver->ver_date[0]        = '\0';
    ver->build_no           = 0;
    ver->build_date[0]      = '\0';
}

Void ld_ver_from_file(Ver *ver, Ch *path, Err *err) {
    Ch      *file_data      = NIL;
    Ch      temp_str[20];
    ChBuf   ch_buf;
    init_ch_buf(&ch_buf);

    // Read the .ver file
    read_file_to_str(path, &file_data, err);
    if (is_err(err))
        return;
    
    // Use a 'ChBuf' to scan the lines of the file
    ld_ch_buf_from_str(&ch_buf, file_data);
    scan_ch_buf_until(&ch_buf, ver->ver_no, '\n', err);
    if (is_err(err)) {
        THROW(err, ErrCode_DATA, "Could not parse .ver file %s", path)
        return;
    }
    scan_ch_buf_until(&ch_buf, ver->ver_date, '\n', err);
    if (is_err(err)) {
        THROW(err, ErrCode_DATA, "Could not parse .ver file %s", path)
        return;
    }
    scan_ch_buf_until(&ch_buf, temp_str, '\n', err);
    if (is_err(err)) {
        THROW(err, ErrCode_DATA, "Could not parse .ver file %s", path)
        return;
    }
    ver->build_no = str_to_i16(temp_str, 10, err);
    if (is_err(err)) {
        THROW(err, ErrCode_DATA, "Could not parse .ver file %s", path)
        return;
    }
    scan_ch_buf_until(&ch_buf, ver->build_date, '\n', err);
    if (is_err(err)) {
        THROW(err, ErrCode_DATA, "Could not parse .ver file %s", path)
        return;
    }

    // A proper .ver file ends with a single new-line character
    if (!((read_ch_buf(&ch_buf) == '\n') && 
            (peek_ch_buf(&ch_buf, NIL) == '\0'))) {
        THROW(err, ErrCode_DATA, "Could not parse .ver file %s", path)
        return;
    }
}

Void set_ver_no(Ver *ver, Ch *ver_no) {
    strncpy(ver->ver_no, ver_no, VER_NO_BUF_SZ - 1);
}

Void touch_ver_date(Ver *ver) {
    get_curr_iso_time(ver->ver_date);
}

Void touch_ver_build_date(Ver *ver) {
    get_curr_iso_time(ver->build_date);
}

Void write_ver_to_file(Ver *ver, Ch *path, Err *err) {
    write_fmt_to_file(path, "%s\n%s\n%d\n%s\n\n", err, ver->ver_no, 
        ver->ver_date, ver->build_no, ver->build_date);
}
