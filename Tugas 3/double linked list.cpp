
#include <stdio.h>
#include <stdlib.h> 

//========================================================

struct node {
    int data;
    struct node *next;
    struct node *prev; // New pointer to the previous node
};
typedef struct node node;

void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void jumlahData(node *head);
void sumData(node *head);
void tranverse(node *head);

//========================================================

int main() {
    node *head;
    char pilih;

    head = NULL;
    do {
        // Clear the screen (platform-specific)
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("masukkan pilihan\n");
        printf("1. tambah data di awal\n");
        printf("2. tambah data di tengah list\n");
        printf("3. tambah data di akhir list\n");
        printf("4. cetak isi list\n");
        printf("5. hapus data di awal\n");
        printf("6. hapus data di tengah\n");
        printf("7. hapus data di akhir\n");
        printf("8. cari data dalam list\n");
        printf("9. jumlah data dalam list\n");
        printf("0. jumlahkan semua data dalam list\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf(" %c", &pilih);

        if (pilih == '1')
            tambahAwal(&head);
        else if (pilih == '2')
            tambahData(&head);
        else if (pilih == '3')
            tambahAkhir(&head);
        else if (pilih == '4') {
            tranverse(head);
            getchar();  // Wait for key press to continue
        }
        else if (pilih == '5')
            hapusAwal(&head);
        else if (pilih == '6')
            hapusTengah(&head);
        else if (pilih == '7')
            hapusAkhir(&head);
        else if (pilih == '8') {
            cariData(head);
            getchar();  // Wait for key press to continue
        }
        else if (pilih == '9') {
            jumlahData(head);
            getchar();  // Wait for key press to continue
        }
        else if (pilih == '0') {
            sumData(head);
            getchar();  // Wait for key press to continue
        }
    } while (pilih != 'q');

    return 0;
}

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew;

    system("clear");
    fflush(stdin);
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = *head;
        pNew->prev = NULL; // No previous node for the first element
        if (*head != NULL) {
            (*head)->prev = pNew; // Update the previous head's prev pointer
        }
        *head = pNew;
    } else {
        printf("Alokasi memori gagal");
        getchar();
    }
}

//========================================================

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("clear");
    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan : ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL) {
        printf("\nnode tidak ditemukan");
        getchar();
    } else if (pNew == NULL) {
        printf("\nalokasi memeori gagal");
        getchar();
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pNew->prev = pCur; // New node points back to the current node
        if (pCur->next != NULL) {
            pCur->next->prev = pNew; // Update the next node's prev pointer
        }
        pCur->next = pNew;
    }
}

//========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("clear");
    fflush(stdin);
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;

        if (*head == NULL) {
            pNew->prev = NULL;
            *head = pNew;
        } else {
            pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
            pNew->prev = pCur; // Link the new node to the last node
        }
    } else {
        printf("Alokasi memori gagal");
        getchar();
    }
}

//========================================================

void hapusAwal(node **head) {
    node *pDel;

    system("clear");
    if (*head != NULL) {
        pDel = *head;
        *head = (*head)->next;
        if (*head != NULL) {
            (*head)->prev = NULL; // Update the new head's prev pointer
        }
        free(pDel);
        printf("Data pertama berhasil dihapus\n");
    } else {
        printf("List kosong\n");
    }
    getchar();
}

//========================================================

void hapusTengah(node **head) {
    int pos;
    node *pCur;

    system("clear");
    tranverse(*head);
    printf("\nMasukkan data yang ingin dihapus : ");
    fflush(stdin);
    scanf("%d", &pos);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("Data tidak ditemukan\n");
    } else {
        if (pCur->prev != NULL) {
            pCur->prev->next = pCur->next;
        } else {
            *head = pCur->next;
        }
        if (pCur->next != NULL) {
            pCur->next->prev = pCur->prev;
        }
        free(pCur);
        printf("Data berhasil dihapus\n");
    }
    getchar();
}

//========================================================

void hapusAkhir(node **head) {
    node *pCur;

    system("clear");
    if (*head != NULL) {
        pCur = *head;
        while (pCur->next != NULL) {
            pCur = pCur->next;
        }
        if (pCur->prev != NULL) {
            pCur->prev->next = NULL;
        } else {
            *head = NULL;
        }
        free(pCur);
        printf("Data terakhir berhasil dihapus\n");
    } else {
        printf("List kosong\n");
    }
    getchar();
}

//========================================================

void cariData(node *head) {
    int bil;
    node *pCur;

    system("clear");
    printf("Masukkan bilangan yang ingin dicari: ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = head;
    while (pCur != NULL) {
        if (pCur->data == bil) {
            printf("Data ditemukan: %d\n", bil);
            return;
        }
        pCur = pCur->next;
    }
    printf("Data tidak ditemukan\n");
}

//========================================================

void jumlahData(node *head) {
    int count = 0;
    node *pCur = head;

    while (pCur != NULL) {
        count++;
        pCur = pCur->next;
    }
    printf("Jumlah data dalam list: %d\n", count);
}

//========================================================

void sumData(node *head) {
    int sum = 0;
    node *pCur = head;

    while (pCur != NULL) {
        sum += pCur->data;
        pCur = pCur->next;
    }
    printf("Jumlah total dari semua data: %d\n", sum);
}

//========================================================

void tranverse(node *head) {
    node *pWalker;

    system("clear");
    pWalker = head;
    while (pWalker != NULL) {
        printf("%d\t", pWalker->data);
        pWalker = pWalker->next;
        printf(" -> ");
    }
    printf("NULL\n");

    // Optional: print in reverse (backward traversal)
    printf("Reverse Traversal:\n");
    if (head != NULL) {
        pWalker = head;
        while (pWalker->next != NULL) {
            pWalker = pWalker->next;
        }
        while (pWalker != NULL) {
            printf("%d\t", pWalker->data);
            pWalker = pWalker->prev;
            printf(" <- ");
        }
        printf("NULL\n");
    }
}