#include "shell.h"

ssize_t input_buf(info_t *info, char **buf, size_t *len) {
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len) {
        free(*buf);
        *buf = NULL;

        r = _getline(info, buf, &len_p);

        if (r > 0 && (*buf)[r - 1] == '\n') {
            (*buf)[r - 1] = '\0';
            r--;
            info->linecount_flag = 1;
            *len = r;
            info->cmd_buf = buf;
        }
    }
    return r;
}

ssize_t get_input(info_t *info) {
    static char *buf;
    static size_t i, len;
    ssize_t r = 0;
    char **buf_p = &(info->args), *p;

    _putchar(BUF_FLUSH);
    r = input_buf(info, &buf, &len);
    if (r == -1)
        return -1;
    if (len) {
        p = buf + i;
        i = len = 0;
        *buf_p = p;
        return _strlen(p);
    }
    *buf_p = buf;
    return r;
}

ssize_t read_buf(info_t *info, char *buf, size_t *i) {
    ssize_t r = 0;

    if (*i)
        return 0;
    r = read(info->readfd, buf, BUF_SIZE);
    if (r >= 0)
        *i = r;
    return r;
}

int _getline(info_t *info, char **ptr, size_t *length) {
    static char buf[BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0;
    char *p = *ptr, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        *length = 0;
    if (i == len)
        i = len = 0;

    r = read_buf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return -1;

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, *length, *length ? *length + k : k + 1);
    if (!new_p)
        return (p ? free(p), -1 : -1);

    if (*length)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);

    *length += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = *length;
    *ptr = p;
    return *length;
}

