#include "../minishell.h"

void free_data(data_t *data) {
    free(data->promt);
    free(data);
}