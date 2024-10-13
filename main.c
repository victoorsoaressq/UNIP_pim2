#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100 // Limite de produtos no estoque
#define MAX_NAME 50      // Tamanho máximo do nome do produto
#define MAX_TYPE 20      // Tamanho máximo do tipo do produto
#define MAX_CART 50   // Limite de itens no carrinho

typedef struct {
    char name[MAX_NAME];
    float price;
    int amount;
    char type[MAX_TYPE]; // Novo campo para armazenar o tipo do produto
} Product;

typedef struct {
    Product product;
    int amount; // Quantidade do produto que foi comprada
} CarItem;

// Variável global para o estoque de produtos
Product estoque[MAX_PRODUCTS];
int numProducts = 0; // Número de produtos cadastrados

// Variável global para o carrinho de compras
CarItem cart[MAX_CART];
int numCarIten = 0; // Número de itens no carrinho


void headerServidor() {
    system("clear");
    printf("--------------------------------------------------------------------------------\n");
    printf("        Servidor                                                                \n");
    printf("--------------------------------------------------------------------------------\n");
}

//Funcao cadastro de produtos
void toRegister(){

    int option;
    int typeOption;

headerServidor();
 if (numProducts >= MAX_PRODUCTS) {
        printf("Estoque cheio! Não é possível cadastrar mais produtos.\n");
        return;
    }

 Product newProduct;
// Recebendo o nome do produto
    printf("Digite o nome do produto: ");
    getchar(); // Limpa o buffer antes de usar fgets
    fgets(newProduct.name, MAX_NAME, stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = '\0'; // Remove o '\n' do final

// Recebendo o tipo do produto
    printf("Escolha o tipo do produto:\n");
    printf("1. Fruta\n");
    printf("2. Legume\n");
    printf("3. Verdura\n");
    printf("Opção: ");
    scanf("%d", &typeOption);

    switch (typeOption) {
        case 1:
            strcpy(newProduct.type, "Fruta");
            break;
        case 2:
            strcpy(newProduct.type, "Legume");
            break;
        case 3:
            strcpy(newProduct.type, "Verdura");
            break;
        default:
            printf("Opção inválida! Definindo como 'Outro'.\n");
            strcpy(newProduct.type, "Outro");
    }

    // Recebendo o preço do produto
    printf("Digite o preço do produto: ");
    scanf("%f", &newProduct.price);

    // Recebendo a quantidade do produto
    printf("Digite a quantidade do produto: ");
    scanf("%d", &newProduct.amount);

    // Adiciona o produto ao estoque
    estoque[numProducts] = newProduct;
    numProducts++;
    printf("\n");
    printf("Produto cadastrado com sucesso!\n");
    printf("\n");
    printf("Deseja cadastrar um novo produto?");
    printf("\n");
    printf("\n [1] Para sim .");
    printf("\n");
    printf(" \n [2] Para não.");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("Escolha um opção: ");
    scanf("%d", &option);

    if(option == 1 ){ 
        toRegister();
    }else if (option == 2){
        return;
    }


}




void stock(){

    int option;

 if (numProducts == 0){




    headerServidor();
        printf(" Estoque vazio.");
        printf("\n");
        printf("\n");
        printf("Digite 0 para retornar ao início.");
        printf("\n");
        printf("Digite a opção: ");
        scanf("%d", &option);

    if (option != 1) return;
    
 }else{

    headerServidor();

        for (int i = 0; i < numProducts; i++)
    {
     printf("Produto %d:\n", i + 1);
            printf("Nome: %s\n", estoque[i].name);
            printf("Tipo: %s\n", estoque[i].type);
            printf("Preço: %.2f\n", estoque[i].price);
            printf("Quantidade: %d\n", estoque[i].amount);
            printf("---------------------------\n");
    }
    printf("\n");
        printf("\n");
        printf("Digite 0 para retornar ao início.");
        printf("\n");
        printf("Digite a opção: ");
        scanf("%d", &option);

    if (option != 1) return;

    
 }
 
}


// Painel ADMIN
void admin() {

int option;


headerServidor();

        printf("                            1. Cadastro de produtos\n");
        printf("\n");
        printf("                            2. Estoque\n");
        printf("\n");
        printf("                            3. Sair\n");

        printf("\n");

        printf("\n    Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                toRegister();
                break;
            case 2:
                stock();
                break;
            case 4:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opção inválida!\n");

        }

}

// Painel CLIENT
// Função Header
void headerClient() {
    system("clear");
    printf("--------------------------------------------------------------------------------\n");
    printf("        Caixa                                                                \n");
    printf("--------------------------------------------------------------------------------\n");
}

void showToCart() {

int option;

    printf("\n=========== Carrinho de Compras ===========\n");
    if (numCarIten == 0) {
        printf("Carrinho vazio!\n");
        printf("\n");
        printf("\n");
        printf("Digite 0 para retornar ao início.");
        printf("\n");
        printf("Digite a opção: ");
        scanf("%d", &option);

    if (option != 1) return;

    } else {
        for (int i = 0; i < numCarIten; i++) {
            printf("Item %d:\n", i + 1);
            printf("Nome: %s\n", cart[i].product.name);
            printf("Preço: %.2f\n", cart[i].product.price);
            printf("Quantidade: %d\n", cart[i].amount);
            printf("---------------------------\n");
        }
        printf("\n");
        printf("\n");
        printf("Digite 0 para retornar ao início.");
        printf("\n");
        printf("Digite a opção: ");
        scanf("%d", &option);

    if (option != 1) return;

    }
}

// Função para adicionar um item ao carrinho
void addToCart(Product product, int amount) {
int option;

    if (numCarIten >= MAX_CART) {
        printf("Carrinho cheio! Não é possível adicionar mais itens.\n");
        return;
    }

    CarItem newItem;
    newItem.product = product;
    newItem.amount = amount;

    cart[numCarIten] = newItem;
    numCarIten++;

    printf("Produto adicionado ao carrinho com sucesso!\n");
    printf("Deseja comprar um novo produto?");
    printf("\n");
    printf("\n [1] Para sim .");
    printf("\n");
    printf(" \n [2] Para não.");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("Escolha um opção: ");
    scanf("%d", &option);

    if(option == 1 ){ 
        return;
    }else if (option == 2){
        return;
    }

}

// Função Comprar Produto
void buyProduct() {
int typeOptions;
int productOption;
int amount;
    Product *productAvailable [MAX_PRODUCTS];
    int numAvailable = 0;

    // Menu de escolha do tipo de produto
    printf("Escolha o tipo de produto:\n");
    printf("1. Fruta\n");
    printf("2. Legume\n");
    printf("3. Verdura\n");
    printf("Opção: ");
    scanf("%d", &typeOptions);

    // Filtra os produtos no estoque com base no tipo escolhido
    for (int i = 0; i < numProducts; i++) {
        if ((typeOptions== 1 && strcmp(estoque[i].type, "Fruta") == 0) ||
            (typeOptions== 2 && strcmp(estoque[i].type, "Legume") == 0) ||
            (typeOptions == 3 && strcmp(estoque[i].type, "Verdura") == 0)) {
            productAvailable[numAvailable] = &estoque[i];
            numAvailable++;
        }
    }

    // Exibe os produtos disponíveis
    if (numAvailable == 0) {
        printf("Não há produtos disponíveis para essa categoria.\n");
        return;
    }

    printf("\nProdutos disponíveis:\n");
    for (int i = 0; i < numAvailable; i++) {
        printf("%d. %s (Preço: %.2f, Quantidade em estoque: %d)\n", 
               i + 1, 
               productAvailable[i]->name, 
               productAvailable[i]->price, 
               productAvailable[i]->amount);
    }

    // Escolha do produto
    printf("Escolha um produto (número): ");
    scanf("%d", &productOption);
    if (productOption < 1 || productOption > numAvailable) {
        printf("Opção inválida!\n");
        return;
    }

    Product *selectProduct = productAvailable[productOption - 1];

    // Escolha da quantidade
    printf("Digite a quantidade desejada: ");
    scanf("%d", &amount);
    printf("\n");

    // Verifica se há estoque suficiente
    if (amount > selectProduct->amount) {
        printf("Quantidade indisponível em estoque!\n");
        printf("\n");
        return;
    }

    // Reduz o estoque e adiciona o produto ao carrinho
    selectProduct->amount -= amount;
    addToCart(*selectProduct, amount);
}


// Função Realizar Pagamento
// Função para exibir e pagar os itens do carrinho
void toPay() {

    int option;
    float total = 0;

    if (numCarIten == 0) {
        printf("Carrinho vazio! Não há nada para pagar.\n");
        return;
    }

    printf("\n=========== Pagamento ===========\n");
    printf("Itens no carrinho:\n");
    for (int i = 0; i < numCarIten; i++) {
        printf("%d. %s - Quantidade: %d - Preço unitário: %.2f - Total: %.2f\n",
               i + 1,
               cart[i].product.name,
               cart[i].amount,
               cart[i].product.price,
               cart[i].product.price * cart[i].amount);
        total += cart[i].product.price * cart[i].amount;
    }

    printf("\nValor total da compra: %.2f\n", total);
    printf("\n");
    printf("\nDeseja pagar? (1-Sim / 2-Não): ");
    printf("\n");
    

    scanf("%d", &option);

    if (option == 1) {
        printf("\n========= Nota Fiscal =========\n");
        for (int i = 0; i < numCarIten; i++) {
            printf("%d. %s - Quantidade: %d - Preço unitário: %.2f - Total: %.2f\n",
                   i + 1,
                   cart[i].product.name,
                   cart[i].amount,
                   cart[i].product.price,
                   cart[i].product.price * cart[i].amount);
        }
        printf("\nValor total pago: %.2f\n", total);
        printf("\n");
        printf("\n");
        printf("Obrigado pela compra!\n");
        printf("\n");

        // Limpa o carrinho após a compra
        numCarIten = 0;
        printf("Deseja comprar um novo produto?");
        printf("\n");
        printf("\n [1] Para sim .");
        printf("\n");
        printf(" \n [2] Para não.");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("Escolha um opção: ");
        scanf("%d", &option);

    if(option == 1 ){ 
        return;
    }else if (option == 2){
        return;
    }
    } else {
        printf("Pagamento cancelado.\n");
    }
}

// Painel CLIENT
void client() {
    int option;

    while(1) {
        headerClient();

        printf("\n");
        printf("\n");
        printf("                            1. Comprar Produto\n");
        printf("\n");
        printf("                            2. Exibir Carrinho\n");
        printf("\n");
        printf("                            3. Realizar Pagamento\n");
        printf("\n");
        printf("                            4. Sair\n");

        printf("\n");

        printf("\n    Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                buyProduct();
                break;
            case 2:
                showToCart();
                break;
            case 3:
                toPay();
                break;   
            case 4:
            return;
            break;
            default:
                printf("Opção inválida!\n");
        }

    }
  
}
// Função Principal
int main(){

    int option;

system("clear");

printf("\n");
printf("\n");
printf("\n");

    while(1) {

        printf("                            1. Servidor\n");
        printf("\n");
        printf("                            2. Caixa\n");
        printf("\n");
        printf("                            3. Sair\n");

        printf("\n");

        printf("\n    Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
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