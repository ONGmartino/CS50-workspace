#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool parse(const char* line, char* abs_path, char* query)
{
    // allocate method, request, version
    
    char* method = malloc(sizeof(char) * (strlen(line)+1));
    char* request = malloc(sizeof(char) * (strlen(line)+1));
    char* version = malloc(sizeof(char) * 20);
        if (!method || !request || !version ) return false;
    
    //request_line_is_valid

        //crlf_check
        if ((strstr(line, "\r\n") + strlen("\r\n"))[0] != '\0') return false;
  
        // space_count
        unsigned int count = 0;
        for (int i = 0, length = strlen(line); i < length; i++)
            if (line[i] == ' ') count++;
        if (count != 2) return false;

        //method_check
        char* token = malloc(sizeof(char) * strlen(line) + 1);

            //get_method_header
            strcpy(token, line);
            strchr(token, ' ')[0] = '\0';

        const char* valid_methods = "OPTIONS GET HEAD POST PUT DELETE TRACE CONNECT";
        if (strstr(valid_methods, token) == NULL) return false;
        free(token);
        
    // extract the headers from the request line
    
        //get_method_header
        strcpy(method, line);
        strchr(method, ' ')[0] = '\0';
    
        //get_request_header
        strcpy(request, strchr(line, ' ') + 1);
        strrchr(request, ' ')[0] = '\0';  
    
        //get_version_header
        strcpy(version, strrchr(line, ' ') + 1);
        strstr(version, "\r\n")[0] = '\0';
    
    // ensure headers meet requirments
    
        //validate_version_header
        if (strcmp(version, "HTTP/1.1") != 0) {error(505); return false;}

        //validate_method_header
        if (strcmp(method, "GET") != 0) {error(405); return false;}

        //validate_request_header
        if (request[0] != '/') {error(501);return false;}
        if (strchr(request, '\"')) {error(400);return false;}
    
    // seperate the absolute path and the query from request

        //get_abs_path
        strcpy(abs_path, request);
        if (strchr(abs_path, '?')) strchr(abs_path, '?')[0] = '\0';
        else abs_path[strlen(abs_path) / sizeof(abs_path[0])] = '\0';
    
        //get_query
        if (strchr(request, '?')) 
        {
            strcpy(query, strchr(request, '?') + 1);
            query[strlen(query) / sizeof(query[0])] = '\0';
        }
        else query[0] = '\0';
    
    // cleanup
    free(request);
    free(method);
    free(version);
    return true;
}