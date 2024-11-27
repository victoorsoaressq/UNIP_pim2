#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_PRODUCTS 100 // Limite de produtos no estoque
#define MAX_NAME 50      // Tamanho máximo do nome do produto
#define MAX_TYPE 20      // Tamanho máximo do tipo do produto
#define MAX_CART 50      // Limite de itens no carrinho

typedef struct
{
    char name[MAX_NAME];
    char type[20];
    float price;
    int amount;
    float weight;
} Product;

typedef struct
{
    Product product;
    int amount; // Quantidade do produto que foi comprada
} CarItem;

// Estrutura para armazenar os produtos vendidos
typedef struct
{
    char name[50];
    float price;
    int amount;
} ProdutoVendido;

// Array para armazenar produtos vendidos
ProdutoVendido produtosVendidos[100];
int numProdutosVendidos = 0; // Contador de produtos vendidos

// Variável global para o estoque de produtos
Product estoque[MAX_PRODUCTS];
int numProducts = 0; // Número de produtos cadastrados

// Variável global para o carrinho de compras
CarItem cart[MAX_CART];
int numCarIten = 0; // Número de itens no carrinho

void headerServidor()
{
    system("cls");
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

    printf("                 _____             _              _                      \n");
    printf("                /  __ \\           | |            | |                     \n");
    printf("                | /  \\/  __ _   __| |  __ _  ___ | |_  _ __   __ _  _ __ \n");
    printf("                | |     / _` | / _` | / _` |/ __|| __|| '__| / _` || '__|\n");
    printf("                | \\__/\\| (_| || (_| || (_| |\\__ \\| |_ | |   | (_| || |   \n");
    printf("                 \\____/ \\__,_| \\__,_| \\__,_||___/ \\__||_|    \\__,_||_|   \n");

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

    // Recebendo o peso por unidade do produto
    printf("   Digite o peso por unidade (em kg): ");
    scanf("%f", &newProduct.weight);

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

// Função apagar produto
void deleteProduct()
{
    int productId;

    if (numProducts == 0)
    {
        headerServidor();
        printf(" Estoque vazio.\n");
        printf("\nDigite 0 para retornar ao início.\n");
        printf("Digite a opção: ");
        scanf("%d", &productId);

        if (productId == 0)
            return;
    }
    else
    {
        headerServidor();
        printf("\n===== Produtos disponíveis =====\n");

        // Listar todos os produtos no estoque
        for (int i = 0; i < numProducts; i++)
        {
            printf("Produto: %d\n", i + 1);
            printf("Nome: %s\n", estoque[i].name);
            printf("Preço: %.2f\n", estoque[i].price);
            printf("Quantidade: %d\n", estoque[i].amount);
            printf("---------------------------\n");
        }

        printf("\nDigite o número do produto que deseja apagar: ");
        scanf("%d", &productId);

        // Validar ID do produto
        if (productId < 1 || productId > numProducts)
        {
            printf("\nID inválido. Retornando...\n");
            return;
        }

        // Ajustar índice para zero-based
        productId--;

        // Remover o produto do estoque
        for (int i = productId; i < numProducts - 1; i++)
        {
            estoque[i] = estoque[i + 1];
        }

        // Reduzir o número de produtos no estoque
        numProducts--;

        printf("\nProduto removido com sucesso!\n");
    }
};

// Função Estoque
void stock()
{
    int option;

    if (numProducts == 0)
    {
        headerServidor();

        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");

        printf("                                Estoque vazio.");

        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");

        printf("  Digite 0 para retornar ao início");
        printf("\n");
        printf("\n");
        printf("  Digite a opção: ");
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
            float totalWeight = estoque[i].amount * estoque[i].weight;

            if (strcmp(estoque[i].type, "Fruta") == 0)
            {
                printf("                                   Produto: %d\n", i + 1);
                printf("                                   Nome: %s\n", estoque[i].name);
                printf("                                   Preço: %.2f\n", estoque[i].price);
                printf("                                   Quantidade: %d\n", estoque[i].amount);
                printf("                                   Peso por unidade: %.3f kg\n", estoque[i].weight);
                printf("                                   Peso total: %.3f kg\n", totalWeight);
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
                printf("                            ---------------------------\n");
            }
        }

        printf("\n");
        printf("\n");
        printf("\n    Digite 0 para retornar.");
        printf("\n");
        printf("\n    Digite 1 para apagar produto.");
        printf("\n");
        printf("\n    opção: ");
        scanf("%d", &option);

        if (option == 1)
        {
            deleteProduct();
        }
        else if (option != 2)
        {
            return;
        };
    };
}

void registrarProdutosVendidos()
{
    // Adicionar produtos do carrinho ao array de produtos vendidos
    for (int i = 0; i < numCarIten; i++)
    {
        strcpy(produtosVendidos[numProdutosVendidos].name, cart[i].product.name);
        produtosVendidos[numProdutosVendidos].price = cart[i].product.price;
        produtosVendidos[numProdutosVendidos].amount = cart[i].amount;
        numProdutosVendidos++;
    }
}

void exibirProdutosVendidos()
{
    int option;

    headerServidor();
    printf("\n");
    printf("\n");
    printf("                                 PRODUTOS VENDIDOS");
    printf("\n");
    printf("\n");

    if (numProdutosVendidos == 0)
    {
        printf("\n                      Nenhum produto foi vendido até agora.\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");

        printf("  Digite 0 para retornar ao início");
        printf("\n");
        printf("\n");
        printf("  Digite a opção: ");
        scanf("%d", &option);

        if (option != 1)
            return;
    }
    else
    {
        printf("\n=========== Produtos Vendidos ===========\n");
        for (int i = 0; i < numProdutosVendidos; i++)
        {
            printf("Item %d:\n", i + 1);
            printf("Nome: %s\n", produtosVendidos[i].name);
            printf("Preço unitário: %.2f\n", produtosVendidos[i].price);
            printf("Quantidade: %d\n", produtosVendidos[i].amount);
            printf("Total: %.2f\n", produtosVendidos[i].price * produtosVendidos[i].amount);
            printf("---------------------------\n");
        }

        printf("  Digite 0 para retornar ao início");
        printf("\n");
        printf("\n");
        printf("  Digite a opção: ");
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

    printf("                _____                     _      _              \n");
    printf("               /  ___|                   (_)    | |             \n");
    printf("               \\ `--.   ___  _ __ __   __ _   __| |  ___   _ __ \n");
    printf("                `--. \\ / _ \\| '__|\\ \\ / /| | / _` | / _ \\ | '__|\n");
    printf("               /\\__/ /|  __/| |    \\ V / | || (_| || (_) || |   \n");
    printf("               \\____/  \\___||_|     \\_/  |_| \\__,_| \\___/ |_|   \n");

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    printf("                            1. Cadastro de produtos\n");
    printf("\n");
    printf("                            2. Estoque\n");
    printf("\n");
    printf("                            3. Produtos vendidos\n");
    printf("\n");
    printf("                            4. Voltar\n");

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
        exibirProdutosVendidos();
        break;
    case 4:
        return;
    default:
        printf("Opção inválida!\n");
    }
}

// Função Header
void headerClient()
{
    system("cls");
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
    if (numCarIten == 0)
    {
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");

        printf("                                Carrinho vazio!\n");

        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");

        printf("Digite 0 para retornar ao início.");
        printf("\n");
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
            float totalWeight = cart[i].amount * cart[i].product.weight;

            printf("\n");
            

            printf("                 _____                     _         _            \n");
            printf("                /  __ \\                   (_)       | |           \n");
            printf("                | /  \\/  __ _  _ __  _ __  _  _ __  | |__    ___  \n");
            printf("                | |     / _` || '__|| '__|| || '_ \\ | '_ \\  / _ \\ \n");
            printf("                | \\__/\\| (_| || |   | |   | || | | || | | || (_) |\n");
            printf("                 \\____/ \\__,_||_|   |_|   |_||_| |_||_| |_| \\___/ \n");

            printf("\n");
            printf("\n");
            printf("\n");

            printf("                          Item %d:\n", i + 1);
            printf("                          Nome: %s\n", cart[i].product.name);
            printf("                          Preço: %.2f\n", cart[i].product.price);
            printf("                          Quantidade: %d\n", cart[i].amount);
            printf("                          Peso total: %.3f kg\n", totalWeight);
            printf("                        -------------------\n");
            printf("\n");
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

    printf("               ______                   _         _               \n");
    printf("               | ___ \\                 | |       | |              \n");
    printf("               | |_/ / _ __   ___    __| | _   _ | |_   ___   ___ \n");
    printf("               |  __/ | '__| / _ \\  / _` || | | || __| / _ \\ / __|\n");
    printf("               | |    | |   | (_) || (_| || |_| || |_ | (_) |\\__ \\\n");
    printf("               \\_|    |_|    \\___/  \\__,_| \\__,_| \\__| \\___/ |___/\n");

    printf("\n");
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
        int option;

        system("cls");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        

        printf("                 Não há produtos disponíveis para essa categoria.\n");

        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("  Digite 0 para retornar ao início");
        printf("\n");
        printf("\n");
        printf("  Digite a opção: ");
        scanf("%d", &option);

        if (option != 1)
            return;
    }
    headerClient();
    printf("\n");

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
        printf("\n");

        printf("\n                    Carrinho vazio! Não há nada para pagar.\n");
        
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");

        printf("  Digite 0 para retornar ao início");
        printf("\n");
        printf("\n");
        printf("  Digite a opção: ");
        scanf("%d", &option);

        if (option != 1)
            return;
    }

    headerClient();
    printf("\nItens no carrinho:\n");

    for (int i = 0; i < numCarIten; i++)
    {
        printf(" %d. %s - Quantidade: %d - Preço unitário: %.2f - Total: %.2f\n",
               i + 1,
               cart[i].product.name,
               cart[i].amount,
               cart[i].product.price,
               cart[i].product.price * cart[i].amount);
        total += cart[i].product.price * cart[i].amount;
    }

    printf("\nValor total da compra: %.2f\n", total);
    printf("\nDeseja pagar? (1-Sim / 2-Não): ");
    scanf("%d", &option);

    if (option == 1)
    {
        headerClient();
        printf("\nPagamento efetuado com sucesso!\n");

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

        // Registrar os produtos vendidos
        registrarProdutosVendidos();

        // Limpa o carrinho após a compra
        numCarIten = 0;

        printf("\nDeseja comprar um novo produto?");
        printf("\n[1] Para sim.");
        printf("\n[2] Para não.");
        printf("\nEscolha uma opção: ");
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
        printf("\nPagamento cancelado.\n");
    }
};

int weight()
{

    int productId, quantity;
    float totalWeight, totalPrice;

    if (numProducts == 0)
    {
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");

        printf("                                  Estoque vazio.\n");
        printf("\n");
        printf("\n                       Digite 0 para retornar ao início.\n");

        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("     Digite a opção: ");
        scanf("%d", &productId);

        if (productId == 0)
        {
            return 0;
        };
    }
    else
    {
        system("cls");
        printf("\n");
        printf("\n");

        printf("\n          ==================== Produtos disponíveis ====================\n");

        printf("\n");
        printf("\n");

        // Listar todos os produtos no estoque
        for (int i = 0; i < numProducts; i++)
        {
            printf("\n");
            printf("\n");

            printf("                                  Produto: %d\n", i + 1);
            printf("                                  Nome: %s\n", estoque[i].name);
            printf("                                  Preço: %.2f\n", estoque[i].price);
            printf("                                  Quantidade: %d\n", estoque[i].amount);
            printf("                                ------------------\n");
        }
        printf("\n");
        printf("\n");
        printf("Selecione o número do produto que deseja pesar (ou 0 para voltar): ");
        scanf("%d", &productId);

        // Validar a seleção do produto
        if (productId == 0)
            return 0;

        if (productId < 1 || productId > numProducts)
        {
            printf("Produto inválido!\n");
            return 0;
        }

        // Ajustar para índice do array
        productId--;

        // Solicitar a quantidade do produto
        printf("\n");
        printf("Digite a quantidade de '%ss': ", estoque[productId].name);
        scanf("%d", &quantity);

        // Calcular o peso total
        totalWeight = quantity * estoque[productId].weight;
        totalPrice = quantity * estoque[productId].price;

        system("cls");
        printf("\n");
        printf("\n");
        printf("\n");

        printf("                   ============ Etiqueta ============\n");
        printf("\n");
        printf("                       Produto selecionado: %s\n", estoque[productId].name);
        printf("                       Quantidade informada: %d \n", quantity);
        printf("                       Peso total: %.3f kg\n", totalWeight);
        printf("                       TOTAL: R$ %.2f \n", totalPrice);
        printf("\n");
        printf("                       |||| ||| ||||| || ||| ||||  \n");
        printf("                       |||| ||| ||||| || ||| ||||  \n");
        printf("\n");
        printf("                   ==================================\n");

        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");

        printf("\nDigite 0 para retornar ao início.\n");
        int option;
        scanf("%d", &option);

        if (option == 0)
            return 0;
    };
};

void balance()
{

    int option;

    while (1)
    {
        system("cls");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");

        printf("                ______         _                            \n");
        printf("                | ___ \\       | |                           \n");
        printf("                | |_/ /  __ _ | |  __ _  _ __    ___   __ _ \n");
        printf("                | ___ \\ / _` || | / _` || '_ \\  / __| / _` |\n");
        printf("                | |_/ /| (_| || || (_| || | | || (__ | (_| |\n");
        printf("                \\____/  \\__,_||_| \\__,_||_| |_| \\___| \\__,_|\n");

        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");

        printf("                              1. Pesar Produto \n");
        printf("\n");
        printf("                              2. Voltar \n");
        printf("\n");

        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");

        printf("\n   Escolha uma opção: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            weight();
            break;
        case 2:
            return;
            break;
        };
    };
};

// Painel CLIENT
void client()
{
    int option;

    while (1)
    {
        headerClient();
        printf("\n");

        printf("                          _____         _              \n");
        printf("                         /  __ \\       (_)             \n");
        printf("                         | /  \\/  __ _  _ __  __  __ _ \n");
        printf("                         | |     / _` || |\\ \\/ / / _` |\n");
        printf("                         | \\__/\\| (_| || | >  < | (_| |\n");
        printf("                          \\____/ \\__,_||_|/_/\\_\\ \\__,_|\n");

        printf("\n");
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
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    int option;
    system("color 1F");

    while (1)
    {

        system("cls");
        printf("\n");
        printf("\n");
        printf("                 _                   _    _   __               _    _ \n");
        printf("                | |                 | |  (_) / _|             | |  (_)\n");
        printf("                | |__    ___   _ __ | |_  _ | |_  _ __  _   _ | |_  _ \n");
        printf("                | '_ \\  / _ \\ | '__|| __|| ||  _|| '__|| | | || __|| |\n");
        printf("                | | | || (_) || |   | |_ | || |  | |   | |_| || |_ | |\n");
        printf("                |_| |_| \\___/ |_|    \\__||_||_|  |_|    \\__,_| \\__||_|\n");
        printf("\n");

        printf("\n");
        printf("\n");
        printf("\n");

        printf("                                  1. Servidor\n");
        printf("\n");
        printf("                                  2. Balança\n ");
        printf("\n");
        printf("                                  3. Caixa\n");
        printf("\n");
        printf("\n");
        printf("                                  4. Sair\n");

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
            balance();
            break;
        case 3:
            client();
            break;
        case 4:
            system("cls");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("                                     SAINDO...\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");

            exit(0);
        default:
            printf("Opção inválida!\n");
        }
    }
};

// Função Principal
int main()
{
    principal();
};
