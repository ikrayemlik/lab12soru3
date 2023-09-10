#include <stdio.h>
#include <stdlib.h>
/*2) Öðrenci bilgilerinden (öðrenci no, isim, bölüm) oluþan rastgele eriþimli
bir dosya oluþturan ve bu dosya içerisinde öðrenci no’ya göre arama
yapan programý yazýnýz. Program menü þeklinde hazýrlanmalýdýr. Dosya
oluþturma, kayýt ekleme gibi gerekli tüm fonksiyonlar yazýlmalýdýr.*/


struct ogrencibilgi{
    int ogrno;
    char ad[50];
    char bolum[50];
};
//kayýt ekleme
void kayitekle(FILE *fptr)
{
    int no;
    struct ogrencibilgi ogrenci={0,"",""};
    printf("yeni ogrenci no gir");
    scanf("%d",&no);

    fseek(fptr,(no-1)*sizeof(struct ogrencibilgi),SEEK_SET);
    fread(&ogrenci,sizeof(struct ogrencibilgi),1,fptr);

    if(ogrenci.ogrno!=0)
    {
        printf("%d nolu ogrenci zaten mevcut",no);

    }
    else
    {
        printf("ogrno,ad ve bolum gir");
        scanf("%d %s %s",&ogrenci.ogrno,ogrenci.ad,ogrenci.bolum);
        ogrenci.ogrno=no;
        fseek(fptr,(no-1)*sizeof(struct ogrencibilgi),SEEK_SET);
        fwrite(&ogrenci,sizeof(struct ogrencibilgi),1,fptr);
    }
}
// kayit silme
void kayitsil(FILE *fptr)
{
    struct ogrencibilgi ogrenci,bosogr={0,"",""};
    int no;
    printf("silmek istediginiz ogrenci no giriniz");
    scanf("%d",&no);

    fseek(fptr,(no-1)*sizeof(struct ogrencibilgi),SEEK_SET);
    fread(&ogrenci,sizeof(struct ogrencibilgi),1,fptr);
if (ogrenci.ogrno==0)
{
    printf("%d nolu ogrenci kaydi bulunmamaktadir",no);
}
else
{
    fseek(fptr,(no-1)*sizeof(struct ogrencibilgi),SEEK_SET);
    fwrite(&bosogr,sizeof(struct ogrencibilgi),1,fptr);
}
}
void ogrenciarama(FILE*fptr)
{
    struct ogrencibilgi ogrenci={0,"",""};
    int arananno;
    printf("aramak istediðiniz ogrenci numarasýný giriniz");
    scanf("%d",&arananno);
     fseek(fptr,(arananno-1)*sizeof(struct ogrencibilgi),SEEK_SET);
     fread(&ogrenci,sizeof(struct ogrencibilgi),1,fptr);
     if(ogrenci.ogrno==0)
     {
         printf("aradiginiz ogrenci bulunmamaktadir");
     }
     else
     {
        printf("Ogrenci No: %d\n", ogrenci.ogrno);
        printf("Ad: %s\n", ogrenci.ad);
        printf("Bolum: %s\n", ogrenci.bolum);
     }
}
//secim girme
int secimgir()
{
    int menusecim;
    printf("secim yap");
    printf("1-yeni kayit ekle\n"
           "2-mevcut kayiti silme\n"
           "3-aranan ogrenciyi bulma\n"
           "4-listeleme\n"
            "5-cikis\n?");
           scanf("%d",&menusecim);
           return menusecim;
}
void listeleme(FILE *fptr)
{
    struct ogrencibilgi ogrenci={0,"",""};
    printf("%-10s%-16s%-11s%10s\n","OGRNO","AD","BOLUM");
     while(!feof(fptr))
     {
         fread(&hesapbilgi,sizeof(struct ogrencibilgi),1,fptr);
         if(ogrenci.ogrno!=0)
         {
             printf("%d %s %s",ogrenci.ogrno,ogrenci.ad,ogrenci.bolum);
         }

     }
}

int main()
{
    FILE *dosya;
    int secim;
    if((dosya=fopen("ogrenci.txt","r+"))==NULL)
    {
        printf("dosya acilamadi");
    }
    else
    {
        while((secim=secimgir())!=5)
        {
            switch(secim)
            {
                case 1: kayitekle(dosya); break;
                case 2: kayitsil(dosya);  break;
                case 3: ogrenciarama(dosya); break;
                case 4: listeleme(dosya); break;

            }

        }
        fclose(dosya);
    }
    return 0;
}
