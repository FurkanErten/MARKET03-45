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
	int adet;
	float fiyati;
	char* eklenme_tarihi;
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

		printf("\n\n\tLutfen yapmak istediginiz islemi seciniz.\n\n\t1. Yeni urun ekleme.\n\n\t2. Urun arama.\n\n\t3. Stok guncelleme.\n\n\t4. Urunleri kategori et.\n\n\t5. Stoklari guncelle.\n\n\t6. Kapat.");


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
			mallar[*mal_sayisi].eklenme_tarihi = (char*)malloc(50 * sizeof(char));

			sscanf(buffer, "%d,%49[^,],%49[^,],%d,%f,%49[^\n]",
				&mallar[*mal_sayisi].ID,
				mallar[*mal_sayisi].malinAdi,
				mallar[*mal_sayisi].kategori,
				&mallar[*mal_sayisi].adet,
				&mallar[*mal_sayisi].fiyati,
				mallar[*mal_sayisi].eklenme_tarihi);

			(*mal_sayisi)++;
		}




	}



	fclose(dosya);

}


void ekrana_Yaz(URUNLER mallar[], int mal_sayisi) 
{
	// urunlerin ekrana yazdirma.

	system("cls");

	printf("ID   %-20s %-20s %-10s %-10s %-15s\n", "Urun Ismi", "Kategori", "Adet", "Fiyati", "Eklenme Tarihi");
	printf("-----------------------------------------------------------------------------\n");
	for (int i = 0; i < mal_sayisi; i++) {
		printf("%-4d %-20s %-20s %-10d %-10.2f %-15s\n",
			mallar[i].ID,
			mallar[i].malinAdi,
			mallar[i].kategori,
			mallar[i].adet,
			mallar[i].fiyati,
			mallar[i].eklenme_tarihi);
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

	if (dosyadegisim == NULL)
	{
		printf("Dosya acilirken hata olustu...");
	}
	else
	{
		mallar[*mal_sayisi].malinAdi = (char*)malloc(50 * sizeof(char));
		mallar[*mal_sayisi].kategori = (char*)malloc(50 * sizeof(char));
		mallar[*mal_sayisi].eklenme_tarihi = (char*)malloc(50 * sizeof(char));


		printf("Eklemek istediginiz urunun ID'sini giriniz: ");
		scanf("%d", &mallar[*mal_sayisi].ID);

		printf("Eklemek istediginiz urunun ismini giriniz: ");
		scanf(" %[^\n]", mallar[*mal_sayisi].malinAdi);

		printf("Eklemek istediginiz urunun kategorisini giriniz: ");
		scanf(" %[^\n]", mallar[*mal_sayisi].kategori);

		printf("Eklemek istediginiz urunun adetini giriniz: ");
		scanf("%d", &mallar[*mal_sayisi].adet);

		printf("Eklemek istediginiz urunun fiyatini giriniz: ");
		scanf("%f", &mallar[*mal_sayisi].fiyati);

		printf("Eklemek istediginiz urunun eklenme tarihini giriniz: ");
		scanf(" %[^\n]", mallar[*mal_sayisi].eklenme_tarihi);

		printf("\nEklenen urunun ID'si -> %d\nEklenen urunun ismi -> %s\nEklenen urunun kategorisi -> %s\nEklenen urunun adeti -> %d\nEklenen urunun fiyati -> %.2f\nEklenen urunun eklenme tarihi -> %s\n\n",
			mallar[*mal_sayisi].ID,
			mallar[*mal_sayisi].malinAdi,
			mallar[*mal_sayisi].kategori,
			mallar[*mal_sayisi].adet,
			mallar[*mal_sayisi].fiyati,
			mallar[*mal_sayisi].eklenme_tarihi);

		fprintf(dosya, "\n%d,%s,%s,%d,%.2f,%s",
			mallar[*mal_sayisi].ID,
			mallar[*mal_sayisi].malinAdi,
			mallar[*mal_sayisi].kategori,
			mallar[*mal_sayisi].adet,
			mallar[*mal_sayisi].fiyati,
			mallar[*mal_sayisi].eklenme_tarihi);



		fprintf(dosyadegisim, "%s %-4d %-20s %-20s %-10d %-10.2f %-15s\n",
			"URUN EKLEME ->",
			mallar[*mal_sayisi].ID,
			mallar[*mal_sayisi].malinAdi,
			mallar[*mal_sayisi].kategori,
			mallar[*mal_sayisi].adet,
			mallar[*mal_sayisi].fiyati,
			mallar[*mal_sayisi].eklenme_tarihi);

		fprintf(dosya_log, "%s %-4d %-20s %-20s %-10d %-10.2f %-15s\n",
			"URUN EKLEME ->",
			mallar[*mal_sayisi].ID,
			mallar[*mal_sayisi].malinAdi,
			mallar[*mal_sayisi].kategori,
			mallar[*mal_sayisi].adet,
			mallar[*mal_sayisi].fiyati,
			mallar[*mal_sayisi].eklenme_tarihi);

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
					mallar[i].eklenme_tarihi);
				kontrol++;
			}
		}
		if (kontrol == 0)
		{
			system("cls");
			printf("Aradiginiz urun yoktur.");
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
					mallar[i].eklenme_tarihi);
				kontrol++;
			}

		}

		if (kontrol == 0)
		{
			system("cls");
			printf("Aradiginiz urun yoktur.");
		}

		secim = _getch();


	}


}

void urun_guncelleme(URUNLER mallar[], int mal_sayisi)
{
	FILE* dosya_log, * dosyadegisim, *dosya;
	dosyadegisim = fopen("stok_degisim.txt", "a");
	dosya_log = fopen("log.txt", "a");
	dosya_log = fopen("log.txt", "a");
	dosya = fopen("products.txt", "w");
	int secim_urun, stok;
	system("cls");
	printf("\t\t\t\t\tURUN GUNCELLE\n\n");

	printf("Guncellemek istediginiz urunun ID'sini giriniz: ");

	scanf("%d", &secim_urun);
	

	printf("Stok miktarýný giriniz:");
	scanf("%d", &stok);

	printf("%d. %s eski stogu %d.\n\n", mallar[secim_urun-1].ID, mallar[secim_urun - 1].malinAdi, mallar[secim_urun - 1].adet);
	mallar[secim_urun-1].adet = stok;

	printf("%d. %s yeni stogu %d.\n\n", mallar[secim_urun-1].ID, mallar[secim_urun - 1].malinAdi, mallar[secim_urun - 1].adet);

	fprintf(dosya_log, "%s %d %s\n",
		"Stok degisti -> ", mallar[secim_urun - 1].ID, mallar[secim_urun - 1].malinAdi);

	fprintf(dosyadegisim, "%s %d %s\n",
		"Stok degisti -> ", mallar[secim_urun - 1].ID, mallar[secim_urun - 1].malinAdi);


	fprintf(dosya, "%s", "ID,Urun Ismi,Kategorisi,Adedi,Fiyati,Eklenme Tarihi");

	for (int i = 0; i < mal_sayisi; i++)
	{
		
		fprintf(dosya, "\n%d,%s,%s,%d,%.2f,%s",
			mallar[i].ID,
			mallar[i].malinAdi,
			mallar[i].kategori,
			mallar[i].adet,
			mallar[i].fiyati,
			mallar[i].eklenme_tarihi);
	}

	fclose(dosya);
	fclose(dosyadegisim);
	fclose(dosya_log);


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
				mallar[i].eklenme_tarihi);
			kontrol++;
		}

	}



	if (kontrol == 0)
	{
		system("cls");
		printf("Aradiginiz urun yoktur.");
	}

	secim = _getch();


}
