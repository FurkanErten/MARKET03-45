#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

char secim;
char buffer[256];

typedef struct
{
	int ID;
	char* malinAdi;
	char* kategori;
	char* alt_kategori;
	int adet;
	float fiyati;
	char* konumu;
} URUNLER;



void dosyadan_Oku(URUNLER[], int*);
void ekrana_Yaz(URUNLER[], int);
void urun_ekleme(URUNLER[], int*);
void urun_arama(URUNLER[], int);
void urun_guncelleme(URUNLER[], int);
void urun_kategori(URUNLER[], int);



int main()
{
	// Gerekli deger atamalari.
	URUNLER mallar[100];
	int mal_sayisi = 0;

	//Dosyadan verileri okuma.
	dosyadan_Oku(mallar, &mal_sayisi);

	//Dosyadan verileri yazma.
	while (true)
	{
		ekrana_Yaz(mallar, mal_sayisi);

		printf("\n\n\tLutfen yapmak istediginiz islemi seciniz.\n\n\t1. Yeni urun ekleme.\n\n\t2. Urun arama.\n\n\t3. Stok guncelleme.\n\n\t4. Urunleri kategori et.\n\n\t5. Ekrani guncelle.\n\n\t6. Kapat.");


		secim = _getch();



		if (secim == '1')
		{

			urun_ekleme(mallar, &mal_sayisi);

		}
		else if (secim == '2')
		{
			urun_arama(mallar, mal_sayisi);

		}
		else if (secim == '3')
		{
			urun_guncelleme(mallar, mal_sayisi);

		}
		else if (secim == '4')
		{
			urun_kategori(mallar, mal_sayisi);

		}
		else if (secim == '5')
		{
			ekrana_Yaz(mallar, mal_sayisi);
		}
		else if (secim == '6')
		{
			return 0;
		}
		else
		{

			printf("\n\n\nLutfen dogru kodu giriniz.");

			secim = _getch();
		}
	}

	return 0;


}
void dosyadan_Oku(URUNLER mallar[], int* mal_sayisi)
{
	system("cls");
	// Urunlerin dosyasini okuma kodu.
	FILE* dosya = fopen("products.txt", "r");
	

	// Dosya acilmamasina karsilik onlem.
	if (dosya == NULL)
	{
		printf("Dosya Acilmadi...\n");
		exit(1);

	}
	else
	{
		//Dosyadan verileri alma kismi.

		printf("Dosya okunuyor...\n\n");

		// Ýlk satýrý atlamak için bir kez fgets çaðýrýlýr
		fgets(buffer, sizeof(buffer), dosya);

		// Dosyadan verileri alma kýsmý
		while (fgets(buffer, sizeof(buffer), dosya) != NULL)
		{
			if (*mal_sayisi >= 100) {
				printf("Dizinin sýnýrýna ulaþýldý. Daha fazla veri eklenemez.\n");
				break;
			}


			mallar[*mal_sayisi].malinAdi = (char*)malloc(50 * sizeof(char));
			mallar[*mal_sayisi].kategori = (char*)malloc(50 * sizeof(char));
			mallar[*mal_sayisi].alt_kategori = (char*)malloc(50 * sizeof(char));
			mallar[*mal_sayisi].konumu = (char*)malloc(50 * sizeof(char));

			sscanf(buffer, "%d,%49[^,],%49[^,],%49[^,],%f,%d,%49[^\n]",
				&mallar[*mal_sayisi].ID,
				mallar[*mal_sayisi].malinAdi,
				mallar[*mal_sayisi].kategori,
				mallar[*mal_sayisi].alt_kategori,
				&mallar[*mal_sayisi].fiyati,
				& mallar[*mal_sayisi].adet,
				mallar[*mal_sayisi].konumu);

			(*mal_sayisi)++;
		}




	}



	fclose(dosya);

}
void ekrana_Yaz(URUNLER mallar[], int mal_sayisi) 
{
	// urunlerin ekrana yazdirma.

	system("cls");

	printf("ID   %-20s %-20s %-20s %-10s %-10s %-15s\n", "Urun Ismi", "Kategori", "Alt Kategori", "Adeti", "Fiyati", "Magzadaki Yeri");
	printf("--------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < mal_sayisi; i++) {
		printf("%-4d %-20s %-20s %-20s %-10d %-10.2f %-15s\n",
			mallar[i].ID,
			mallar[i].malinAdi,
			mallar[i].kategori,
			mallar[i].alt_kategori,
			mallar[i].adet,
			mallar[i].fiyati,
			mallar[i].konumu);
	}


}
void urun_ekleme(URUNLER mallar[], int* mal_sayisi)
{

	system("cls");
	printf("\t\t\t\t\tURUN EKLEME\n\n");

	FILE* dosyadegisim, *dosya_log, *dosya;
	dosya = fopen("products.txt", "a");
	dosyadegisim = fopen("stok_degisim.txt", "a");
	dosya_log = fopen("log.txt", "a");

	if (dosya == NULL || dosya_log == NULL || dosyadegisim == NULL) {
		printf("Dosya acilirken hata olustu...\n");
		return;
	}
	else
	{
		mallar[*mal_sayisi].malinAdi = (char*)malloc(50 * sizeof(char));
		if (mallar[*mal_sayisi].malinAdi == NULL) {
			printf("Bellek tahsis edilemedi.\n");
			return;
		}
		mallar[*mal_sayisi].kategori = (char*)malloc(50 * sizeof(char));
		if (mallar[*mal_sayisi].kategori == NULL) {
			printf("Bellek tahsis edilemedi.\n");
			return;
		}
		mallar[*mal_sayisi].alt_kategori = (char*)malloc(50 * sizeof(char));
		if (mallar[*mal_sayisi].alt_kategori == NULL) {
			printf("Bellek tahsis edilemedi.\n");
			return;
		}
		mallar[*mal_sayisi].konumu = (char*)malloc(50 * sizeof(char));
		if (mallar[*mal_sayisi].konumu == NULL) {
			printf("Bellek tahsis edilemedi.\n");
			return;
		}

		printf("Eklemek istediginiz urunun ID'sini giriniz: ");
		scanf("%d", &mallar[*mal_sayisi].ID);

		printf("Eklemek istediginiz urunun ismini giriniz: ");
		scanf(" %[^\n]", mallar[*mal_sayisi].malinAdi);

		printf("Eklemek istediginiz urunun kategorisini giriniz: ");
		scanf(" %[^\n]", mallar[*mal_sayisi].kategori);

		printf("Eklemek istediginiz urunun alt kategorisini giriniz: ");
		scanf(" %[^\n]", mallar[*mal_sayisi].alt_kategori);

		printf("Eklemek istediginiz urunun fiyatini giriniz: ");
		scanf("%f", &mallar[*mal_sayisi].fiyati);

		printf("Eklemek istediginiz urunun adetini giriniz: ");
		scanf("%d", &mallar[*mal_sayisi].adet);

		printf("Eklemek istediginiz urunun eklenme magzadaki yerini giriniz: ");
		scanf(" %[^\n]", mallar[*mal_sayisi].konumu);

		

		printf("\nEklenen urunun ID'si -> %d\n\nEklenen urunun ismi -> %s\n\nEklenen urunun kategorisi -> %s\n\nEklenen urunun alt kategorisi -> %s\n\nEklenen urunun fiyati -> %.2f\n\nEklenen urunun adeti -> %d\n\nEklenen urunun magzadaki yeri -> %s\n\n",
			mallar[*mal_sayisi].ID,
			mallar[*mal_sayisi].malinAdi,
			mallar[*mal_sayisi].kategori,
			mallar[*mal_sayisi].alt_kategori,
			mallar[*mal_sayisi].fiyati,
			mallar[*mal_sayisi].adet,
			mallar[*mal_sayisi].konumu);

		

		fprintf(dosya, "\n%d,%s,%s,%s,%.2f,%d,%s",
			mallar[*mal_sayisi].ID,
			mallar[*mal_sayisi].malinAdi,
			mallar[*mal_sayisi].kategori,
			mallar[*mal_sayisi].alt_kategori,
			mallar[*mal_sayisi].fiyati,
			mallar[*mal_sayisi].adet,
			mallar[*mal_sayisi].konumu);




		fprintf(dosyadegisim, "%s, %d,%s,%s,%s,%.2f,%d,%s\n",
			"URUN EKLEME ->",
			mallar[*mal_sayisi].ID,
			mallar[*mal_sayisi].malinAdi,
			mallar[*mal_sayisi].kategori,
			mallar[*mal_sayisi].alt_kategori,
			mallar[*mal_sayisi].fiyati,
			mallar[*mal_sayisi].adet,
			mallar[*mal_sayisi].konumu);

		fprintf(dosya_log, "%s, %d,%s,%s,%s,%.2f,%d,%s\n",
			"URUN EKLEME ->",
			mallar[*mal_sayisi].ID,
			mallar[*mal_sayisi].malinAdi,
			mallar[*mal_sayisi].kategori,
			mallar[*mal_sayisi].alt_kategori,
			mallar[*mal_sayisi].fiyati,
			mallar[*mal_sayisi].adet,
			mallar[*mal_sayisi].konumu);

		fclose(dosya);
		fclose(dosyadegisim);
		fclose(dosya_log);

		printf("Urun basariyla eklendi...\n\n\n");

		printf("ANA EKRANA DONMEK ICIN HERHANGI BIR TUSA BASIN");

		secim = _getch();


		(*mal_sayisi)++;	
	}

	
}
void urun_arama(URUNLER mallar[], int mal_sayisi)
{
	int secim_ID, kontrol = 0;
	char secim, secim_isim[100];

	FILE* dosya_log;
	dosya_log = fopen("log.txt", "a");

	system("cls");
	printf("\t\t\t\t\tURUN ARAMA\n\n");
	printf("ID ile arama yapmak icin 1'e basin.\nIsim ile arama yapmak icin 2'e basin.\n ");
	secim = _getch();
	system("cls");

	if (secim == '1')
	{
		printf("Aradiginiz urunun ID'sini giriniz: ");
		scanf("%d", &secim_ID);

		fprintf(dosya_log, "%s %d \n",
			"Aranan urunun ID'si ->", secim_ID);
		fclose(dosya_log);
		system("cls");

		printf("Aradiginiz urunler bunlar.\n\n");

		for (int i = 0; i < mal_sayisi; i++)
		{
			if (mallar[i].ID == secim_ID)
			{
				printf("%-4d %-20s %-20s %-10d %-10.2f %-15s\n",
					mallar[i].ID,
					mallar[i].malinAdi,
					mallar[i].kategori,
					mallar[i].adet,
					mallar[i].fiyati,
					mallar[i].konumu);
				kontrol++;
			}
		}
		if (kontrol == 0)
		{
			system("cls");
			printf("Aradiginiz urun yoktur.\n\n\nANA EKRANA DONMEK ICIN HERHANGI BIR TUSA BASIN\n\n\n");
		}
		else
		{
			printf("\n\nAradiginiz urunlerin hepsi.\n\n\nANA EKRANA DONMEK ICIN HERHANGI BIR TUSA BASIN\n\n\n");
		}
		secim = _getch();
		
	}
	else if (secim == '2')
	{
		printf("Aradiginiz urunun ismini giriniz: ");
		scanf("%s", secim_isim);
		fprintf(dosya_log, "%s %s \n",
			"Aranan urunun ismi ->", secim_isim);
		fclose(dosya_log);
		system("cls");


		printf("Aradiginiz urunler bunlar.\n\n");

		for (int i = 0; i < mal_sayisi; i++)
		{
			if (strcmp(mallar[i].malinAdi, secim_isim) == 0)
			{
				printf("%-4d %-20s %-20s %-10d %-10.2f %-15s\n",
					mallar[i].ID,
					mallar[i].malinAdi,
					mallar[i].kategori,
					mallar[i].adet,
					mallar[i].fiyati,
					mallar[i].konumu);
				kontrol++;
			}

		}

		if (kontrol == 0)
		{
			system("cls");
			printf("Aradiginiz urun yoktur.\n\n\nANA EKRANA DONMEK ICIN HERHANGI BIR TUSA BASIN\n\n\n");
		}
		else
		{
			printf("\n\nAradiginiz urunlerin hepsi.\n\n\nANA EKRANA DONMEK ICIN HERHANGI BIR TUSA BASIN\n\n\n");
		}
		secim = _getch();

	}


}
void urun_guncelleme(URUNLER mallar[], int mal_sayisi)
{
	FILE* dosya_log, * dosyadegisim, *dosya;
	dosyadegisim = fopen("stok_degisim.txt", "a");
	dosya_log = fopen("log.txt", "a");
	dosya = fopen("products.txt", "w");
	int secim_urun, stok, kontrol = 0;
	system("cls");
	printf("\t\t\t\t\tURUN GUNCELLE\n\n");

	printf("\n\nGuncellemek istediginiz urunun ID'sini giriniz: ");

	scanf("%d", &secim_urun);
	

	printf("\n\nStok miktarini giriniz:");
	scanf("%d", &stok);


	for (int i = 0; i < mal_sayisi; i++)
	{
		if (mallar[i].ID == secim_urun)
		{
			secim_urun = i;
			kontrol++;
		}
	}

	if (kontrol == 0)
	{

		for (int i = 0; i < mal_sayisi; i++)
		{

			fprintf(dosya, "\n%d,%s,%s,%s,%.2f,%d,%s",
				mallar[i].ID,
				mallar[i].malinAdi,
				mallar[i].kategori,
				mallar[i].alt_kategori,
				mallar[i].fiyati,
				mallar[i].adet,
				mallar[i].konumu);
		}

		fclose(dosya);
		fclose(dosyadegisim);
		fclose(dosya_log);

		system("cls");
		printf("Boyle bir urun yoktur.\n\n\nANA EKRANA DONMEK ICIN HERHANGI BIR TUSA BASIN\n\n\n");


		secim = _getch();
	}
	else
	{
		printf("\n\n%d. %s eski stogu %d.\n\n", mallar[secim_urun].ID, mallar[secim_urun].malinAdi, mallar[secim_urun].adet);
		mallar[secim_urun].adet = stok;

		printf("%d. %s yeni stogu %d.\n\n", mallar[secim_urun].ID, mallar[secim_urun].malinAdi, mallar[secim_urun].adet);

		fprintf(dosya_log, "%s %d %s\n",
			"Stok degisti -> ", mallar[secim_urun].ID, mallar[secim_urun].malinAdi);

		fprintf(dosyadegisim, "%s %d %s\n",
			"Stok degisti -> ", mallar[secim_urun].ID, mallar[secim_urun].malinAdi);


		fprintf(dosya, "%s", "UrunID,UrunIsmi,Kategori,AltKategori,Fiyati,StokMiktari,MagazadaYeri");

		for (int i = 0; i < mal_sayisi; i++)
		{

			fprintf(dosya, "\n%d,%s,%s,%s,%.2f,%d,%s",
				mallar[i].ID,
				mallar[i].malinAdi,
				mallar[i].kategori,
				mallar[i].alt_kategori,
				mallar[i].fiyati,
				mallar[i].adet,
				mallar[i].konumu);
		}
		fclose(dosya);
		fclose(dosyadegisim);
		fclose(dosya_log);
	
		printf("\n\n\n\n\nANA EKRANA DONMEK ICIN HERHANGI BIR TUSA BASIN\n\n\n");
		
		secim = _getch();

		
	}


	


}
void urun_kategori(URUNLER mallar[], int mal_sayisi)
{

	int kontrol = 0;
	char secim_kategori[100], secim;

	FILE* dosya_log;
	dosya_log = fopen("log.txt", "a");

	system("cls");
	printf("\t\t\t\t\tURUN KATEGORI ETME\n\n");
	printf("Listelemek istedigimiz kategoriyi giriniz:");
	scanf("%s", secim_kategori);

	fprintf(dosya_log, "%s %s \n",
		"Kategori edildi ->", secim_kategori);

	fclose(dosya_log);

	for (int i = 0; i < mal_sayisi; i++)
	{
		if (strcmp(mallar[i].kategori, secim_kategori) == 0)
		{
			printf("%-4d %-20s %-20s %-10d %-10.2f %-15s\n",
				mallar[i].ID,
				mallar[i].malinAdi,
				mallar[i].kategori,
				mallar[i].adet,
				mallar[i].fiyati,
				mallar[i].konumu);
			kontrol++;
		}

	}



	if (kontrol == 0)
	{
		system("cls");
		printf("Aradiginiz urun yoktur.");
	}

	printf("\n\n\n\n\nANA EKRANA DONMEK ICIN HERHANGI BIR TUSA BASIN\n\n\n");
	

	secim = _getch();


}
