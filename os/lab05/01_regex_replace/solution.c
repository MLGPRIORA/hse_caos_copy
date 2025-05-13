#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <pattern> <text> <replacement>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pattern     = argv[1];
    const char *text        = argv[2];
    const char *replacement = argv[3];

    regex_t regex;
    int comp_status = regcomp(&regex, pattern, REG_EXTENDED);
    if (comp_status != 0) {
        char errbuf[256];
        regerror(comp_status, &regex, errbuf, sizeof errbuf);
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return EXIT_FAILURE;
    }

    size_t text_len = strlen(text);
    size_t repl_len = strlen(replacement);

    size_t out_cap = text_len + 1;
    char  *output  = malloc(out_cap);
    if (!output) {
        perror("malloc");
        regfree(&regex);
        return EXIT_FAILURE;
    }

    size_t out_len      = 0;
    const char *cursor  = text;
    regmatch_t match;

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t prefix_len = (size_t)match.rm_so;
        size_t required   = out_len + prefix_len + repl_len + 1;
        if (required > out_cap) {
            out_cap = required * 2;
            char *tmp = realloc(output, out_cap);
            if (!tmp) {
                perror("realloc");
                free(output);
                regfree(&regex);
                return EXIT_FAILURE;
            }
            output = tmp;
        }
        memcpy(output + out_len, cursor, prefix_len);
        out_len += prefix_len;

        memcpy(output + out_len, replacement, repl_len);
        out_len += repl_len;

        size_t match_len = (size_t)(match.rm_eo - match.rm_so);
        if (match_len == 0) {
            if (cursor[match.rm_eo] == '\0') {
                break;
            }
            if (out_len + 2 > out_cap) {
                out_cap = (out_len + 2) * 2;
                char *tmp = realloc(output, out_cap);
                if (!tmp) {
                    perror("realloc");
                    free(output);
                    regfree(&regex);
                    return EXIT_FAILURE;
                }
                output = tmp;
            }
            output[out_len++] = cursor[match.rm_eo];
            cursor += match.rm_eo + 1;
        } else {
            cursor += match.rm_eo;
        }
    }

    size_t tail_len  = strlen(cursor);
    size_t required  = out_len + tail_len + 1;
    if (required > out_cap) {
        char *tmp = realloc(output, required);
        if (!tmp) {
            perror("realloc");
            free(output);
            regfree(&regex);
            return EXIT_FAILURE;
        }
        output = tmp;
        out_cap = required;
    }
    memcpy(output + out_len, cursor, tail_len);
    out_len += tail_len;
    output[out_len] = '\0';

    printf("%s\n", output);

    free(output);
    regfree(&regex);
    return EXIT_SUCCESS;
}
