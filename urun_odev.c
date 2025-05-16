#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "product.bat"

struct Product{
    int id;
    char name[20];
    float price;
    int stock;
};

void menu();
void addProducts();
void updateProducts();
void showProducts();
void deleteProducts();


//rastgele erişimli dosya
// urun açma
// urun okuma
// urun yazma
// urun silme

int main(){
    menu();
}

void menu(){
        int choice;
        do{
            printf("\n----- URUN YONETIMI -----\n");
            printf("1. Urun Ekleme\n");
            printf("2. Stok Guncelleme\n");
            printf("3. Urun Goster\n");
            printf("4. Urun Sil\n");
            printf("5. Cikis\n");
            printf("-------------------------\n");
            printf("Seciminizi yapin: ");

            scanf("%d", &choice);
            switch(choice){
                case 1:
                    addProducts();
                    break;
                case 2:
                    updateProducts();
                    break;
                case 3:
                    showProducts();
                    break;
                case 4:
                    deleteProducts();
                    break;
                case 5:
                    printf("Cikis yapiliyor...\n");
                    break;
                default:
                    printf("Gecersiz secim. Lutfen tekrar deneyin.\n");
                    break;
            }
        }while(choice != 5);

}

void addProducts(){
    struct Product newProduct;
    FILE *file;
    file = fopen(FILE_NAME, "ab");
    printf("Urun ID: ");
    scanf("%d", &newProduct.id);
    printf("Urun Adi: ");
    scanf("%s", newProduct.name);
    printf("Urun Fiyati: ");
    scanf("%f", &newProduct.price);
    printf("Urun Stok: ");
    scanf("%d", &newProduct.stock);
    fwrite(&newProduct, sizeof(struct Product), 1, file);
    fclose(file);
}

void updateProducts(){
    struct Product product;
    FILE *file;
    file = fopen(FILE_NAME, "rb+");
    int id;
    printf("Guncellenecek urun ID: ");
    scanf("%d", &id);
    fseek(file, (id -1) *sizeof(struct Product), SEEK_SET);
    fread(&product,sizeof(struct Product), 1, file);
        //SEEK_SET : Dosya Başından Sonuna Kadar Kontrol
        //SEEK_CUR : Dosya İçerisinde Kontrol
        //SEEK_END : Dosya Sonundan Başına Kadar Kontrol

    printf("Yeni Urun Stok: ");
    scanf("%d", &product.stock);

    fseek(file, (id -1) *sizeof(struct Product), SEEK_CUR);
    fwrite(&product, sizeof(struct Product), 1, file);

    fclose(file);
    printf("Urun guncellendi.\n");
}

void showProducts(){
    struct Product product;
    FILE *file;
    file = fopen(FILE_NAME, "rb");
    printf("\n----- URUN LISTESI -----\n");

    while (fread(&product, sizeof(struct Product), 1, file)) {
        if (product.id != -1) {
            printf("ID: %d, Adi: %s, Fiyati: %.2f, Stok: %d\n", product.id, product.name, product.price, product.stock);
        }
    }

    fclose(file);
}

void deleteProducts(){
    struct Product product;
    FILE *file;
    file = fopen(FILE_NAME, "rb+");
    int id;
    printf("Silinecek urun ID: ");
    scanf("%d", &id);

    // Dosyanın başından itibaren sırayla ürünleri oku
    while (fread(&product, sizeof(struct Product), 1, file)) {
        if (product.id == id) {
            // Ürün bulundu, id'sini -1 yap ve aynı konuma yaz
            product.id = -1;
            fseek(file, -1 * sizeof(struct Product), SEEK_CUR); // Geri git
            fwrite(&product, sizeof(struct Product), 1, file);
            break;
        }
    }

    fclose(file);
    printf("Urun silindi.\n");
}