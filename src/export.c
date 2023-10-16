#include "../minishell.h"


int custom_setenv(char **env, const char *name, const char *value, int overwrite)
{
	int	i;
	char *var;

	i = 0;
	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
		return -1;
	while (env[i] != NULL)
	{
		if (strncmp(env[i], name, strlen(name)) == 0)
		{
			if (overwrite)
			{
				*var = malloc(strlen(name) + strlen(value) + 2);
				if (var != NULL) 
				{
					sprintf(var, "%s=%s", name, value);
					env[i] = var;
				}
				return 0;  // Success
			} else {
				return 0;  // Variable exists, and overwrite is not allowed
			}
		}
		i++;
	}

	// Variable doesn't exist, create a new one
	char *var = malloc(strlen(name) + strlen(value) + 2);
	if (var != NULL) {
		sprintf(var, "%s=%s", name, value);
		// Find the last NULL pointer in the environ array
		for (int i = 0; env[i] != NULL; i++) {
			if (env[i + 1] == NULL) {
				env[i + 1] = var;
				env[i + 2] = NULL;
				return 0;  // Success
			}
		}
	}
	return -1;  // Error
}

void builtin_export(char **env, char *args[])
{
	if (args[1] != NULL && args[2] != NULL) {
		int overwrite = 1;  // Set to 1 to allow overwriting existing variables
		int result = custom_setenv(env, args[1], args[2], overwrite);
		if (result == 0) {
			// Environment variable set successfully
			printf("%s=%s\n", args[1], args[2]);
		} else {
			perror("export"); // Handle any errors
		}
	} else {
		// Invalid or missing arguments
		printf("Usage: export VAR_NAME VAR_VALUE\n");
	}
}

// Handle the export command to set environment variables