#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <syslog.h>
#include "pdu.h"
#include "smsd_cfg.h"
#include "logging.h"
#include "charset.h" // required for conversions of partial text content.
#include "extras.h"

#define BUFSIZE 1024
#define NODE "node"
#define SCRIPT "/usr/local/bin/cdma.js"

int run_external(char *cmd, char *pdu) {
    char buf[BUFSIZE];
    FILE *fp;

    writelogfile(LOG_DEBUG, 0, "Run command(%s)!", cmd);
    if ((fp = popen(cmd, "r")) == NULL) {
        writelogfile(LOG_CRIT, 0, "Error opening command(%s)!", cmd);
        return -1;
    }

    while (fgets(buf, BUFSIZE, fp) != NULL) {
        strcpy(pdu, buf);
    }

    if (pclose(fp)) {
        writelogfile(LOG_CRIT, 0, "Error close command(%s)!", cmd);
        return -1;
    }

    return 0;
}

void make_cdma_pdu(
  char *number,
  char *message,
  int messagelen,
  char *pdu
)
{
    char cmd[BUFSIZE];
    char msg[BUFSIZE];

    memset(msg,0,sizeof(msg));
    strncpy(msg, message, messagelen);
    sprintf(cmd, "%s %s %s \"%s\"", NODE, SCRIPT, number, msg);
    run_external(cmd, pdu);
}
