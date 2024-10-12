#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Painel ADMIN
void admin() {
    printf("Admin\n");
}
// Painel CLIENT
void client() {
    printf("Client\n");
}

// Função Principal
int main(){
    int opcao;

    while(1) {

        printf("                            1. Admin\n");
        printf("\n");
        printf("                            2. Client\n");
        printf("\n");
        printf("                            3. Sair\n");

        printf("\n");

        printf("\n    Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                admin();
                break;
            case 2:
                client();
                break;
            case 3:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opção inválida!\n");
        }

    }
    return 0;
}