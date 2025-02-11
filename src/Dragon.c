#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para procesar un archivo .DragonC
void process_dragonc(const char *filename);

// Función para ejecutar un comando
void execute_command(const char *command);

// Función para detectar el sistema operativo
int is_windows();

int my_setenv(const char *name, const char *value)
{
    size_t needed = snprintf(NULL, 0, "%s=%s", name, value) + 1;
    char *env_var = malloc(needed);
    if (env_var == NULL)
        return -1;
    snprintf(env_var, needed, "%s=%s", name, value);
    return putenv(env_var);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: %s <archivo .DragonC>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    process_dragonc(filename);

    return 0;
}

void process_dragonc(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        // Remover el salto de línea
        line[strcspn(line, "\n")] = 0;

        // Ignorar líneas vacías y comentarios
        if (line[0] == '\0' || line[0] == '#')
        {
            continue;
        }

        // Si es una definición de variable
        char *equals = strchr(line, '=');
        if (equals != NULL)
        {
            *equals = '\0';
            const char *var_name = line;
            const char *value = equals + 1;
            my_setenv(var_name, value);
            printf("Variable %s definida como %s\n", var_name, value);
        }
        else if (strchr(line, ':'))
        {
            // Es una función
            printf("Función detectada: %s\n", line);
        }
        else
        {
            // Es un comando
            execute_command(line);
        }
    }

    fclose(file);
}

void execute_command(const char *command)
{
    char expanded_command[256];
    strcpy(expanded_command, command);

    // Expandir variables
    char *dollar = strchr(expanded_command, '$');
    while (dollar != NULL)
    {
        char var_name[50];
        sscanf(dollar + 1, "%49[^ \t\n$]", var_name);
        const char *value = getenv(var_name);
        if (value)
        {
            char temp[256];
            strncpy(temp, expanded_command, dollar - expanded_command);
            temp[dollar - expanded_command] = '\0';
            strcat(temp, value);
            strcat(temp, dollar + 1 + strlen(var_name));
            strcpy(expanded_command, temp);
        }
        dollar = strchr(dollar + 1, '$');
    }

    if (is_windows())
    {
        char *rm_pos = strstr(expanded_command, "rm -rf");
        if (rm_pos != NULL)
        {
            strncpy(rm_pos, "del /Q", 6);
        }
    }

    system(expanded_command);
    printf("Ejecutado: %s\n", expanded_command);
}

int is_windows()
{
#ifdef _WIN32
    return 1;
#else
    return 0;
#endif
}
