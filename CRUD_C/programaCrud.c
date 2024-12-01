#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cJSON.h"

typedef struct {
    char nome[50];
    char estado[30];
    int gols;
} Time;

// Criando as funcoes

//* Função para converter string para minúsculas
void str_to_lower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

//* Função para adicionar time no array
void adicionarTime(const char *arquivo) {
    Time novo_time;
    printf("\033[1;34mDigite o nome do time: \033[0m");
    scanf(" %[^\n]", novo_time.nome);
    str_to_lower(novo_time.nome);
    printf("\033[1;34mDigite o estado do time: \033[0m");
    scanf(" %[^\n]", novo_time.estado);
    str_to_lower(novo_time.estado);
    printf("\033[1;34mDigite o numero de gols: \033[0m");
    scanf("%d", &novo_time.gols);

    FILE *f = fopen(arquivo, "r");
    cJSON *times = NULL;

    if (f) {
        fseek(f, 0, SEEK_END);
        long length = ftell(f);
        fseek(f, 0, SEEK_SET);

        if (length > 0) {
            char *buffer = (char *)malloc(length + 1);
            fread(buffer, 1, length, f);
            buffer[length] = '\0';
            times = cJSON_Parse(buffer);
            free(buffer);
        }
        fclose(f);
    }

    if (!times) times = cJSON_CreateArray();

    cJSON *time = cJSON_CreateObject();
    cJSON_AddStringToObject(time, "nome", novo_time.nome);
    cJSON_AddStringToObject(time, "estado", novo_time.estado);
    cJSON_AddNumberToObject(time, "gols", novo_time.gols);
    cJSON_AddItemToArray(times, time);

    char *json_string = cJSON_Print(times);
    f = fopen(arquivo, "w");
    if (f) {
        fprintf(f, "%s", json_string);
        fclose(f);
    } else {
        printf("Erro ao abrir o arquivo.\n");
    }

    cJSON_Delete(times);
    free(json_string);

    printf("\033[1;32mTime adicionado com sucesso!\033[0m\n");
}

//* Função para listar os times do array
void listarTime(const char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    if (!f) {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (length == 0) {
        printf("Nenhum time cadastrado.\n");
        fclose(f);
        return;
    }

    char *buffer = (char *)malloc(length + 1);
    fread(buffer, 1, length, f);
    buffer[length] = '\0';
    fclose(f);

    cJSON *times = cJSON_Parse(buffer);
    free(buffer);

    if (!cJSON_IsArray(times)) {
        printf("\033[38;5;196m0.Nenhum time cadastrado.\033[0m\n");
        cJSON_Delete(times);
        return;
    }

    printf("\n\033[1;36mTimes cadastrados:\033[0m\n");
    cJSON *time;
    cJSON_ArrayForEach(time, times) {
        cJSON *nome = cJSON_GetObjectItem(time, "nome");
        cJSON *estado = cJSON_GetObjectItem(time, "estado");
        cJSON *gols = cJSON_GetObjectItem(time, "gols");

        if (cJSON_IsString(nome) && cJSON_IsString(estado) && cJSON_IsNumber(gols)) {
            printf("\n\033[1;33m- Nome: %s\033[0m\n", nome->valuestring);
            printf("\033[1;33m  Estado: %s\033[0m\n", estado->valuestring);
            printf("\033[1;33m  gols: %d\033[0m\n", gols->valueint);
        }
    }

    cJSON_Delete(times);
}

//* Função para alterar time do array
void alterarTime(const char *arquivo) {
    char nome_para_alterar[50];
    printf("\033[1;33mDigite o nome do time que deseja alterar: \033[0m");
    scanf(" %[^\n]", nome_para_alterar);
    str_to_lower(nome_para_alterar);

    FILE *f = fopen(arquivo, "r");
    if (!f) {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (length == 0) {
        printf("Nenhum time cadastrado.\n");
        fclose(f);
        return;
    }

    char *buffer = (char *)malloc(length + 1);
    fread(buffer, 1, length, f);
    buffer[length] = '\0';
    fclose(f);

    cJSON *times = cJSON_Parse(buffer);
    free(buffer);

    if (!cJSON_IsArray(times)) {
        printf("Nenhum time cadastrado.\n");
        cJSON_Delete(times);
        return;
    }

    cJSON *time;
    int encontrado = 0;

    cJSON_ArrayForEach(time, times) {
        cJSON *nome = cJSON_GetObjectItem(time, "nome");
        if (cJSON_IsString(nome) && strcmp(nome->valuestring, nome_para_alterar) == 0) {
            encontrado = 1;

            printf("\033[1;34mAltere o nome do time: \033[0m");
            char novo_nome[30];
            scanf(" %[^\n]", novo_nome);
            str_to_lower(novo_nome);

            printf("\033[1;34mAltere o estado do time: \033[0m");
            char novo_estado[30];
            scanf(" %[^\n]", novo_estado);
            str_to_lower(novo_estado);

            printf("\033[1;34mAltere o numero de gols: \033[0m");
            int novos_gols;
            scanf("%d", &novos_gols);

            cJSON_ReplaceItemInObject(time, "estado", cJSON_CreateString(novo_estado));
            cJSON_ReplaceItemInObject(time, "gols", cJSON_CreateNumber(novos_gols));

            break;
        }
    }

    if (encontrado) {
        char *json_string = cJSON_Print(times);
        f = fopen(arquivo, "w");
        if (f) {
            fprintf(f, "%s", json_string);
            fclose(f);
        } else {
            printf("Erro ao abrir o arquivo para escrita.\n");
        }
        free(json_string);

        printf("\n\033[1;32mTime alterado com sucesso!\033[0m\n");
    } else {
        printf("\033[1;31mTime nao encontrado.\033[0m\n");
    }

    cJSON_Delete(times);
}

//* Função para remover time do array
void removerTime(const char *arquivo) {
    char nome_para_remover[50];
    printf("\033[1;31m3.Digite o nome do time que deseja remover: \033[0m");
    scanf(" %[^\n]", nome_para_remover);
    str_to_lower(nome_para_remover);
    
    FILE *f = fopen(arquivo, "r");
    if (!f) {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (length == 0) {
        printf("Nenhum time cadastrado.\n");
        fclose(f);
        return;
    }

    char *buffer = (char *)malloc(length + 1);
    fread(buffer, 1, length, f);
    buffer[length] = '\0';
    fclose(f);

    cJSON *times = cJSON_Parse(buffer);
    free(buffer);

    if (!cJSON_IsArray(times)) {
        printf("Nenhum time cadastrado.\n");
        cJSON_Delete(times);
        return;
    }

    cJSON *time, *prev = NULL;
    int encontrado = 0;
    cJSON_ArrayForEach(time, times) {
        cJSON *nome = cJSON_GetObjectItem(time, "nome");
        if (cJSON_IsString(nome) && strcmp(nome->valuestring, nome_para_remover) == 0) {
            cJSON_DetachItemViaPointer(times, time);
            encontrado = 1;
            break;
        }
        prev = time;
    }

    if (encontrado) {
        char *json_string = cJSON_Print(times);
        f = fopen(arquivo, "w");
        if (f) {
            fprintf(f, "%s", json_string);
            fclose(f);
        } else {
            printf("Erro ao abrir o arquivo para escrita.\n");
        }
        free(json_string);
        printf("\n\033[1;32mTime removido com sucesso!\033[0m\n");
    } else {
        printf("Time nao encontrado.\n");
    }

    cJSON_Delete(times);
}

// Estilização e config do menu e opções

int main() {
    const char *arquivo = "times.json";

    int opcao;
    do {
        // printf("\n\033[1;33m---> Temporada de 2024 <---\033[0m\n");
        printf("\n\033[1;36mTemporada de 2024 \033[0m\n");
        printf("\n\033[1;36m----> Menu <----\033[0m\n");
        printf("\033[1;32m1. Adicionar time\033[0m\n");
        printf("\033[1;32m2. Listar times\033[0m\n");
        printf("\033[1;32m3. Alterar time\033[0m\n");
        printf("\033[1;31m4. Remover time\033[0m\n");
        printf("\n\033[38;5;196m0. Sair\033[0m\n\n");
        printf("\033[1;34mEscolha uma opcao: \033[0m");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarTime(arquivo);
                break;
            case 2:
                listarTime(arquivo);
                break;
            case 3:
                alterarTime(arquivo);
                break;
            case 4:
                removerTime(arquivo);
                break;
            case 0:
                printf("\n\033[1;31m0. Desligando... Bip Bop\033[0m\n\n");
                break;
            default:
                printf("\033[1;31m0. Opcao invalida.\033[0m\n");
        }
    } while (opcao != 0);

    return 0;
}
