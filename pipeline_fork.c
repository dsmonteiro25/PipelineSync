 // Developed by Daniel Monteiro
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

void consumidor(int read_fd, int write_fd) {
    printf("Iniciando o processo consumidor...\n");
    char buffer[100];
    char confirmacao[] = "Recebido";
    int bytes_read;

    while ((bytes_read = read(read_fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("Consumidor: %s\n", buffer);
        write(write_fd, confirmacao, strlen(confirmacao));
    }
    printf("Processo consumidor finalizado.\n");
    close(read_fd);
    close(write_fd);
}

void produtor(int write_fd, int read_fd) {
    printf("Iniciando o processo produtor...\n");
    char buffer[50];
    char resposta[20];
    int bytes_read;

    for (int i = 0; i < 5; i++) {
        snprintf(buffer, sizeof(buffer), "Mensagem número %d", i + 1);
        write(write_fd, buffer, strlen(buffer));
        printf("Produtor: enviando '%s'\n", buffer);

        // Aguarda confirmação do consumidor
        bytes_read = read(read_fd, resposta, sizeof(resposta) - 1);
        if (bytes_read > 0) {
            resposta[bytes_read] = '\0';
            printf("Produtor: confirmação recebida: '%s'\n", resposta);
        }
    }
    printf("Processo produtor finalizado.\n");
    close(write_fd);
    close(read_fd);
}

int main() {
    int pipe1[2], pipe2[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Erro ao criar os pipes");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Erro ao criar o processo filho");
        return 1;
    }

    if (pid == 0) { 
        close(pipe1[1]); 
        close(pipe2[0]); 
        consumidor(pipe1[0], pipe2[1]);
    } else { 
        close(pipe1[0]); 
        close(pipe2[1]); 
        produtor(pipe1[1], pipe2[0]);
    }

    return 0;
}