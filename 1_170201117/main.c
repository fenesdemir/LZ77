#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define OFFSET 5
#define BOYUT 3

#define OFFSETMAX 31
#define BOYUTMAX 7

#define DUGUMOFFSET(x,y) ((x << 3) | y)

struct lz77_dugum{
    uint8_t offset;
    char c;
};

int eslesme(int sinir, char *str1, char *str2){

    int i = 0;

    while(i < sinir && *str1++ == *str2++){
        i++;
    }

    return i;
}

struct lz77_dugum *lz77( char *metin, int kacKarakter, int *dugumSayisi){

    int hafiza = 1;
    int kacDugumVar = 0;
    char *ileri, *arama;

    struct lz77_dugum d;
    struct lz77_dugum *sikistirilmis = malloc(hafiza * sizeof(struct lz77_dugum));

    for(ileri = metin; ileri < (metin + kacKarakter); ileri++){
        arama = ileri - OFFSETMAX;

        if(arama < metin){
            arama = metin;
        }

        int eslesmeUzunluk = 0;

        char *enUzunEslesme = ileri;

        for(;arama < ileri; arama++){
            int uzunluk = eslesme(BOYUTMAX, arama, ileri);

            if(uzunluk > eslesmeUzunluk){
                eslesmeUzunluk = uzunluk;
                enUzunEslesme = arama;
            }
        }

        if((ileri + eslesmeUzunluk) >= (metin + kacKarakter)){
            eslesmeUzunluk = metin + kacKarakter - ileri - 1;
        }

        d.offset = DUGUMOFFSET((ileri - enUzunEslesme), eslesmeUzunluk);
        ileri = ileri + eslesmeUzunluk;
        d.c = *ileri;

        if((kacDugumVar + 1) > hafiza){
            hafiza = hafiza * 2;
            sikistirilmis = realloc(sikistirilmis, hafiza * sizeof(struct lz77_dugum));
        }

        sikistirilmis[kacDugumVar++] = d;

    }

    if(dugumSayisi){
        *dugumSayisi = kacDugumVar;
    }

    return sikistirilmis;
}

char *dosyaOku(FILE *f, int *boyut)
{
    char *icerik;
    fseek(f, 0, SEEK_END);
    *boyut = ftell(f);
    icerik = malloc(*boyut);
    fseek(f, 0, SEEK_SET);
    fread(icerik, 1, *boyut, f);
    return icerik;
}

int main(){
    FILE *f;
    int metinBoyutu, dugumSayisi, sikistirilmisMetinBoyutu;
    char *kaynak_metin;
    struct dugum *sikistirilmis_metin;

    if (f = fopen("metin.txt", "r")){

        kaynak_metin = dosyaOku(f, &metinBoyutu);
        fclose(f);
    }else{

        printf("Hata sikistirilacak metin belgesi bulunamadi.\n");
        return EXIT_FAILURE;
    }

    sikistirilmis_metin = lz77(kaynak_metin, metinBoyutu, &dugumSayisi);

    if (f = fopen("lz77_cikti.txt", "w"))
    {
        fwrite(sikistirilmis_metin, sizeof(struct lz77_dugum), dugumSayisi, f);
        fclose(f);
    }

    sikistirilmisMetinBoyutu = dugumSayisi * sizeof(struct lz77_dugum);

    printf("Orijinal metnin boyutu: %d, Sikistirilmis metnin boyutu: %d\n", metinBoyutu, sikistirilmisMetinBoyutu);

    if(metinBoyutu > sikistirilmisMetinBoyutu){

        float yuzde = ((sikistirilmisMetinBoyutu *100) / metinBoyutu);
        printf("Metin boyutu kuculmustur. Metin yuzde %f oraninda sikistirilmistir. LZ77 algoritmasinin burada kullanilmasi uygundur.\n", yuzde);

    }else if(metinBoyutu < sikistirilmisMetinBoyutu){

        float yuzde = ((sikistirilmisMetinBoyutu *100) / metinBoyutu);
        printf("Metin boyutu butumustur. Metin yuzde %f oraninda genislemistir. LZ77 algoritmasinin burada kullanilmasi uygun degildir.\n", yuzde);

    }else{

        printf("Metin boyutunda bir degisiklik olmamistir.\n");
    }

    return 0;
}
