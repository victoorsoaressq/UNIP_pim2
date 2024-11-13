#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100 // Limite de produtos no estoque
#define MAX_NAME 50      // Tamanho máximo do nome do produto
#define MAX_TYPE 20      // Tamanho máximo do tipo do produto
#define MAX_CART 50      // Limite de itens no carrinho

typedef struct
{
    char name[MAX_NAME];
    float price;
    int amount;
    char type[MAX_TYPE]; 
} Product;

typedef struct
{
    Product product;
    int amount; // Quantidade do produto que foi comprada
} CarItem;

// Variável global para o estoque de produtos
Product estoque[MAX_PRODUCTS];
int numProducts = 0; // Número de produtos cadastrados

// Variável global para o carrinho de compras
CarItem cart[MAX_CART];
int numCarIten = 0; // Número de itens no carrinho

void headerServidor()
{
    system("clear");
    int totalItems = 0;

    // Calcula a quantidade total de itens no estoque
    for (int i = 0; i < numProducts; i++)
    {
        totalItems += estoque[i].amount; // Soma a quantidade de cada produto no estoque
    }

    printf("--------------------------------------------------------------------------------\n");
    printf("        Servidor                                        Itens no estoque: %d\n", totalItems);
    printf("--------------------------------------------------------------------------------\n");
}

// Função cadastro de produtos
void toRegister()
{
    int option;
    int typeOption;

    headerServidor();
    if (numProducts >= MAX_PRODUCTS)
    {
        printf("Estoque cheio! Não é possível cadastrar mais produtos.\n");
        return;
    }

    Product newProduct;

    printf("\n");
    printf("     ██████  █████  ██████   █████  ███████ ████████ ██████   █████  ██████ \n");
    printf("    ██      ██   ██ ██   ██ ██   ██ ██         ██    ██   ██ ██   ██ ██   ██\n");
    printf("    ██      ███████ ██   ██ ███████ ███████    ██    ██████  ███████ ██████ \n");
    printf("    ██      ██   ██ ██   ██ ██   ██      ██    ██    ██   ██ ██   ██ ██   ██\n");
    printf("     ██████ ██   ██ ██████  ██   ██ ███████    ██    ██   ██ ██   ██ ██   ██\n");
    printf("\n");

    printf("\n");
    printf("\n");
    printf("\n");

    // Recebendo o tipo do produto
    printf("                            Escolha o tipo do produto:\n");
    printf("\n");
    printf("                   [1] Fruta      [2] Legume      [3] Verdura\n");

    printf("\n");
    printf("\n");
    printf("\n");

    printf("   Opção: ");
    scanf("%d", &typeOption);

    switch (typeOption)
    {
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

    // Recebendo o nome do produto
    printf("   Digite o nome do produto: ");
    getchar(); // Limpa o buffer antes de usar fgets
    fgets(newProduct.name, MAX_NAME, stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = '\0'; // Remove o '\n' do final

    // Recebendo o preço do produto
    printf("   Digite o preço do produto: ");
    scanf("%f", &newProduct.price);

    // Recebendo a quantidade do produto
    printf("   Digite a quantidade do produto: ");
    scanf("%d", &newProduct.amount);

    // Verificar se o produto já existe no estoque (mesmo nome e tipo)
    for (int i = 0; i < numProducts; i++)
    {
        if (strcmp(estoque[i].name, newProduct.name) == 0 && strcmp(estoque[i].type, newProduct.type) == 0)
        {
            // Produto encontrado, atualiza a quantidade
            estoque[i].amount += newProduct.amount;
            headerServidor();
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");

            printf("\n");
            printf("                    Produto já cadastrado! Quantidade atualizada.\n");
            printf("\n");
            printf("                         Deseja cadastrar um novo produto?");
            printf("\n");
            printf("\n                                  [1] Para sim");
            printf("\n");
            printf("\n                                  [2] Para não");

            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");

            printf("   Escolha um opção: ");
            scanf("%d", &option);

            if (option == 1)
            {
                toRegister();
            }
            return; // Sai da função se o produto já foi atualizado
        }
    }

    // Se o produto não foi encontrado no estoque, cadastra como um novo produto
    estoque[numProducts] = newProduct;
    numProducts++;

    headerServidor();

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                          Produto cadastrado com sucesso!\n");
    printf("\n");
    printf("                         Deseja cadastrar um novo produto?");
    printf("\n");
    printf("\n");
    printf("\n                                  [1] Para sim");
    printf("\n");
    printf("\n                                  [2] Para não");

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    printf("   Escolha um opção: ");
    scanf("%d", &option);

    if (option == 1)
    {
        toRegister();
    }
    else if (option == 2)
    {
        return;
    }
}

// Função Estoque
void stock()
{
    int option;

    if (numProducts == 0)
    {
        headerServidor();
        printf(" Estoque vazio.");
        printf("\n");
        printf("\n");
        printf("Digite 0 para retornar ao início.");
        printf("\n");
        printf("Digite a opção: ");
        scanf("%d", &option);

        if (option != 1)
            return;
    }
    else
    {
        headerServidor();

        printf("\n");

        // Exibir produtos do tipo "Fruta"
        printf("                          ====== Sessão: Frutas ======\n");
        for (int i = 0; i < numProducts; i++)
        {
            if (strcmp(estoque[i].type, "Fruta") == 0)
            {
                printf("                                   Produto: %d\n", i + 1);
                printf("                                   Nome: %s\n", estoque[i].name);
                printf("                                   Preço: %.2f\n", estoque[i].price);
                printf("                                   Quantidade: %d\n", estoque[i].amount);
                printf("                            ---------------------------\n");
            }
        }

        // Exibir produtos do tipo "Legume"
        printf("                          ====== Sessão: Legumes ======\n");
        for (int j = 0; j < numProducts; j++)
        {
            if (strcmp(estoque[j].type, "Legume") == 0)
            {
                printf("                                   Produto: %d\n", j + 1);
                printf("                                   Nome: %s\n", estoque[j].name);
                printf("                                   Preço: %.2f\n", estoque[j].price);
                printf("                                   Quantidade: %d\n", estoque[j].amount);
                printf("                            ---------------------------\n");
            }
        }

        // Exibir produtos do tipo "Verdura"
        printf("                          ====== Sessão: Verduras ======\n");
        for (int t = 0; t < numProducts; t++)
        {
            if (strcmp(estoque[t].type, "Verdura") == 0)
            {
                printf("                                   Produto: %d\n", t + 1);
                printf("                                   Nome: %s\n", estoque[t].name);
                printf("                                   Preço: %.2f\n", estoque[t].price);
                printf("                                   Quantidade: %d\n", estoque[t].amount);
                printf("                            ---------------------------\n");
            }
        }

        printf("\n");
        printf("\n");
        printf("\n    Digite 0 para retornar");
        printf("\n");
        printf("\n    opção: ");
        scanf("%d", &option);

        if (option != 1)
            return;
    }
}

// Painel ADMIN
void server()
{

    int option;

    headerServidor();
    printf("\n");

    printf("           ███████ ███████ ██████  ██    ██ ██ ██████   ██████  ██████   \n");
    printf("           ██      ██      ██   ██ ██    ██ ██ ██   ██ ██    ██ ██   ██  \n");
    printf("           ███████ █████   ██████  ██    ██ ██ ██   ██ ██    ██ ██████   \n");
    printf("                ██ ██      ██   ██  ██  ██  ██ ██   ██ ██    ██ ██   ██  \n");
    printf("           ███████ ███████ ██   ██   ████   ██ ██████   ██████  ██   ██  \n");

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    printf("                            1. Cadastro de produtos\n");
    printf("\n");
    printf("                            2. Estoque\n");
    printf("\n");
    printf("                            3. Voltar\n");

    printf("\n");
    printf("\n");
    printf("\n");

    printf("\n   Escolha uma opção: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        toRegister();
        break;
    case 2:
        stock();
        break;

    case 3:
        return;
    default:
        printf("Opção inválida!\n");
    }
}

// Função Header
void headerClient()
{
    system("clear");
    int totalItems = 0;

    // Calcula a quantidade total de itens no carrinho
    for (int i = 0; i < numCarIten; i++)
    {
        totalItems += cart[i].amount; // Soma a quantidade de cada item no carrinho
    }

    printf("--------------------------------------------------------------------------------\n");
    printf("        Caixa                                         Itens no carrinho: %d\n", totalItems);
    printf("--------------------------------------------------------------------------------\n");
}

// Função mostrar carrinho
void showToCart()
{

    int option;

    headerClient();

    printf("\n=========== Carrinho de Compras ===========\n");
    if (numCarIten == 0)
    {
        printf("Carrinho vazio!\n");
        printf("\n");
        printf("\n");
        printf("Digite 0 para retornar ao início.");
        printf("\n");
        printf("Digite a opção: ");
        scanf("%d", &option);

        if (option != 1)
            return;
    }
    else
    {
        for (int i = 0; i < numCarIten; i++)
        {
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

        if (option != 1)
            return;
    }
}

// Função para adicionar um item ao carrinho
void addToCart(Product product, int amount)
{
    int option;

    if (numCarIten >= MAX_CART)
    {
        printf("Carrinho cheio! Não é possível adicionar mais itens.\n");
        return;
    }

    CarItem newItem;
    newItem.product = product;
    newItem.amount = amount;

    cart[numCarIten] = newItem;
    numCarIten++;

    headerClient();
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("               Produto adicionado ao carrinho com sucesso!\n");
    printf("\n");
    printf("                    Deseja comprar um novo produto?");
    printf("\n");
    printf("\n");
    printf("\n                             [1] Para sim.");
    printf("\n");
    printf("\n                             [2] Para não.");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("   Escolha um opção: ");
    scanf("%d", &option);

    if (option == 1)
    {
        return;
    }
    else if (option == 2)
    {
        return;
    }
}

// Função Comprar Produto
void buyProduct()
{

    int typeOptions;
    int productOption;
    int amount;
    Product *productAvailable[MAX_PRODUCTS];
    int numAvailable = 0;

    headerClient();
    printf("\n");

    printf("          ██████  ██████  ███    ███ ██████  ██████   █████  ██████  \n");
    printf("         ██      ██    ██ ████  ████ ██   ██ ██   ██ ██   ██ ██   ██ \n");
    printf("         ██      ██    ██ ██ ████ ██ ██████  ██████  ███████ ██████  \n");
    printf("         ██      ██    ██ ██  ██  ██ ██      ██   ██ ██   ██ ██   ██ \n");
    printf("          ██████  ██████  ██      ██ ██      ██   ██ ██   ██ ██   ██ \n");
    
    printf("\n");
    printf("\n");
    // Menu de escolha do tipo de produto
    printf("                        Escolha o tipo de produto:\n");
    printf("\n");
    printf("                                1. Fruta\n");
    printf("\n");
    printf("                                2. Legume\n");
    printf("\n");
    printf("                                3. Verdura\n");
    printf("\n");
    printf("                                4. Voltar\n");
    printf("\n");
    printf("\n");

    printf("   Opção: ");
    scanf("%d", &typeOptions);

    // Logica para voltar ao inicio.

    if (typeOptions == 4)
    {
        return;
    }

    // Filtra os produtos no estoque com base no tipo escolhido
    for (int i = 0; i < numProducts; i++)
    {
        if ((typeOptions == 1 && strcmp(estoque[i].type, "Fruta") == 0) ||
            (typeOptions == 2 && strcmp(estoque[i].type, "Legume") == 0) ||
            (typeOptions == 3 && strcmp(estoque[i].type, "Verdura") == 0))
        {
            productAvailable[numAvailable] = &estoque[i];
            numAvailable++;
        }
    }

    // Exibe os produtos disponíveis
    if (numAvailable == 0)
    {
        printf("Não há produtos disponíveis para essa categoria.\n");
        return;
    }
    headerClient();
    printf("\n");
    printf("     ██████  ██████   ██████  ██████  ██    ██ ████████  ██████  ███████ \n");
    printf("     ██   ██ ██   ██ ██    ██ ██   ██ ██    ██    ██    ██    ██ ██      \n");
    printf("     ██████  ██████  ██    ██ ██   ██ ██    ██    ██    ██    ██ ███████ \n");
    printf("     ██      ██   ██ ██    ██ ██   ██ ██    ██    ██    ██    ██      ██ \n");
    printf("     ██      ██   ██  ██████  ██████   ██████     ██     ██████  ███████ \n");
    printf("\n");
    printf("\n");
    printf("\n");
    for (int i = 0; i < numAvailable; i++)
    {
        printf("             %d. %s (Preço: %.2f, Quantidade em estoque: %d)\n",
               i + 1,
               productAvailable[i]->name,
               productAvailable[i]->price,
               productAvailable[i]->amount);
    }

    // Escolha do produto

    printf("\n");
    printf("\n");
    printf("     Escolha um produto [número]: ");
    scanf("%d", &productOption);
    if (productOption < 1 || productOption > numAvailable)
    {
        printf("Opção inválida!\n");
        return;
    }

    Product *selectProduct = productAvailable[productOption - 1];

    // Escolha da quantidade
    printf("     Digite a quantidade desejada: ");
    scanf("%d", &amount);
    printf("\n");

    // Verifica se há estoque suficiente
    if (amount > selectProduct->amount)
    {
        printf("Quantidade indisponível em estoque!\n");
        printf("\n");
        return;
    }

    // Reduz o estoque e adiciona o produto ao carrinho
    selectProduct->amount -= amount;
    addToCart(*selectProduct, amount);
}

// Função para exibir e pagar os itens do carrinho
void toPay()
{

    int option;
    float total = 0;

    if (numCarIten == 0)
    {
        headerClient();
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("                Carrinho vazio! Não há nada para pagar.\n");
        return;
    }

    headerClient();
    printf("\n");

    printf(" ██████   █████   ██████   █████  ███    ███ ███████ ███    ██ ████████  ██████ \n");
    printf(" ██   ██ ██   ██ ██       ██   ██ ████  ████ ██      ████   ██    ██    ██    ██\n");
    printf(" ██████  ███████ ██   ███ ███████ ██ ████ ██ █████   ██ ██  ██    ██    ██    ██\n");
    printf(" ██      ██   ██ ██    ██ ██   ██ ██  ██  ██ ██      ██  ██ ██    ██    ██    ██\n");
    printf(" ██      ██   ██  ██████  ██   ██ ██      ██ ███████ ██   ████    ██     ██████ \n");

    printf("\n");
    printf("\n");

    printf("                                Itens no carrinho:\n");
    printf("\n");
    printf("\n");
    for (int i = 0; i < numCarIten; i++)
    {
        printf("     %d. %s - Quantidade: %d - Preço unitário: %.2f - Total: %.2f\n",
               i + 1,
               cart[i].product.name,
               cart[i].amount,
               cart[i].product.price,
               cart[i].product.price * cart[i].amount);
        total += cart[i].product.price * cart[i].amount;
    }

    printf("\n                     Valor total da compra: %.2f\n", total);
    printf("\n");
    printf("\n  Deseja pagar? (1-Sim / 2-Não): ");
    scanf("%d", &option);

    if (option == 1)
    {
        headerClient();
        printf("\n");
        printf("███    ██  ██████  ████████  █████      ███████ ██ ███████  ██████  █████  ██   \n");
        printf("████   ██ ██    ██    ██    ██   ██     ██      ██ ██      ██      ██   ██ ██   \n");
        printf("██ ██  ██ ██    ██    ██    ███████     █████   ██ ███████ ██      ███████ ██   \n");
        printf("██  ██ ██ ██    ██    ██    ██   ██     ██      ██      ██ ██      ██   ██ ██   \n");
        printf("██   ████  ██████     ██    ██   ██     ██      ██ ███████  ██████ ██   ██ █████\n");
        printf("\n");
        for (int i = 0; i < numCarIten; i++)
        {
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

        if (option == 1)
        {
            return;
        }
        else if (option == 2)
        {
            return;
        }
    }
    else
    {
        printf("Pagamento cancelado.\n");
    }
}

// Painel CLIENT
void client()
{
    int option;

    while (1)
    {
        headerClient();
        printf("\n");

        printf("                        ██████  █████  ██ ██   ██  █████  \n");
        printf("                       ██      ██   ██ ██  ██ ██  ██   ██ \n");
        printf("                       ██      ███████ ██   ███   ███████ \n");
        printf("                       ██      ██   ██ ██  ██ ██  ██   ██ \n");
        printf("                        ██████ ██   ██ ██ ██   ██ ██   ██ \n");

        printf("\n");
        printf("\n");

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

        switch (option)
        {
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

// Painel principal.
void principal()
{

    int option;

    while (1)
    {
        system("clear");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");

        printf("   ██   ██  ██████  ██████  ████████ ██ ███████ ██████  ██    ██ ████████ ██ \n");
        printf("   ██   ██ ██    ██ ██   ██    ██    ██ ██      ██   ██ ██    ██    ██    ██ \n");
        printf("   ███████ ██    ██ ██████     ██    ██ █████   ██████  ██    ██    ██    ██ \n");
        printf("   ██   ██ ██    ██ ██   ██    ██    ██ ██      ██   ██ ██    ██    ██    ██ \n");
        printf("   ██   ██  ██████  ██   ██    ██    ██ ██      ██   ██  ██████     ██    ██ \n");

        printf("\n");
        printf("\n");
        printf("\n");

        printf("                                  1. Servidor\n");
        printf("\n");
        printf("                                  2. Caixa\n");
        printf("\n");
        printf("                                  3. Sair\n");

        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
       

        printf("\n   Escolha uma opção: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            server();
            break;
        case 2:
            client();
            break;
        case 3:

            system("clear");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");

            printf(" ███████  █████  ██ ███    ██ ██████   ██████           \n");
            printf(" ██      ██   ██ ██ ████   ██ ██   ██ ██    ██          \n");
            printf(" ███████ ███████ ██ ██ ██  ██ ██   ██ ██    ██          \n");
            printf("      ██ ██   ██ ██ ██  ██ ██ ██   ██ ██    ██          \n");
            printf(" ███████ ██   ██ ██ ██   ████ ██████   ██████  ██ ██ ██ \n");
            exit(0);
        default:
            printf("Opção inválida!\n");
        }
    }
}

// Função Principal
int main()
{

    principal();
}