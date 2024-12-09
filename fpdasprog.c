#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototipe fungsi
void bacaDNAfile(char *namaFile, char *dna);
void mutasiDNA(char *dna, char target, char pengganti, int kelipatan, int *jumlahMutasi);
float hitungpersentasemutasi(int jumlahMutasi, int panjang);
void transkripsikeMRNA(char *dna, char *mrna);
void bagikodon(char *mrna, char kodon[][4], int *jumlahKodon);
void terjemahkankodon(char kodon[][4], int jumlahKodon, char *asamAmino);

// Fungsi utama
int main() {
    char dna[1000], mrna[1000];
    char kodon[400][4]; // Maksimal 333 kodon untuk mRNA panjang 1000
    char asamAmino[400];
    int jumlahMutasi = 0, jumlahKodon = 0;

    // Langkah 1: Membaca urutan DNA dari file
    bacaDNAfile("dna.txt", dna);
    printf("DNA Asli: %s\n", dna);

    // Langkah 2: Melakukan mutasi DNA
    char basaTarget = 'G', basaPengganti = 'T';
    int kelipatan = 5;
    mutasiDNA(dna, basaTarget, basaPengganti, kelipatan, &jumlahMutasi);
    printf("DNA Setelah Mutasi: %s\n", dna);

    // Langkah 3: Menghitung persentase mutasi
    float persentaseMutasi = hitungpersentasemutasi(jumlahMutasi, strlen(dna));
    printf("Persentase Mutasi: %.2f%%\n", persentaseMutasi);

    // Langkah 4: Transkripsi DNA ke mRNA
    transkripsikeMRNA(dna, mrna);
    printf("mRNA: %s\n", mrna);

    // Langkah 5: Membagi mRNA menjadi kodon
    bagikodon(mrna, kodon, &jumlahKodon);
    printf("Kodon:\n");
    for (int i = 0; i < jumlahKodon; i++) {
        printf("%s ", kodon[i]);
    }
    printf("\n");

    // Langkah 6: Menerjemahkan kodon menjadi asam amino
    terjemahkankodon(kodon, jumlahKodon, asamAmino);
    printf("Asam Amino: %s\n", asamAmino);

    return 0;
}

// Implementasi fungsi
void bacaDNAfile(char *namaFile, char *dna) {
    FILE *file = fopen(namaFile, "r");
    if (!file) {
        printf("Error: Tidak dapat membuka file %s\n", namaFile);
        exit(1);
    }
    fscanf(file, "%s", dna);
    fclose(file);
}

void mutasiDNA(char *dna, char target, char pengganti, int kelipatan, int *jumlahMutasi) {
    int panjang = strlen(dna);
    for (int i = 0; i < panjang; i++) {
        if ((i + 1) % kelipatan == 0 && dna[i] == target) {
            dna[i] = pengganti;
            (*jumlahMutasi)++;
        }
    }
}

float hitungpersentasemutasi(int jumlahMutasi, int panjang) {
    return (jumlahMutasi / (float)panjang) * 100;
}

void transkripsikeMRNA(char *dna, char *mrna) {
    int panjang = strlen(dna);
    for (int i = 0; i < panjang; i++) {
        switch (dna[i]) {
            case 'A': mrna[i] = 'U'; break;
            case 'T': mrna[i] = 'A'; break;
            case 'G': mrna[i] = 'C'; break;
            case 'C': mrna[i] = 'G'; break;
        }
    }
    mrna[panjang] = '\0';
}

void bagikodon(char *mrna, char kodon[][4], int *jumlahKodon) {
    int panjang = strlen(mrna);
    *jumlahKodon = 0;
    for (int i = 0; i < panjang; i += 3) {
        strncpy(kodon[*jumlahKodon], &mrna[i], 3);
        kodon[*jumlahKodon][3] = '\0'; // Akhiri kodon dengan null
        (*jumlahKodon)++;
    }
}


void terjemahkankodon(char kodon[][4], int jumlahKodon, char *asamAmino) {
    for (int i = 0; i < jumlahKodon; i++) {
        if (strcmp(kodon[i], "AUG") == 0) asamAmino[i] = 'M'; // Metionin
        else if (strcmp(kodon[i], "UUU") == 0 || strcmp(kodon[i], "UUC") == 0) asamAmino[i] = 'F'; // Fenilalanin
        else if (strcmp(kodon[i], "UUA") == 0 || strcmp(kodon[i], "UUG") == 0) asamAmino[i] = 'L'; // Leusin
        else if (strcmp(kodon[i], "CUU") == 0 || strcmp(kodon[i], "CUC") == 0 || strcmp(kodon[i], "CUA") == 0 || strcmp(kodon[i], "CUG") == 0) asamAmino[i] = 'L'; // Leusin
        else if (strcmp(kodon[i], "AUU") == 0 || strcmp(kodon[i], "AUC") == 0 || strcmp(kodon[i], "AUA") == 0) asamAmino[i] = 'I'; // Isoleusin
        else if (strcmp(kodon[i], "GUU") == 0 || strcmp(kodon[i], "GUC") == 0 || strcmp(kodon[i], "GUA") == 0 || strcmp(kodon[i], "GUG") == 0) asamAmino[i] = 'V'; // Valin
        else if (strcmp(kodon[i], "CAU") == 0) asamAmino[i] = 'H'; // Histidin
        else if (strcmp(kodon[i], "GAA") == 0) asamAmino[i] = 'E'; // Glutamat
        else if (strcmp(kodon[i], "CGU") == 0) asamAmino[i] = 'A'; // Glutamat
        else asamAmino[i] = '?'; // Tidak diketahui
    // TAMBAHIN KODON ANJENG
    }
    asamAmino[jumlahKodon] = '\0'; // Null terminator untuk string asam amino
}

