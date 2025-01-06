#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h> 

struct Date {
    int month, day, year;
};

struct Book {
    int id;
    char title[100];
    char author[100];
    int quantity;
    float price;
    struct Date publication;
};

struct Book books[100];
int bookCount = 0;

struct Customer {
    int id;
    char name[100];
    char phone[15];
    char status[10];
    char address[100];
    char email[100];
    int borrowedBooks[100];
    int borrowedCount;
};

struct Customer customers[100];
int customerCount = 0;

void libMenu();
void customerMenu();
void displayBooks();
void addBook();
void editBook();
void deleteBook();
void sortBooksByPrice();
void searchBooksByName();
void saveBooksToFile();
void loadBooksFromFile();
void openBooksFromFile();
int authenticateAdmin();
void saveAdminAccount(const char* username, const char* password);
void registerAdmin();
void showCustomerList();
void addCustomer();
void editCustomer();
void lockUnlockCustomer();
void searchCustomerByName();
void borrowBook();
void returnBook();
int isNumber(char* str);
int authenticateAdmin();
void saveAdminAccount(const char* username, const char* password);
void registerAdmin();

int main() {
    int isAuthenticated = 0;

    FILE *file = fopen("admin.txt", "r");
    if (file == NULL) {
        fclose(file);
        printf("Chua co tai khoan admin. Vui long tao tai khoan moi.\n");
        registerAdmin();
    }

    while (!isAuthenticated) {
        isAuthenticated = authenticateAdmin();
    }

    printf("\nDang nhap thanh cong! Chao mung admin.\n");

    int choice;
    do {
        printf("\n==================== QUAN LY THU VIEN ====================\n");
        printf("1. Quan ly sach\n");
        printf("2. Quan ly khach hang\n");
        printf("3. Thoat\n");
        printf("========================================================\n");
        scanf("%d",&choice);
        getchar();
		switch (choice){
			case 1: 
				libMenu();
				break;
			case 2:
				customerMenu();
				break;
			case 3:
				break;
		}
		}while (choice!=3);
    return 0;
}

void displayBooks() {
    int choice;
    do {
        printf("\nBan da chon 'Hien thi danh sach sach'.\n");
        printf("1. Hien thi danh sach\n");
        printf("2. Quay lai menu chinh\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            if (bookCount == 0) {
                printf("Danh sach sach rong!\n");
            } else {
                printf("\nDanh sach sach:\n");
                printf("+-----+-------------------------------+--------------------------------+------------+----------+-----------+------------+\n");
                printf("| ID  | Tieu de                       | Tac gia                        | So luong  | Gia      | Ngay XB    |\n");
                printf("+-----+-------------------------------+--------------------------------+------------+----------+-----------+------------+\n");
                for (int i = 0; i < bookCount; i++) {
                    printf("| %-3d | %-29s | %-30s | %-10d | %-8.0f | %-02d/%02d/%04d |\n", 
                        books[i].id, books[i].title, books[i].author, books[i].quantity, 
                        books[i].price, books[i].publication.month, books[i].publication.day, books[i].publication.year);
                }
                printf("+-----+-------------------------------+--------------------------------+------------+----------+-----------+------------+\n");
            }
        } else if (choice == 2) {
            break;
        } else {
            printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (1);
}

void addBook() {
	int choice;
    do {
        printf("\nBan da chon 'Them sach'.\n");
        printf("1. Them sach\n");
        printf("2. Quay lai menu chinh\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
    if (bookCount >= 100) {
        printf("Khong the them sach, danh sach da day!\n");
        return;
    }

    struct Book newBook;
    
    printf("\nNhap ID sach: ");
    while (scanf("%d", &newBook.id) != 1) {
        printf("ID sach khong hop le. Vui long nhap lai: ");
        while (getchar() != '\n');
    }

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == newBook.id) {
            printf("ID sach da ton tai. Vui long nhap ID khac.\n");
            return;
        }
    }

    printf("Nhap tieu de sach: ");
    getchar();
    while (fgets(newBook.title, sizeof(newBook.title), stdin)) {
        newBook.title[strcspn(newBook.title, "\n")] = 0;
        if (strlen(newBook.title) > 0) {
            break;
        } else {
            printf("Tieu de sach khong hop le. Vui long nhap lai: ");
        }
    }

    printf("Nhap tac gia: ");
    while (fgets(newBook.author, sizeof(newBook.author), stdin)) {
        newBook.author[strcspn(newBook.author, "\n")] = 0;
        if (strlen(newBook.author) > 0) {
            break;
        } else {
            printf("Tac gia khong hop le. Vui long nhap lai: ");
        }
    }

    printf("Nhap so luong: ");
    while (scanf("%d", &newBook.quantity) != 1 || newBook.quantity <= 0) {
        printf("So luong sach khong hop le. Vui long nhap lai: ");
        while (getchar() != '\n');
    }

    printf("Nhap gia sach: ");
    while (scanf("%f", &newBook.price) != 1 || newBook.price <= 0) {
        printf("Gia sach khong hop le. Vui long nhap lai: ");
        while (getchar() != '\n');
    }
    
    printf("Nhap ngay xuat ban (thang/ngay/nam): ");
    while (scanf("%d/%d/%d", &newBook.publication.month, &newBook.publication.day, &newBook.publication.year) != 3 || 
           newBook.publication.month < 1 || newBook.publication.month > 12 || 
           newBook.publication.day < 1 || newBook.publication.day > 31 || newBook.publication.year < 1900) {
        printf("Ngay xuat ban khong hop le. Vui long nhap lai (thang/ngay/nam): ");
        while (getchar() != '\n');
    }

    books[bookCount] = newBook;
    bookCount++;

    printf("\nThem sach thanh cong!\n");
} else if (choice == 2) {
            break;
        } else {
            printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    }	while (1);
}

void editBook() {
	int choice;
    do {
        printf("\nBan da chon 'Sua sach'.\n");
        printf("1. Sua sach\n");
        printf("2. Quay lai menu chinh\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
    int id;
    printf("\nNhap ID sach ban muon sua: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            found = 1;
            printf("\nThong tin sach hien tai:\n");
            printf("ID: %d\n", books[i].id);
            printf("Tieu de: %s\n", books[i].title);
            printf("Tac gia: %s\n", books[i].author);
            printf("So luong: %d\n", books[i].quantity);
            printf("Gia: %.2f\n", books[i].price);
            printf("Ngay xuat ban: %02d/%02d/%04d\n", books[i].publication.month, books[i].publication.day, books[i].publication.year);

            printf("\nNhap tieu de moi: ");
            getchar();
            fgets(books[i].title, sizeof(books[i].title), stdin);
            books[i].title[strcspn(books[i].title, "\n")] = 0;

            printf("Nhap tac gia moi: ");
            fgets(books[i].author, sizeof(books[i].author), stdin);
            books[i].author[strcspn(books[i].author, "\n")] = 0;

            printf("Nhap so luong moi: ");
            while (scanf("%d", &books[i].quantity) != 1 || books[i].quantity <= 0) {
                printf("Vui long nhap so luong hop le: ");
                while (getchar() != '\n');
            }

            printf("Nhap gia sach moi: ");
            while (scanf("%f", &books[i].price) != 1 || books[i].price <= 0) {
                printf("Vui long nhap gia sach hop le: ");
                while (getchar() != '\n');
            }

            printf("Nhap ngay xuat ban moi (thang/ngay/nam): ");
            while (scanf("%d/%d/%d", &books[i].publication.month, &books[i].publication.day, &books[i].publication.year) != 3 || 
                   books[i].publication.month < 1 || books[i].publication.month > 12 || 
                   books[i].publication.day < 1 || books[i].publication.day > 31 || books[i].publication.year < 1900) {
                printf("Vui long nhap ngay xuat ban hop le (thang/ngay/nam): ");
                while (getchar() != '\n');
            }

            printf("\nSua thong tin sach thanh cong!\n");
            break;
        }
    }

    if (!found) {
        printf("Sach voi ID %d khong ton tai.\n", id);
    }
}else if (choice == 2) {
            break;
        } else {
            printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    }	while (1);
}

void deleteBook() {
    int choice;
    do {
        printf("\nBan da chon 'Xoa sach'.\n");
        printf("1. Xoa sach\n");
        printf("2. Quay lai menu chinh\n");
        printf("Lua chon: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); 
            printf("Lua chon khong hop le. Vui long chon lai.\n");
            continue; 
        }

        if (choice == 1) {
            int id;
            printf("\nNhap ID sach ban muon xoa: ");
            while (scanf("%d", &id) != 1) {
                while(getchar() != '\n');
                printf("ID khong hop le. Vui long nhap ID la mot so.\n");
                printf("Nhap ID sach ban muon xoa: ");
            }

            int found = 0;
            for (int i = 0; i < bookCount; i++) {
                if (books[i].id == id) {
                    found = 1;

                    char confirm;
                    printf("\nBan co chac chan muon xoa sach '%s' (Y/N)? ", books[i].title);
                    while ((getchar()) != '\n');
                    scanf("%c", &confirm);

                    if (confirm == 'Y' || confirm == 'y') {
                        for (int j = i; j < bookCount - 1; j++) {
                            books[j] = books[j + 1];
                        }
                        bookCount--;
                        printf("Xoa sach thanh cong!\n");
                    } else {
                        printf("Xoa sach bi huy!\n");
                    }
                    break;
                }
            }

            if (!found) {
                printf("Sach voi ID %d khong ton tai.\n", id);
            }
        } else if (choice == 2) {
            break;
        } else {
            printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (1);
}

void sortBooksByPrice() {
    int choice;
    do {
        printf("\nBan da chon 'Sap xep sach theo gia tien'.\n");
        printf("1. Sap xep theo gia tang dan\n");
        printf("2. Sap xep theo gia giam dan\n");
        printf("3. Quay lai menu chinh\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            for (int i = 0; i < bookCount - 1; i++) {
                for (int j = i + 1; j < bookCount; j++) {
                    if (books[i].price > books[j].price) {
                        struct Book temp = books[i];
                        books[i] = books[j];
                        books[j] = temp;
                    }
                }
            }
            printf("\nDanh sach sach sau khi sap xep theo gia tang dan:\n");
            displayBooks();
        } else if (choice == 2) {
            for (int i = 0; i < bookCount - 1; i++) {
                for (int j = i + 1; j < bookCount; j++) {
                    if (books[i].price < books[j].price) {
                        struct Book temp = books[i];
                        books[i] = books[j];
                        books[j] = temp;
                    }
                }
            }
            printf("\nDanh sach sach sau khi sap xep theo gia giam dan:\n");
            displayBooks();
        }
    } while (choice != 3);
}

void searchBooksByName() {
	int choice;
    do {
        printf("\nBan da chon 'Tim kiem sach'.\n");
        printf("1. Tim sach\n");
        printf("2. Quay lai menu chinh\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
    char name[100];
    printf("\nNhap ten sach ban muon tim: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;  

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, name)) {
            if (!found) {
                printf("+-----+-------------------------------+--------------------------------+------------+----------+-----------+------------+\n");
                printf("| ID  | Tieu de                       | Tac gia                        | So luong  | Gia      | Ngay XB    |\n");
                printf("+-----+-------------------------------+--------------------------------+------------+----------+-----------+------------+\n");
            }
            printf("| %-3d | %-29s | %-30s | %-10d | %-8.0f | %-02d/%02d/%04d |\n", 
                books[i].id, books[i].title, books[i].author, books[i].quantity, 
                books[i].price, books[i].publication.month, books[i].publication.day, books[i].publication.year);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay sach co ten '%s'.\n", name);
    }
}else if (choice == 2) {
            break;
        } else {
            printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    }	while (1);
}

void openBooksFromFile() {
    loadBooksFromFile();
}

void saveBooksToFile() {
    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file de ghi du lieu.\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%d\n", books[i].id);
        fprintf(file, "%s\n", books[i].title);
        fprintf(file, "%s\n", books[i].author);
        fprintf(file, "%d\n", books[i].quantity);
        fprintf(file, "%.2f\n", books[i].price);
        fprintf(file, "%d/%d/%d\n", books[i].publication.month, books[i].publication.day, books[i].publication.year);
    }

    fclose(file);
    printf("Du lieu sach da duoc luu vao file 'books.txt'.\n");
}

void loadBooksFromFile() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file de doc du lieu.\n");
        return;
    }

    while (fscanf(file, "%d\n", &books[bookCount].id) == 1) {
        fgets(books[bookCount].title, sizeof(books[bookCount].title), file);
        books[bookCount].title[strcspn(books[bookCount].title, "\n")] = 0;
        fgets(books[bookCount].author, sizeof(books[bookCount].author), file);
        books[bookCount].author[strcspn(books[bookCount].author, "\n")] = 0;
        fscanf(file, "%d\n", &books[bookCount].quantity);
        fscanf(file, "%f\n", &books[bookCount].price);
        fscanf(file, "%d/%d/%d\n", &books[bookCount].publication.month, 
               &books[bookCount].publication.day, &books[bookCount].publication.year);

        bookCount++;
    }

    fclose(file);
    printf("Du lieu sach da duoc tai tu file 'books.txt'.\n");
}
void libMenu() {
	int choice;
    do {
        printf("\n==================== QUAN LY SACH ====================\n");
        printf("1. Hien thi danh sach sach\n");
        printf("2. Them sach\n");
        printf("3. Sua thong tin sach\n");
        printf("4. Xoa sach\n");
        printf("5. Sap xep sach theo gia tien\n");
        printf("6. Tim kiem sach theo ten\n");
        printf("7. Mo file du lieu sach\n");
        printf("8. Thoat\n");
        printf("========================================================\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                displayBooks();
                break;
            case 2:
                addBook();
                break;
            case 3:
                editBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                sortBooksByPrice();
                break;
            case 6:
                searchBooksByName();
                break;
            case 7:
                openBooksFromFile(); 
                break;
            case 8:
                saveBooksToFile();
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 8);
}
void customerMenu() {
	int choice;
    do{
        printf("\n==================== QUAN LY KHACH HANG ====================\n");
    	printf("1. Hien thi danh sach khach hang\n");
    	printf("2. Them khach hang\n");
    	printf("3. Sua thong tin khach hang\n");
    	printf("4. Khoa/Mo khoa khach hang\n");
    	printf("5. Tim kiem khach hang theo ten\n");
    	printf("6. Muon sach\n");
    	printf("7. Tra lai sach\n");
    	printf("8. Luu du lieu khach hang vao file\n");
    	printf("9. Mo du lieu khach hang tu file\n");
    	printf("10. Thoat\n");
    	printf("========================================================\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                showCustomerList();
                break;
            case 2:
                addCustomer();
                break;
            case 3:
                editCustomer();
                break;
            case 4:
                lockUnlockCustomer();
                break;
            case 5:
                searchCustomerByName();
                break;
            case 6:
                borrowBook();
                break;
            case 7:
                returnBook();
                break;
            case 8:            
            	default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    }while (choice!=8);
}
void showCustomerList() {
    printf("ID\tTen\tSdt\tTrang thai\n");
    for (int i = 0; i < customerCount; i++) {
        printf("%d\t%s\t%s\t%s\n", customers[i].id, customers[i].name, customers[i].phone, customers[i].status);
    }
}
int findCustomerById(int id) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].id == id) {
            return i;
        }
    }
    return -1;
}
int findBookById(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            return i;
        }
    }
    return -1;
}

void addCustomer() {
    struct Customer newCustomer;
    printf("Nhap ID khach hang: ");
    scanf("%d", &newCustomer.id);
    getchar();
    if (findCustomerById(newCustomer.id) != -1) {
        printf("ID khach hang da ton tai!\n");
        return;
    }
    printf("Nhap ten khach hang: ");
    fgets(newCustomer.name, sizeof(newCustomer.name), stdin);
    newCustomer.name[strcspn(newCustomer.name, "\n")] = '\0';
    int validPhone = 0;
    while (!validPhone) {
        printf("Nhap so dien thoai khach hang: ");
        fgets(newCustomer.phone, sizeof(newCustomer.phone), stdin);
        newCustomer.phone[strcspn(newCustomer.phone, "\n")] = '\0';
        if (strlen(newCustomer.phone) >= 10) {
            validPhone = 1;
        } else {
            printf("So dien thoai khong hop le, vui long nhap lai!\n");
        }
    }
    printf("Nhap dia chi khach hang: ");
    fgets(newCustomer.address, sizeof(newCustomer.address), stdin);
    newCustomer.address[strcspn(newCustomer.address, "\n")] = '\0';
    printf("Nhap email khach hang: ");
    fgets(newCustomer.email, sizeof(newCustomer.email), stdin);
    newCustomer.email[strcspn(newCustomer.email, "\n")] = '\0';
    strcpy(newCustomer.status, "Active");
    newCustomer.borrowedCount = 0;
    customers[customerCount] = newCustomer;
    customerCount++;
    printf("Them khach hang thanh cong!\n");
}
void editCustomer() {
    int id;
    printf("Nhap ID khach hang muon sua: ");
    scanf("%d", &id);
    int index = findCustomerById(id);
    if (index == -1) {
        printf("Khach hang khong ton tai!\n");
        return;
    }
    printf("Dang sua khach hang: %s\n", customers[index].name);
    getchar();
    printf("Nhap ten moi: ");
    fgets(customers[index].name, sizeof(customers[index].name), stdin);
    customers[index].name[strcspn(customers[index].name, "\n")] = '\0';
    printf("Nhap so dien thoai moi: ");
    fgets(customers[index].phone, sizeof(customers[index].phone), stdin);
    customers[index].phone[strcspn(customers[index].phone, "\n")] = '\0';
    printf("Nhap dia chi moi: ");
    fgets(customers[index].address, sizeof(customers[index].address), stdin);
    customers[index].address[strcspn(customers[index].address, "\n")] = '\0';
    printf("Nhap email moi: ");
    fgets(customers[index].email, sizeof(customers[index].email), stdin);
    customers[index].email[strcspn(customers[index].email, "\n")] = '\0';

    printf("Cap nhat thong tin khach hang thanh cong!\n");
}

void lockUnlockCustomer() {
    int id;
    printf("Nhap ID khach hang muon khoa/mo khoa: ");
    scanf("%d", &id);
    int index = findCustomerById(id);
    if (index == -1) {
        printf("Khach hang khong ton tai!\n");
        return;
    }

    if (strcmp(customers[index].status, "Locked") == 0) {
        strcpy(customers[index].status, "Active");
        printf("Khach hang mo khoa thanh cong!\n");
    } else {
        strcpy(customers[index].status, "Locked");
        printf("Khach hang khoa thanh cong!\n");
    }
}

void searchCustomerByName() {
    char name[100];
    getchar();
    printf("Nhap ten khach hang de tim kiem: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    int found = 0;
    printf("ID\tTen\tSdt\tTrang thai\n");
    for (int i = 0; i < customerCount; i++) {
        if (strstr(customers[i].name, name)) {
            printf("%d\t%s\t%s\t%s\n", customers[i].id, customers[i].name, customers[i].phone, customers[i].status);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay khach hang!\n");
    }
}

void borrowBook() {
    int customerId, bookId, quantity;
    printf("Nhap ID khach hang: ");
    scanf("%d", &customerId);
    int customerIndex = findCustomerById(customerId);
    if (customerIndex == -1) {
        printf("Khach hang khong ton tai!\n");
        return;
    }
    if (strcmp(customers[customerIndex].status, "Locked") == 0) {
        printf("Khach hang bi khoa!\n");
        return;
    }
    if (customers[customerIndex].borrowedCount >= 5) {
        printf("Khach hang da muon toi da 5 cuon sach!\n");
        return;
    }
    printf("Nhap ID sach muon muon: ");
    scanf("%d", &bookId);
    int bookIndex = findBookById(bookId);
    if (bookIndex == -1) {
        printf("Sach khong ton tai!\n");
        return;
    }

    printf("Nhap so luong sach muon: ");
    scanf("%d", &quantity);
    if (quantity <= 0 || quantity > books[bookIndex].quantity) {
        printf("So luong sach khong hop le!\n");
        return;
    }
    books[bookIndex].quantity -= quantity;
    customers[customerIndex].borrowedBooks[customers[customerIndex].borrowedCount] = bookId;
    customers[customerIndex].borrowedCount++;
    printf("Muon sach thanh cong!\n");
}

void returnBook() {
    int customerId, bookId;
    printf("Nhap ID khach hang: ");
    scanf("%d", &customerId);
    int customerIndex = findCustomerById(customerId);
    if (customerIndex == -1) {
        printf("Khach hang khong ton tai!\n");
        return;
    }
    printf("Nhap ID sach muon tra: ");
    scanf("%d", &bookId);
    int bookIndex = findBookById(bookId);
    if (bookIndex == -1) {
        printf("Sach khong ton tai!\n");
        return;
    }
    books[bookIndex].quantity++;
    for (int i = 0; i < customers[customerIndex].borrowedCount; i++) {
        if (customers[customerIndex].borrowedBooks[i] == bookId) {
            for (int j = i; j < customers[customerIndex].borrowedCount - 1; j++) {
                customers[customerIndex].borrowedBooks[j] = customers[customerIndex].borrowedBooks[j + 1];
            }
            customers[customerIndex].borrowedCount--;
            break;
        }
    }
    printf("Tra lai sach thanh cong!\n");
}

int authenticateAdmin() {
    char inputUsername[50], inputPassword[50];
    char storedUsername[50], storedPassword[50];
    FILE *file = fopen("admin.txt", "r");

    if (file == NULL) {
        printf("Khong tim thay file luu tru tai khoan admin.\n");
        return 0;
    }

    fgets(storedUsername, sizeof(storedUsername), file);
    storedUsername[strcspn(storedUsername, "\n")] = 0; 

    fgets(storedPassword, sizeof(storedPassword), file);
    storedPassword[strcspn(storedPassword, "\n")] = 0; 

    fclose(file);

    printf("Nhap tai khoan admin: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    inputUsername[strcspn(inputUsername, "\n")] = 0; 

    printf("Nhap mat khau admin: ");
    int i = 0;
    while (1) {
        inputPassword[i] = getch(); 
        if (inputPassword[i] == '\r') { 
            inputPassword[i] = '\0';  
            break;
        }
        printf("*");  
        i++;
    }

    if (strcmp(inputUsername, storedUsername) == 0 && strcmp(inputPassword, storedPassword) == 0) {
        return 1; 
    } else {
        printf("\nTai khoan hoac mat khau sai. Vui long nhap lai.\n");
        return 0; 
    }
}

void saveAdminAccount(const char* username, const char* password) {
    FILE *file = fopen("admin.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file de luu tai khoan.\n");
        return;
    }
    fprintf(file, "%s\n", username);  
    fprintf(file, "%s\n", password);  
    fclose(file);
}

void registerAdmin() {
    char username[50], password[50];

    printf("Tao tai khoan admin moi:\n");
    printf("Nhap tai khoan: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Nhap mat khau: ");
    int i = 0;
    while (1) {
        password[i] = getch();
        if (password[i] == '\r') {
            password[i] = '\0';
            break;
        }
        printf("*");
        i++;
    }

    saveAdminAccount(username, password);
    printf("\nTai khoan admin moi da duoc tao!\n");
}

