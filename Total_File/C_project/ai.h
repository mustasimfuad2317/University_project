#include <stdio.h>
#include <stdlib.h>
#include <string.h>



static char *sanitize(const char *in)
{
    char *out = malloc(8192);
    char *p = out;

    while (*in && (p - out) < 8190) {
        if (*in == '"') { *p++='\\'; *p++='"'; }
        else if (*in == '\'') { *p++='\\'; *p++='\''; }
        else if (*in == '\n' || *in == '\r') { *p++=' '; }
        else { *p++ = *in; }
        in++;
    }
    *p = 0;
    return out;
}


/* Call Ollama API via system() + curl and return concatenated assistant text */
char *ollama_chat_cli(const char *input)
{
    /* Read aiinfo.txt */
    FILE *f = fopen("aiinfo.txt", "r");
    if (!f) return NULL;

    char sys_raw[4096] = {0};
    fread(sys_raw, 1, sizeof(sys_raw)-1, f);
    fclose(f);

    char *system_msg = sanitize(sys_raw);
    char *user_msg   = sanitize(input);

    char command[8192];
    snprintf(command, sizeof(command),
        "curl -s -X POST http://localhost:11434/api/chat "
        "-H \"Content-Type: application/json\" "
        "-d \"{\\\"model\\\":\\\"llama3.2:latest\\\","
        "\\\"messages\\\":["
        "{\\\"role\\\":\\\"system\\\",\\\"content\\\":\\\"Your name is Taskbot\\\"},"
        "{\\\"role\\\":\\\"user\\\",\\\"content\\\":\\\"%s %s\\\"}"
        "]}\"",
        system_msg, user_msg);

    free(system_msg);
    free(user_msg);

    FILE *fp = popen(command, "r");
    if (!fp) return NULL;

    char line[4096];
    char *result = calloc(8192, 1);

    while (fgets(line, sizeof(line), fp)) {
        char *p = strstr(line, "\"content\":\"");
        if (p) {
            p += 11;
            char *end = strchr(p, '"');
            if (end) {
                strncat(result, p, end - p);
                strcat(result, " ");
            }
        }
    }

    pclose(fp);

    if (!*result) {
        free(result);
        return NULL;
    }

    return result;
}
