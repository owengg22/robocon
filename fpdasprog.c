#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//membaca file dari dna
void bacafile(char *namafile, char *dna) {
    FILE *file = fopen(namafile, "r");
    if (!file) {
        printf("file tidak terdeteksi %s\n", namafile);
        exit(1);
    }
    fscanf(file, "%s", dna);
    fclose(file);
}

//digunakan untuk melakukan mutasi
void mutasidna(char *dna, char target, char pengganti, int kelipatan, int *jumlahmutasi) {
    int panjang = strlen(dna);
    for (int i = 0; i < panjang; i++) {
        if ((i + 1) % kelipatan == 0 && dna[i] == target) {
            dna[i] = pengganti;
            (*jumlahmutasi)++;
        }
    }
}

//digunakan untuk menghitung persentase mutasi
float persentasemutasi(int jumlahmutasi, int panjang) {
    return (jumlahmutasi / (float)panjang) * 100;
}

// digunakan untuk transkripsi DNA ke mRNA
void transkripsikemrna(char *dna, char *mrna) {
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

// membagi mRNA menjadi kodon
void bagikodon(char *mrna, char kodon[][4], int *jumlahkodon) {
    int panjang = strlen(mrna);
    *jumlahkodon = 0;
    for (int i = 0; i < panjang; i += 3) {
        strncpy(kodon[*jumlahkodon], &mrna[i], 3);
        kodon[*jumlahkodon][3] = '\0'; // Akhiri kodon dengan null
        (*jumlahkodon)++;
    }
}

//menerjemahkan kodon menjadi asam amino
void terjemahkankodon(char kodon[][4], int jumlahkodon, char *asamamino) {
    for (int i = 0; i < jumlahkodon; i++) {
        if (strcmp(kodon[i], "AUG") == 0) asamamino[i] = 'M'; // Metionin
        else if (strcmp(kodon[i], "UUU") == 0 || strcmp(kodon[i], "UUC") == 0) asamamino[i] = 'F'; // Fenilalanin
        else if (strcmp(kodon[i], "UUA") == 0 || strcmp(kodon[i], "UUG") == 0) asamamino[i] = 'L'; // Leusin
        else if (strcmp(kodon[i], "CUU") == 0 || strcmp(kodon[i], "CUC") == 0 || strcmp(kodon[i], "CUA") == 0 || strcmp(kodon[i], "CUG") == 0) asamamino[i] = 'L'; // Leusin
        else if (strcmp(kodon[i], "AUU") == 0 || strcmp(kodon[i], "AUC") == 0 || strcmp(kodon[i], "AUA") == 0) asamamino[i] = 'I'; // Isoleusin
        else if (strcmp(kodon[i], "GUU") == 0 || strcmp(kodon[i], "GUC") == 0 || strcmp(kodon[i], "GUA") == 0 || strcmp(kodon[i], "GUG") == 0) asamamino[i] = 'V'; // Valin
        else if (strcmp(kodon[i], "CAU") == 0) asamamino[i] = 'H'; // Histidin
        else if (strcmp(kodon[i], "GAA") == 0) asamamino[i] = 'E'; // Glutamat
        else if (strcmp(kodon[i], "CGU") == 0) asamamino[i] = 'A'; // Arginin
        else asamamino[i] = '?'; // Tidak diketahui
    }
    asamamino[jumlahkodon] = '\0'; // Null terminator untuk string asam amino
}


int main() {
    char dna[1000], mrna[1000];
    char kodon[400][4];
    char asamamino[400];
    int jumlahmutasi = 0, jumlahkodon = 0;

    // Membaca urutan DNA dari file
    bacafile("dna.txt", dna);
    printf("DNA Asli: %s\n", dna);

    // Melakukan mutasi DNA
    char basatarget = 'G', basapengganti = 'T';
    int kelipatan = 5;
    mutasidna(dna, basatarget, basapengganti, kelipatan, &jumlahmutasi);
    printf("DNA Setelah Mutasi: %s\n", dna);

    // Menghitung persentase mutasi
    float persentase = persentasemutasi(jumlahmutasi, strlen(dna));
    printf("Persentase Mutasi: %.2f%%\n", persentase);

    // Transkripsi DNA ke mRNA
    transkripsikemrna(dna, mrna);
    printf("mRNA: %s\n", mrna);

    // Membagi mRNA menjadi kodon
    bagikodon(mrna, kodon, &jumlahkodon);
    printf("Kodon:\n");
    for (int i = 0; i < jumlahkodon; i++) {
        printf("%s ", kodon[i]);
    }
    printf("\n");

    // Menerjemahkan kodon menjadi asam amino
    terjemahkankodon(kodon, jumlahkodon, asamamino);
    printf("Asam Amino: %s\n", asamamino);

    return 0;
}
